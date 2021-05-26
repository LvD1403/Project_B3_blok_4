#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Header.h"

void init (void)
{
    DDRE |= (1 << PE5); //pwm links
    DDRE |= (1 << PE4); //pwm rechts
	DDRE |= (1 << PJ1); //motorrichting links
	DDRE |= (1 << PJ0); //motorrichting rechts
    DDRA &= ~(1 << PA0); //nadering links
    DDRA &= ~(1 << PA1); //nadering rechts
	DDRL &= ~(1 << PL0); //Ultrasoon echopin
	DDRA |= (1 << PA3); //Ultrasoon trigger
}

void rechte_lijn(void)
{
    while (ultrasoon <= 37)
    {
        motor(122,122);
        if (PINA &(1 << PA0))
        {
            for (int a = 120;PINA &(1 << PA0); a++)
            {
                motor (a,100);
                _delay_ms(20);
            }
        }
        if (PINA &(1 << PA1))
        {
            for (int a = 120;(PINA &(1 << PA1)); a++)
            {
                motor (a,100);
                _delay_ms(20);
            }
        }
    }
}

void bocht_links (void)
{
	    while (ultrasoon <= 19) //rij door totdat we op +/-
    {
        motor(20,20);
        if (PINA &(1 << PA0))
        {
            for (int a = 20;PINA &(1 << PA0); a++)
            {
                motor (a,15);
                _delay_ms(20);
            }
        }
        if (PINA &(1 << PA1))
        {
            for (int a = 20;(PINA &(1 << PA1)); a++)
            {
                motor (a,15);
                _delay_ms(20);
            }
        }
    }
	while (PINA &(1 << PA0))
	{
		motor(10,20); //bocht naar links maken
	}
	if(ultrasoon <= 24)
	{
	}

}

void bocht_rechts (void)
{



}
