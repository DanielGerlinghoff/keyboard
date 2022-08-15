/*
Copyright 2022 Daniel Gerlinghoff <daniel.gerlinghoff@outlook.com>
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBB80
#define PRODUCT_ID      0x050D
#define DEVICE_VER      0x0001
#define MANUFACTURER    PrimeNumber1
#define PRODUCT         Lattice60

/* Key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 13

/*
 * Keyboard matrix assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW: COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL: ROW = Anode (+), COL = Cathode (-, marked on diode)
*/
#define MATRIX_ROW_PINS { F4, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { C6, D4, D0, D1, D2, D3, F5, F6, F7, B1, B3, B2, B6 }

#define DIODE_DIRECTION COL2ROW

/* Bootmagic Lite
 * Assign row and column of ESC key to reset EEPROM and enter bootloader
 * Hold ESC key down when plugging in the keyboard
*/
#define BOOTMAGIC_LITE_ROW 4
#define BOOTMAGIC_LITE_COLUMN 0

/* Debounce reduces chatter (unintended double-presses)
 * Set 0 if debouncing is not needed
*/
#define DEBOUNCE 15
