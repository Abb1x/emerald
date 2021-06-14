/*
 * Copyright (c) 2021, Abb1x
 *
 * SPDX-License-Identifier: MIT
 */

#include <emerald/str/fmt.h>

#define make_integer(base, type)     \
    type i = va_arg(args, type);     \
    if (i < (type)ZERO)              \
    {                                \
        i = -i;                      \
        buffer[position] = '-';      \
        position++;                  \
    }                                \
    String s = str_convert(i, base); \
    str_concat(s, make_str(buffer)); \
    position += s.size;

void fmt_buffer(char *buffer, char *string, va_list args)
{
    Scanner scan = {.buffer = string, .size = cstrlen(string), .head = 0};

    unsigned int ZERO = 0;
    int position = 0;

    while (!scan_ended(&scan))
    {

        if (scan_current(&scan) == '{')
        {
            scan_forward(&scan);

            switch (scan_current(&scan))
            {
            case 's':
            {
                char *s = va_arg(args, char *);
                str_concat(make_str(s), make_str(buffer));
                position += cstrlen(s);
                break;
            }

            case 'd':
            {
                make_integer(10, int);
                break;
            }

            case 'c':
            {
                buffer[position] = scan_current(&scan);
                position++;
                break;
            }

            case 'x':
            {

                make_integer(16, unsigned int);
                break;
            }

            default:
                buffer[position] = '{';
                position++;
                break;
            }

            scan_forward(&scan);
        }

        else
        {
            buffer[position] = scan_current(&scan);
            position++;
        }

        scan_forward(&scan);
        scan_skip_c(&scan, '}');
    }
}
