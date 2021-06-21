#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Header.h"

void init (void)
{
    DDRE |= (1 << PE3);     //pwm links
    DDRE |= (1 << PE4);     //pwm rechts
    DDRH |= (1 << PH4);     //lampje
    DDRE |= (1 << PJ1);     //motorrichting links
    DDRE |= (1 << PJ0);     //motorrichting rechts
    DDRA &= ~(1 << PA0);    //Nadering links
    DDRA &= ~(1 << PA1);    //Nadering rechts
    DDRF |= (1 << PF0);     //testlampje
}

void rechte_lijn(void)
{
    //PORTF &= ~(1 << PF0);
    int vlag;
    TCNT1 = 0;
    Grote_klok = 0;
    while (vlag)
    {
        if ((!(PINA & (1 << PA0))) && (!(PINA & (1 << PA1))))
        {
            motor(170,170);
        }
        if (PINA &(1 << PA0))
        {
            motor (0,170);
        }
        if (PINA &(1 << PA1))
        {
            motor (170,0);
        }

        if (Grote_klok >= 180)//stel de boog begint te laat dan kun je de waarde veranderen nu 18.0 seconden
        {
            vlag = 1;
            PORTF = (1<<PF0);
        }
    }

}


void bocht_links (void)
{
    int vlag;
    TCNT1 = 0;
    Grote_klok = 0;
    while ((PINA &(1 << PA0)) && (vlag == 1))
    {
        motor(35,170); //bocht naar rechts maken
        if ((PINA &(1 << PA0)) && (Grote_klok <= 11.3)) //waarde
        {
            error();
        }
        if (Grote_klok >= 11.3)
        {
            vlag = 1;
        }

    }

}

void bocht_rechts (void)
{
    int vlag;
    TCNT1 = 0;
    Grote_klok = 0;
    while ((PINA &(1 << PA0)) && (vlag == 1))
    {
        motor(170,35); //bocht naar rechts maken
        if ((PINA &(1 << PA0)) && (Grote_klok <= 11.3)) //waarde
        {
            error();
        }
        if (Grote_klok >= 11.3)
        {
            vlag = 1;
        }

    }

}

void error (void) //om een probleem optelossen todat we een betere oplossing hebben of niet
{
    while (1)
    {
        motor(0,0);
        //error lampje knipperen?
    }
}
