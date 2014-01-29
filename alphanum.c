#include <msp430.h>

static int port1[] = { 0x5d, 0x61, 0x75, 0x61, 0x7d, 0x5d, 0x75, 0x1c, 0x61 };
static int port2[] = { 0x68, 0x7e, 0x10, 0x76, 0x10, 0x00, 0x58, 0x68, 0x16 };

void off() {
	P1OUT = 0xff;
	P2OUT = 0xff;
}

int main()
{
	WDTCTL = WDTHOLD | WDTPW;
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1= CALBC1_1MHZ;

	P2SEL &= ~BIT6;
	P2SEL &= ~BIT7;

	P1DIR = 0xff;
	P2DIR = 0xff;
	P1OUT = 0;
	P2OUT = 0;

	int i = 0;
	int j = 0;
	int k = 0;
	int seg = 0;
	int count = 0;
	int alpha = 0;

	for(;;) {
		// for(k = 0; k < 3000; k++) {
		// 	off();

		// 	if (j == 0) P1OUT &= ~(port1[alpha] & (1<<i));
		// 	if (j == 1) P2OUT &= ~(port2[alpha] & (1<<i));

		// 	seg = (j * 8) + (i + 1);
		// 	if (seg !=  1 && 
		// 		seg !=  4 &&
		// 		seg !=  6 &&
		// 		seg !=  7 &&
		// 		seg != 12 &&
		// 		seg != 13) {
		// 		if (count++ == 4) { i++; count = 0; }
		// 	} else {
		// 		i++;
		// 	}

		// 	if (i == 8) { i = 0; j++; }
		// 	if (j == 2) j = 0;

		// 	__delay_cycles(180);
		// }
		// if (++alpha == 9) alpha = 0;
	}

	return 0;
}