Arduino dev env
...............

install netbeans c++
https://netbeans.org/downloads/


run buildout.sh


Open Netbeans

Add Tool Collection in Tools->options->C/C++ -> Build Tools
............................................................

Base directory: ../bin/arduino-1.6.1/hardware/tools/avr/bin
C compiler: ../bin/arduino-1.6.1/hardware/tools/avr/bin/avr-gcc
C++ compiler: ../bin/arduino-1.6.1/hardware/tools/avr/bin/avr-g++
Assebler: ../bin/arduino-1.6.1/hardware/tools/avr/bin/avr-as


Add includes in Tools->options->C/C++->Code Assistance->C++ Compiler
....................................................................
Add Includes:
../bin/arduino-1.6.1/hardware/arduino/avr/cores/arduino
../bin/arduino-1.6.1/hardware/arduino/avr/variants/standard
../bin/arduino-1.6.1/liberies/Wire


Issues
......


fix undefined reference to XXXX

edit nbproject/configurations.xml - make sure all libs are there!



