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
}

void rechte_lijn(void)
{
    while (1)
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
