#ifndef HEATMAP_H
#define HEATMAP_H

#include "quantum.h"


// Set unique user hash
#define USERHASH "fa12c64fbaa2393b23b82b690e9f835365c631dedf91679167e860cc5027b053"

// Set array to transform physical key positions into matrix key positions
// when dumping the array, assign -1 to unused keys (also double check with
// lattice60.h)
#define PHYSICAL_ROWS 5
#define PHYSICAL_COLS 14

static const int transform_row[PHYSICAL_ROWS][PHYSICAL_COLS] = { \
 {4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, \
 {4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1}, \
 {4,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, -1}, \
 {4,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3}, \
 {4,  4,  4,  4,  4,  4,  4,  4, -1, -1, -1, -1, -1, -1}, \
};
static const int transform_col[PHYSICAL_ROWS][PHYSICAL_COLS] = { \
 {0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12}, \
 {1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12}, \
 {2,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, -1}, \
 {3,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12}, \
 {4,  5,  6,  7,  9, 10, 11, 12, -1, -1, -1, -1, -1, -1}, \
};

// Declare the global 2D array
extern uint16_t keycount[MATRIX_ROWS][MATRIX_COLS];

// Function to increment keycount value based on key position
void increment_keycount(keyrecord_t *record);

// Function to dump keycount array as a Python list
void dump_keycount(char *output);

#endif // HEATMAP_H
