#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Header.h"
uint16_t waarde1;
uint16_t waarde2;
uint32_t counts;
int ultasoon_nr;

ISR(TIMER1_COMPA_vect)
{
    TCNT1 = 0;
    Grote_klok++;
}

ISR (TIMER4_CAPT_vect)
{
    if (TCCR4B & (1<<ICES4)) // On rising edge
    {
        TCCR4B &= ~(1<<ICES4); // Next time detect falling edge
        waarde1 = TCNT4; // Save current count
    }
    else // On falling edge
    {
        TCCR4B |= 0; // geen interrupts meer
        waarde2 = TCNT4; // Save current count
        counts = (uint32_t)waarde1 - (uint32_t)waarde2;
		if ((ultasoon_nr = 3))
		{
        ultrasoon = (counts/2)*0.01715; //snelheid van geluid keer de tijd die de klok vertegenwoordigd (16/8 = 2 1/2E6= 5E-7)
		}
		if ((ultasoon_nr = 2))
		{
        ultrasoon_links = (counts/2)*0.01715; //snelheid van geluid keer de tijd die de klok vertegenwoordigd (16/8 = 2 1/2E6= 5E-7)
		}
		if ((ultasoon_nr = 1))
		{
        ultrasoon_rechts = (counts/2)*0.01715; //snelheid van geluid keer de tijd die de klok vertegenwoordigd (16/8 = 2 1/2E6= 5E-7)
		}
    }
}

ISR(TIMER4_COMPA_vect)
{
    PORTC = 0;
    TIMSK4 = (1 << ICIE4);
    TCCR4B |= (1 << ICES4);
}

ISR(TIMER2_OVF_vect)
{
    TIMSK4 = (1<<OCIE4A);
    PORTA |= (1<<PC5);
    TCNT4 =0;
    OCR4A = 20000;
	ultasoon_nr = 3; //VOOR
}

ISR(TIMER2_COMPA_vect)
{
    TIMSK4 = (1<<OCIE4A);
    PORTA |= (1<<PC6); //LINKS
    TCNT4 =0;
    OCR4A = 20000;
	ultasoon_nr = 2;
}

ISR(TIMER2_COMPB_vect)
{
    TIMSK4 = (1<<OCIE4A);
    PORTA |= (1<<PC5); //RECHTS
    TCNT4 =0;
    OCR4A = 20000;
	ultasoon_nr = 1;
}

ISR(TIMER0_OVF_vect)
{
    if (OCR0A == 0 && OCR0B == 0)
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
    TIMSK1 = (1<<OCIE0A);
    OCR1A = 6250; //0.1 van een seconde dus kan gebruikt worden om een grote klok te maken voor 25.5 seconden

    // Use mode 0, clkdiv = 1024   klok 2 globale trigger
    TCCR2A = 0;
    TCCR2B = (1<<CS22) | (0<<CS21) | (1<<CS20);
    OCR2A = 85;
    OCR2B = 170;
    TIMSK2 = (1<<OCIE2B) | (1<<OCIE2A) | (1<<TOIE2);

    // Use mode 0, clkdiv = 8 klok 4 ultrasoon
    TCCR4A = 0;
    TCCR4B = (0<<CS42) | (1<<CS41) | (0<<CS40);


    // Interupts geactiveerd
    sei();
}

void motor (signed int Af, signed int Bf)
{
    if(Af < 0)
    {
        PORTJ |= (1<<PJ0);
        OCR0A = Af;
    }
    if (Bf < 0)
    {
        PORTJ |= (1<<PJ1);
        OCR0B = Bf;
    }
    if (Af > 0)
    {
        PORTJ &= ~(1<<PJ0);
        OCR0A = Af;
    }
    if (Bf > 0)
    {
        PORTJ &= ~(1<<PJ1);
        OCR0B = Bf;
    }
}
