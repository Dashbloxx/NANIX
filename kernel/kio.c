#include "kio.h"
#include "ioport.h"
#include "tty.h"
#include "serial.h"

extern tty_t current_tty;

unsigned short int *video_memory = (unsigned short int *)0xB8000;
unsigned char cursor_x = 0;
unsigned char cursor_y = 0;

static void update_cursor() {
	switch(current_tty) {
	case tty0:
		unsigned short int cursor_location = cursor_y * 80 + cursor_x;
		outb(0x3D4, 14);
		outb(0x3D5, cursor_location >> 8);
		outb(0x3D4, 15);
		outb(0x3D5, cursor_location);
		return;
	case ttyS0:
		return;
	}
}

static void scroll() {
	switch(current_tty) {
	case tty0:
		unsigned char attribute_byte = (0 << 4) | (15 & 0x0F);
		unsigned short int blank = 0x20 | (attribute_byte << 8);

		if(cursor_y >= 25) {
			int i;
			for(i = 0*80; i < 24*80; i++) {
				video_memory[i] = video_memory[i + 80];
			} for(i = 24*80; i < 25*80; i++) {
				video_memory[i] = blank;
			}
			cursor_y = 24;
		}
		update_cursor();
		return;
	case ttyS0:
		return;
	}
}

void kclrscr() {
	switch(current_tty) {
	case tty0:
		unsigned char attribute_byte = (0 << 4) | (15 & 0x0F);
		unsigned short int blank = 0x20 | (attribute_byte << 8);

		int i;
		for(i = 0; i < 80 * 25; i++) {
			video_memory[i] = blank;
		}

		cursor_x = 0;
		cursor_y = 0;
		update_cursor();
		return;
	case ttyS0:
		return;
	}
}

void kputc(char character) {
	switch(current_tty) {
	case tty0:
		unsigned char back_color = 0;
		unsigned char fore_color = 15;
		unsigned char attribute_byte = (back_color << 4) | (fore_color & 0x0F);
		unsigned short int attribute = attribute_byte << 8;
		unsigned short int *location;

		if(character == 0x08 && cursor_x) {
			cursor_x--;
		} else if(character == 0x09) {
			cursor_x = (cursor_x + 8) & ~(8 - 1);
		} else if(character == '\r') {
			cursor_x = 0;
		} else if(character == '\n') {
			cursor_x = 0;
			cursor_y++;
		} else if(character >= ' ') {
			location = video_memory + (cursor_y * 80 + cursor_x);
			*location = character | attribute;
			cursor_x++;
		}

		if(cursor_x >= 80) {
			cursor_x = 0;
			cursor_y++;
		}

		scroll();
		update_cursor();
		return;
	case ttyS0:
		write_serial(character, (unsigned char)com1);
		return;
	}
}

void kprintf(char *fmt, ...) {
	int arg;
	void *args = (void *)(&fmt + 1);
	char *string;

	while(*fmt) {
		if(*fmt == '%') {
			fmt++;
			switch(*fmt) {
			case 'c':
				arg = *((int *)args);
				args += sizeof(int);
				kputc((char)arg);
				break;
			case 's':
				string = *((char **)args);
				args += sizeof(char *);
				while(*string) {
					kputc(*string);
					string++;
				}
				break;
			default:
				kputc('%');
				kputc(*fmt);
				break;
			}
		} else {
			kputc(*fmt);
		}
		fmt++;
	}
}
