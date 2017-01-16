#ifndef __FRAMEBUFFER
#define __FRAMEBUFFER

#include "util/type.h"

typedef uint16_t    fb_t;

#define FBBase          ((fb_t *)0x000B8000)
#define FBCol           80
#define FBRow           25
#define FBIndex(x, y)   (FBCol * (x) + (y))
#define FB(x, y)        (*(FBBase + FBIndex(x, y)))

#define FBBlack         0x0
#define FBWhite         0xf

#define FBWhiteSpace    0

#define FBCommand       0x3d4
#define FBData          0x3d5

#define FBHiCommand     14
#define FBLoCommand     15

void fbSetCell(int x, int y, char c, uint8_t fg, uint8_t bg);
void fbSetCursor(int x, int y);

void fbClear(void);
void fbScroll(void);
void fbNewLine(void);
void fbPutChar(char ch);

void fbWrite(uint32_t info, const char *ch, size_t n);

#endif
