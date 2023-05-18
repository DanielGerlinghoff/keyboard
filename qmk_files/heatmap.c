#include <stdio.h>
#include <string.h>

#include "quantum.h"
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
void dump_keycount(void) {
  // Construct string with Python-like list
  char output[PHYSICAL_ROWS*PHYSICAL_COLS*6];

  sprintf(output, "[");
  for (int phy_row = 0; phy_row < PHYSICAL_ROWS; phy_row++) {
    strcat(output, "[");
    for (int phy_col = 0; phy_col < PHYSICAL_COLS; phy_col++) {
      // Transform physical to wire matrix position
      int mat_row = transform_row[phy_row][phy_col];
      int mat_col = transform_col[phy_row][phy_col];

      // Append keycount to current output string
      if (mat_row != -1 && mat_col != -1) {
        sprintf(output + strlen(output), "%d", keycount[mat_row][mat_col]);
      } else {
        sprintf(output + strlen(output), "%d", -1);
      }
      if (phy_col != PHYSICAL_COLS - 1) {
        strcat(output, ",");
      }

      // Reset keycount
      keycount[mat_row][mat_col] = 0;
    }
    strcat(output, "]");
    if (phy_row != PHYSICAL_ROWS - 1) {
      strcat(output, ",");
    }
  }
  strcat(output, "]");

  // Send user hash, tab and keycount list
  SEND_STRING(USERHASH);
  SEND_STRING(SS_TAP(X_TAB));
  send_string(output);
}
