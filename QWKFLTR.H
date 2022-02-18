#ifndef _QWKFLTR_H_
#define	_QWKFLTR_H_

#include <bios.h>        // bioskey

#include "mouse.h"
#include "mytxt.h"
#include "cfg.h"


#define _1_NUM 2
#define _2_NUM 10
#define _6_NUM 73

#define A_1 "F"
#define A_2 "n"
#define A_6 "K"

#define B_1V   B_F
#define B_1M   B_f
#define B_1ALT B_ALTf
#define B_2V   B_N
#define B_2M   B_n
#define B_2ALT B_ALTn
#define B_6V   B_K
#define B_6M   B_k
#define B_6ALT B_ALTk

#define _1 { gotoxy(_1_NUM,1);textcolor(RED);cputs(" F");textcolor(BLACK);cputs("ilter "); }
#define _2 { gotoxy(_2_NUM,1);textcolor(BLACK);cputs(" Ko");textcolor(RED);cputs("n");textcolor(BLACK);cputs("figuracija "); }
#define _6 { gotoxy(_6_NUM,1);textcolor(RED);cputs(" K");textcolor(BLACK);cputs("raj! "); }

#define WORKDIR  "work"
#define CONFDIR  "conf"
#define CFGFILE  "conf\\qwkfltr.cfg"
#define FROMFILE "conf\\from.dat"
#define TOFILE   "conf\\to.dat"
#define SUBJFILE "conf\\subject.dat"
#define FLRFILE  "conf\\filtrano.dat"
#define NQWKFILE "conf\\ne_qwk.dat"

#define CFGTXT  "; QWKFLTR.CFG\n; QWK Filter konfiguracijska datoteka\n;\n; duzina pojedine linije mora biti manja ili jednaka 80 znakova!\n; duzina stringa pojedine varijable mora biti manja ili jednaka 54 znaka!\n;\n;\n; QwkDir - direktorij s QWK paketima\n;\n; Arh    - arhiver\n; DeArh  - dearhiver\n\n\n; DIREKTORIJI PAKETA\n\nQwkDir = \n\n\n; PATHOVI EKSTERNIH PROGRAMA\n\nArh   = PKZIP !\nDeArh = PKZNZIP !\n"


#define DIRLENGHT 56


void osnovna();
void sjencenje();
char Prozor_1();
char Prozor_2();
char Prozor_6();

#endif