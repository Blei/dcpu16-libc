/*
 * DCPU specific routines.
 */

#pragma once

/***
 * Interrupt handling routines.
 ***/

typedef void __attribute__((dcpu16_intr)) (*interrupt_handler)(unsigned);

interrupt_handler get_interrupt_handler();
void set_interrupt_handler(interrupt_handler handler);
void enable_interrupt_queueing(int queueing);
void software_interrupt(unsigned msg);

/***
 * Device handling routines.
 ***/

struct device_information {
  unsigned id_lo, id_hi;
  unsigned version;
  unsigned manufacturer_lo, manufacturer_hi;
};

unsigned get_number_of_devices();
void get_device_information(unsigned device_id,
                            struct device_information *info);

/***
 * Hardware identifiers.
 ***/
#define CLOCK_ID_LO 0xb402
#define CLOCK_ID_HI 0x12d0

#define KEYBOARD_ID_LO 0x7406
#define KEYBOARD_ID_HI 0x30cf

#define LEM_ID_LO 0xf615
#define LEM_ID_HI 0x7349

#define LEM1802_VERSION 0x1802

/***
 * Vendor identifiers.
 ***/
#define NYA_ELEKTRISKA_LO 0x8b36
#define NYA_ELEKTRISKA_HI 0x1c6c

/***
 * Clock routines.
 ***/
void clock_enable_ticks(unsigned device_id, unsigned divisor);
unsigned clock_get_ticks(unsigned device_id);
void clock_enable_interrupts(unsigned device_id, unsigned msg);

/***
 * Keyboard routines.
 ***/

enum SpecialKeys {
  BACKSPACE = 0x10,
  RETURN = 0x11,
  INSERT = 0x12,
  DELETE = 0x13,
  // 0x20 - 0x7f: ASCII characters, use 'a' etc
  ARROW_UP = 0x80,
  ARROW_DOWN = 0x81,
  ARROW_LEFT = 0x82,
  ARROW_RIGHT = 0x83,
  SHIFT = 0x90,
  CONTROL = 0x91
};

void keyboard_clear_buffer(unsigned device_id);
unsigned keyboard_get_next_key(unsigned device_id);
int keyboard_is_key_pressed(unsigned device_id, unsigned key);
void keyboard_enable_interrupts(unsigned device_id, unsigned msg);

/***
 * Monitor routines.
 ***/

#define LEM_WIDTH 128
#define LEM_HEIGHT 96

#define LEM_GLYPH(character, blink, foreground, background) \
  ((character) & 0x7f) | \
    ((blink) ? 0x80 : 0) | \
    (((background) & 0xf) << 8) | \
    (((foreground) & 0xf) << 12)

#define LEM_COLOR(r, g, b) \
  ((b) & 0xf) | \
    (((g) & 0xf) << 4) | \
    (((r) & 0xf) << 8)

struct font_char {
  unsigned left, right;
};

void lem_memmap_screen(unsigned device_id, unsigned *memory);
void lem_memmap_font(unsigned device_id, struct font_char *font);
void lem_memmap_palette(unsigned device_id, unsigned *palette);
void lem_set_border_color(unsigned device_id, unsigned color_index);
void lem_memdump_font(unsigned device_id, struct font_char *font);
void lem_memdump_palette(unsigned device_id, unsigned *palette);

