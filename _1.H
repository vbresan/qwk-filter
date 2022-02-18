#ifndef	__1_H_
#define	__1_H_

#define B__1V   B_R
#define B__1M   B_r
#define B__1ALT B_ALTr
#define B__2V   B_T
#define B__2M   B_t
#define B__2ALT B_ALTt
#define B__3V   B_S
#define B__3M   B_s
#define B__3ALT B_ALTs

#define __1 { gotoxy(_1_NUM+2,3);cputs(" F");textcolor(RED);cputs("r");textcolor(BLACK);cputs("om    "); }
#define __2 { gotoxy(_1_NUM+2,4);textcolor(RED);cputs(" T");textcolor(BLACK);cputs("o      "); }
#define __3 { gotoxy(_1_NUM+2,5);textcolor(RED);cputs(" S");textcolor(BLACK);cputs("ubject "); }

#define DODAJ { textcolor(RED);cputs(" D");textcolor(BLACK);cputs("odaj ");   }
#define BRISI { textcolor(RED);cputs(" I");textcolor(BLACK);cputs("zbrisi "); }

#endif