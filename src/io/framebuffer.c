#include "io/framebuffer.h"
#include "io/port.h"
#include "mm/kmem.h"

static int cursorX, cursorY;
static uint8_t fbFG = FBWhite;
static uint8_t fbBG = FBBlack;

void fbSetCell(int x, int y, char c, uint8_t fg, uint8_t bg) {
    FB(x, y) = (c & 0xff) | ((bg & 0xf) << 12) | ((fg & 0xf) << 8);
}

static void fbUpdateCursor() {
    uint16_t pos = FBIndex(cursorX, cursorY);

    outb(FBCommand, FBHiCommand);
    outb(FBData, (pos >> 8) & 0xff);
    outb(FBCommand, FBLoCommand);
    outb(FBData, pos & 0xff);
}

void fbSetCursor(int x, int y) {
    cursorX = x;
    cursorY = y;
    fbUpdateCursor();
}

device_t *initFB() {
    fbClear();

    device_t *ret = (device_t *)kalloc(KmemDevice);
    ret -> write = fbWrite;
    return ret;
}

void fbClear() {
    int i, j;
    for (i = 0; i < FBRow; ++i) {
        for (j = 0; j < FBCol; ++j) {
            fbSetCell(i, j, FBWhiteSpace, fbFG, fbBG);
        }
    }
    fbSetCursor(0, 0);
}

void fbScroll() {
    int i, j;
    for (i = 1; i < FBRow; ++i) {
        for (j = 0; j < FBCol; ++j) {
            FB(i - 1, j) = FB(i, j);
        }
    }
    for (j = 0; j < FBCol; ++j) {
        fbSetCell(FBRow - 1, j, FBWhiteSpace, fbFG, fbBG);
    }
    fbSetCursor(cursorX - 1, cursorY);
}

void fbNewLine() {
    cursorY = 0;
    if (++cursorX >= FBRow) {
        fbScroll();
    } else {
        fbUpdateCursor();
    }
}

static void fbBackspace() {
    if (cursorX || cursorY) {
        if (--cursorY < 0) {
            --cursorX;
            cursorY += FBCol;
        }
        while (cursorY > 0 && (FB(cursorX, cursorY) & 0xff) == FBWhiteSpace) --cursorY;
        fbSetCell(cursorX, cursorY, FBWhiteSpace, fbFG, fbBG);
        fbUpdateCursor();
    }
}

static void fbPutRegularChar(char ch) {
    fbSetCell(cursorX, cursorY, ch, fbFG, fbBG);
    if (++cursorY >= FBCol) {
        fbNewLine();
    } else {
        fbUpdateCursor();
    }
}

void fbPutChar(char ch) {
    switch (ch) {
    case '\n':
        fbNewLine();
        break;
    case '\r':
        fbBackspace();
        break;
    default:
        fbPutRegularChar(ch);
        break;
    }
}

void fbWrite(uint32_t info, const char *data, size_t n) {
    info = info;
    while (n-- > 0) {
        fbPutChar(*data++);
    }
}
