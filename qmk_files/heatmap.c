#include <stdio.h>
#include <string.h>

#include "heatmap.h"


// Define the global 2D array
uint8_t keycount[MATRIX_ROWS][MATRIX_COLS] = {0};

// Function to increment keycount value based on key position
void increment_keycount(keyrecord_t *record) {
  // Get key position from key event
  uint8_t row = record->event.key.row;
  uint8_t col = record->event.key.col;

  // Increment keycount value at row, col position
  keycount[row][col]++;
}

// Function to dump keycount array as a Python list
void dump_keycount(char *output) {
  char buffer[256];
  sprintf(output, "[");
  for (int row = 0; row < MATRIX_ROWS; row++) {
    sprintf(buffer, "[");
    strcat(output, buffer);
    for (int col = 0; col < MATRIX_COLS; col++) {
      sprintf(buffer, "%d", keycount[row][col]);
      strcat(output, buffer);
      if (col != MATRIX_COLS - 1) {
        sprintf(buffer, ",");
        strcat(output, buffer);
      }
      keycount[row][col] = 0;
    }
    sprintf(buffer, "]");
    strcat(output, buffer);
    if (row != MATRIX_ROWS - 1) {
      sprintf(buffer, ",");
      strcat(output, buffer);
    }
  }
  sprintf(buffer, "]");
  strcat(output, buffer);
}
