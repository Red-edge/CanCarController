#! /usr/bin/bash
# echo `date`

bash killtest.sh

sudo -S ip link set can0 up type can bitrate 1000000 <<EOF
123
EOF

# gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 201 -L 8 -g 4
gnome-terminal --geometry=80x10+10+10 --title "cansniffer" -- cansniffer can0 -c
gnome-terminal --geometry=50x20+10+300 --title "virtual can vc" -- candump can0

cd ./build

cmake ..
make

gnome-terminal --geometry=80x25+700+400 --title "real-can-test(can0)" -- ./test

cd ../
