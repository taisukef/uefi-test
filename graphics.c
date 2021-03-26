#include "efi.h"
#include "graphics.h"

const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL white = {0xff, 0xff, 0xff, 0xff};

void draw_pixel(unsigned int x, unsigned int y,
		struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL color)
{
	unsigned int hr = GOP->Mode->Info->HorizontalResolution;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base =
		(struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)GOP->Mode->FrameBufferBase;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = base + (hr * y) + x;

	p->Blue = color.Blue;
	p->Green = color.Green;
	p->Red = color.Red;
	p->Reserved = color.Reserved;
}

void draw_rect(struct RECT r, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL c)
{
	unsigned int i;

	for (i = r.x; i < (r.x + r.w); i++)
		draw_pixel(i, r.y, c);
	for (i = r.x; i < (r.x + r.w); i++)
		draw_pixel(i, r.y + r.h - 1, c);

	for (i = r.y; i < (r.y + r.h); i++)
		draw_pixel(r.x, i, c);
	for (i = r.y; i < (r.y + r.h); i++)
		draw_pixel(r.x + r.w - 1, i, c);
}

void draw_line(int x1, int y1, int x2, int y2, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL c) {
	int dx = x2 - x1;
	int dx2 = dx;
	if (dx < 0)
		dx2 = -dx;
	int dy = y2 - y1;
	int dy2 = dy;
	if (dy2 < 0)
		dy2 = -dy;
 	if (dx == 0 && dy == 0) {
		draw_pixel(x1, y1, c);
	} else if (dx2 < dy2) {
		if (y1 < y2) {
			for (int i = 0; y1 + i <= y2; i++) {
				draw_pixel(x1 + (dx * i) /  dy, y1 + i, c);
			}
		} else {
			for (int i = 0; y2 + i <= y1; i++) {
				draw_pixel(x2 + (dx * i) / dy, y2 + i, c);
			}
		}
	} else {
		if (x1 < x2) {
			for (int i = 0; x1 + i <= x2; i++) {
				draw_pixel(x1 + i, y1 + (dy * i) / dx, c);
			}
		} else {
			for (int i = 0; x2 + i <= x1; i++) {
				draw_pixel(x2 + i, y2 + (dy * i) / dx, c);
			}
		}
	}
}
