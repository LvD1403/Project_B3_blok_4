/*
 */
#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Header.h"




int main(void)
{
 Init();
    while(1)
    {
       rechte_lijn();
    }

    return 0;
}
