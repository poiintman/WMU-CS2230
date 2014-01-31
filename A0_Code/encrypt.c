#include <msp430.h>
#include <string.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>
#include <libemb/shell/shell.h>

/*******************************************
      PROTOTYPES
*******************************************/
int shell_cmd_help(shell_cmd_args *args);
int shell_cmd_argt(shell_cmd_args *args);
int shell_cmd_encr(shell_cmd_args *args);

/*******************************************
      GLOBALS
*******************************************/
char *key = "____________________";

/*******************************************
      SHELL COMMANDS STRUCT
*******************************************/
shell_cmds commands = {
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
      .cmd  = "encrypt",
      .desc = "encrypt a string",
      .func = shell_cmd_encr
    }
  }
};

/*******************************************
      SHELL CALLBACK HANDLERS
*******************************************/
int shell_cmd_help(shell_cmd_args *args)
{
  int k;

  for(k = 0; k < commands.count; k++) {
    cio_printf("%s: %s\n\r", commands.cmds[k].cmd, commands.cmds[k].desc);
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

int shell_cmd_encr(shell_cmd_args *args)
{
  if(args->count == 0) {
    cio_print((char *) "ERROR, no string to encrypt\n\r");
    return -1;
  }
  if(strlen(args->args[0].val) > 20) {
    cio_print((char *) "ERROR, string to encrypt is too long\n\r");
    return -1;
  }
  int k;
  char string[21];
  strncpy(string, args->args[0].val, 20);

  for(k = 0; k < strlen(string); k++) {
    string[k] = string[k] ^ key[k];
  }

  cio_printf("encrypted string: %s\n\r", string);

  return 0;
}

int shell_process(char *cmd_line)
{
  return shell_process_cmds(&commands, cmd_line);
}

/*******************************************
      INITIALIZE
*******************************************/
int main(void)
{
  WDTCTL  = WDTPW + WDTHOLD;                // Stop watchdog timer
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL  = CALDCO_1MHZ;

  serial_init(9600);

  __dint();                                 // Enable global interrupts

/*******************************************
      MAIN LOOP
*******************************************/
  for(;;)
  {
    int j = 0;                              // Char array counter
    char cmd_line[90] = { 0 };              // Init empty array

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
