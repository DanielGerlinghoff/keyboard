# Convert path to Windows
file=$(echo $1 | sed -e "s/\/c/C:/" -e "s;\/;\\\;g")

# Flash
avrdude.exe -p atmega32u4 -c avr109 -U flash:w:$file:i -P COM4
