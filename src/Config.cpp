#include "Config.h"

// Ticker for base timer
Ticker ticker(TIM16);

// Segment array (a b c d e f g)
DigitalOut segment[] = {DigitalOut(PA_4), DigitalOut(PA_6), DigitalOut(PB_15), DigitalOut(PA_11),
                        DigitalOut(PA_12), DigitalOut(PA_5), DigitalOut(PB_14)};

												
// Digit array (d4 d3 d2 d1)
DigitalOut digit[] = {DigitalOut(PB_2), DigitalOut(PB_1), DigitalOut(PB_0), DigitalOut(PA_7)};

// Dots
DigitalOut dots(PA_8);

// One seven segment is composed of an array of segment and one digit pin
SevenSeg sevenSeg0(segment, &digit[0]);
SevenSeg sevenSeg1(segment, &digit[1]);
SevenSeg sevenSeg2(segment, &digit[2]);
SevenSeg sevenSeg3(segment, &digit[3]);

// Create group of seven segment
SevenSegGroup sevenSegGroup;
	
// Pusb buttons on encoders
Button buttonRight(PA_2);
Button buttonLeft(PB_5);
	
// led brightness
Brightness brightness(PA_3, 1000, TIM15, Channel_2);

// I2C object
I2C	i2c(I2C2, PF_7, PF_6);
