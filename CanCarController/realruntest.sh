#! /usr/bin/bash
# echo `date`

bash killtest.sh

gnome-terminal -- sudo ip link set can0 up type can bitrate 1000000

# gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 201 -L 8 -g 4
gnome-terminal --geometry=80x10+10+10 --title "cansniffer" -- cansniffer can0 -c

cd ./build

cmake ..
make

gnome-terminal --geometry=80x25+700+400 --title "real-can-test(can0)" -- ./test 

cd ../
