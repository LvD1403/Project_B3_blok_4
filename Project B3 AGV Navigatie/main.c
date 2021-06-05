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
            rechte_lijn();
            bocht_links();
            rechte_lijn();
            bocht_rechts();
        }
    return 0;
}
