#ifndef __DRIVERS__VBE_H__
#define __DRIVERS__VBE_H__

#include <stdint.h>
#include <stdbool.h>

int init_vbe(uint32_t **framebuffer, uint16_t *pitch, uint16_t *target_width, uint16_t *target_height, uint16_t *target_bpp);

void vbe_tty_init(int *rows, int *cols);

void vbe_putchar(char c);
void vbe_clear(bool move);
void vbe_enable_cursor(void);
void vbe_disable_cursor(void);
void vbe_set_cursor_pos(int x, int y);
void vbe_get_cursor_pos(int *x, int *y);
void vbe_set_text_fg(int fg);
void vbe_set_text_bg(int bg);

#endif
