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
    rechte_lijnlinks();
    return 0;
}
