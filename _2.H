#ifndef	__2_H_
#define	__2_H_

#define B__1V   B_D
#define B__1M   B_d
#define B__1ALT B_ALTd
#define B__2V   B_E
#define B__2M   B_e
#define B__2ALT B_ALTe

#define __1 { gotoxy(_2_NUM+2,3);textcolor(RED);cputs(" D");textcolor(BLACK);cputs("irektorij paketa "); }
#define __2 { gotoxy(_2_NUM+2,4);textcolor(RED);cputs(" E");textcolor(BLACK);cputs("ksterni programi "); }

#define POHRANI { textcolor(RED);cputs(" P");textcolor(BLACK);cputs("ohrani ");          }
#define OTKAZI  { cputs(" Otka");textcolor(RED);cputs("z");textcolor(BLACK);cputs("i "); }

#define DIR_ZASIVI { textcolor(DARKGRAY);gotoxy(10,6);cputs("Q");textcolor(BLACK); }
#define DIR_ODSIVI { textcolor(RED);     gotoxy(10,6);cputs("Q");textcolor(BLACK); }

#define EXT_ZASIVI { textcolor(DARKGRAY);gotoxy(10,6);cputs("A");gotoxy(8,8);cputs("D");textcolor(BLACK); }
#define EXT_ODSIVI { textcolor(RED);     gotoxy(10,6);cputs("A");gotoxy(8,8);cputs("D");textcolor(BLACK); }

#define MAXNIZLENGHT DIRLENGHT


extern struct CfgStrings CfgData[];


class ExtDirs
 { char QwkDir[DIRLENGHT+1];

   public:
    char Pohrani();
    void Ispisi();
    void SetQwkDir();
    char *GetQwkDir()         { return(QwkDir);                 }
    void ModQwkDir(char *NewPath) { strcpy(QwkDir,NewPath);         }
 };

class ExtProgs
 { char Arh[DIRLENGHT+1],
	DeArh[DIRLENGHT+1];

   public:
    char PohraniSve();
    void IspisiSve();
    char *Get(char LineNum);
    void Set(char LineNum,char *NewPath);
    void SetArh();
    void SetDeArh();
 };

#endif