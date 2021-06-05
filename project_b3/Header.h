#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
float ultrasoon;
uint16_t Ir_links;
uint16_t Ir_rechts;
int Grote_klok;

//overige functie's
void rechte_lijn (void);
void rechte_lijnlinks (void);
void rechte_lijnrechts (void);
void bocht_links (void);
void bocht_rechts (void);
void init (void);
void error (void);

//PwM_signalen
void motor (int Af, int Bf);
void init_motor (void);

#endif // HEADER_H_INCLUDED
