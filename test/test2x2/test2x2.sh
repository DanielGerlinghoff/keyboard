# Set configuration and copy files
echo "Setting keyboard to handwired/test2x2/"
qmk config user.keyboard=handwired/test2x2
echo "Setting keymap to default"
qmk config user.keymap=default

qmk_path=$(qmk config user.qmk_home | cut -d '=' -f 2)
kb_path=$qmk_path/keyboards/$(qmk config user.keyboard | cut -d '=' -f 2)
km_path=$kb_path/keymaps/$(qmk config user.keymap | cut -d '=' -f 2)

echo "Copying test files to QMK keyboard and keymap directory"
mkdir -p $km_path

for file in "config.h test2x2.c test2x2.h rules.mk"
do
    cp $file $kb_path
done

for file in "keymap.c"
do
    cp $file $km_path
done

# Flash to microcontroller
echo "Short GND and RST pin twice within 750 ms to enter bootloader mode"
qmk flash
