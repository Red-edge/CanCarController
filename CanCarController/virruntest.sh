#! /usr/bin/bash
# echo `date`

sudo modprobe vcan
sudo ip link add dev vc type vcan
sudo ip link set up vc

gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 201 -L 8 -D '00001220000000'
# gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 202 -L 8 -D '00000F20000000'
# gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 203 -L 8 -D '00000420000000'
# gnome-terminal --geometry=80x10+10+10 --title "virtual can vc" -- cangen vc -I 204 -L 8 -D '00000120000000'

gnome-terminal --geometry=80x10+10+10 --title "cansniffer" -- cansniffer vc -c
gnome-terminal --geometry=80x20+10+300 --title "virtual can vc" -- candump vc

cd ./build

cmake ..
make

gnome-terminal --geometry=80x25+700+400 --title "virtual-can-test(vc)" -- ./test 

cd ../
