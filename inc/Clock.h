#ifndef __CLOCK_H
#define __CLOCK_H

#define CLOCK_INIT 0x00
#define CLOCK_MAIN 0x01
#define CLOCK_SUB  0x02

#define CLOCK_INIT_TIME 500  // 500ms
#define CLOCK_SYNC_TIME 1000 // 1000ms

void clock_init(void);
void clock_main(void);
void clock_sub(void);
void clock_timer(void);

#endif
