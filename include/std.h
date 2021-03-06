//
// Created by tia on 2020/03/16.
//

#ifndef CIEOS_STD_H
#define CIEOS_STD_H

#include <stdint.h>

typedef _Bool bool;
#define true ((_Bool)1)
#define false ((_Bool)0)
#define null ((void *)0)

struct DivMod {
    int64_t div;
    int64_t mod;
};

enum ITOA_FRAGS {
    DEFAULT             = 0,
    FILL_SPACE          = 0x1,
    FILL_ZERO           = 0x2,
    IS_SIGNED           = 0x4,
    SET_SIGN            = 0x8,
    UPPERCASE           = 0x10,
    SET_NULL_TERMINATE  = 0x20,
    ZERO_IS_EMPTY       = 0x40
};

#define RINGBUFFERSIZE 64

struct RingBuffer {
    uint8_t buffer[RINGBUFFERSIZE];
    uint8_t free;
    uint8_t next_write;
    uint8_t next_read;
    bool overflow;
};

struct DateTime {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    uint8_t _align[2];
};

struct DoubleWordAccess {
    uint32_t low;
    uint32_t high;
};

struct WordAccess {
    uint16_t word_0;
    uint16_t word_1;
    uint16_t word_2;
    uint16_t word_3;
};

struct ByteAccess {
    uint8_t byte_0;
    uint8_t byte_1;
    uint8_t byte_2;
    uint8_t byte_3;
    uint8_t byte_4;
    uint8_t byte_5;
    uint8_t byte_6;
    uint8_t byte_7;
};

struct BitAccess {
    unsigned bit_0: 1;
    unsigned bit_1: 1;
    unsigned bit_2: 1;
    unsigned bit_3: 1;
    unsigned bit_4: 1;
    unsigned bit_5: 1;
    unsigned bit_6: 1;
    unsigned bit_7: 1;
    unsigned bit_8: 1;
    unsigned bit_9: 1;
    unsigned bit_10: 1;
    unsigned bit_11: 1;
    unsigned bit_12: 1;
    unsigned bit_13: 1;
    unsigned bit_14: 1;
    unsigned bit_15: 1;
    unsigned bit_16: 1;
    unsigned bit_17: 1;
    unsigned bit_18: 1;
    unsigned bit_19: 1;
    unsigned bit_20: 1;
    unsigned bit_21: 1;
    unsigned bit_22: 1;
    unsigned bit_23: 1;
    unsigned bit_24: 1;
    unsigned bit_25: 1;
    unsigned bit_26: 1;
    unsigned bit_27: 1;
    unsigned bit_28: 1;
    unsigned bit_29: 1;
    unsigned bit_30: 1;
    unsigned bit_31: 1;
    unsigned bit_32: 1;
    unsigned bit_33: 1;
    unsigned bit_34: 1;
    unsigned bit_35: 1;
    unsigned bit_36: 1;
    unsigned bit_37: 1;
    unsigned bit_38: 1;
    unsigned bit_39: 1;
    unsigned bit_40: 1;
    unsigned bit_41: 1;
    unsigned bit_42: 1;
    unsigned bit_43: 1;
    unsigned bit_44: 1;
    unsigned bit_45: 1;
    unsigned bit_46: 1;
    unsigned bit_47: 1;
    unsigned bit_48: 1;
    unsigned bit_49: 1;
    unsigned bit_50: 1;
    unsigned bit_51: 1;
    unsigned bit_52: 1;
    unsigned bit_53: 1;
    unsigned bit_54: 1;
    unsigned bit_55: 1;
    unsigned bit_56: 1;
    unsigned bit_57: 1;
    unsigned bit_58: 1;
    unsigned bit_59: 1;
    unsigned bit_60: 1;
    unsigned bit_61: 1;
    unsigned bit_62: 1;
    unsigned bit_63: 1;
};

#define M_DOUBLEWORD_ACCESS(target) (*((struct DoubleWordAccess*)&target))
#define M_WORD_ACCESS(target) (*((struct WordAccess*)&target))
#define M_BYTE_ACCESS(target) (*((struct ByteAccess*)&target))
#define M_BIT_ACCESS(target) (*((struct BitAccess*)&target))

extern uint64_t TIMER_COUNT;  // defined by timer.c
extern struct RingBuffer KEYBOARD_BUFFER;  // defined by keyboard.c
extern struct RingBuffer MOUSE_BUFFER;  // defined by mouse.c
extern struct DateTime RTC_DATA;  // defined by rtc.c
extern void * KERNEL_LOADED_POINT;
extern void * ENTRY_POINT;


void halt();

_Noreturn void hstop();
void sleepms(uint64_t ms);

struct DivMod divmod(int64_t x, int64_t y);
void itoa(uint64_t value, char *buffer, uint64_t buffer_size, uint64_t radix, uint32_t flags);
bool strncmp(const char *a, const char *b, uint64_t n);
bool strcmp(const char *a, const char *b);
void strncpy(const char *src, char *dist, uint64_t n);
void strcpy(const char *src, char *dist);
void bool2str(char *dist, bool x);
const char* bool2shortstraddr(bool x);
const char* bool2straddr(bool x);
void ringbuf_init(struct RingBuffer* ring_buffer);
bool ringbuf_write(struct RingBuffer* ring_buffer, uint8_t data);
uint8_t ringbuf_read(struct RingBuffer* ring_buffer);
bool ringbuf_read_dist(struct RingBuffer* ring_buffer, uint8_t *dist);

void test_and_set(uint64_t *arr, uint64_t pos);  // asm

#endif //CIEOS_STD_H
