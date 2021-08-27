#include <emerald/mem.h>
#include <emerald/str/str.h>
#include <emerald/log.h>

size_t cstrlen(char *str)
{
    size_t i;

    for (i = 0; str[i] != '\0'; i++)
        ;
    return i;
}

String make_str_cstr(char const* str)
{
  return (String){(char*)str, cstrlen((char*)str)};
}

String make_str_i(int i)
{
    return str_convert(10, i);
}

String make_str_x(unsigned int i)
{
    return str_convert(16, i);
}

String make_str_str(String str)
{
    return str;
}

String make_str_char(char c)
{
    return make_str_cstr(&c);
}

String str_convert(uint16_t base, int64_t num)
{
    static char ibuf[128] = {0};

    itocstr(num, ibuf, base);

    String s = make_str_cstr(ibuf);

    return s;
}

String str_concat(String src, String dest)
{
    size_t i;

    for (i = 0; i < src.size && src.buffer[i] != '\0'; i++)
    {
        dest.buffer[dest.size + i] = src.buffer[i];
    }

    dest.buffer[dest.size + i] = '\0';

    return dest;
}

bool str_ncmp(String str, String str2, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (str.buffer[i] != str2.buffer[i])
        {
            if (str.buffer[1] < str2.buffer[1])
            {
                return false;
            }
            else
            {
                return false;
            }
        }

        if (str.buffer[i] == '\0')
        {
            return true;
        }
    }

    return true;
}

bool str_cmp(String str, String str2)
{
    return str_ncmp(str, str2, str.size);
}
/* These two functions were taken from https://github.com/not-microsowoft/experimental, licensed under GPL 3

Copyright (C) 2021 keyboard-slayer
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.

*/

void strrev(char *s)
{
    char tmp;
    size_t end = cstrlen(s) - 1;
    size_t start = 0;

    while (start < end)
    {
        tmp = s[start];
        s[start++] = s[end];
        s[end--] = tmp;
    }
}

char *itocstr(int64_t value, char *str, uint16_t base)
{
    size_t index = 0;
    int8_t digit;

    if (value < 0 && base != 10)
    {
        int64_t left;
        int64_t right;
        size_t i;

        char left_str[32];
        char right_str[32];

        right = value & 0xffffffff;
        left = (value & 0xffffffff00000000) >> 32;

        itocstr(left, left_str, base);
        itocstr(right, right_str, base);

        for (i = 0; i < cstrlen(left_str); i++)
        {
            str[i] = left_str[i];
        }

        for (i = 0; i < cstrlen(right_str); i++)
        {
            str[i + cstrlen(left_str)] = right_str[i];
        }

        return str;
    }

    else if (value < 0)
    {
        str[index++] = '-';
        value *= 1;
    }

    do
    {
        digit = value % base;

        if (digit < 0xa)
        {
            str[index++] = digit + '0';
        }
        else
        {
            str[index++] = (digit - 0xa) + 'a';
        }

        value /= base;
    } while (value);

    str[index] = 0;

    strrev(str);

    return str;
}

int cstrtoi(char *str)
{
    int res = 0;

    int i;
    for (i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    return res;
}