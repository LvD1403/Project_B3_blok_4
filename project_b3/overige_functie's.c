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
    DDRA &= ~(1 << PD0);    //Nadering links
    DDRA &= ~(1 << PD1);    //Nadering rechts
	DDRL &= ~(1 << PL0);    //Ultrasoon echopin
	DDRA |= (1 << PA3);     //Ultrasoon trigger
	DDRC |= (1<<PC7);       //Ultrasoon rechts 30
	DDRC |= (1<<PC6);       //Ultrasoon links 31
	DDRC |= (1<<PC5);       //Ultrasoon voor 32
}

void rechte_lijn(void)
{
	int vlag;
	TCNT1 = 0;
	Grote_klok = 0;
   // while ((ultrasoon <= 37) && (vlag == 1))
   // {
	//	if (((ultrasoon_rechts > 10) && (ultrasoon_rechts < 37)) || ((ultrasoon_links > 10) && (ultrasoon_links < 37)))
		//{
        //if ((!(PINA & (1 << PA0))) && (!(PINA & (1 << PA1))))
        //{
        //        motor(170,170);
        //}
        if (PINA &(1 << PA0))
        {
                motor (170,160);
               // _delay_ms(40);
        }
        if (PINA &(1 << PA1))
        {
                motor (160,170);
                //_delay_ms(40);
        }

	//	if (Grote_klok >= 180)//stel de boog begint te laat dan kun je de waarde veranderen nu 18.0 seconden
	//	{
		//	vlag = 1;
	//	}
	//	if ((ultrasoon <= 20) && (vlag != 1))
	//	{
	//		motor(0,0);
	//	}
	//	}
	//	else
	//	{
	//		motor(0,0);
		//	PORTH |= (1 << PH4);
			//_delay_ms(500);
			//PORTH &= ~(1 << PH4);
//		}

    //}
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
