#ifndef __SATELLITES_H
#define __SATELLITES_H

#define SATELLITES_INIT 0x00
#define SATELLITES_MAIN 0x01
#define SATELLITES_SUB  0x02

#define SATELLITES_INIT_TIME 500 // 500ms

void satellites_init(void);
void satellites_main(void);
void satellites_sub(void);
void satellites_timer(void);

#endif
