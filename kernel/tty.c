#include "tty.h"

/*
 *	This variable represents the kernel's current TTY to print to. For example, if it's
 *	set to `tty` on a x86-based PC, when the kernel tries to print something as output, it
 *	will be printed to the display's text mode...
 */
tty_t current_tty;
