#ifndef PSEUDOALEATORIO_H
#define PSEUDOALEATORIO_H
/***** GENERADOR DE NUMEROS PSEUDOALETORIOS *****/
/* used in random number generator below */
#define MASK 2147483647
#define PRIME 65539
#define SCALE 0.4656612875e-9

long Seed;

/*******************************************************************/
/*  Rand genera un numero real pseudoaleatorio entre 0 y 1,        */
/*  excluyendo el 1.						   */
/*  Randint genera un numero entero entre low y high, ambos 	   */
/*  incluidos.	   						   */
/*  Randfloat genera un numero real entre low y high, incluido low */
/*  y no incluido high                                             */
/*******************************************************************/

#define Rand()  (( Seed = ( (Seed * PRIME) & MASK) ) * SCALE )

#define Randint(low,high) ( (int) (low + (high-(low)+1) * Rand()))

#define Randfloat(low,high) ( (low + (high-(low))*Rand()))

#endif // PSEUDOALEATORIO_H
