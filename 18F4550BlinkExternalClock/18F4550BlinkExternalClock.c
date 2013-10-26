// 18F4550BlinkExternalClock.c

// chip config ////////////////////////////////////////////////////////////////////////////////////
					// clock options, see 18F4550 data sheet figure 2-1 "clock diagram" for explanation
#pragma config PLLDIV = 5				// 20 MHz external clock / PLL prescaler value of 5 = 4 MHz required input to PLL circuit
#pragma config CPUDIV = OSC1_PLL2		// non-PLL postscale / 1 OR PLL postscale / 2 for CPU clock speed, depending on FOSC setting below
#pragma config USBDIV = 2				// USB clock source = 96 MHz PLL source / 2, (full-speed USB mode)

						// if desired, could change this line to "FOSC = HS" & "oscillator postscaler" gate would be used 
						// (not the "PLL postscaler" gate), CPU speed would be 20MHz, USB circuitry would still receive 48Mhz clock
#pragma config FOSC = HSPLL_HS			// use high-speed external osc crystal, & use PLL postscaler gate to feed CPU (CPU speed = 48 MHz)

					// now the other less confusing options . . .
#pragma config FCMEN = OFF				// fail-safe clock monitor disabled
#pragma config IESO = OFF				// internal / external osc switchover bit disabled
#pragma config PWRT = OFF				// power-up timer disabled
#pragma config BOR = OFF				// brown-out reset disabled in hardware & software
#pragma config BORV = 3					// brown-out reset voltage bits, does not matter since brown-out is disabled 
#pragma config VREGEN = ON				// USB voltage regulator enabled (If using USB, capacitor goes on pin 18 (VUSB))
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
	
	int i;
	
	ADCON1bits.PCFG3 = 1;			// set all AN pins to digital I/O
	ADCON1bits.PCFG2 = 1;			//
	ADCON1bits.PCFG1 = 1;			//
	ADCON1bits.PCFG0 = 1;			//
	
	TRISBbits.TRISB3 = 0;			// set RB3 to output
	TRISBbits.TRISB2 = 0;			// set RB2 to output
	TRISBbits.TRISB1 = 0;			// set RB1 to output
	TRISBbits.TRISB0 = 0;			// set RB0 to output
	
	PORTBbits.RB3 = 0;				// init output pins to off
	PORTBbits.RB2 = 0;
	PORTBbits.RB1 = 0;
	PORTBbits.RB0 = 0;
	
	while(1) {
		PORTBbits.RB3 = 1;		// turn on RB3
		PORTBbits.RB2 = 1;		// turn on RB2
		PORTBbits.RB1 = 1;		// turn on RB1
		PORTBbits.RB0 = 1;		// turn on RB0
		
		for(i=0;i<5;i++) Delay10KTCYx(120);		// TCY = 0.08333 us, delay = 10 * 1,000 * 0.08333 * 10^-6 * 120 * 5 = 0.5 sec
		
		PORTBbits.RB3 = 0;		// turn off RB3
		PORTBbits.RB2 = 0;		// turn off RB2
		PORTBbits.RB1 = 0;		// turn off RB1
		PORTBbits.RB0 = 0;		// turn off RB0
		
		for(i=0;i<5;i++) Delay10KTCYx(120);		// TCY = 0.08333 us, delay = 10 * 1,000 * 0.08333 * 10^-6 * 120 * 5 = 0.5 sec
	}

}
