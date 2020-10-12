#ifndef __FIX_H
#define __FIX_H

#define FIX_INIT 0x00
#define FIX_MAIN 0x01
#define FIX_SUB  0x02

#define FIX_INIT_TIME 500 // 500ms

void fix_init(void);
void fix_main(void);
void fix_sub(void);
void fix_timer(void);

#endif
