#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Header.h"

ISR(TIMER1_COMPA_vect)
{
    TCNT1 = 0;
    Grote_klok++;
}

ISR(TIMER0_OVF_vect)
{
    if (OCR0A == 0 && OCR0B == 0);
    {
        PORTE &= ~(1<<PE4);
        PORTE &= ~(1<<PE3);
    }
    if (OCR0A != 0)
    {
        PORTE |= (1<<PE4);
    }
    if (OCR0B != 0)
    {
        PORTE |= (1<<PE3);
    }
}

ISR(TIMER0_COMPA_vect)
{
    PORTE &= ~(1<<PE4);
}

ISR(TIMER0_COMPB_vect)
{
    PORTE &= ~(1<<PE3);
}

void init_motor (void)
{
    // Output low
    PORTE &= ~(1<<PE4);
    PORTE &= ~(1<<PE3);

    // Use mode 0, clkdiv = 64 klok 0 Pwm signalen
    TCCR0A = 0;
    TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);
    TIMSK0 = (1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0);
    OCR0A = 0;
    OCR0B = 0;

    // Use mode 0, clkdiv = 256 klok 1 globale klok
    TCCR1A = 0;
    TCCR1B = (1<<CS02) | (0<<CS01) | (0<<CS00);
    TIMSK1 = (1<<OCIE1A);
    OCR1A = 6250; //0.1 van een seconde dus kan gebruikt worden om een grote klok te maken voor 25.5 seconden

    // Interupts geactiveerd
    sei();
}

void motor (signed int Af, signed int Bf)
{
        OCR0A = Af;
        OCR0B = Bf;
}
