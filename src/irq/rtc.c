#include "irq/rtc.h"
#include "io/port.h"
#include "irq/pic.h"
#include "util/log.h"

void initRTC() {
    uint8_t prev;

    outb(RTCCommand, RTCNMI | RTCRegA);
    prev = inb(RTCData);
    outb(RTCCommand, RTCNMI | RTCRegA);
    outb(RTCData, (prev & 0xf0) | RTCRate);

    outb(RTCCommand, RTCNMI | RTCRegB);
    prev = inb(RTCData);
    outb(RTCCommand, RTCNMI | RTCRegB);
    outb(RTCData, prev | RTCIntPeriodic);

    prev = inb(RTCCommand);
    outb(RTCCommand, prev & (~RTCNMI));

    picSetMask(RTCIRQ, 0);
}

void rtcPeriodicHandler() {
    klog("clock tick!!");

    outb(RTCCommand, RTCRegC);
    inb(RTCData);
    picEOI(RTCIRQ);
}
