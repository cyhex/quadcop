#!/bin/sh
wget  arduino.cc/download_handler.php?f=/arduino-1.6.1-linux64.tar.xz -O arduino.tar.xz
tar xf arduino.tar.xz
rm arduino.tar.xz
rm -rf bin
mkdir bin
mv arduino-1.6.1 bin/
cd bin/arduino-1.6.1/libraries/
ln -s ../hardware/arduino/avr/libraries/* ./