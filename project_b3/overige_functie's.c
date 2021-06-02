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
	//DDRA |= (1 << PA3);     //Ultrasoon trigger 25
	DDRC |= (1<<PC7);       //Ultrasoon rechts 30
	DDRC |= (1<<PC6);       //Ultrasoon links 31
	DDRC |= (1<<PC5);       //Ultrasoon voor 32
}

void rechte_lijn(void)
{
	int vlag;
	TCNT1 = 0;
	Grote_klok = 0;
    while (vlag == 1) //(ultrasoon <= 37)
    {
		//if (((ultrasoon_rechts > 0) && (ultrasoon_rechts < 37)) || ((ultrasoon_links > 0) && (ultrasoon_links < 37)))
		//{

        if ((!(PINA & (1 << PA0))) && (!(PINA & (1 << PA1))))
            {
                motor(170,170);
            }
        if (PINA &(1 << PA0))
            {
                motor (170,160);
                _delay_ms(40);
            }
        if (PINA &(1 << PA1))
        {
                motor (160,170);
                _delay_ms(40);
        }

		if (Grote_klok >= 180)//stel de boog begint te laat dan kun je de waarde veranderen nu 18.0 seconden
		{
			vlag = 1;
		}
		/*if ((ultrasoon <= 20) && (vlag != 1))
		{
			motor(0,0);
		}
		*/
		else
		{
			motor(0,0);

			_delay_ms(500);
			PORTH &= ~(1 << PH4);
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
