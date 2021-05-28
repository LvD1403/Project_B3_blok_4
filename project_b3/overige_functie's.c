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
	int vlag;
	TCNT1 = 0;
	Grote_klok = 0;
    while ((ultrasoon <= 37) && (vlag == 1))
    {
        motor(170,170);
        if (PINA &(1 << PA0))
        {
            for (int a = 170;PINA &(1 << PA0); a++)
            {
                motor (a,160);
                _delay_ms(40);
            }
        }
        if (PINA &(1 << PA1))
        {
            for (int a = 170;(PINA &(1 << PA1)); a++)
            {
                motor (a,160);
                _delay_ms(40);
            }
        }
		if (Grote_klok >= 180)//stel de boog begint te laat dan kun je de waarde veranderen nu 18.0 seconden
		{
			vlag = 1;
		}
		if ((ultrasoon <= 37) && (vlag != 1))
		{
			motor(0,0);
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
		//motor(,); //bocht naar links maken
		if ((PINA &(1 << PA0)) && (Grote_klok <=)) //waarde
		{
			error();
		}
		//if (Grote_klok >= 180)
		//{

		//}
	}
}

void bocht_rechts (void)
{
	int vlag;
	TCNT1 = 0;
	Grote_klok = 0;
	while ((PINA &(1 << PA0)) && (vlag == 1))
	{
		//motor(,); //bocht naar rechts maken
		if ((PINA &(1 << PA0)) && (Grote_klok <=)) //waarde
		{
			error();
		}
		//if (Grote_klok >= 180)
		//{

		//}
		if ((ultrasoon <= 37) && (vlag != 1))
		{
			motor(0,0);
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
