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
 * hexCtrl() can take a hex, decimal, or octal value and recreate the binary
 * representation on LEDs up to 8 bits. This is the code from lab 2
 * recreated to be a standalone function.
 *
 */

#ifndef LEDCTRL_H
#define LEDCTRL_H

void ledInit(void);
int ledToggle(int n);
int hexCtrl(int n, char*c[]);

#endif
