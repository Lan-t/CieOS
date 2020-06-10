//
// Created by tia on 2020/05/06.
//

#include <graphics/draw.h>
#include <std.h>
#include <stdint.h>
#include <graphics/print.h>
#include <zconf.h>

#define NEWLINE(r) (((r) = ((r) + 1) % max_row))


const uint32_t gPRINTCOLOR = LIGHTGRAY;
uint64_t row_left = 0;
uint64_t row_right = 0;
uint64_t max_row = 0;
uint64_t half_col = 0;


uint64_t put(uint64_t *row, const char *str, uint64_t col) {
    if (max_row == 0) {
        max_row = draw_get_height() / 16;
    }

    for (uint64_t i = 0; str[i]; i ++, col ++) {
        if (str[i] == '\n') {
            col = 0;
            NEWLINE(*row);
        } else if (str[i] == '\r') {
            col = 0;
        } else {
            draw_char_bg(str[i], col * 8, *row * 16, gPRINTCOLOR);
        }
    }
    return col;
}

void puts(const char *str) {
    if (max_row == 0) {
        max_row = draw_get_height() / 16;
    }

    put(&row_left, str, 0);
    NEWLINE(row_left);
}

void puts_right(const char *str) {
    if (max_row == 0) {
        max_row = draw_get_height() / 16;
    }
    if (half_col == 0) {
        half_col = draw_get_width() / (2 * 8);
    }

    put(&row_right, str, half_col);
    NEWLINE(row_right);
}

void print(const char *format, ...) {
    if (max_row == 0) {
        max_row = draw_get_height() / 16;
    }

    va_list ap;
    va_start(ap, format);
    uint64_t col = 0;
    for (uint64_t i = 0; format[i]; i ++, col ++) {
        if (format[i] == '\n') {
            col = 0;
            NEWLINE(row_left);
        } else if (format[i] == '\r') {
            col = 0;
        } else if (format[i] == '%') {
            col = put(&row_left, va_arg(ap, char *), col);
        } else {
            draw_char_bg(format[i], col * 8, row_left * 16, gPRINTCOLOR);
        }
    }
    NEWLINE(row_left);
}
