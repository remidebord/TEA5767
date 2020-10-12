#ifndef __MAIN_H
#define __MAIN_H

/* includes ------------------------------------------------------------------*/
#include "Menu.h"
#include "Clock.h"
#include "Temperature.h"
#include "Altitude.h"
#include "Fix.h"
#include "Satellites.h"

/* defines --------------------------------------------------------------------*/
/* variables ------------------------------------------------------------------*/
/* functions ------------------------------------------------------------------*/
void tickRTC(void);
void tickMCU(void);

#endif /* __MAIN_H */
