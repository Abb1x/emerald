#ifndef __LIB__TERM_H__
#define __LIB__TERM_H__

#include <stddef.h>
#include <stdbool.h>

extern void (*raw_putchar)(char c);
extern void (*clear)(bool move);
extern void (*enable_cursor)(void);
extern void (*disable_cursor)(void);
extern void (*set_cursor_pos)(int x, int y);
extern void (*get_cursor_pos)(int *x, int *y);
extern void (*set_text_fg)(int fg);
extern void (*set_text_bg)(int bg);

void term_vbe(void);
void term_textmode(void);
void term_deinit(void);
void term_write(const char *buf, size_t count);

#endif
