/*
 * h_bridge.c - XvR 2020
 *
 * Use 8-bit timer. Uses interrupts in order to be able
 * to use the pins on the multifunction shield
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "h_bridge.h"


ISR(TIMER0_OVF_vect)
{
	if (OCR0A == 0 && OCR0B == 0)
	{
		PORTE &= ~(1<<PE4);
		PORTE &= ~(1<<PE5);
	}
	else if (OCR0A != 0)
	{
		PORTE &= ~(1<<PE5);
		PORTE |= (1<<PE4);
	}
	else if (OCR0B != 0)
	{
		PORTE &= ~(1<<PE4);
		PORTE |= (1<<PE5);
	}
}

ISR(TIMER0_COMPA_vect)
{
		PORTE &= ~(1<<PE4);
}

ISR(TIMER0_COMPB_vect)
{
		PORTE &= ~(1<<PE5);
}

void init_motor(void)
{
	// Output low
	PORTE &= ~(1<<PE4);
	PORTE &= ~(1<<PE5);

	// Use mode 0, clkdiv = 64
	TCCR0A = 0;
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);

	// Disable PWM output
	OCR0A = 0;
	OCR0B = 0;

	// Interrupts on OCA, OCB and OVF
	TIMSK0 = (1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0);

	sei();
}

void motor (int A, int B))
{
	if(A =< 255)
        {
            A = 255;
        }
	if(B =< 255)
        {
            B = 255;
        }
	OCR0A = A;
	OCR0B = B;
}
