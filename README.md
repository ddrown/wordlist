This library stores a compressed wordlist on your device.  It defaults to a list of 2,741 common english words.

Flash space needed for just the word list:
 * 1,194 words (words-1194.txt): 2,765 bytes
 * 2,741 words (words-2741.txt): 7,480 bytes (default)
 * 3,345 words (words-3345.txt): 9,370 bytes
 * 4,657 words (words-4657.txt): 13,060 bytes


To generate a new words.c file, use the compress script like this: `./compress <words-2741.txt >words.c`

When adding new words, pay close attention to the characters used.  Right now only a..z and ' are allowed.  Words are stored with incremental encoding, so the list should be sorted.  Using a fixed character list of 32 entries means eight input bytes result in five output bytes.

Right now the `MAX_WORD_LEN` is 15.  Change it if you need longer words.

Example code is for a SSD1306 128x64 display on the default i2c bus, address 0x3C
