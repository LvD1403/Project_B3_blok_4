Void Init (void)
{
    DDRE |= (1 << PE5); //pwm links
    DDRE |= (1 << PE4); //pwm rechts
    init_motor()
    DDRA |= (1 << PA0); //nadering links
    DDRA |= (1 << PA1); //nadering rechts
}

rechte_lijn(void)
{
    while (1)
    {
        motor(122,122)
        if (PINA &(1 << PA0))
        {
            for (int a = 120; (PINA &(1 << PA0)) ; a++;)
            {
                motor (a,100)
                _delay_ms(20);
            }
        }
        if (PINA &(1 << PA1))
        {
            for (int a = 120; (PINA &(1 << PA1)) ; a++;)
            {
                motor (a,100)
                _delay_ms(20);
            }
        }
    }
}
