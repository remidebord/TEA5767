#ifndef __ALTITUDE_H
#define __ALTITUDE_H

#define ALTITUDE_INIT 0x00
#define ALTITUDE_MAIN 0x01
#define ALTITUDE_SUB  0x02

#define ALTITUDE_INIT_TIME 500 // 500ms

void altitude_init(void);
void altitude_main(void);
void altitude_sub(void);
void altitude_timer(void);

#endif
