#include "mouse.h"
#include "mytxt.h"


char OldCurWDir[MAXPATH],
     NewCurWDir[MAXPATH];
int OldDrive,
    NewDrive;


TextProzor::TextProzor(char xl, char yg, char xd, char yd,
		       char *Ime,
		       char lb1, char lb2)
 {
   livi=xl; gornji=yg; desni=xd+2; donji=yd+1;
   strcpy(ImeProzora,Ime);
   LineBreak1=lb1; LineBreak2=lb2;

   ptext=(char *) malloc((desni-livi+1)*(donji-gornji+1)*2);
   gettext(livi,gornji,desni,donji,ptext);

   window(livi,gornji,desni-2,donji-1);
   clrscr();

   gotoxy(2,1);cputs("Ú");
   gotoxy((desni-livi-2),1);cputs("¿");
   gotoxy(2,(donji-gornji-1)+1);cputs("À");
   gotoxy((desni-livi-2),(donji-gornji-1)+1);cputs("Ù");

   for(register char i=3;i<(desni-livi-2);i++)
    { gotoxy(i,1);cputs("Ä");
      gotoxy(i,(donji-gornji-1)+1);cputs("Ä");
      if(LineBreak1)
       { gotoxy(i,LineBreak1);
	 cputs("Ä");
       }
      if(LineBreak2)
       { gotoxy(i,LineBreak2);
	 cputs("Ä");
       }
    }

   for(i=2;i<(donji-gornji-1)+1;i++)
    { gotoxy(2,i);cputs("³");
      gotoxy((desni-livi-2),i);cputs("³");
    }

   if(LineBreak1)
    { gotoxy(2,LineBreak1);cputs("Ã");
      gotoxy((desni-livi-2),LineBreak1);cputs("´");
    }
   if(LineBreak2)
    { gotoxy(2,LineBreak2);cputs("Ã");
      gotoxy((desni-livi-2),LineBreak2);cputs("´");
    }

   window(1,1,80,25);

   for(i=gornji+1;i<donji+1;i++)
    { gotoxy(desni-1,i);
      cputs("²²");
    }
   for(i=livi+2;i<=desni-1;i++)
    { gotoxy(i,donji);
      cputs("²");
    }

   gotoxy((int) (livi+desni-strlen(ImeProzora))/2,gornji);
   cputs(ImeProzora);
 }


TextProzor::~TextProzor()
 {
   puttext(livi,gornji,desni,donji,ptext);
   free(ptext);
 }


void peglaj()
 {
   clrscr();
   gotoxy(1,2);
   for(register char i=0;i<23;i++)
    cputs("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°");
 }


void Exit(char kod_greske,char *poruka)
 {
   window(1,1,80,25);
   textbackground(BLACK);
   textcolor(LIGHTGRAY);
   clrscr();

   _setcursortype(_NORMALCURSOR);
   mouse_install();

   Exit();

   perror(poruka);
   exit(kod_greske);
 }


void Exit()
 {
   setdisk(OldDrive);
   if(strcmp(NewCurWDir,OldCurWDir)) chdir(OldCurWDir);
 }


void Exit(char kod_greske)
 {
   window(1,1,80,25);
   textbackground(BLACK);
   textcolor(LIGHTGRAY);
   clrscr();

   _setcursortype(_NORMALCURSOR);
   mouse_install();

   Exit();

   exit(kod_greske);
 }


void ChangeDir(char **argv)
 {
   getcwd(OldCurWDir,MAXPATH);
   OldDrive=getdisk();

   for(register char i=strlen(argv[0]);i>=0;i--)
    if(argv[0][i]=='\\')
     { argv[0][i]='\0';
       i=0;
     }

   strcpy(NewCurWDir,argv[0]);
   NewDrive=tolower(NewCurWDir[0])-'a';

   if(OldDrive!=NewDrive)
    { setdisk(NewDrive);
      if(NewDrive!=getdisk())
       Exit(1,"Programu je onemogucena promjena diska");
    }

   if(strcmp(OldCurWDir,argv[0]))
    { if(chdir(argv[0]))
	Exit(2,"Programu je onemogucena promjena direktorija");
    }
 }


char *Unos(char UlazniNiz[],
	   char MaxNizLenght,
	   char Text_x,			// x koordinata pocetka teksta
	   char NewTextcolor,
	   char NewBackground,
	   char OldTextcolor,
	   char OldBackground,
	   char IzDirektorija		// ako je TRUE dodaje '\' stringu
	  )
 { char Niz[MAXPATH],      		// kopija ul. niza za editiranje
	slovo,				// ucitano slovo
	LenNiz,                         // duzina Niza
	br,                             // pozicija kursora u nizu
	brEdt,				// brojac za editiranja
	Insert;				// indikator insert tipke


   textcolor(NewTextcolor);
   textbackground(NewBackground);
   _setcursortype(_NORMALCURSOR);

   strcpy(Niz,UlazniNiz);
   LenNiz=strlen(Niz);
   Niz[LenNiz]='\0';
   br=0;
   Insert=FALSE;
   slovo=getch();

   while(slovo!=A_ESC && slovo!=A_ENTER)
    { if(slovo)
       { if(slovo==A_BACKSPACE)
	  { if(br>0)
	     { _BACKSPACE

	       if(br!=LenNiz)
		{ cprintf("%s ",&Niz[br]);             // & treba!
		  for(brEdt=br-1;brEdt<LenNiz;brEdt++)
		    Niz[brEdt]=Niz[brEdt+1];
		  gotoxy(br-1+Text_x,wherey());
		}
	       else Niz[br-1]='\0';

	       --br;
	       --LenNiz;
	     }
	    else _BEEP
	  }
	 else if(slovo==A_TAB)                    ;
	 else if(slovo==A_SPACE && IzDirektorija) ;
	 else
	  { if(br<MaxNizLenght && LenNiz+1<MaxNizLenght)  // stedim jedan znak za \
	     { slovo=toupper(slovo);
	       cprintf("%c",slovo);

	       if(Insert)
		{ if(br==LenNiz)
		   ++LenNiz;
		}
	       else
		{ if(br!=LenNiz)
		   { cprintf("%s",&Niz[br]);
		     for(brEdt=LenNiz+1;brEdt>br;brEdt--)
		      Niz[brEdt]=Niz[brEdt-1];
		     gotoxy(br+1+Text_x,wherey());
		   }
		  ++LenNiz;
		}

	       Niz[br++]=slovo;
	       Niz[LenNiz]='\0';
	     }
	    else _BEEP
	  }
       }
      else                              // slovo==0
       { slovo=getch();
	 switch(slovo)
	  { case A_ARROW_LEFT: if(br>0)
				{ gotoxy(wherex()-1,wherey());
				  --br;
				}
			       break;
	    case A_ARROW_RIGH: if(br<MaxNizLenght && br<LenNiz)
				{ gotoxy(wherex()+1,wherey());
				  ++br;
				}
			       break;
	    case A_END:        gotoxy(Text_x+LenNiz,wherey());
			       br=LenNiz;
			       break;
	    case A_HOME:       gotoxy(Text_x,wherey());
			       br=0;
			       break;
	    case A_DEL:        if(br==LenNiz) _BEEP
			       else
				{ cprintf("%s ",&Niz[br+1]);
				  for(brEdt=br;brEdt<LenNiz;brEdt++)
				    Niz[brEdt]=Niz[brEdt+1];
				  --LenNiz;
				  gotoxy(br+Text_x,wherey());
				}
			       break;
	    case A_INS:        if(Insert)
				{ _setcursortype(_NORMALCURSOR);
				  Insert=FALSE;
				}
			       else
				{ _setcursortype(_SOLIDCURSOR);
				  Insert=TRUE;
				}
			       break;
	    default:           break;
	  }
       }

      slovo=getch();
    }

   textcolor(OldTextcolor);
   textbackground(OldBackground);
   _setcursortype(_NOCURSOR);

   if(slovo==A_ESC)
    { textcolor(NewTextcolor);
      textbackground(NewBackground);

      gotoxy(Text_x,wherey());
      for(br=0;br<MaxNizLenght-1;br++)
       cputs(" ");
      gotoxy(Text_x,wherey());cputs(UlazniNiz);

      textcolor(OldTextcolor);
      textbackground(OldBackground);

      return(UlazniNiz);
    }

   if(Niz[LenNiz-1]!='\\' && LenNiz!=0 && IzDirektorija)
    { Niz[LenNiz++]='\\';
      Niz[LenNiz]='\0';
    }

   return(Niz);
 }
