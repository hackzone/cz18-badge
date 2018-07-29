//
// Created by Tom on 29/07/2018.
//

#include "cybers.h"

void cybest(const char *text) {
    Serial.println(text);
}

void cybercyber(void (*cybars)(const char *)) {
    char* nothingtoseehere = malloc(17);
    (*cybars)("");
    nothingtoseehere[1] = 0x54;
    nothingtoseehere[11] = 'a';
    nothingtoseehere[13] = '7';
    nothingtoseehere[5] = 52;
    nothingtoseehere[12] = '8';
    (*cybars)("cyber cyber");
    nothingtoseehere[0] = 0x43;
    nothingtoseehere[4] = '8';
    nothingtoseehere[7] = '2';
    nothingtoseehere[15] = 125;
    nothingtoseehere[8] = '4';
    nothingtoseehere[14] = '5';
    nothingtoseehere[9] = 'c';
    nothingtoseehere[16] = '\0';
    nothingtoseehere[3] = 0x7B;
    nothingtoseehere[6] = '6';
    nothingtoseehere[2] = 'F';
    nothingtoseehere[10] = 'a';
    (*cybars)(nothingtoseehere);
    free(nothingtoseehere);
}

volatile const unsigned char* cybara = "RCe3A8YLsbaYyq5U";
volatile const unsigned char* cybarb = "qfJeVwzuiRDzpqPu";
volatile const unsigned char* cybarc = "GbtyvuAsahiqbxVP";
volatile const unsigned char* cybard = "MFEqkyukapQziTW9";
volatile const unsigned char* cybare = "nx6Yx0jsLgc5huOi";
volatile const unsigned char* cybarf = "WT7MyuMizyLmKxb9";

volatile void cybercybercyber(char* stuff) {
    strncpy(stuff, "\x3E\x3F\x63\x31\x5F\x17\x1C\x06\x3B\x4C\x45\x15\x4C\x57\x64\x07", 16);
    stuff[17] = 0;
}

volatile void cybarsinthecybe(char* stuff) {
    size_t len = strnlen(stuff, 32);
    for(int i = 0; i < len; i ++) {
        stuff[i] ^= 0x13;
    }
}

volatile void cybesinthecybar(char* stuff) {
    size_t len = strnlen(stuff, 32);
    for(int i = 0; i < len; i ++) {
        stuff[i] ^= 0x37;
    }
}

volatile void cybesinthecyber(char* stuff1, char* stuff2) {
    size_t len = strnlen(stuff1, 32);
    for(int i = 0; i < len; i ++) {
        stuff1[i] ^= stuff2[i];
    }
}

void (*cybercybercyber_p)(char*) = cybercybercyber;
void (*cybarsinthecybe_p)(char*) = cybarsinthecybe;
void (*cybesinthecybar_p)(char*) = cybesinthecybar;
void (*cybesinthecyber_p)(char*) = cybesinthecyber;