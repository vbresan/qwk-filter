/* +++Date last modified: 03-Nov-1996 */

/*
**  SNIPMATH.H - Header file for SNIPPETS math functions and macros
*/

#ifndef SNIPMATH__H
#define SNIPMATH__H

#include <math.h>
#include "sniptype.h"
#include "round.h"

/*
**  Callable library functions begin here
*/

void    SetBCDLen(int n);                             /* Bcd.C          */
long    BCDtoLong(char *BCDNum);                      /* Bcd.C          */
void    LongtoBCD(long num, char BCDNum[]);           /* Bcd.C          */
DWORD   ncomb1 (int n, int m);                        /* Combin.C       */
DWORD   ncomb2 (int n, int m);                        /* Combin.C       */
void    SolveCubic(double a, double b, double c,      /* Cubic.C        */
                  double d, int *solutions,
                  double *x);
DWORD   dbl2ulong(double t);                          /* Dbl2Long.C     */
long    dbl2long(double t);                           /* Dbl2Long.C     */
double  dround(double x);                             /* Dblround.C     */

/* Use #defines for Permutations and Combinations     -- Factoryl.C     */

#define log10P(n,r) (log10factorial(n)-log10factorial((n)-(r)))
#define log10C(n,r) (log10P((n),(r))-log10factorial(r))

double  log10factorial(double N);                     /* Factoryl.C     */

double  fibo(unsigned short term);                    /* Fibo.C         */
double  frandom(int n);                               /* Frand.C        */
double  ipow(double x, int n);                        /* Ipow.C         */
int     ispow2(int x);                                /* Ispow2.C       */
long    double ldfloor(long double a);                /* Ldfloor.C      */
float   MSBINToIEEE(float f);                         /* Msb2Ieee.C     */
float   IEEEToMSBIN(float f);                         /* Msb2Ieee.C     */
int     perm_index (char pit[], int size);            /* Perm_Idx.C     */
int     round_div(int n, int d);                      /* Rnd_Div.C      */
long    round_ldiv(long n, long d);                   /* Rnd_Div.C      */
double  rad2deg(double rad);                          /* Rad2Deg.C      */
double  deg2rad(double deg);                          /* Rad2Deg.C      */

#include "pi.h"
#ifndef PHI
 #define PHI      ((1.0+sqrt(5.0))/2.0)         /* the golden number    */
 #define INV_PHI  (1.0/PHI)                     /* the golden ratio     */
#endif

/*
**  File: ISQRT.C
*/

struct int_sqrt {
      unsigned sqrt,
               frac;
};

void usqrt(unsigned long x, struct int_sqrt *q);


#endif /* SNIPMATH__H */
