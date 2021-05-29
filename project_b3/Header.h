#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
float ultrasoon;
float ultrasoon_links;
float ultrasoon_rechts;
int Grote_klok;

//overige functie's
void rechte_lijn (void);
void bocht_links (void);
void bocht_rechts (void);
void init (void);

//PwM_signalen
void motor (signed int Af, signed int Bf);
void init_motor (void);

#endif // HEADER_H_INCLUDED
