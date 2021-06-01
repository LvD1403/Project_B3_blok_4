/*
 */
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Header.h"



int main(void)
{
    init();
    init_motor();
    while(1)
    {
        while ((!(PINA & (1 << PA0))) && (!(PINA & (1 << PA1))))
        {
            motor(170,170);
        }
            while (PINA &(1 << PA0))
            {
                motor (170,0);
                // _delay_ms(40);
            }
            while (PINA &(1 << PA1))
            {
                motor (0,170);
                //_delay_ms(40);
            }

        // motor(170,170);
        // rechte_lijn();
        //bocht_links();
        //rechte_lijn();
        // bocht_rechts();
    }
    return 0;
}
