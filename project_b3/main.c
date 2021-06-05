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
        rechte_lijnlinks();
        bocht_links();
		rechte_lijnbeide();
        bocht_rechts();
		rechte_lijnbeide();
		bocht_links();
		rechte_lijnrechts();
    }
    return 0;
}
