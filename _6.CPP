#include "qwkfltr.h"

char Zeleni_6()
 { int x,y,botun,
       slovo;

   hide_mouse();
   textbackground(GREEN); _6
   textbackground(LIGHTGRAY); _1 _2
   gotoxy(1,25);cputs(" ( )  Izlazak iz programa                                               ");
   show_mouse();

   do
    { get_mouse(&x,&y,&botun);
      if(x>=(_6_NUM-1)*8 && x<=78*8 && y==0 && botun==1)
       { Prozor_6();
	 return (0);
       }
      if(x<(_6_NUM-1)*8 && y==0)
       return (0);
    }
   while(!kbhit());

   slovo=bioskey(0);
   switch(slovo)
    { case B_1M: case B_1V: set_mouse((_1_NUM-1)*8,0);break;
      case B_2M: case B_2V: set_mouse((_2_NUM-1)*8,0);break;
      case B_1ALT: Prozor_1();break;
      case B_2ALT: Prozor_2();break;
      case B_6ALT:
      case B_ENTER:      Prozor_6();               break;
      case B_ARROW_RIGH: set_mouse((_1_NUM-1)*8,0);break;
      case B_ARROW_LEFT: set_mouse((_2_NUM-1)*8,0);break;
      default:           break;
    }
   return(0);
 }

char Prozor_6(void)
 { int x,y,botun;
   char slovce;
   TextProzor *pProzor;

   hide_mouse();
   _1 _2
   sjencenje();
   textbackground(GREEN); _6
   textbackground(LIGHTGRAY);
   gotoxy(1,25);cputs(" (*)  Izlazak iz programa                                  ");

   pProzor = new TextProzor(8,10,72,12,"");

   gotoxy(22,11);
   cputs("Nastavi s izlaskom iz programa  (");
   textcolor(RED);  cputs("d");
   textcolor(BLACK);cputs("/");
   textcolor(RED);  cputs("n");
   textcolor(BLACK);cputs(")?");

   set_mouse(55*8,10*8);
   show_mouse();

   do
    { get_mouse(&x,&y,&botun);
      if((x==56*8 && y==10*8 && botun==1) || botun==2)
       { hide_mouse();
	 delete pProzor;
	 set_mouse((_1_NUM-1)*8,0);
	 show_mouse();
	 return (0);
       }
      if(x==54*8 && y==10*8 && botun==1)
	{ hide_mouse();
	  delete pProzor;
	  Exit(0);
	}
    }
   while(!kbhit());

   slovce=getch();
   if(slovce==0)
    getch();
   if(toupper(slovce)!='D')
    { hide_mouse();
      delete pProzor;
      set_mouse((_1_NUM-1)*8,0);
      show_mouse();
      return (0);
    }

   Exit(0);
   return(0);
 }
