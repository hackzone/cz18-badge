//
// Created by Tom on 07/06/2018.
//

#include "SoftSynth.h"

#define DEBUG

#define NORMAL_SAMPLE_WIDTH 16
#define MAX_FREQ 2000
//#define TIMER_CYCLES ((F_CPU / (MAX_FREQ * NORMAL_SAMPLE_WIDTH)) - 1)
#define TIMER_CYCLES 1600

/* Patch delay() to use custom softsynth_delay() instead. */
void (*orig_delay)(unsigned long) = delay;

#define delay() softsynth_delay()

/***** Source of voice intensities:
 * "Volume2" library
 * @author         Connor Nishijima  */
Voice square_voice = {16, {255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0}};
Voice saw_voice = {16, {0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240}};
Voice triangle_voice = {16, {0, 32, 64, 96, 128, 160, 192, 224, 255, 224, 192, 160, 128, 96, 64, 32}};
Voice pwm12_voice = {16, {255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
Voice pwm25_voice = {16, {255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

ChannelList *channels;
volatile ChannelList *cur_chan;
volatile SoftSynth *cur_synth;
volatile uint8_t cur_duty;
volatile uint16_t cycle_diff;
volatile int16_t intensity_diff;

void start_timer() {
    cli();

#ifdef DEBUG
    Serial.println("timer_start");
#endif

    /* Set timer0 and timer2 prescalers to 1 */
    sbi(TCCR0A, CS10);
    cbi(TCCR0A, CS11);
    cbi(TCCR0A, CS12);

    /* Clear current timer1 configuration */
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    /* Enable CTC mode */
    sbi(TCCR1B, WGM12);

    /* Set prescaler to 1 */
    sbi(TCCR1B, CS10);

    /* Configure amount of cycles in between interrupts */
    OCR1A = TIMER_CYCLES;

    /* Enable timer interrupt */
    sbi(TIMSK1, OCIE1A);

    sei();
}

void stop_timer() {
    cli();

#ifdef DEBUG
    Serial.println("timer_stop");
#endif

    /* Set timer0 and timer2 prescalers to 64 (default) */
    sbi(TCCR0A, CS10);
    sbi(TCCR0A, CS11);
    cbi(TCCR0A, CS12);

    /* Disable timer interrupt */
    cbi(TIMSK1, OCIE1A);

    sei();
}

void insert_channel(SoftSynth *chan) {
#ifdef DEBUG
    Serial.println("chan_insert");
#endif
    if (!channels) {
#ifdef DEBUG
        Serial.println("chan_insert_new");
#endif
        /* Create first channel list entry */
        channels = malloc(sizeof(ChannelList));
        channels->prev = NULL;
        channels->next = NULL;
        channels->synth = chan;
    } else {
#ifdef DEBUG
        Serial.println("chan_insert_existing");
#endif
        /* Add new channel to channel list */
        ChannelList *newChan = malloc(sizeof(ChannelList));
        newChan->synth = chan;
        newChan->next = channels;
        channels->prev = newChan;
        channels = newChan;
    }

    if (channels->synth == chan) {
        start_timer();
    }
}

void remove_channel(SoftSynth *chan) {
#ifdef DEBUG
    Serial.println("chan_remove");
#endif
    if (channels) {
        ChannelList *cur = channels;

        /* Find entry */
        while (cur->synth != chan) {
            if (!cur->next) {
                return;
            }
            cur = cur->next;
        }

        /* Remove entry */
        if (cur->prev) {
            cur->prev->next = cur->next ? cur->next : NULL;
        }
        if (cur->next) {
            cur->next->prev = cur->prev ? cur->prev : NULL;
        }
        if (channels == cur) {
            channels = cur->next ? cur->next : NULL;
        }
        free(cur);
    }

    if (!channels) {
        stop_timer();
    }
}

SoftSynth::SoftSynth(uint8_t gpio) {
#ifdef DEBUG
    Serial.println("synth_const");
#endif
    pin = gpio;
}

void SoftSynth::play(uint16_t frequency, Voice *voice, float volume) {
#ifdef DEBUG
    Serial.println("synth_play");
#endif
    this->frequency = frequency;
    this->voice = voice;
    this->voiceIndex = 0;
    this->volume = volume;
    this->wantedCycles = (F_CPU / (this->frequency * voice->length)) - 1;

#ifdef DEBUG
    Serial.print("wc ");
    Serial.print(this->wantedCycles, 10);
    Serial.println();
#endif

    if (!this->isActive) {
        this->isActive = true;
        insert_channel(this);
    }

    /* Set pin to current voice output */
    analogWrite(cur_synth->pin, cur_synth->voice->intensities[cur_synth->voiceIndex] * cur_synth->volume);
}

void SoftSynth::stop() {
#ifdef DEBUG
    Serial.println("synth_stop");
#endif
    this->isActive = false;
    remove_channel(this);
}

ISR(TIMER1_COMPA_vect) {
    short start = TCNT1;
    volatile uint8_t output = 0;
    
//    Serial.print("TCNT1: ");
//    Serial.println(start);

    cur_chan = channels;
    while (cur_chan) {
        cur_synth = cur_chan->synth;
        cur_synth->cyclesSinceLast += TIMER_CYCLES;

        if (cur_synth->cyclesSinceLast >= cur_synth->wantedCycles) {
            cur_synth->voiceIndex++;
            cur_synth->cyclesSinceLast -= cur_synth->wantedCycles;
            cur_synth->voiceIndex = cur_synth->nextVoiceIndex;
            if (cur_synth->voiceIndex + 1 >= cur_synth->voice->length) {
                cur_synth->nextVoiceIndex = 0;
            } else {
                cur_synth->nextVoiceIndex = cur_synth->voiceIndex + 1;
            }
        }

        cycle_diff = cur_synth->wantedCycles - cur_synth->cyclesSinceLast;

        intensity_diff = cur_synth->voice->intensities[cur_synth->nextVoiceIndex] -
                         cur_synth->voice->intensities[cur_synth->voiceIndex];
//        analogWrite(cur_synth->pin, (char)((cur_synth->voice->intensities[cur_synth->voiceIndex] +
//                                    (char)(intensity_diff * (cur_synth->cyclesSinceLast / cur_synth->wantedCycles)))));
//          output += (uint8_t)((cur_synth->voice->intensities[cur_synth->voiceIndex] +
//                                    (uint8_t)(intensity_diff * (cur_synth->cyclesSinceLast / cur_synth->wantedCycles))));
        sbi(TCCR0A, COM0A1);
        OCR0A = (uint8_t)((cur_synth->voice->intensities[cur_synth->voiceIndex] +
                                    (uint8_t)(intensity_diff * (cur_synth->cyclesSinceLast / cur_synth->wantedCycles)))); // set pwm duty
        OCR0B = OCR0A;
//          sbi(TCCR0A, COM0A1);
//          OCR0A = 128;
//          output = (uint8_t)((cur_synth->voice->intensities[cur_synth->voiceIndex] +
//                                    (uint8_t)(intensity_diff * (cur_synth->cyclesSinceLast / cur_synth->wantedCycles))));

        cur_chan = cur_chan->next;
    }
//    analogWrite(5, output * 0.5);
    start -= TCNT1;
if(random(0, 100) > 95){
    Serial.print("Cycles: ");
    Serial.println(start);
}
    TCNT1 = 0;
}
