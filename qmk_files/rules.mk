# Hardware configuration
MCU = atmega32u4
F_CPU = 8000000
BOOTLOADER = caterina

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
TAP_DANCE_ENABLE = yes      # Enable multi-tap functionality
COMBO_ENABLE = no           # Enable combo feature
SEND_STRING_ENABLE = yes    # Enable sending of strings

# Source File Options
SRC += heatmap.c
