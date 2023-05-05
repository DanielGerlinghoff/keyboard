# Lattice60 Keyboard Firmware
This repository contains firmware files and deployment tools for the Quantum Mechanical Keyboard (QMK) firmware. QMK is an open-source firmware that allows users to fully customise and program their keyboard's behavior and layout. Head over to my [project log](https://hackaday.io/project/185358-lattice60/log/218466-keyboard-layout-and-layers) to see how I optimised the layers to reduce finger movement and increase typing comfort.

## Deployment Steps
1. Install QMK version 0.17.x and go through the short setup procedure.
2. Navigate to this folder from within QMK.
```shell
cd <repo_root>/qmk_files
```
3. Run the `compile.sh` script, which copies all necessary files over where QMK can find them and compiles them.
```shell
source compile.sh
```
4. Flash the firmware when asked to by unplugging the keyboard and re-connecting it with **ESC** pressed.
5. The keyboard is ready to use!

