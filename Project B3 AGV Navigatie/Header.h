#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
int Grote_klok;

//overige functie's
void rechte_lijn (void);
void bocht_links (void);
void bocht_rechts (void);
void init (void);
void error (void);

//PwM_signalen
void motor (signed int Af, signed int Bf);
void init_motor (void);

#endif // HEADER_H_INCLUDED
