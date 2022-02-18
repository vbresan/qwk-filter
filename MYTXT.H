#ifndef	_MYTXT_H_
#define	_MYTXT_H_

/*---------------------------- header files -------------------------------*/

#include <conio.h>
#include <dir.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// strlen, strcmp, strcpy
#include <dos.h>		// sound, nosound, delay
#include <ctype.h>		// toupper



/*------------------------- logicke konstante -----------------------------*/

#define TRUE  1
#define FALSE 0

#define MAGIC 13		// specificna vrijednost za razne primjene



/*------------------------ numericke konstante ----------------------------*/

#define PRVI  1
#define DRUGI 2
#define TRECI 3
#define CVRTI 4
#define PETI  5
#define SESTI 6
#define SEDMI 7

#define UL 0			// UL - up left
#define UR 1			// UR - up right
#define DL 2			// DL - down left
#define DR 3			// DR - down right



/*---------------- tipke i njihove ASCII vrijednosti ----------------------*/

#define A_BACKSPACE  8
#define A_TAB	     9
#define A_ESC       27
#define A_ENTER	    13
#define A_SPACE	    32


// ASCII 0 + EXT

#define A_ARROW_UP   72
#define A_ARROW_DOWN 80
#define A_ARROW_LEFT 75
#define A_ARROW_RIGH 77

#define A_PGUP 73
#define A_PGDN 81
#define A_INS  82
#define A_HOME 71
#define A_DEL  83
#define A_END  79



/*----------------- tipke i njihove BIOS vrijednosti ----------------------*/

// funkcijeske tipke

#define B_F1  15104
#define B_F2  15360
#define B_F3  15616
#define B_F4  15872
#define B_F5  16128
#define B_F6  16384
#define B_F7  16640
#define B_F8  16896
#define B_F9  17152
#define B_F10 17408


// strelice

#define B_ARROW_UP   18432
#define B_ARROW_DOWN 20480
#define B_ARROW_LEFT 19200
#define B_ARROW_RIGH 19712


// vece - manje od

#define B_LESS 22076
#define B_MORE 22078


// numericka tastatura

#define B_NUM0 21040
#define B_NUM1 20273
#define B_NUM2 20530
#define B_NUM3 20787
#define B_NUM4 19252
#define B_NUM5 19509
#define B_NUM6 19766
#define B_NUM7 18231
#define B_NUM8 18488
#define B_NUM9 18745

#define B_0 2864
#define B_1  561
#define B_2  818
#define B_3 1075
#define B_4 1332
#define B_5 1589
#define B_6 1846
#define B_7 2103
#define B_8 2360
#define B_9 2617

#define B_SH0 2877			// =
#define B_SH1  545			// !
#define B_SH2  802			// "
#define B_SH3 1059			// #
#define B_SH4 1316			// $
#define B_SH5 1573			// %
#define B_SH6 1830			// &
#define B_SH7 2095			// /
#define B_SH8 2344			// (
#define B_SH9 2601			// )

#define B_ENTER      7181
#define B_SPACE     14624
#define B_ESC         283
#define B_BACKSPACE  3592
#define B_PGUP      18688
#define B_PGDN      20736

#define B_PLUS  3371                    // +
#define B_APOS  3111                    // '
#define B_STAR  3370                    // *
#define B_QUES  3135                    // ?
#define B_MINU 13613                    // -
#define B_DOTT 13663                    // _
#define B_PLOT 13358                    // .
#define B_DPLO 13370                    // :
#define B_COMM 13100                    // ,
#define B_DCOM 13115                    // ;

#define B_a     7777
#define B_A     7745
#define B_ALTa  7680
#define B_b    12386
#define B_B    12354
#define B_ALTb 12288
#define B_c    11875
#define B_C    11843
#define B_ALTc 11776
#define B_d     8292
#define B_D     8260
#define B_ALTd  8192
#define B_e     4709
#define B_E     4677
#define B_ALTe  4608
#define B_f     8550
#define B_F     8518
#define B_ALTf  8448
#define B_g     8807
#define B_G     8775
#define B_ALTg  8704
#define B_h     9064
#define B_H     9032
#define B_ALTh  8960
#define B_i     5993
#define B_I     5961
#define B_ALTi  5888
#define B_j     9322
#define B_J     9290
#define B_ALTj  9216
#define B_k     9579
#define B_K     9547
#define B_ALTk  9472
#define B_l     9836
#define B_L     9804
#define B_ALTl  9728
#define B_m    12909
#define B_M    12877
#define B_ALTm 12800
#define B_n    12654
#define B_N    12622
#define B_ALTn 12544
#define B_o     6255
#define B_O     6223
#define B_ALTo  6144
#define B_p     6512
#define B_P     6480
#define B_ALTp  6400
#define B_q     4209
#define B_Q     4177
#define B_ALTq  4096
#define B_r     4978
#define B_R     4946
#define B_ALTr  4864
#define B_s     8051
#define B_S     8019
#define B_ALTs  7936
#define B_t     5236
#define B_T     5204
#define B_ALTt  5120
#define B_u     5749
#define B_U     5717
#define B_ALTu  5632
#define B_v    12150
#define B_V    12118
#define B_ALTv 12032
#define B_w     4471
#define B_W     4439
#define B_ALTw  4352
#define B_x    11640
#define B_X    11608
#define B_ALTx 11520
#define B_y     5497
#define B_Y     5465
#define B_ALTy  5376
#define B_z    11386
#define B_Z    11354
#define B_ALTz 11264



/*-------------------------- ostale konstante -----------------------------*/

#define MAXIMEPROZ 20



/*------------------------------- macroi ----------------------------------*/

#define _BACKSPACE cprintf("\b \b");		   	// _BACKSPACE - emulacija backspace tipke

#define _BEEP      printf("\a");                        // _BEEP      - beep iz PC speakera
#define _BEEP_H    { sound(523);delay(50); \
		     sound(659);delay(50); \
		     sound(783);delay(50); \
		     sound(1046);delay(50);\
		     nosound(); }
#define _BEEP_B    { sound(523);delay(50); \
		     sound(392);delay(50); \
		     sound(329);delay(50); \
		     sound(261);delay(50);\
		     nosound(); }



/*-------------------------- prototipovi klasa ----------------------------*/

class TextProzor
 { char *ptext,
	 ImeProzora[MAXIMEPROZ+1],
	 LineBreak1,LineBreak2,
	 livi,gornji,desni,donji;
   public:
     TextProzor(char xl, char yg, char xd, char yd,
		char *Ime,
		char lb1=0, char lb2=0);
     ~TextProzor();
 };



/*------------------------ prototipovi funkcija ---------------------------*/

//void peglaj();
void Exit(char,char *);
void Exit(char);
void Exit();
//char *Unos(char *,char,char,char,char,char,char,char);



/*------------------------------ varijable --------------------------------*/

#endif