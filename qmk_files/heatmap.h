#ifndef HEATMAP_H
#define HEATMAP_H

#include "quantum.h"


// Set unique user hash
#define USERHASH "fa12c64fbaa2393b23b82b690e9f835365c631dedf91679167e860cc5027b053"

// Declare the global 2D array
extern uint16_t keycount[MATRIX_ROWS][MATRIX_COLS];

// Function to increment keycount value based on key position
void increment_keycount(keyrecord_t *record);

// Function to dump keycount array as a Python list
void dump_keycount(char *output);

#endif // HEATMAP_H
