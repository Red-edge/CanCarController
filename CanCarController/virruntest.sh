#! /usr/bin/bash
# echo `date`

bash killtest.sh

sudo -S modprobe vcan << EOF
123
EOF

sudo ip link add dev vc type vcan
sudo ip link set up vc

gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 201 -L 8 -D '0000100000000000'
gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 202 -L 8 -D '0000010000000000'
gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 203 -L 8 -D '0000300000000000'
gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 204 -L 8 -D '0000030000000000'

gnome-terminal --geometry=80x10+10+10 --title "cansniffer" -- cansniffer vc -c
gnome-terminal --geometry=50x20+10+300 --title "virtual can vc" -- candump vc

cd ./build

cmake ..
make

gnome-terminal --geometry=80x25+700+400 --title "virtual-can-test(vc)"  -- ./test

cd ../
