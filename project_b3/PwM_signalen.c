#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Header.h"
uint16_t waarde1;
uint16_t waarde2;
uint32_t counts;

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
        counts = (uint32_t)waarde2 - (uint32_t)waarde1;
        ultrasoon = (counts/2)*0.01715; //snelheid van geluid keer de tijd die de klok vertegenwoordigd (16/8 = 2 1/2E6= 5E-7)
    }
}

ISR(TIMER4_COMPA_vect)
{
    PORTC &= ~(1 << PC5);

    TIMSK4 |= (1 << ICIE4);
    TCCR4B |= (1 << ICES4);
}

ISR(TIMER2_OVF_vect)
{
    PORTC |= (1<<PC5);
    TCNT4 =0;
    OCR4A = 20;
}

ISR(TIMER2_COMPA_vect)
{
    if (ADCSRA & (1 << ADIF))
    {
        Ir_links= ADC; //waarde ir links wordt upgedate
    }
    ADMUX &= ~(1);// Analoog 6 wissel naar
    ADCSRA |= (1<<ADSC); //start convertion
}

ISR(TIMER2_COMPB_vect)
{
    if(ADCSRA & (1 << ADIF))
    {
        Ir_rechts = ADC; //waarde ir links wordt upgedate
    }
    ADMUX |= 7;
    ADCSRA |= (1<<ADSC); //start convertion
}

ISR(TIMER0_OVF_vect)
{
    if (OCR0A == 0)
    {
        PORTE &= ~(1<<PE4);
    }
    if (OCR0B == 0)
    {
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
    PORTE &= ~(1<<PE4); //motor laag
    PORTE &= ~(1<<PE3);

    //Use mode 0, clkdiv = 64 klok 0 Pwm signalen
    TCCR0A = 0;
    TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);
    TIMSK0 = (1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0);
    OCR0A = 0;
    OCR0B = 0;

    //Use mode 0, clkdiv = 256 klok 1 globale klok
    TCCR1A = 0;
    TCCR1B = (1<<CS12) | (0<<CS11) | (0<<CS10);
    TIMSK1 = (1<<OCIE0A);
    OCR1A = 6250; //0.1 van een seconde dus kan gebruikt worden om een grote klok te maken voor 25.5 seconden

    //Use mode 0, clkdiv = 1024   klok 2 globale trigger
    TCCR2A = 0;
    TCCR2B = (1<<CS22) | (0<<CS21) | (1<<CS20);
    TIMSK2 = (1<<OCIE2B) | (1<<OCIE2A) | (1<<TOIE2);
    OCR2A = 85;
    OCR2B = 170;

    //Use mode 0, clkdiv = 8 klok 4 ultrasoon
    TCCR4A = 0;
    TCCR4B = (0<<CS42) | (1<<CS41) | (0<<CS40);
    TIMSK4 |= (1<<OCIE4A);

// intialisatie ADC goed controleren vrij nieuw
    ADMUX =(0 << REFS1)|(1 << REFS0); //meet vanaf 0 volt
    ADCSRA = (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);//Division factor van 128
    ADCSRA |=(1 << ADEN); // ADC activeren

    // Interupts geactiveerd*/
    sei();
}

void motor (int Af, int Bf)
{
            OCR0A = Af;
            OCR0B = Bf;
}
