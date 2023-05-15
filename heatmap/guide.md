# Generate a Heatmap for Your QMK Keyboard

With heatmaps of your keystrokes you can track the usage and identify optimization opportunities to improve keyboard layouts for efficiency and comfort.

## Step 1: Register for the service

 * To register, generate a unique hash and enter the physical key array to be used in the heatmap.

## Step 2: Add the function to the QMK firmware

 * In the firmware header file, insert your personal hash and add an array to convert the wiring matrix into the physical key matrix.
 * Assign the macro to dump the keycount to a key combination.

## Step 3: Submit your keycounts

 * Place your cursor into the hash field on the website and press the assigned key combination to print the data.
 * Submit the data and the website will draw the heatmap.

## Step 4: View the heatmap

 * To view the heatmap without submitting new keycounts, insert only your hash and submit.
