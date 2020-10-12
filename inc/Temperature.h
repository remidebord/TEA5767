#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H

#define TEMPERATURE_INIT 0x00
#define TEMPERATURE_MAIN 0x01
#define TEMPERATURE_SUB  0x02

#define TEMPERATURE_INIT_TIME 500 // 500ms

void temperature_init(void);
void temperature_main(void);
void temperature_sub(void);
void temperature_timer(void);

#endif
