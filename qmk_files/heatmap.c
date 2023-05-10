#include <stdio.h>
#include <string.h>

#include "heatmap.h"


// Define the global 2D array
uint16_t keycount[MATRIX_ROWS][MATRIX_COLS] = {0};

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
  for (int phy_row = 0; phy_row < PHYSICAL_ROWS; phy_row++) {
    sprintf(buffer, "[");
    strcat(output, buffer);
    for (int phy_col = 0; phy_col < PHYSICAL_COLS; phy_col++) {
      int mat_row = transform_row[phy_row][phy_col];
      int mat_col = transform_col[phy_row][phy_col];
      if (mat_row != -1 && mat_col != -1) {
        sprintf(buffer, "%d", keycount[mat_row][mat_col]);
      } else {
        sprintf(buffer, "%d", -1);
      }
      strcat(output, buffer);
      if (phy_col != PHYSICAL_COLS - 1) {
        sprintf(buffer, ",");
        strcat(output, buffer);
      }
      keycount[mat_row][mat_col] = 0;
    }
    sprintf(buffer, "]");
    strcat(output, buffer);
    if (phy_row != PHYSICAL_ROWS - 1) {
      sprintf(buffer, ",");
      strcat(output, buffer);
    }
  }
  sprintf(buffer, "]");
  strcat(output, buffer);
}
