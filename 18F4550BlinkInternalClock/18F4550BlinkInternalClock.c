// 18F4550BlinkInternalClock.c

// chip config ////////////////////////////////////////////////////////////////////////////////////
					// clock options, see 18F4550 data sheet figure 2-1 "clock diagram" for explanation
#pragma config PLLDIV = 5				// this does not matter since we are using the internal clock & not using USB, see data sheet fig. 2-1
#pragma config CPUDIV = OSC1_PLL2		// this does not matter since we are using the internal clock & not using USB, see data sheet fig. 2-1
#pragma config USBDIV = 2				// this does not matter since we are using the internal clock & not using USB, see data sheet fig. 2-1

										// internal clock, pin #14 (RA6) as I/O pin, pin #13 unused,
#pragma config FOSC = INTOSCIO_EC		// if OSCCON is left as default clock speed will be 1Mhz

					// now the other less confusing options . . .
#pragma config FCMEN = OFF				// fail-safe clock monitor disabled
#pragma config IESO = OFF				// internal / external osc switchover bit disabled
#pragma config PWRT = OFF				// power-up timer disabled
#pragma config BOR = OFF				// brown-out reset disabled in hardware & software
#pragma config BORV = 3					// brown-out reset voltage bits, does not matter since brown-out is disabled 
#pragma config VREGEN = OFF				// USB voltage regulator, would need to turn on if using internal USB voltage regulator for USB comm.
#pragma config WDT = OFF				// watchdog timer disabled
#pragma config WDTPS = 32768			// watchdog timer postscale, does not matter since watchdog timer is disabled
#pragma config CCP2MX = ON				// use RC1 (pin #16) as CCP2 MUX (this is the default pin for CCP2 MUX)
#pragma config PBADEN = OFF				// RB0, RB1, RB2, RB3, & RB4 are configured as digital I/O on reset
#pragma config LPT1OSC = OFF			// disable low-power option for timer 1 (timer 1 in regular mode)
#pragma config MCLRE = OFF				// master clear disabled, pin #1 is for VPP and / or RE3 use
#pragma config STVREN = ON				// stack full/underflow will cause reset
#pragma config LVP = OFF				// single-supply ICSP disabled
#pragma config ICPRT = OFF				// in-circuit debug/programming port (ICPORT) disabled, this feature is not available on 40 pin DIP package
#pragma config XINST = OFF				// instruction set extension and indexed addressing mode disabled (this is the default setting)
#pragma config DEBUG = OFF				// background debugger disabled, RA6 & RB7 configured as general purpose I/O pins
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF			// code protection bits off
#pragma config CPB = OFF				// boot block code protection off
#pragma config CPD = OFF				// data EEPROM code protection off
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF		// write protection bits off
#pragma config WRTC = OFF				// config registers write protection off
#pragma config WRTB = OFF				// boot block is not write protected
#pragma config WRTD = OFF				// data EEPROM is not write protected
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF	// table read protection bits off
#pragma config EBTRB = OFF				// boot block table read protection off

// includes ///////////////////////////////////////////////////////////////////////////////////////
#include<p18f4550.h>
#include<delays.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
void main(void) {
	
	ADCON1bits.PCFG3 = 1;			// set all AN pins to digital I/O
	ADCON1bits.PCFG2 = 1;			//
	ADCON1bits.PCFG1 = 1;			//
	ADCON1bits.PCFG0 = 1;			//
	
	TRISDbits.RD4 = 0;			// set RB4 to output
	TRISDbits.RD3 = 0;			// set RB3 to output
	TRISDbits.RD2 = 0;			// set RB2 to output
	TRISDbits.RD1 = 0;			// set RB1 to output
	TRISDbits.RD0 = 0;			// set RB0 to output
	
	PORTDbits.RD4 = 0;
	PORTDbits.RD3 = 0;				// init output pins to off
	PORTDbits.RD2 = 0;
	PORTDbits.RD1 = 0;
	PORTDbits.RD0 = 0;
	
	while(1) {
		PORTDbits.RD4 = 1;
		PORTDbits.RD3 = 1;		// turn on RB3
		PORTDbits.RD2 = 1;		// turn on RB2
		PORTDbits.RD1 = 1;		// turn on RB1
		PORTDbits.RD0 = 1;		// turn on RB0
		
		Delay1KTCYx(125);		// TCY = 4 us, delay = 1 * 1,000 * 4 * 10^-6 * 125 = 0.5
		
		PORTDbits.RD4 = 0;
		PORTDbits.RD3 = 0;		// turn off RB3
		PORTDbits.RD2 = 0;		// turn off RB2
		PORTDbits.RD1 = 0;		// turn off RB1
		PORTDbits.RD0 = 0;		// turn off RB0
		
		Delay1KTCYx(125);		// TCY = 4 us, delay = 1 * 1,000 * 4 * 10^-6 * 125 = 0.5
		
	}
}
