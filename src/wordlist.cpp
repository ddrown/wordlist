#include <Arduino.h>
#include "wordlist.h"

extern const uint8_t words[];

static const char char_lookup[] = {
  ' ', // 0: END_OF_WORD
  '\'', 'a', 'b', 'c', 'd', // 5
  'e', 'f', 'g', 'h', 'i',  // 10
  'j', 'k', 'l', 'm', 'n',  // 15
  'o', 'p', 'q', 'r', 's',  // 20
  't', 'u', 'v', 'w', 'x',  // 25
  'y', 'z', '-', ' ', ' ',  // 30
  ' ' // 31: END_OF_RECORDS
};

#define END_OF_WORD 0
#define END_OF_RECORDS 31

wordlist::wordlist() {
  last[0] = '\0';
  s = words;
  next_8_bytes();
}

void wordlist::next_8_bytes() {
  bytes[0] = (s[0] & 0b11111000) >> 3;
  bytes[1] = (s[0] & 0b00000111) << 2 | (s[1] & 0b11000000) >> 6;
  bytes[2] = (s[1] & 0b00111110) >> 1;
  bytes[3] = (s[1] & 0b00000001) << 4 | (s[2] & 0b11110000) >> 4;
  bytes[4] = (s[2] & 0b00001111) << 1 | (s[3] & 0b10000000) >> 7;
  bytes[5] = (s[3] & 0b01111100) >> 2;
  bytes[6] = (s[3] & 0b00000011) << 3 | (s[4] & 0b11100000) >> 5;
  bytes[7] = (s[4] & 0b00011111);
  byte_i = 0;
}

void wordlist::start_walk() {
  last[0] = '\0';
  s = words;
  next_8_bytes();
}

bool wordlist::at_eof() {
  return bytes[byte_i] == END_OF_RECORDS;
}

bool wordlist::next_data() {
  if(at_eof()) {
    return false;
  }
  byte_i++;
  if(byte_i == 8) {
    s = s + 5;
    next_8_bytes();
  }
  return !at_eof();
}

bool wordlist::has_char() {
  return bytes[byte_i] != END_OF_RECORDS && bytes[byte_i] != END_OF_WORD;
}

uint8_t wordlist::this_byte() {
  return bytes[byte_i];
}

const char *wordlist::next_word() {
  if(at_eof()) {
    return NULL;
  }
  uint8_t prefix = this_byte();
  if(prefix > MAX_WORD_LEN) { // error in data
    return NULL;
  }
  last[prefix] = '\0';
  uint32_t len = strlen(last);
  while(next_data() && has_char() && len < MAX_WORD_LEN-1) {
    char suffix = char_lookup[this_byte()];
    last[len] = suffix;
    len++;
  }
  last[len] = '\0';
  next_data(); // move pointer past END_OF_WORD
  return last;
}
