#include "qwkfltr.h"
#include "_1.h"


char Zeleni_1()
 { int x,y,botun,
       slovo;

   hide_mouse();
   textbackground(GREEN); _1
   textbackground(LIGHTGRAY); _2 _6
   gotoxy(1,25);cputs(" ( )  Konfiguriranje filtera                                            ");
   show_mouse();

   do					// cekam opustanje botuna na misu
    get_mouse(&x,&y,&botun);
   while(botun);

   do
    { get_mouse(&x,&y,&botun);
      if(x>=(_1_NUM-1)*8 && x<(_2_NUM-1)*8 && y==0 && botun==1)
       { Prozor_1();
	 return (0);
       }
      if(x>=(_2_NUM-1)*8 && y==0)
       return (0);
    }
   while(!kbhit());

   slovo=bioskey(0);
   switch(slovo)
    { case B_2M: case B_2V: set_mouse((_2_NUM-1)*8,0);break;
      case B_6M: case B_6V: set_mouse((_6_NUM-1)*8,0);break;
      case B_2ALT: Prozor_2();break;
      case B_6ALT: Prozor_6();break;
      case B_1ALT:
      case B_ENTER:      Prozor_1();               break;
      case B_ARROW_RIGH: set_mouse((_2_NUM-1)*8,0);break;
      case B_ARROW_LEFT: set_mouse((_6_NUM-1)*8,0);break;
      default:           break;
    }
   return(0);
 }

char Prozor_1()
 { char koji,
	Od3(char xPrvi,char xZadnji),
	ProzorSvih(char *Ime);
   TextProzor *op;

   hide_mouse();
   _2 _6
   sjencenje();
   textbackground(GREEN); _1
   textbackground(LIGHTGRAY);
   gotoxy(1,25);cputs(" (*)  Konfiguriranje filtera                                            ");
   op = new TextProzor(_1_NUM,2,_1_NUM+12,6,"");
   textbackground(GREEN);     __1
   textbackground(LIGHTGRAY); __2 __3
   show_mouse();

   koji=Od3(_1_NUM+1,_1_NUM+9);

   hide_mouse();
   delete op;

   if(koji==PRVI)       ProzorSvih(" From ");
   else if(koji==DRUGI) ProzorSvih(" To ");
   else if(koji==TRECI) ProzorSvih(" Subject ");
   else if(koji==MAGIC)
    { set_mouse((_2_NUM-1)*8,0);
      show_mouse();
      Prozor_2();
      hide_mouse();
    }

   set_mouse((_1_NUM-1)*8,0);
   show_mouse();
   return(0);
 }

char Od3(char xPrvi,		// x koordinata pocetka zelenog taga
	 char xZadnji           // x koordinata kraja zelenog taga
	)
 { int x,y,botun,
       slovo;
   char koji_je;		// koji je trenutno odabran

   koji_je=PRVI;
   while(TRUE)
    { do
       { get_mouse(&x,&y,&botun);
	 if(y==2*8 && koji_je!=PRVI)
	  { hide_mouse();
	    textbackground(GREEN);     __1
	    textbackground(LIGHTGRAY); __2 __3
	    show_mouse();
	    koji_je=PRVI;
	  }
	 if(y==3*8 && koji_je!=DRUGI)
	  { hide_mouse();
	    textbackground(GREEN);     __2
	    textbackground(LIGHTGRAY); __1 __3
	    show_mouse();
	    koji_je=DRUGI;
	  }
	 if(y==4*8 && koji_je!=TRECI)
	  { hide_mouse();
	    textbackground(GREEN);     __3
	    textbackground(LIGHTGRAY); __1 __2
	    show_mouse();
	    koji_je=TRECI;
	  }
	 if(x>=xPrvi*8 && x<=xZadnji*8 && botun==1)
	  { if(koji_je==PRVI && y==2*8)
	     return (PRVI);
	    if(koji_je==DRUGI && y==3*8)
	     return (DRUGI);
	    if(koji_je==TRECI && y==4*8)
	     return (TRECI);
	  }
	 if(botun==2)
	  return (FALSE);
       }
      while(!kbhit());

      slovo=bioskey(0);
      switch(slovo)
       { case  B_ESC:
	 case   B_1M:
	 case   B_1V:
	 case B_1ALT: return (FALSE);
	 case B__1M:
	 case B__1V: set_mouse(xPrvi*8,2*8);
		     break;
	 case B__1ALT: return (PRVI);
	 case B__2M:
	 case B__2V: set_mouse(xPrvi*8,3*8);
		     break;
	 case B__2ALT: return (DRUGI);
	 case B__3M:
	 case B__3V: set_mouse(xPrvi*8,4*8);
		     break;
	 case B__3ALT: return (TRECI);

	 case B_ARROW_DOWN: if(koji_je==PRVI)       set_mouse(xPrvi*8,3*8);
			    else if(koji_je==DRUGI) set_mouse(xPrvi*8,4*8);
			    else if(koji_je==TRECI) set_mouse(xPrvi*8,2*8);
			    break;
	 case B_ARROW_UP:   if(koji_je==PRVI)       set_mouse(xPrvi*8,4*8);
			    else if(koji_je==DRUGI) set_mouse(xPrvi*8,2*8);
			    else if(koji_je==TRECI) set_mouse(xPrvi*8,3*8);
			    break;
	 case B_ARROW_RIGH: return(MAGIC);
	 case B_ENTER: return(koji_je);
	 default: break;
       }
    }
 }

char ProzorSvih(char *Ime)
 { int x,y,botun,
       slovo;
   char ZeleniBotun,
	*FileName,
	Izbrisi(char *FileName),
	Dodaj(char *FileName);
   void IspisPodataka(char *Datoteka);
   TextProzor *op;

   gotoxy(1,25);
   cputs(" <");textcolor(RED);cputs("Esc");textcolor(BLACK);cputs("> ili ");
   textcolor(RED);cputs("desna tipka misa");textcolor(BLACK);cputs(" za povratak u glavni izbornik               ");

   op = new TextProzor(25,5,55,20,Ime,13);
   textbackground(BLUE);
   window(28,6,52,16);
   clrscr();
   textbackground(LIGHTGRAY);
   window(1,1,80,25);

   if(!strcmp(Ime," From "))
    { IspisPodataka(FROMFILE);
      strcpy(FileName,FROMFILE);
    }
   else if(!strcmp(Ime," To "))
    { IspisPodataka(TOFILE);
      strcpy(FileName,TOFILE);
    }
   else if(!strcmp(Ime," Subject "))
    { IspisPodataka(SUBJFILE);
      strcpy(FileName,SUBJFILE);
    }

   show_mouse();
   ZeleniBotun=PRVI;
   while(TRUE)
    { char VanIzPetlje;

      if(ZeleniBotun==PRVI)
       { hide_mouse();

	 textbackground(LIGHTGREEN);
	 gotoxy(32,18);
	 DODAJ
	 textbackground(LIGHTGRAY);  cputs("Ü");gotoxy(33,19);cputs("ßßßßßßß");

	 gotoxy(41,18);
	 BRISI
	 cputs(" ");gotoxy(42,19);cputs("         ");
       }
      if(ZeleniBotun==DRUGI)
       { hide_mouse();

	 gotoxy(32,18);
	 DODAJ
	 cputs(" ");gotoxy(33,19);cputs("       ");

	 textbackground(LIGHTGREEN);
	 gotoxy(41,18);
	 BRISI
	 textbackground(LIGHTGRAY); cputs("Ü");gotoxy(42,19);cputs("ßßßßßßßßß");
       }

      show_mouse();
      VanIzPetlje=FALSE;
      do
       { get_mouse(&x,&y,&botun);
	 if(ZeleniBotun!=PRVI && (x>=31*8 && x<=37*8 && (y==17*8 || y==18*8)))
	  { ZeleniBotun=PRVI;
	    VanIzPetlje=TRUE;
	  }
	 if(ZeleniBotun!=DRUGI && (x>=40*8 && x<=48*8 && (y==17*8 || y==18*8)))
	  { ZeleniBotun=DRUGI;
	    VanIzPetlje=TRUE;
	  }

	 if(botun==1 && x>=31*8 && x<=37*8 && y==17*8)
	  { if(Dodaj(FileName))
	     { delete op;
	       return(FALSE);
	     }
	    else
	     { gotoxy(1,25);
	       cputs(" <");textcolor(RED);cputs("Esc");textcolor(BLACK);cputs("> ili ");
	       textcolor(RED);cputs("desna tipka misa");textcolor(BLACK);cputs(" za povratak u glavni izbornik               ");

	       textbackground(LIGHTGREEN);
	       gotoxy(32,18);
	       DODAJ
	       textbackground(LIGHTGRAY);  cputs("Ü");gotoxy(33,19);cputs("ßßßßßßß");

	       show_mouse();
	     }
	  }
	 if(botun==1 && x>=40*8 && x<=48*8 && y==17*8)
	  { if(Izbrisi(FileName))
	     { delete op;
	       return(FALSE);
	     }
	    else
	     { gotoxy(1,25);
	       cputs(" <");textcolor(RED);cputs("Esc");textcolor(BLACK);cputs("> ili ");
	       textcolor(RED);cputs("desna tipka misa");textcolor(BLACK);cputs(" za povratak u glavni izbornik               ");

	       textbackground(LIGHTGREEN);
	       gotoxy(41,18);
	       BRISI
	       textbackground(LIGHTGRAY); cputs("Ü");gotoxy(42,19);cputs("ßßßßßßßßß");

	       show_mouse();
	     }
	  }
	 if(botun==2)
	  { hide_mouse();
	    delete op;
	    return(FALSE);
	  }
       }
      while(!kbhit() && !VanIzPetlje);

      if(kbhit())
       { slovo=bioskey(0);
	 switch(slovo)
	  { case B_ESC: hide_mouse();
			delete op;
			return(FALSE);

	    case B_i:
	    case B_I: if(ZeleniBotun==PRVI)  set_mouse(40*8,17*8);
		      break;
	    case B_ALTi: if(ZeleniBotun==PRVI)
			  { hide_mouse();

			    gotoxy(32,18);
			    DODAJ
			    cputs(" ");gotoxy(33,19);cputs("       ");

			    textbackground(LIGHTGREEN);
			    gotoxy(41,18);
			    BRISI
			    textbackground(LIGHTGRAY); cputs("Ü");gotoxy(42,19);cputs("ßßßßßßßßß");

			    show_mouse();
			    ZeleniBotun=DRUGI;
			  }
			 if(Izbrisi(FileName))
			  { delete op;
			    return(FALSE);
			  }
			 else
			  { gotoxy(1,25);
			    cputs(" <");textcolor(RED);cputs("Esc");textcolor(BLACK);cputs("> ili ");
			    textcolor(RED);cputs("desna tipka misa");textcolor(BLACK);cputs(" za povratak u glavni izbornik               ");

			    textbackground(LIGHTGREEN);
			    gotoxy(41,18);
			    BRISI
			    textbackground(LIGHTGRAY); cputs("Ü");gotoxy(42,19);cputs("ßßßßßßßßß");

			    show_mouse();
			  }
			 break;

	    case B_d:
	    case B_D: if(ZeleniBotun==DRUGI) set_mouse(31*8,17*8);
		      break;
	    case B_ALTd: if(ZeleniBotun==DRUGI)
			  { hide_mouse();

			    textbackground(LIGHTGREEN);
			    gotoxy(32,18);
			    DODAJ
			    textbackground(LIGHTGRAY);  cputs("Ü");gotoxy(33,19);cputs("ßßßßßßß");

			    gotoxy(41,18);
			    BRISI
			    cputs(" ");gotoxy(42,19);cputs("         ");

			    show_mouse();
			    ZeleniBotun=PRVI;
			  }
			 if(Dodaj(FileName))
			  { delete op;
			    return(FALSE);
			  }
			 else
			  { gotoxy(1,25);
			    cputs(" <");textcolor(RED);cputs("Esc");textcolor(BLACK);cputs("> ili ");
			    textcolor(RED);cputs("desna tipka misa");textcolor(BLACK);cputs(" za povratak u glavni izbornik               ");

			    textbackground(LIGHTGREEN);
			    gotoxy(32,18);
			    DODAJ
			    textbackground(LIGHTGRAY);  cputs("Ü");gotoxy(33,19);cputs("ßßßßßßß");

			    show_mouse();
			  }
			 break;

	    case B_ARROW_LEFT:
	    case B_ARROW_RIGH: if(ZeleniBotun==PRVI) set_mouse(40*8,17*8);
			       else                  set_mouse(31*8,17*8);
			       break;

	    case B_ENTER: if(ZeleniBotun==PRVI)
			   { if(Dodaj(FileName))
			      { delete op;
				return(FALSE);
			      }
			     else
			      { gotoxy(1,25);
				cputs(" <");textcolor(RED);cputs("Esc");textcolor(BLACK);cputs("> ili ");
				textcolor(RED);cputs("desna tipka misa");textcolor(BLACK);cputs(" za povratak u glavni izbornik               ");

				textbackground(LIGHTGREEN);
				gotoxy(32,18);
				DODAJ
				textbackground(LIGHTGRAY);  cputs("Ü");gotoxy(33,19);cputs("ßßßßßßß");

				show_mouse();
			      }
			   }
			  else
			   { if(Izbrisi(FileName))
			      { delete op;
				return(FALSE);
			      }
			     else
			      { gotoxy(1,25);
				cputs(" <");textcolor(RED);cputs("Esc");textcolor(BLACK);cputs("> ili ");
				textcolor(RED);cputs("desna tipka misa");textcolor(BLACK);cputs(" za povratak u glavni izbornik               ");

				textbackground(LIGHTGREEN);
				gotoxy(41,18);
				BRISI
				textbackground(LIGHTGRAY); cputs("Ü");gotoxy(42,19);cputs("ßßßßßßßßß");

				show_mouse();
			      }
			   }
			  break;
	    default: break;
	  }
       }
    } // while(TRUE)
 }


void IspisPodataka(char *Datoteka)
 { FILE *fp;
   char String[26];

   if((fp=fopen(Datoteka,"rt"))==NULL)
    { if((fp=fopen(Datoteka,"wt"))==NULL)
       Exit(5,"Programu je onemoguceno kreiranje DAT datoteke");
      else
       fclose(fp);
    }
   else
    { char br;

      textbackground(BLUE);
      textcolor(WHITE);

      fgets(String,27,fp);

      br=0;
      while(!feof(fp) && br<11)
       { gotoxy(28,6+br);
	 cprintf("%s",String);

	 fgets(String,27,fp);
	 br++;
       }

      textbackground(LIGHTGRAY);
      textcolor(BLACK);

      fclose(fp);
    }
 }


char Izbrisi(char *FileName)
 { FILE *fp;

   hide_mouse();

   gotoxy(1,25);
   cputs(" <");textcolor(RED);cputs("Esc");textcolor(BLACK);cputs("> ili ");
   textcolor(RED);cputs("desna tipka misa");textcolor(BLACK);cputs(" za povratak                                 ");

   gotoxy(32,18);
   DODAJ
   textbackground(LIGHTGRAY);  cputs(" ");gotoxy(33,19);cputs("       ");
   gotoxy(41,18);
   BRISI
   cputs(" ");gotoxy(42,19);cputs("         ");
   textcolor(DARKGRAY);
   gotoxy(33,18);cputs("D");
   gotoxy(42,18);cputs("I");
   textcolor(BLACK);

   show_mouse();

   if((fp=fopen(FileName,"rt"))==NULL)
     Exit(4,"Programu je onemoguceno citanje DAT datoteke");
   else
    { char br,				// koliko je clanova ucitano
	   Clan[11][27];

      br=0;
      while(!feof(fp) && br<11)
       if(fgets(Clan[br],27,fp)!=NULL) br++;

      fclose(fp);

      if(!br)
       { _BEEP_B
	 hide_mouse();
	 return(FALSE);
       }
      else
       { char Zazelenjeni,i;

	 /* br je broj ucitanih, umanjim li ga za jedan
	    odgovara indeksu posljednjeg ucitanog       */

	 br--;
	 Zazelenjeni=0;
	 textcolor(WHITE);

	 while(TRUE)
	  { char VanIzPetlje;
	    int slovo;

	    hide_mouse();

	    for(i=0;i<=br;i++)
	     { gotoxy(28,6+i);

	       if(i==Zazelenjeni)
		textbackground(LIGHTGREEN);            // ispisi zazelenjenog
	       else
		textbackground(BLUE);

	       cprintf("%s",Clan[i]);
	     }

	    show_mouse();

	    VanIzPetlje=0;
	    do
	     { int x,y,botun;

	       get_mouse(&x,&y,&botun);
	       if(x>=27*8 && x<=51*8 && y>=5*8 && y<=(5+br)*8
				     && y!=(5+Zazelenjeni)*8)
		{ Zazelenjeni=y/8-5;
		  VanIzPetlje=TRUE;
		}
	       if(botun==1 && x>=27*8 && x<=51*8 && y>=5*8 && y<=(5+br)*8)
		{ // izbrisi selektiranog iz niza

		  for(i=Zazelenjeni;i<br;i++)
		   strcpy(Clan[i],Clan[i+1]);
		  br--;

		  // snimi novu datoteku

		  if((fp=fopen(FileName,"wt"))!=NULL)
		   { for(i=0;i<=br;i++)
		      fputs(Clan[i],fp);
		     fclose(fp);

		     _BEEP_H
		   }
		  else
		   Exit(5,"Programu je onemoguceno kreiranje DAT datoteke");

		  hide_mouse();

		  textbackground(LIGHTGRAY);
		  textcolor(BLACK);

		  return(TRUE);
		}
	       if(botun==2)
		{ while(botun)		        // ceka na opustanje botuna
		   get_mouse(&x,&y,&botun);

		  hide_mouse();
		  textbackground(BLUE);

		  for(i=0;i<=br;i++)
		   { gotoxy(28,6+i);
		     cprintf("%s",Clan[i]);
		   }

		  textbackground(LIGHTGRAY);
		  textcolor(BLACK);

		  return(FALSE);
		}
	     }
	    while(!kbhit() && !VanIzPetlje);

	    if(kbhit())
	     { slovo=bioskey(0);
	       switch(slovo)
		{ case B_ESC:
		       hide_mouse();
		       textbackground(BLUE);

		       for(i=0;i<=br;i++)
			{ gotoxy(28,6+i);
			  cprintf("%s",Clan[i]);
			}

		       textbackground(LIGHTGRAY);
		       textcolor(BLACK);

		       return(FALSE);
		  case B_ARROW_UP:
		       if(Zazelenjeni)
			Zazelenjeni--;
		       else
			Zazelenjeni=br;
		       set_mouse(27*8,(5+Zazelenjeni)*8);
		       break;
		  case B_ARROW_DOWN:
		       if(Zazelenjeni==br)
			Zazelenjeni=0;
		       else
			Zazelenjeni++;
		       set_mouse(27*8,(5+Zazelenjeni)*8);
		       break;
		  case B_ENTER:
		       // izbrisi selektiranog iz niza

		       for(i=Zazelenjeni;i<br;i++)
			strcpy(Clan[i],Clan[i+1]);
		       br--;

		       // snimi novu datoteku

		       if((fp=fopen(FileName,"wt"))!=NULL)
			{ for(i=0;i<=br;i++)
			   fputs(Clan[i],fp);
			  fclose(fp);

			  _BEEP_H
			}
		       else
			Exit(5,"Programu je onemoguceno kreiranje DAT datoteke");

		       hide_mouse();

		       textbackground(LIGHTGRAY);
		       textcolor(BLACK);

		       return(TRUE);
		  default: break;
		}
	     }
	  } // while(TRUE)
       } // else (br!=0)
    } // else (fopen)

   return(FALSE);
 }


char Dodaj(char *FileName)
 { FILE *fp;

   hide_mouse();

   gotoxy(1,25);
   cputs(" <");textcolor(RED);cputs("Esc");textcolor(BLACK);cputs("> otkazi  <");
   textcolor(RED);cputs("Enter");textcolor(BLACK);cputs("> pohrani                                    ");

   if((fp=fopen(FileName,"rt+"))!=NULL)
    { char Clan[27],
	   br;				// broj ucitanih

      br=0;
      while(!feof(fp) && br<11)
       if(fgets(Clan,27,fp)!=NULL) br++;

      if(br<11)
       { char *Unos(char *,char,char,char,char,char,char,char);
	 //!		24.10.'98 - nemam pojma sta ovde fali

	 gotoxy(28,6+br);
	 textbackground(LIGHTGREEN);
	 cputs("                         ");

	 gotoxy(28,6+br);
	 strcpy(Clan,Unos("\0",25+1,28,WHITE,LIGHTGREEN,
				       BLACK,LIGHTGRAY,FALSE));

	 if(strcmp(Clan,"\0"))
	  { char pronasao,
		 Ucitani[27];

	    if(strlen(Clan)<25)
	     { char i;
	       for(i=strlen(Clan);i<25;i++)
		Clan[i]=' ';
	       Clan[25]='\0';
	     }

	    pronasao=FALSE;
	    rewind(fp);
	    fgets(Ucitani,27,fp);
	    while(!feof(fp) && !pronasao)
	     { if(!strncmp(Ucitani,Clan,25))
		pronasao=TRUE;
	       else
		fgets(Ucitani,27,fp);
	     }

	    if(!pronasao)
	     { fputs(Clan,fp);
	       fputc('\n',fp);
	       unlink(FLRFILE);
	       _BEEP_H
	     }
	    else
	     { textbackground(BLUE);
	       gotoxy(28,6+br);
	       cputs("                         ");
	       textbackground(LIGHTGRAY);
	     }

	    fclose(fp);
	    return(!pronasao);
	  }
	 else
	  { fclose(fp);

	    textbackground(BLUE);
	    gotoxy(28,6+br);
	    cputs("                         ");
	    textbackground(LIGHTGRAY);

	    return(FALSE);
	  }
       } // if(br<11)
      else
       { fclose(fp);
	 _BEEP_B
	 return(FALSE);
       }
    }
   else
    Exit(5,"Programu je onemoguceno kreiranje DAT datoteke");

   return(0);
 }