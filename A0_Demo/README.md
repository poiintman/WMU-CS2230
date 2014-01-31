# A0: Shell Demo

This program was written to demonstrate what is possible using the MSP430 and Steven Wendler's Libemb library. A simple prompt is set-up to enter commands and they are parsed using the library to function callbacks registered in the commands struct.

Run minicom and at the prompt execute:

	$ encrypt exm1234

Please use your BroncoID and submit the result in the format

	ID: (your id)
	Code: (encrypted string)

in an email to __trenarycs223@gmail.com__. These tools are necessary for the course so you _must_ be able to do this or you won't be able to complete any of the following assignments.

# Makefile

Included is a makefile with some useful targets. [Here](http://www.opussoftware.com/tutorial/TutMakefile.htm) is some useful reading if you don't understand the format.

* `$(NAME).elf: $(SOURCE)` is the default target that will compile whatever file is defined in `SOURCE` into a `.elf` ready to be flashed to the MSP430. It will automatically link the Libemb library if it is mentioned in the file.
* `flash: $(NAME).elf` will flash the MCU for you, compiling the source if necessary.
* `erase:` completely erases the MSP430.
* `clean:` deletes any `.elf` files in the directory.
* `debug: $(NAME).elf` will automatically begin a remote debugging session for you, opening up the msp430-gdb command line.
