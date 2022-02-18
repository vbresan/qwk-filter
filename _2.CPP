#include "qwkfltr.h"
#include "_2.h"


char Zeleni_2()
 { int x,y,botun,
       slovo;

   hide_mouse();
   textbackground(GREEN); _2
   textbackground(LIGHTGRAY); _1 _6
   gotoxy(1,25);cputs(" ( )  Konfiguriranje programa                                           ");
   show_mouse();

   do
    { get_mouse(&x,&y,&botun);
      if(x>=(_2_NUM-1)*8 && x<=23*8 && y==0 && botun==1)
       { Prozor_2();
	 return (0);
       }
      if((x<(_2_NUM-1)*8 || x>23*8) && y==0)
       return (0);
    }
   while(!kbhit());

   slovo=bioskey(0);
   switch(slovo)
    { case B_1M: case B_1V: set_mouse((_1_NUM-1)*8,0);break;
      case B_6M: case B_6V: set_mouse((_6_NUM-1)*8,0);break;
      case B_1ALT: Prozor_1();break;
      case B_6ALT: Prozor_6();break;
      case B_2ALT:
      case B_ENTER:      Prozor_2();               break;
      case B_ARROW_RIGH: set_mouse((_6_NUM-1)*8,0);break;
      case B_ARROW_LEFT: set_mouse((_1_NUM-1)*8,0);break;
      default:           break;
    }
   return(0);
 }

char Prozor_2(void)
 { char koji,
	Od2(char xPrvi,char xZadnji),
	PromjenaDirProzor(void),
	PromjenaExtProzor(void);
   TextProzor *op;

   hide_mouse();
   _1 _6
   sjencenje();
   textbackground(GREEN); _2
   textbackground(LIGHTGRAY);
   gotoxy(1,25);cputs(" (*)  Konfiguriranje programa                                           ");
   op = new TextProzor(_2_NUM,2,_2_NUM+22,5,"");
   textbackground(GREEN);     __1
   textbackground(LIGHTGRAY); __2
   show_mouse();

   koji=Od2(_2_NUM+1,_2_NUM+19);

   hide_mouse();
   delete op;

   if(koji==PRVI)       PromjenaDirProzor();
   else if(koji==DRUGI) PromjenaExtProzor();
   else if(koji==MAGIC)
    { set_mouse((_1_NUM-1)*8,0);
      show_mouse();
      Prozor_1();
      hide_mouse();
    }

   set_mouse((_1_NUM-1)*8,0);
   show_mouse();
   return(0);
 }

char Od2(char xPrvi,
	 char xZadnji
	)
 { int x,y,botun,
       slovo;
   char koji_je;

   koji_je=PRVI;
   while(TRUE)
    { do
       { get_mouse(&x,&y,&botun);
	 if(y==2*8 && koji_je!=PRVI)
	  { hide_mouse();
	    textbackground(GREEN);     __1
	    textbackground(LIGHTGRAY); __2
	    show_mouse();
	    koji_je=PRVI;
	  }
	 if(y==3*8 && koji_je!=DRUGI)
	  { hide_mouse();
	    textbackground(GREEN);     __2
	    textbackground(LIGHTGRAY); __1
	    show_mouse();
	    koji_je=DRUGI;
	  }
	 if(x>=xPrvi*8 && x<=xZadnji*8 && botun==1)
	  { if(koji_je==PRVI && y==2*8)  return(PRVI);
	    if(koji_je==DRUGI && y==3*8) return(DRUGI);
	  }
	 if(botun==2)
	  return(FALSE);
       }
      while(!kbhit());

      slovo=bioskey(0);
      switch(slovo)
       { case  B_ESC:
	 case   B_2M:
	 case   B_2V:
	 case B_2ALT: return (FALSE);
	 case B__1M:
	 case B__1V: set_mouse(xPrvi*8,2*8);
		     break;
	 case B__1ALT: return(PRVI);
	 case B__2M:
	 case B__2V: set_mouse(xPrvi*8,3*8);
		     break;
	 case B__2ALT: return(DRUGI);
	 case B_ARROW_DOWN:
	 case B_ARROW_UP:   if(koji_je==PRVI)       set_mouse(xPrvi*8,3*8);
			    else if(koji_je==DRUGI) set_mouse(xPrvi*8,2*8);
			    break;
	 case B_ARROW_LEFT: return(MAGIC);
	 case B_ENTER: return(koji_je);
	 default: break;
       }
    }
 }

/****************************************************************************/

char PromjenaDirProzor(void)
 { char PromjenaDir(void);
   TextProzor *op;

   // mis je vec skriven
   _1 _2 _6
   sjencenje();
   op = new TextProzor(5,4,75,11," Direktorij paketa ",5);
   gotoxy(10,6);textcolor(RED);cputs("Q");textcolor(BLACK);cputs("WK ");
   textcolor(WHITE);
   textbackground(BLUE);
   gotoxy(14,6);cputs("                                                          ");
   textbackground(LIGHTGRAY);
   textcolor(BLACK);

   show_mouse();
   PromjenaDir();

   hide_mouse();
   delete op;

   return(0);
 }

char PromjenaDir(void)
 { int x,y,botun,
       slovo;
   char ZeleniBotun,
	*Unos(char *,char,char,char,char,char,char,char),
	IzUnosa[DIRLENGHT+1],
	Pohraniti;			// indikator za snimanje
   ExtDirs Dirs;

   Pohraniti=FALSE;
   Dirs.SetQwkDir();
   Dirs.Ispisi();

   ZeleniBotun=PRVI;
   while(TRUE)
    { char VanIzPetlje;

      if(ZeleniBotun==PRVI)
       { hide_mouse();

	 textbackground(LIGHTGREEN);
	 gotoxy(31,9);
	 POHRANI
	 textbackground(LIGHTGRAY);  cputs("Ü");gotoxy(32,10);cputs("ßßßßßßßßß");

	 gotoxy(42,9);
	 OTKAZI
	 cputs(" ");gotoxy(43,10);cputs("        ");

	 show_mouse();
       }
      if(ZeleniBotun==DRUGI)
       { hide_mouse();

	 gotoxy(31,9);
	 POHRANI
	 cputs(" ");gotoxy(32,10);cputs("         ");

	 textbackground(LIGHTGREEN);
	 gotoxy(42,9);
	 OTKAZI
	 textbackground(LIGHTGRAY);  cputs("Ü");gotoxy(43,10);cputs("ßßßßßßßß");

	 show_mouse();
       }

      VanIzPetlje=FALSE;
      do
       { get_mouse(&x,&y,&botun);
	 if(botun==1 && y==(6-1)*8)
	  { hide_mouse();
	    DIR_ZASIVI
	    gotoxy(14,6);

	    strcpy(IzUnosa,Unos(Dirs.GetQwkDir(),MAXNIZLENGHT,14,WHITE,BLUE,
	                                                         BLACK,LIGHTGRAY,TRUE));
	    if(strcmp(IzUnosa,Dirs.GetQwkDir()))
	     { Dirs.ModQwkDir(IzUnosa);
	       Pohraniti=TRUE;
	     }

	    DIR_ODSIVI
	    show_mouse();
	  }

	 if(ZeleniBotun!=PRVI && (x>=30*8 && x<=39*8 && (y==8*8 || y==9*8)))
	  { ZeleniBotun=PRVI;
	    VanIzPetlje=TRUE;
	  }
	 if(ZeleniBotun!=DRUGI && (x>=41*8 && x<=49*8 && (y==8*8 || y==9*8)))
	  { ZeleniBotun=DRUGI;
	    VanIzPetlje=TRUE;
	  }

	 if(botun==1 && x>=30*8 && x<=39*8 && y==8*8 && Pohraniti)
	  { Dirs.Pohrani();
	    return(FALSE);
	  }
	 if(botun==2 || (botun==1 && x>=41*8 && x<=48*8 && y==8*8))
	  return(FALSE);
       }
      while(!kbhit() && !VanIzPetlje);

      if(kbhit())
       { slovo=bioskey(0);
	 switch(slovo)
	  { case B_ESC:
	    case B_ALTz: return(FALSE);

	    case B_z:
	    case B_Z: if(ZeleniBotun==PRVI)  set_mouse(41*8,8*8);
		      break;
	    case B_p:
	    case B_P: if(ZeleniBotun==DRUGI) set_mouse(30*8,8*8);
		      break;
	    case B_ALTp: if(Pohraniti) Dirs.Pohrani();
			 return(FALSE);

	    case B_q:
	    case B_Q:
	    case B_ALTq: hide_mouse();
			 DIR_ZASIVI
			 gotoxy(14,6);

			 strcpy(IzUnosa,Unos(Dirs.GetQwkDir(),MAXNIZLENGHT,14,WHITE,BLUE,
			                                                      BLACK,LIGHTGRAY,TRUE));
			 if(strcmp(IzUnosa,Dirs.GetQwkDir()))
			  { Dirs.ModQwkDir(IzUnosa);
			    Pohraniti=TRUE;
			  }

			 DIR_ODSIVI
			 show_mouse();
			 break;

	    case B_ARROW_LEFT:
	    case B_ARROW_RIGH: if(ZeleniBotun==PRVI) set_mouse(41*8,8*8);
			       else                  set_mouse(30*8,8*8);
			       break;

	    case B_ENTER: if(ZeleniBotun==PRVI)
			   { if(Pohraniti)
			      Dirs.Pohrani();
			   }
			  return(FALSE);
	    default: break;
	  }
       }	// if(kbhit())
    }		// while(TRUE)
 }

void ExtDirs::SetQwkDir(void)
 {
   strcpy(QwkDir,CfgData[0].data);

   if(strlen(CfgData[0].data)>DIRLENGHT)
    QwkDir[DIRLENGHT]='\0';
 }

void ExtDirs::Ispisi(void)
 {
   textcolor(WHITE);
   textbackground(BLUE);

   if(QwkDir)
    { gotoxy(14,6);
      cputs(QwkDir);
    }

   textcolor(BLACK);
   textbackground(LIGHTGRAY);
 }

char ExtDirs::Pohrani(void)
 { FILE *fpR,				// za citanje
	*fpW;                           // za pisanje
   char *tmp,				// tmp ime za tmp datoteku
	line[80];			// txt linija datoteke
   void KreirajCfg(void);		// kreiranje CFG datoteke

   tmp=tmpnam(NULL);

   if((fpR=fopen(CFGFILE,"rt"))==NULL)
    { textcolor(RED);
      gotoxy(1,25);cputs(" Nedostaje konfiguracijska datoteka -- kreiranje nove!                  ");
      textcolor(BLACK);
      _BEEP_B

      KreirajCfg();
    }

   if((fpW=fopen(tmp,"wt"))==NULL)
    Exit(5,"Programu je onemoguceno kreiranje TMP datoteke");

   fgets(line,80,fpR);
   while(!feof(fpR))
    { char *pTZ,			// pointer na tocku-zarez
	   *pPS;                        // pointer na podstring

      if((pPS=strstr(line,"QwkDir"))!=NULL)     //   potrazi odgovarajuci string
       { pTZ=strchr(line,';');
	 if(pPS<pTZ || !pTZ)                    //   ako je string pronadjen
	  { strcpy(line,"QwkDir = ");           //     izmjenjeni liniju
	    strcat(line,QwkDir);
	    strcat(line,"\n");
	  }
       }

      fputs(line,fpW);			//     prepisi liniju

      fgets(line,80,fpR);
    }

   fclose(fpR);				// zatvori konfiguracijsku datoteku
   fclose(fpW);				// zatvori privremenu datoteku

   if(unlink(CFGFILE))
    { textcolor(RED);
      gotoxy(1,25);cputs(" Konfiguracijska datoteka zasticena -- unesene promjene nisu vazece!    ");
      textcolor(BLACK);
      _BEEP_B

      if(!getch())
       getch();

      unlink(tmp);			// izbrisi tmp file
    }
   else
    { rename(tmp,CFGFILE);		// preimenuj privremenu datoteku
      CfgRead(CFGFILE, CfgData);        // izvrsi promjene u memorij
      _BEEP_H
    }

   return(0);
 }

/****************************************************************************/

char PromjenaExtProzor(void)
 { char PromjenaExt(void);
   TextProzor *op;

   // mis je vec skriven
   _1 _2 _6
   sjencenje();
   op = new TextProzor(5,4,75,13," Eksterni programi ",7);
   gotoxy(10,6);textcolor(RED);cputs("A");textcolor(BLACK);cputs("rh ");
   gotoxy(8,8);textcolor(RED);cputs("D");textcolor(BLACK);cputs("eArh ");
   textcolor(WHITE);
   textbackground(BLUE);
   gotoxy(14,6);cputs("                                                          ");
   gotoxy(14,8);cputs("                                                          ");
   textbackground(LIGHTGRAY);
   textcolor(BLACK);

   show_mouse();
   PromjenaExt();

   hide_mouse();
   delete op;

   return(0);
 }

char PromjenaExt(void)
 { int x,y,botun,
       slovo;
   char ZeleniBotun,
	*Unos(char *,char,char,char,char,char,char,char),
	IzUnosa[DIRLENGHT+1],
	Pohraniti;			// indikator za snimanje
   ExtProgs Progs;

   Pohraniti=FALSE;
   Progs.SetArh();
   Progs.SetDeArh();
   Progs.IspisiSve();

   ZeleniBotun=PRVI;
   while(TRUE)
    { char VanIzPetlje;

      if(ZeleniBotun==PRVI)
       { hide_mouse();

	 textbackground(LIGHTGREEN);
	 gotoxy(31,11);
	 POHRANI
	 textbackground(LIGHTGRAY);  cputs("Ü");gotoxy(32,12);cputs("ßßßßßßßßß");

	 gotoxy(42,11);
	 OTKAZI
	 cputs(" ");gotoxy(43,12);cputs("        ");

	 show_mouse();
       }
      if(ZeleniBotun==DRUGI)
       { hide_mouse();

	 gotoxy(31,11);
	 POHRANI
	 cputs(" ");gotoxy(32,12);cputs("         ");

	 textbackground(LIGHTGREEN);
	 gotoxy(42,11);
	 OTKAZI
	 textbackground(LIGHTGRAY);  cputs("Ü");gotoxy(43,12);cputs("ßßßßßßßß");

	 show_mouse();
       }

      VanIzPetlje=FALSE;
      do
       { get_mouse(&x,&y,&botun);
	 if(botun==1 && (y==(6-1)*8 || y==(8-1)*8))
	  { hide_mouse();
	    EXT_ZASIVI
	    gotoxy(14,(int) y/8+1);

	    strcpy(IzUnosa,Unos(Progs.Get((char) y/8+1),MAXNIZLENGHT,14,WHITE,BLUE,
									BLACK,LIGHTGRAY,FALSE));
	    if(strcmp(IzUnosa,Progs.Get((char) y/8+1)))
	     { Progs.Set((char) y/8+1,IzUnosa);
	       Pohraniti=TRUE;
	     }

	    EXT_ODSIVI
	    show_mouse();
	  }

	 if(ZeleniBotun!=PRVI && (x>=30*8 && x<=39*8 && (y==10*8 || y==11*8)))
	  { ZeleniBotun=PRVI;
	    VanIzPetlje=TRUE;
	  }
	 if(ZeleniBotun!=DRUGI && (x>=41*8 && x<=49*8 && (y==10*8 || y==11*8)))
	  { ZeleniBotun=DRUGI;
	    VanIzPetlje=TRUE;
	  }

	 if(botun==1 && x>=30*8 && x<=39*8 && y==10*8 && Pohraniti)
	  { Progs.PohraniSve();
	    return(FALSE);
	  }
	 if(botun==2 || (botun==1 && x>=41*8 && x<=48*8 && y==10*8))
	  return(FALSE);
       }
      while(!kbhit() && !VanIzPetlje);

      if(kbhit())
       { slovo=bioskey(0);
	 switch(slovo)
	  { case B_ESC:
	    case B_ALTz: return(FALSE);

	    case B_z:
	    case B_Z: if(ZeleniBotun==PRVI)  set_mouse(41*8,10*8);
		      break;
	    case B_p:
	    case B_P: if(ZeleniBotun==DRUGI) set_mouse(30*8,10*8);
		      break;
	    case B_ALTp: if(Pohraniti) Progs.PohraniSve();
			 return(FALSE);

	    case B_a:
	    case B_A:
	    case B_ALTa: hide_mouse();
			 EXT_ZASIVI
			 gotoxy(14,6);

			 strcpy(IzUnosa,Unos(Progs.Get(6),MAXNIZLENGHT,14,WHITE,BLUE,
									  BLACK,LIGHTGRAY,FALSE));
			 if(strcmp(IzUnosa,Progs.Get(6)))
			  { Progs.Set(6,IzUnosa);
			    Pohraniti=TRUE;
			  }

			 EXT_ODSIVI
			 show_mouse();
			 break;
	    case B_d:
	    case B_D:
	    case B_ALTd: hide_mouse();
			 EXT_ZASIVI
			 gotoxy(14,8);

			 strcpy(IzUnosa,Unos(Progs.Get(8),MAXNIZLENGHT,14,WHITE,BLUE,
									  BLACK,LIGHTGRAY,FALSE));
			 if(strcmp(IzUnosa,Progs.Get(8)))
			  { Progs.Set(8,IzUnosa);
			    Pohraniti=TRUE;
			  }

			 EXT_ODSIVI
			 show_mouse();
			 break;

	    case B_ARROW_LEFT:
	    case B_ARROW_RIGH: if(ZeleniBotun==PRVI) set_mouse(41*8,10*8);
			       else                  set_mouse(30*8,10*8);
			       break;

	    case B_ENTER: if(ZeleniBotun==PRVI)
			   { if(Pohraniti)
			      Progs.PohraniSve();
			   }
			  return(FALSE);
	    default: break;
	  }
       }	// if(kbhit())
    }		// while(TRUE)
 }

void ExtProgs::SetArh(void)
 {
   strcpy(Arh,CfgData[1].data);

   if(strlen(CfgData[1].data)>DIRLENGHT)
    Arh[DIRLENGHT]='\0';
 }


void ExtProgs::SetDeArh(void)
 {
   strcpy(DeArh,CfgData[2].data);

   if(strlen(CfgData[2].data)>DIRLENGHT)
    DeArh[DIRLENGHT]='\0';
 }

char *ExtProgs::Get(char LineNum)
 {
   if(LineNum==6)      return(Arh);
   else                return(DeArh);
 }


void ExtProgs::IspisiSve(void)
 {
   textcolor(WHITE);
   textbackground(BLUE);

   if(Arh)
    { gotoxy(14,6);
      cputs(Arh);
    }
   if(DeArh)
    { gotoxy(14,8);
      cputs(DeArh);
    }

   textcolor(BLACK);
   textbackground(LIGHTGRAY);
 }


void ExtProgs::Set(char LineNum,char *NewPath)
 {
   if(LineNum==6)       strcpy(Arh,NewPath);
   else                 strcpy(DeArh,NewPath);
 }


char ExtProgs::PohraniSve(void)
 { FILE *fpR,				// za citanje
	*fpW;                           // za pisanje
   char *tmp,				// tmp ime za tmp datoteku
	line[80];			// txt linija datoteke
   void KreirajCfg(void);		// kreiranje CFG datoteke

   tmp=tmpnam(NULL);

   if((fpR=fopen(CFGFILE,"rt"))==NULL)
    { textcolor(RED);
      gotoxy(1,25);cputs(" Nedostaje konfiguracijska datoteka -- kreiranje nove!                  ");
      textcolor(BLACK);
      _BEEP_B

      KreirajCfg();
    }

   if((fpW=fopen(tmp,"wt"))==NULL)
    Exit(5,"Programu je onemoguceno kreiranje TMP datoteke");

   fgets(line,80,fpR);
   while(!feof(fpR))
    { char *pTZ,			// pointer na tocku-zarez
	   *pPS;                        // pointer na podstring

      if((pPS=strstr(line,"Arh"))!=NULL && strstr(line,"DeArh")==NULL)
       { pTZ=strchr(line,';');
	 if(pPS<pTZ || !pTZ)                    //   ako je string pronadjen
	  { strcpy(line,"Arh   = ");           	//     izmjenjeni liniju
	    strcat(line,Arh);
	    strcat(line,"\n");
	  }
       }
      else if((pPS=strstr(line,"DeArh"))!=NULL)
       { pTZ=strchr(line,';');
	 if(pPS<pTZ || !pTZ)
	  { strcpy(line,"DeArh = ");
	    strcat(line,DeArh);
	    strcat(line,"\n");
	  }
       }

      fputs(line,fpW);			//     prepisi liniju

      fgets(line,80,fpR);
    }

   fclose(fpR);				// zatvori konfiguracijsku datoteku
   fclose(fpW);				// zatvori privremenu datoteku

   if(unlink(CFGFILE))
    { textcolor(RED);
      gotoxy(1,25);cputs(" Konfiguracijska datoteka zasticena -- unesene promjene nisu vazece!    ");
      textcolor(BLACK);
      _BEEP_B

      if(!getch())
       getch();

      unlink(tmp);			// izbrisi tmp file
    }
   else
    { rename(tmp,CFGFILE);		// preimenuj privremenu datoteku
      CfgRead(CFGFILE, CfgData);        // izvrsi promjene u memoriji
      _BEEP_H
    }

   return(0);
 }
