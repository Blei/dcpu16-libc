CFLAGS = -O -Wall -Iinclude -S -target dcpu16

S_SRCS = libc/string/memmove.s \
	libc/string/memcpy.s

C_SRCS = libc/stdlib/malloc.c \
	libc/stdlib/realloc.c \
	libc/string/string.c \
	libc/dcpu.c

S_PRODUCED = $(C_SRCS:.c=.s)

OBJS = $(C_SRCS:.c=.o) $(S_SRCS:.s=.o)

libc.a: $(OBJS)
	dcpu-ar rs libc.a $(OBJS)

$(S_PRODUCED): %.s: %.c
	dcpu-clang -o $@ $< $(CFLAGS)

$(OBJS): %.o: %.s
	dcpu-as -o $@ $<

clean:
	rm -f $(OBJS) $(S_PRODUCED) libc.a
