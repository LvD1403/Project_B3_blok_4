#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Header.h"

void init (void)
{
    DDRE |= (1 << PE3);     //pwm links 5
    DDRE |= (1 << PE4);     //pwm rechts 2
    DDRH |= (1 << PH4);     //lampje 7
    DDRE |= (1 << PJ1);     //motorrichting links 14
    DDRE |= (1 << PJ0);     //motorrichting rechts 15
    DDRA &= ~(1 << PD0);    //Nadering links 21
    DDRA &= ~(1 << PD1);    //Nadering rechts 20
    DDRL &= ~(1 << PL0);    //Ultrasoon echopin 49
    DDRC |=  (1 << PC5);    //Ultrasoon trigger 32
    DDRF &= ~(1 << PF7);    //Ir sensor Analoog 7 links
    DDRF &= ~(1 << PF6);    //Ir sensor Analoog 6 rechts
    DDRF &= ~(1 << PF0);    //Noodstop

}

void rechte_lijnrechts(void)
{
    int vlag = 1;
    TCNT1 = 0;
    Grote_klok = 0;
    while (vlag) //(ultrasoon <= 37)
    {
        if  (!(PINF && (1 << PF0)))
        {
            motor(0,0);
            int waarde6 = Grote_klok;
            _delay_ms(20);
            Grote_klok = waarde6;
        }
        else
        {
            if (ultrasoon > 20)
            {
                if (((Ir_links < 265))) //boomdectectie
                {
                    if ((!(PINA & (1 << PA0))) && (!(PINA & (1 << PA1))))
                    {
                        motor(170,170);
                    }
                    if (PINA &(1 << PA0))
                    {
                        motor (170,0);
                        _delay_ms(40);
                    }
                    if (PINA &(1 << PA1))
                    {
                        motor (0,170);
                        _delay_ms(40);
                    }
                    if (Grote_klok >= 180)//stel de boog begint te laat dan kun je de waarde veranderen nu 18.0 seconden
                    {
                        vlag = 0;
                    }
                }
                else
                {
                    int waarde = Grote_klok;
                    motor (0,0);
                    PORTH |=  (1 << PH4);
                    _delay_ms(500);
                    PORTH &= ~(1 << PH4);
                    Grote_klok = waarde;
                    motor(170,170);
                    _delay_ms(100);
                }
            }
            else
            {
                int waarde = Grote_klok;
                motor (0,0);
                PORTH |=  (1 << PH4);
                _delay_ms(500);
                PORTH &= ~(1 << PH4);
                Grote_klok = waarde;
            }
        }
    }
}

void rechte_lijnlinks(void)
{
    int vlag = 1;
    TCNT1 = 0;
    Grote_klok = 0;
    while (vlag) //(ultrasoon <= 37)
    {
        if  (!(PINF && (1 << PF0)))
        {
            motor(0,0);
            int waarde6 = Grote_klok;
            _delay_ms(20);
            Grote_klok = waarde6;
        }
        else
        {
            if (ultrasoon > 20)
            {
                if (((Ir_rechts < 265))) //boomdectectie
                {
                    if ((!(PINA & (1 << PA0))) && (!(PINA & (1 << PA1))))
                    {
                        motor(170,170);
                    }
                    if (PINA &(1 << PA0))
                    {
                        motor (170,0);
                        _delay_ms(40);
                    }
                    if (PINA &(1 << PA1))
                    {
                        motor (0,170);
                        _delay_ms(40);
                    }
                    if (Grote_klok >= 180)//stel de boog begint te laat dan kun je de waarde veranderen nu 18.0 seconden
                    {
                        vlag = 0;
                    }
                }
                else
                {
                    int waarde = Grote_klok;
                    motor (0,0);
                    PORTH |=  (1 << PH4);
                    _delay_ms(500);
                    PORTH &= ~(1 << PH4);
                    Grote_klok = waarde;
                    motor(170,170);
                    _delay_ms(100);
                }
            }
            else
            {
                int waarde = Grote_klok;
                motor (0,0);
                PORTH |=  (1 << PH4);
                _delay_ms(500);
                PORTH &= ~(1 << PH4);
                Grote_klok = waarde;
            }
        }
    }
}


void rechte_lijnbeide(void)
{
    int vlag = 1;
    TCNT1 = 0;
    Grote_klok = 0;
    while (vlag) //(ultrasoon <= 37)
    {
        if  (!(PINF && (1 << PF0)))
        {
            motor(0,0);
            int waarde6 = Grote_klok;
            _delay_ms(20);
            Grote_klok = waarde6;
        }
        else
        {
            if (ultrasoon > 20)
            {
                if (((Ir_links < 265) && (Ir_rechts < 265))) //boomdectectie
                {
                    if ((!(PINA & (1 << PA0))) && (!(PINA & (1 << PA1))))
                    {
                        motor(170,170);
                    }
                    if (PINA &(1 << PA0))
                    {
                        motor (170,0);
                        _delay_ms(40);
                    }
                    if (PINA &(1 << PA1))
                    {
                        motor (0,170);
                        _delay_ms(40);
                    }
                    if (Grote_klok >= 180)//stel de boog begint te laat dan kun je de waarde veranderen nu 18.0 seconden
                    {
                        vlag = 0;
                    }
                }
                else
                {
                    int waarde = Grote_klok;
                    motor (0,0);
                    PORTH |=  (1 << PH4);
                    _delay_ms(500);
                    PORTH &= ~(1 << PH4);
                    Grote_klok = waarde;
                    motor(170,170);
                    _delay_ms(100);
                }
            }
            else
            {
                int waarde = Grote_klok;
                motor (0,0);
                PORTH |=  (1 << PH4);
                _delay_ms(500);
                PORTH &= ~(1 << PH4);
                Grote_klok = waarde;
            }
        }
    }
}

    void bocht_links (void)
    {
        int vlag;
        TCNT1 = 0;
        Grote_klok = 0;
        while ((vlag == 1))// && (PINA &(1 << PA0))
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
    while ((vlag == 1)) //(PINA &(1 << PA0)) &&
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
