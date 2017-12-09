#ifndef __wordlist__
#define __wordlist__

// change this if the compressed wordlist has longer words
#define MAX_WORD_LEN 15

class wordlist {
 public:
  wordlist();

  void start_walk();
  const char *next_word(); // pointer into object data, changes on call of next_word

 private:
  const uint8_t *s;
  char bytes[8]; // 8 bytes stored in 5 bytes
  uint8_t byte_i;
  char last[MAX_WORD_LEN+1];

  void next_8_bytes();
  bool at_eof();
  bool next_data();
  bool has_char();
  uint8_t this_byte();
};

#endif
