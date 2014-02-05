# A1: Hidden Value

For this assignment, you will be required to utilize `msp430-gdb` to locate a value on the microcontroller. Provided is a precompiled `.elf` file that you must flash to your launchpad.

Once it is programmed, run minicom and at the prompt execute:

	$ hide exm1234

Please use your BroncoID. This will calculate a unique value and "hide" it somewhere in the MSP430's memory. It will be up to you to locate where it is being stored and submit the value, along with your ID in this format:

	ID: (your id)
	Code: (calculated value)

in an email to __trenarycs223@gmail.com__.

# Debugging

To set up a debugging environment, use the Makefile and execute:

	$ make debug

_Do this while minicom is still running_ so that you have command access to the microcontroller while you are debugging. This is important because you will need to break the program during it's execution of the `hide` command.

Some breakpoint targets are provided to you for convenience:

	shell_cmd_hide
	cmd_hide_loop
	cmd_hide_end

However, the assembly file is _not_ provided, so you will have to use the  commands GDB has available to examine instructions. [Here]() is some useful reading on debugger commands and there is also a very handy [cheat sheet]().