#include <dcpu.h>

interrupt_handler get_interrupt_handler(void) {
  interrupt_handler handler;
  asm volatile ("IAG %0" : "=r" (handler) : );
  return handler;
}

void set_interrupt_handler(interrupt_handler handler) {
  asm volatile ("IAS %0" : : "r" (handler));
}

void enable_interrupt_queueing(int queueing) {
  asm volatile ("IAQ %0" : : "r" (queueing));
}

void software_interrupt(unsigned msg) {
  asm volatile ("INT %0" : : "r" (msg));
}

unsigned get_number_of_devices(void) {
  unsigned n;
  asm volatile ("HWN %0" : "=r" (n) : );
  return n;
}

void get_device_information(unsigned device_number,
                            struct device_information *info) {
  register unsigned A asm("A");
  register unsigned B asm("B");
  register unsigned C asm("C");
  register unsigned X asm("X");
  register unsigned Y asm("Y");
  asm volatile (
      "HWQ %5"
      :
      "=r" (A),
      "=r" (B),
      "=r" (C),
      "=r" (X),
      "=r" (Y)
      :
      "r" (device_number));
  info->id_lo = A;
  info->id_hi = B;
  info->version = C;
  info->manufacturer_lo = X;
  info->manufacturer_hi = Y;
}

// divisor == 0 -> disable clock
void clock_enable_ticks(unsigned device_id, unsigned divisor) {
  register unsigned A asm("A") = 0;
  register unsigned B asm("B") = divisor;
  asm volatile ("HWI %0" : : "r" (device_id), "r" (A), "r" (B));
}

unsigned clock_get_ticks(unsigned device_id) {
  register unsigned A asm("A") = 1;
  register unsigned C asm("C");
  asm volatile ("HWI %1" : "=r" (C) : "r" (device_id), "r" (A));
  return C;
}

// msg == 0 -> disable interrupts
void clock_enable_interrupts(unsigned device_id, unsigned msg) {
  register unsigned A asm("A") = 1;
  register unsigned B asm("B") = msg;
  asm volatile ("HWI %0" : : "r" (device_id), "r" (A), "r" (B));
}

void keyboard_clear_buffer(unsigned device_id) {
  asm volatile("SET A, 0" : : : "A");
  asm volatile("HWI %0" : : "r" (device_id));
}

unsigned keyboard_get_next_key(unsigned device_id) {
  asm volatile("SET A, 1" : : : "A");
  register unsigned result asm("C");
  asm volatile("HWI %1" : "=r" (result) : "r" (device_id));
  return result;
}

int keyboard_is_key_pressed(unsigned device_id, unsigned key) {
  register unsigned A asm("A") = 2;
  register unsigned B asm("B") = key;
  register unsigned C asm("C");
  asm volatile ("HWI %1" : "=r" (C) :
      "r" (device_id), "r" (A), "r" (B));
  return C;
}

// msg == 0 -> disable interrupts
void keyboard_enable_interrupts(unsigned device_id, unsigned msg) {
  register unsigned A asm("A") = 3;
  register unsigned B asm("B") = msg;
  asm volatile ("HWI %0" : : "r" (device_id), "r" (A), "r" (B));
}

// memory == NULL -> turn screen off
void lem_memmap_screen(unsigned device_id, unsigned *memory) {
  register unsigned A asm("A") = 0;
  register unsigned *B asm("B") = memory;
  asm volatile ("HWI %0" : : "r" (device_id), "r" (B), "r" (A));
}

// font == NULL -> use default font
void lem_memmap_font(unsigned device_id, struct font_char *font) {
  register unsigned A asm("A") = 1;
  register struct font_char *B asm("B") = font;
  asm volatile ("HWI %0" : : "r" (device_id), "r" (B), "r" (A));
}

// palette == NULL -> use default palette
void lem_memmap_palette(unsigned device_id, unsigned *palette) {
  register unsigned A asm("A") = 2;
  register unsigned *B asm("B") = palette;
  asm volatile ("HWI %0" : : "r" (device_id), "r" (B), "r" (A));
}

void lem_set_border_color(unsigned device_id, unsigned color_index) {
  register unsigned A asm("A") = 3;
  register unsigned B asm("B") = color_index;
  asm volatile ("HWI %0" : : "r" (device_id), "r" (B), "r" (A));
}

void lem_memdump_font(unsigned device_id, struct font_char *font) {
  register unsigned A asm("A") = 4;
  register struct font_char *B asm("B") = font;
  asm volatile ("HWI %0" : : "r" (device_id), "r" (B), "r" (A));
}

void lem_memdump_palette(unsigned device_id, unsigned *palette) {
  register unsigned A asm("A") = 5;
  register unsigned *B asm("B") = palette;
  asm volatile ("HWI %0" : : "r" (device_id), "r" (B), "r" (A));
}
