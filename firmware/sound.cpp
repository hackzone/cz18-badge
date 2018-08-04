//
// Created by Tom on 25/07/2018.
//

#include <avr/pgmspace.h>
#include "sound.h"
#include "leds.h" // for a call to update led-status

// A fun sketch to demonstrate the use of the Tone library.

// To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
// simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
// Don't forget to connect the other side of the speaker to ground!

// You can get more RTTTL (RingTone Text Transfer Language) songs from
// http://code.google.com/p/rogue-code/wiki/ToneLibraryDocumentation

#define OCTAVE_OFFSET 0
#define isdigit(n) (n >= '0' && n <= '9')

int notes[] = { 0,
                NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
                NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
                NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
                NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
              };

const char PROGMEM takeonme[] = {"TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5"};
const char PROGMEM cenfox[] = {"20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b"};
const char PROGMEM starwars[] = {"StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6"};
const char PROGMEM song[] = {"MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d"};



void sound_init()
{
  pinMode(6, INPUT); // Set high impedance
  pinMode(9, INPUT); // Set high impedance
}


void playz(uint8_t pin, uint16_t frequency) {
  // What does this do?
  if (frequency == 0) {
    return analogWrite(pin, 0);

  }

  uint8_t prescalarbits = 0;
  
  uint16_t top = F_CPU / frequency / 2 - 1;
  // Example: 10mhz / 2000hz / 2 -1 =  2500 -1 = 2499 ticks per toggle
  
  

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  TCCR1A = 0;           // undo the configuration done by...
  TCCR1B = 0;           // ...the Arduino core library
  TCNT1  = 0;           // reset timer
  TCCR1A = _BV(COM1A0);  // Toggle pin on interrupt
  TCCR1B = _BV(WGM12)  // Select Mode 4 (CTC)
           | _BV(CS10);   // prescaler = 1 = no prescaler
    
  OCR1A = top;
  OCR1B = top;

  DEBUG_PRINT("Setting ");
  DEBUG_PRINT(pin);
  DEBUG_PRINT(" to ");
  DEBUG_PRINT(top);
  DEBUG_PRINT(" (");
  DEBUG_PRINT(frequency);
  DEBUG_PRINTLN(")");
}

void play_rtttl(char *p)
{
  // Absolutely no error checking in here
  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while (pgm_read_byte(p) != ':') {
    p++;    // ignore name
  }
  p++;                     // skip ':'

  // get default duration
  if (pgm_read_byte(p) == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while (isdigit(pgm_read_byte(p)))
    {
      num = (num * 10) + (pgm_read_byte(p++) - '0');
    }
    if (num > 0) default_dur = num;
    p++;                   // skip comma
  }

  DEBUG_PRINT("ddur: "); DEBUG_PRINTLN(default_dur, 10);

  // get default octave
  if (pgm_read_byte(p) == 'o')
  {
    p++; p++;              // skip "o="
    num = pgm_read_byte(p++) - '0';
    if (num >= 3 && num <= 7) default_oct = num;
    p++;                   // skip comma
  }

  DEBUG_PRINT("doct: "); DEBUG_PRINTLN(default_oct, 10);

  // get BPM
  if (pgm_read_byte(p) == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while (isdigit(pgm_read_byte(p)))
    {
      num = (num * 10) + (pgm_read_byte(p++) - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

  DEBUG_PRINT("bpm: "); DEBUG_PRINTLN(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  DEBUG_PRINT("wn: "); DEBUG_PRINTLN(wholenote, 10);


  // now begin note loop
  while (pgm_read_byte(p))
  {
    // first, get note duration, if available
    num = 0;
    while (isdigit(pgm_read_byte(p)))
    {
      num = (num * 10) + (pgm_read_byte(p++) - '0');
    }

    if (num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch (pgm_read_byte(p))
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if (pgm_read_byte(p) == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if (pgm_read_byte(p) == '.')
    {
      duration += duration / 2;
      p++;
    }

    // now, get scale
    if (isdigit(pgm_read_byte(p)))
    {
      // example c6
      scale = pgm_read_byte(p) - '0';

      //scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if (pgm_read_byte(p) == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if (note)
    {
      DEBUG_PRINT("Playing: ");
      DEBUG_PRINT(scale, 10); DEBUG_PRINT(' ');
      DEBUG_PRINT(note, 10); DEBUG_PRINT(" (");
      DEBUG_PRINT(notes[(scale - 4) * 12 + note], 10);
      DEBUG_PRINT(") ");
      DEBUG_PRINTLN(duration, 10);
      // Set leds:
      do_disco(note);
      // Play note
      playz(10, notes[(scale - 4) * 12 + note]);
      //          tone2.play(notes[(scale - 4) * 12 - 5 + note]);
      delay(duration);
      // Switch off leds:
      do_disco(0);
      //  buzz(10,notes[(scale - 4) * 12 + note],duration);
      playz(10, 0);
    }
    else
    {
      DEBUG_PRINT("Pausing: ");
      //buzz(10,0,duration);
      TCCR1A = 0;
      DEBUG_PRINTLN(duration, 10);
      delay(duration);

    }
  }
  delay(500); // Make tone2 last a bit longer than the song itself
}

bool sound_learn(uint8_t slot, bool reinit) {
  return true;
}

void sound_play(uint8_t slot) {
  switch (slot)
  {
    case 0: play_rtttl(cenfox); break;
    case 1: play_rtttl(takeonme); break;
    case 2: play_rtttl(starwars); break;
    default: play_rtttl(song);
  }
  // stop playback
  TCCR1A = 0;
}
