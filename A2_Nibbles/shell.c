#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>
#include <libemb/shell/shell.h>
#include <stdlib.h>

/*******************************************
      PROTOTYPES & GLOBALS
*******************************************/
int shell_cmd_help(shell_cmd_args *args);
int shell_cmd_argt(shell_cmd_args *args);
int shell_cmd_getn(shell_cmd_args *args);
int nibble(int n, int i);

/*******************************************
      SHELL COMMANDS STRUCT
*******************************************/
shell_cmds my_shell_cmds = {
  .count  = 3,
  .cmds = {
    {
      .cmd  = "help",
      .desc = "list available commands",
      .func = shell_cmd_help
    },
    {
      .cmd  = "args",
      .desc = "print back given arguments",
      .func = shell_cmd_argt
    },
    {
      .cmd  = "getn",
      .desc = "print the nth nibble of a number",
      .func = shell_cmd_getn
    }
  }
};

/*******************************************
      SHELL CALLBACK HANDLERS
*******************************************/
int shell_cmd_help(shell_cmd_args *args)
{
  int k;

  for(k = 0; k < my_shell_cmds.count; k++) {
    cio_printf("%s: %s\n\r", my_shell_cmds.cmds[k].cmd, my_shell_cmds.cmds[k].desc);
  }

  return 0;
}

int shell_cmd_argt(shell_cmd_args *args)
{
  int k;

  cio_print((char *)"args given:\n\r");

  for(k = 0; k < args->count; k++) {
    cio_printf(" - %s\n\r", args->args[k].val);
  }

  return 0;
}

int shell_cmd_getn(shell_cmd_args *args)
{
  if(args->count != 2) {
    cio_print((char *)"ERROR, incorrect number of arguments\n\r");
    return 0;
  }
  char n = '0';
  itoa(nibble(strtol(args->args[0].val, NULL, 16), atoi(args->args[1].val)), &n, 16);
  cio_printf("%c\n\r", n);

  return 0;
}

int shell_process(char *cmd_line)
{
  return shell_process_cmds(&my_shell_cmds, cmd_line);
}

/*******************************************
      INITIALIZE
*******************************************/
int main(void)
{
  WDTCTL  = WDTPW + WDTHOLD;                // Stop watchdog timer
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL  = CALDCO_1MHZ;

  // BCSCTL3 = (BCSCTL3 & ~(BIT4+BIT5)) | LFXT1S_2;     // Disable xtal

  serial_init(9600);

  __eint();                                 // Enable global interrupts

/*******************************************
      MAIN LOOP
*******************************************/
  for(;;)
  {
    int j = 0;                              // Char array counter
    char cmd_line[90] = {0};                // Init empty array

    cio_print((char *) "$ ");               // Display prompt
    char c = cio_getc();                    // Wait for a character
    while(c != '\r') {                      // until return sent then ...
      if(c == 0x08) {                       //  was it the delete key?
        if(j != 0) {                        //  cursor NOT at start?
          cmd_line[--j] = 0;                //  delete key logic
          cio_printc(0x08); cio_printc(' '); cio_printc(0x08);
        }
      } else {                              // otherwise ...
        cmd_line[j++] = c; cio_printc(c);   //  echo received char
      }
      c = cio_getc();                       // Wait for another
    }

    cio_print((char *) "\n\n\r");           // Delimit command result

    switch(shell_process(cmd_line))         // Execute specified shell command
    {                                       // and handle any errors
      case SHELL_PROCESS_ERR_CMD_UNKN:
        cio_print((char *) "ERROR, unknown command given\n\r");
        break;
      case SHELL_PROCESS_ERR_ARGS_LEN:
        cio_print((char *) "ERROR, an arguement is too lengthy\n\r");
        break;
      case SHELL_PROCESS_ERR_ARGS_MAX:
        cio_print((char *) "ERROR, too many arguements given\n\r");
        break;
      default:
        break;
    }

    cio_print((char *) "\n");               // Delimit before prompt
  }

  return 0;
}

/*******************************************
      INTERRUPTS
*******************************************/
#pragma vector=TIMER0_A0_VECTOR
  __interrupt void Timer0_A0 (void) {

}
