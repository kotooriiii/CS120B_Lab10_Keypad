/*	Author: Carlos Miranda cmira039@ucr.edu
 *  Partner(s) Name: n/a
 *	Lab Section: 23
 *	Assignment: Lab #10  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo Link: 
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
/*
	Bit start
*/ 

// Permission to copy is granted provided that this header remains intact. 
// This software is provided with no warranties.

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Functionality - Sets bit on a PORTx
//Parameter: Takes in a uChar for a PORTx, the pin number and the binary value 
//Returns: The new value of the PORTx
unsigned char SetBit(unsigned char pin, unsigned char number, unsigned char bin_value) 
{
	return (bin_value ? pin | (0x01 << number) : pin & ~(0x01 << number));
}

////////////////////////////////////////////////////////////////////////////////
//Functionality - Gets bit from a PINx
//Parameter: Takes in a uChar for a PINx and the pin number
//Returns: The value of the PINx
unsigned char GetBit(unsigned char port, unsigned char number) 
{
	return ( port & (0x01 << number) );
}

/* 
	Bit end 
*/

/* 
	Keyboard start
*/

// Permission to copy is granted provided that this header remains intact. 
// This software is provided with no warranties.

////////////////////////////////////////////////////////////////////////////////

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port C
// Keypad arrangement
//        Px4 Px5 Px6 Px7
//	  col 1   2   3   4
//  row  ______________
//Px0 1	| 1 | 2 | 3 | A
//Px1 2	| 4 | 5 | 6 | B
//Px2 3	| 7 | 8 | 9 | C
//Px3 4	| * | 0 | # | D


// Keypad Setup Values
#define KEYPADPORT PORTC
#define KEYPADPIN  PINC
#define ROW1 0
#define ROW2 1
#define ROW3 2
#define ROW4 3
#define COL1 4
#define COL2 5
#define COL3 6
#define COL4 7

////////////////////////////////////////////////////////////////////////////////
//Functionality - Gets input from a keypad via time-multiplexing
//Parameter: None
//Returns: A keypad button press else '\0'
unsigned char GetKeypadKey() {
	
	unsigned char currentKeypadKey = '\0';

	// Check keys in col 1
	KEYPADPORT = SetBit(0xFF,COL1,0); // Set Px4 to 0; others 1
	asm("nop"); // add a delay to allow PORTx to stabilize before checking
	if ( GetBit(~KEYPADPIN,ROW1) ) { 
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '1';
		}
		else
		{
			return '\0';
		}
	}
	if ( GetBit(~KEYPADPIN,ROW2) ) { 
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '4';
		}
		else
		{
			return '\0';
		}	
	}
	if ( GetBit(~KEYPADPIN,ROW3) ) { 
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '7';
		}
		else
		{
			return '\0';
		}	
	}
	if ( GetBit(~KEYPADPIN,ROW4) ) { 	
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '*';
		}
		else
		{
			return '\0';
		} 
	}

	// Check keys in col 2
	KEYPADPORT = SetBit(0xFF,COL2,0); // Set Px5 to 0; others 1
	asm("nop"); // add a delay to allow PORTx to stabilize before checking
	if ( GetBit(~KEYPADPIN,ROW1) ) { 
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '2';
		}
		else
		{
			return '\0';
		}	
	}
	if ( GetBit(~KEYPADPIN,ROW2) ) { 
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '5';
		}
		else
		{
			return '\0';
		}
	}
	if ( GetBit(~KEYPADPIN,ROW3) ) { 
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '8';
		}
		else
		{
			return '\0';
		}
	}
	if ( GetBit(~KEYPADPIN,ROW4) ) {
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '0';
		}
		else
		{
			return '\0';
		}
	}

	// Check keys in col 3
	KEYPADPORT = SetBit(0xFF,COL3,0); // Set Px6 to 0; others 1
	asm("nop"); // add a delay to allow PORTx to stabilize before checking
	if ( GetBit(~KEYPADPIN,ROW1) ) {
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '3';
		}
		else
		{
			return '\0';
		}
	}
	if ( GetBit(~KEYPADPIN,ROW2) ) {
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '6';
		}
		else
		{
			return '\0';
		}
	}
	if ( GetBit(~KEYPADPIN,ROW3) ) { 
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '9';
		}
		else
		{
			return '\0';
		}	
	}
	if ( GetBit(~KEYPADPIN,ROW4) ) {
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = '#';
		}
		else
		{
			return '\0';
		}
	}

	// Check keys in col 4
	KEYPADPORT = SetBit(0xFF,COL4,0); // Set Px7 to 0; others 1
	asm("nop"); // add a delay to allow PORTx to stabilize before checking
	if (GetBit(~KEYPADPIN,ROW1) ) {
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = 'A';
		}
		else
		{
			return '\0';
		}
	}
	if (GetBit(~KEYPADPIN,ROW2) ) {
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = 'B';
		}
		else
		{
			return '\0';
		}		
	}
	if (GetBit(~KEYPADPIN,ROW3) ) { 
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = 'C';
		}
		else
		{
			return '\0';
		}
	}
	if (GetBit(~KEYPADPIN,ROW4) ) { 
		if(currentKeypadKey  == '\0')
		{
			currentKeypadKey = 'D';
		}
		else
		{
			return '\0';
		}
	}
	
	return currentKeypadKey;
}

/* 
	Keyboard end 
*/

/*
	Timer start
*/

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerISR()
{
	TimerFlag = 1;
}

void TimerOff()
{
	TCCR1B = 0x00;
}

void TimerOn()
{
	TCCR1B = 0x0B;

	OCR1A = 125;

	TIMSK1 = 0x02;

	TCNT1 = 0;

	_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80;

}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

/*
	Timer end
*/

/*
	Shared variables
*/

	//KeypadSM
	unsigned char currentKey = '\0';
	
	//PORTB temp
	unsigned char currPORTB = 0x00;
	
	unsigned char code[5] = {'1','2','3','4','5'};
	unsigned char codeSize = 0x05;
	unsigned char codeIndex = 0x00;
	unsigned char isSuccessful = 0x00;
/*
	End Shared variables
*/

typedef struct task
{
	signed char state; //current state
	unsigned long int period; //current task period
	unsigned long int elapsedTime; //elapsed time since last tick
	int (*TickFct)(int); //task tick func
} task;

enum KeypadListenerSM { KL_INIT, KL_LISTEN};
enum SequenceSM { S_INIT, S_WAIT, S_CLEAN, S_READ_CHAR, S_WAIT_RELEASE, S_RELEASE, S_OPEN};
enum LockInsideSM {LI_INIT, LI_LISTENER};

int keypadListenerSMTick(int state);
int sequenceSMTick(int state);
int lockInsideSMTick(int state);

int main(void) 
{
	
	DDRB = 0x3F; PORTB = 0x80;
	DDRC = 0xF0; PORTC = 0x0F;

	//Task initialization
	static task task0, task1, task2;
	task *tasks[] = {&task0,&task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	//Task state undefined
	const char undefined = -1;
	const long int gcd = 5;

	//Task 0 (KeypadListenerSM)
	task0.state = undefined;
	task0.period = 50;
	task0.elapsedTime = task0.period;
	task0.TickFct = &keypadListenerSMTick;
	
	//Task 1 (SequenceSM)
	task1.state = undefined;
	task1.period = 5;
	task1.elapsedTime = task1.period;
	task1.TickFct =&sequenceSMTick;
	
	//Task 2 (LockInsideSM)
	task2.state = undefined;
	task2.period = 25;
	task2.elapsedTime = task2.period;
	task2.TickFct = &lockInsideSMTick;
	
	TimerSet(gcd);	
	TimerOn();
	
	
	unsigned short i; //scheduler
	while(1) 
	{
		for(i = 0; i < numTasks; i++)
		{
			if(tasks[i]->elapsedTime ==  tasks[i]->period)
			{
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += gcd;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	return 1;
}

int keypadListenerSMTick(int state)
{
	switch(state)
	{
		case KL_INIT:
		state = KL_LISTEN;
		break;
		
		case KL_LISTEN:
		state = KL_LISTEN;
		break;
		
		default:
		state = KL_INIT;
		break;
	}
	
	switch(state)
	{
		case KL_INIT:
		break;
		
		case KL_LISTEN:
		currentKey = GetKeypadKey();
		break;
		
		default:
		break;
	}
	
	return state;
}

int sequenceSMTick(int state)
{
	switch(state)
	{
		case S_INIT:
		state = S_WAIT;
		break;
		
		case S_WAIT:
		if(currentKey == '#')
		{
			state = S_CLEAN;
		}
		else 
		{
			state = S_WAIT;
		}
		break;
		
		case S_CLEAN:
		if(currentKey == '#' || currentKey == '\0')
		{
			state = S_CLEAN;
		}
		else
		{
			state = S_READ_CHAR;
		}
		break;
		
		case S_READ_CHAR:
		
		if(currentKey == '#')
		{
			state = S_CLEAN;
		}
		else if(!isSuccessful)
		{
			state = S_WAIT;
		} else 
		{
			state = S_WAIT_RELEASE;
		}			
		break; 
		
		case S_WAIT_RELEASE:
		if(currentKey == '#')
		{
			state = S_CLEAN;
		}
		else if(currentKey == '\0')
		{
			state = S_RELEASE;
		}
		break;
		
		case S_RELEASE:
		if(currentKey == '#')
		{
			state = S_CLEAN;
		}
		else if(codeIndex >= codeSize)
		{
			state = S_OPEN;
		}
		else if (currentKey != '\0')
		{
			state = S_READ_CHAR;
		}
		break;
		
		
		case S_OPEN:
		if(currentKey == '#')
		{
			state = S_CLEAN;
		} 
		else 
		{
			state = S_WAIT;
		}
		break;
		
		default:
		state = S_INIT;
		break;
	}

	switch(state)
	{
		case S_INIT:
		break;
		
		case S_WAIT:
		break;
		
		case S_CLEAN:
		codeIndex = 0x00;
		break;
		
		case S_READ_CHAR:
		if(currentKey == code[codeIndex])
		{
			codeIndex++;
			isSuccessful = 1;
		}
		else 
		{
			isSuccessful = 0;
		}

		break; 
		
		case S_WAIT_RELEASE:
		break;
		
		case S_RELEASE:

		break;
		
		case S_OPEN:
		currPORTB = SetBit(currPORTB, 0, 1);
		PORTB = currPORTB;
		break;
		
		default:
		break;
	}
	
	return state;
}

int lockInsideSMTick(int state)
{
	switch(state)
	{
		case LI_INIT:
		state = LI_LISTENER;
		break;
		
		case LI_LISTENER:
		state = LI_LISTENER;
		break;
		
		default:
		state = LI_INIT;
		break;
	}
	
	switch(state)
	{
		case LI_INIT:
		break;
		
		case LI_LISTENER:
		if(GetBit(~PINB, 7))
		{
			currPORTB = SetBit(currPORTB, 0, 0);
			PORTB = currPORTB;		
		}
		break;
		
		default:
		break;
	}
	return state;
}



	




