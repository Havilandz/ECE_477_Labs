/*
 * Name: ledctrl.h
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 * Date: 02.23.2019
 *
 * This header file contains the function prototypes for ledctrl.c
 *
 * ledInit() initializes the GPIO pins 0-7 on the Raspberry Pi
 * as outputs as well as calls wiringPiSetup().
 *
 * ledToggle() takes an integer argument between 0 and 7 that
 * corresponds to a desired LED and toggles its state high or low
 * depending on its current state when entering the function.
 *
 * hexCtrl() takes a hexadecimal input and recreates the pattern in binary
 * on the LEDs. The maximum representation is up to 8 bits.
 *
 */

#ifndef LEDCTRL_H
#define LEDCTRL_H

void ledInit(void);
int ledToggle(int n);
int hexCtrl(int input);

#endif
