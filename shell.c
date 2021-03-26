#include "common.h"
#include "graphics.h"
#include "shell.h"
#include "rnd.h"

#define MAX_COMMAND_LEN	100
#define SCR_W 800
#define SCR_H 600

void shell(void) {
	unsigned short com[MAX_COMMAND_LEN];
	
	random_init();
	
	for (;;) {
		puts(L"poiOS> ");
		if (gets(com, MAX_COMMAND_LEN) <= 0) {
			continue;
		}

		if (!strcmp(L"hello", com)) {
			puts(L"Hello UEFI!\r\n");
		} else if (!strcmp(L"rect", com)) {
			struct RECT r = { 10, 10, 100, 200 };
			draw_rect(r, white);
		} else if (!strcmp(L"line", com)) {
			draw_line(0, 0, 640, 480, white);
		} else if (!strcmp(L"lines", com)) {
			for (int i = 0; i < 100; i++) {
				int x1 = rnd() % SCR_W;
				int y1 = rnd() % SCR_H;
				int x2 = rnd() % SCR_W;
				int y2 = rnd() % SCR_H;
				draw_line(x1, y1, x2, y2, white);
			}
		} else {
			puts(L"Command not found.\r\n");
		}
	}
}
