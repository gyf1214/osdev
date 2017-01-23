#ifndef __RTC
#define __RTC

#define RTCCommand      0x70
#define RTCData         0x71

#define RTCNMI          0x80
#define RTCSecond       0x00
#define RTCAlarmSecond  0x01
#define RTCMinute       0x02
#define RTCAlarmMinute  0x03
#define RTCHour         0x04
#define RTCAlarmHour    0x05
#define RTCWeek         0x06
#define RTCDay          0x07
#define RTCMonth        0x08
#define RTCYear         0x09
#define RTCRegA         0x0a
#define RTCRegB         0x0b
#define RTCRegC         0x0c
#define RTCRegD         0x0d

#define RTCRate         0x0f

#define RTCIntUpdate    0x10
#define RTCIntAlarm     0x20
#define RTCIntPeriodic  0x40
#define RTCUpdate       0x80

#define RTCIRQ          8

void initRTC(void);
void rtcPeriodicHandler(void);

#endif
