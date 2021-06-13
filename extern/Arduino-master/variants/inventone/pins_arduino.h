/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis
  Modified for ESP8266 platform by Ivan Grokhotkov, 2014-2015.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

//#define PIN_WIRE_SDA (2)
//#define PIN_WIRE_SCL (14)

// valeurs pour pas géner les autres digitales et les analogues
#define PIN_WIRE_SDA (20)
#define PIN_WIRE_SCL (21)
static const char GND = -1;
static const char V5 = -5;
static const char V33 = -3;

typedef unsigned char uint8_t;         /* 8 bit signed */;

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#define LED_BUILTIN 2

//static const uint8_t D1   = 15;
//static const uint8_t D2   = 0;
//static const uint8_t D3   = 14;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 5;
//static const uint8_t D6   = 4;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 12;
//static const uint8_t D9   = 16;
//static const uint8_t RX  = 3;
//static const uint8_t TX = 1;

#define PIN_A0 0
/*Analog pins for Onboard ADC*/
//static const uint8_t A1 = 1;
//static const uint8_t A2 = 2;
//static const uint8_t A3 = 3;
//static const uint8_t A4 = 4;

// valeurs retenues lors des tests sur l'Arduino Uno du robot

static const uint8_t D0   = 0;
static const uint8_t D1   = 1;
static const uint8_t D2   = 2;
static const uint8_t D3   = 3;
static const uint8_t D4   = 4;
static const uint8_t D5   = 5;
static const uint8_t D6   = 6;
static const uint8_t D7   = 7;
static const uint8_t D8   = 8;
static const uint8_t D9   = 9;
static const uint8_t D10  = 10;
static const uint8_t D11  = 11;
static const uint8_t D12  = 12;
static const uint8_t D13  = 13;
static const uint8_t RX   = 0;
static const uint8_t TX   = 1;

static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 18;

//#include "../generic/common.h"

#endif /* Pins_Arduino_h */
