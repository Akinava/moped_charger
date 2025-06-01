avr-gcc -g -DF_CPU=16000000UL -Os -Wall -std=gnu99 -mmcu=atmega328p -c main.c -o main.o
avr-gcc -g -DF_CPU=16000000UL -Os -Wall -std=gnu99 -mmcu=atmega328p -o main.elf main.o
rm -f *.hex
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
rm -f *.o *.elf
#avr-size main.hex
avrdude -p atmega328p -c usbasp -v -v -U flash:w:main.hex