# Set configuration and copy files
echo "Setting keyboard to handwired/lattice60/"
qmk config user.keyboard=handwired/lattice60
echo "Setting keymap to default"
qmk config user.keymap=default

qmk_path=$(qmk config user.qmk_home | cut -d '=' -f 2)
kb_path=$qmk_path/keyboards/$(qmk config user.keyboard | cut -d '=' -f 2)
km_path=$kb_path/keymaps/$(qmk config user.keymap | cut -d '=' -f 2)

echo "Replacing test files to QMK keyboard and keymap directory"
rm -r $kb_path
mkdir -p $km_path

for file in "config.h lattice60.c lattice60.h rules.mk"
do
    cp $file $kb_path
done

for file in "keymap.c"
do
    cp $file $km_path
done

# Compile and flash to microcontroller
echo "Press ESC key while plugging in keyboard to enter bootloader mode"
qmk flash
