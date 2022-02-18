#include "qwkfltr.h"
#include "main.h"


struct CfgStrings CfgData[] =
    {
      { "qwkdir", NULL },
      { "arh",    NULL },
      { "dearh",  NULL },
      { NULL, NULL }         /* array terminator. REQUIRED !!! */
    };


void osnovna()
 { int x,y,botun;
   char Zeleni_1(),Zeleni_2(),Zeleni_6();

   _1 _2 _6
   show_mouse();

   while(TRUE)
    { get_mouse(&x,&y,&botun);
      if(x>=(_1_NUM-1)*8 && x<(_2_NUM-1)*8 && y==0) Zeleni_1();
      if(x>=(_2_NUM-1)*8 && x<=23*8 && y==0) 	    Zeleni_2();
      if(x>=(_6_NUM-1)*8 && x<=78*8 && y==0)        Zeleni_6();
    }
 }

void sjencenje()
 { textcolor(DARKGRAY);
   gotoxy(_1_NUM+1,1);cputs(A_1);
   gotoxy(_2_NUM+3,1);cputs(A_2);
   gotoxy(_6_NUM+1,1);cputs(A_6);
   textcolor(BLACK);
 }

void Direktoriji()
 { if(chdir(WORKDIR))
    { if(mkdir(WORKDIR))
	Exit(3,"Programu je onemoguceno kreiranje direktorija");
    }
   else chdir("..");

   if(chdir(CONFDIR))
    { if(mkdir(CONFDIR))
	Exit(3,"Programu je onemoguceno kreiranje direktorija");
    }
   else chdir("..");
 }


void KreirajCfg()
 { FILE *fp;

   if((fp=fopen(CFGFILE,"rt"))!=NULL)	// ako datoteka postoji
     fclose(fp);
   else					// ako datoteka ne postoji
    { if((fp=fopen(CFGFILE,"wt"))==NULL)
       Exit(5,"Programu je onemoguceno kreiranje CFG datoteke");
      else
       { fputs(CFGTXT,fp);
	 fclose(fp);
       }
    }
 }

/****************************************************************************/

char IsCfgSet()
 {
   return(strlen(CfgData[0].data) && strlen(CfgData[1].data)
				  && strlen(CfgData[2].data));
 }

char AreFilesSet()
 { char From,To,Subj,
	CurrFile(char *);

   From=CurrFile(FROMFILE);
   To=CurrFile(TOFILE);
   Subj=CurrFile(SUBJFILE);

   return(From || To || Subj);		// dovoljno je da jedna postoji
 }


char CurrFile(char *FileName)	       // koristi je samo AreFilesSet
 { FILE *fp;
   char RetValue;

   RetValue=TRUE;

   if((fp=fopen(FileName,"rt"))!=NULL)
    { fseek(fp,0,SEEK_END);
      if(!ftell(fp))
       RetValue=FALSE;
      fclose(fp);
    }
   else
    RetValue=FALSE;

   return(RetValue);
 }

/****************************************************************************/

void Filtriranje(char *Direktorij)
 { ffblk ffblk;
   CLista *poc_T,		// pocetak To liste
	  *poc_F,         	// pocetak From liste
	  *poc_S;         	// pocetak Subject liste
   void IzbrisiListu(CLista *);
   char IsInFile(struct ffblk,char *),
	strFind[MAXPATH],
	CListePopunjene,		// TRUE || FALSE
	NekiDrugiDir;			// ---- || -----
   int done;				// kontrola petlje, int za > 256

   poc_T=KRAJ_LISTE;
   poc_F=KRAJ_LISTE;
   poc_S=KRAJ_LISTE;
   CListePopunjene=FALSE;
   if(strcmp(Direktorij,CfgData[0].data))
    NekiDrugiDir=TRUE;
   else
    NekiDrugiDir=FALSE;

   // uzmi svaku datoteku iz direktorija

   strcpy(strFind,Direktorij);
   strcat(strFind,"*.*");
   done=findfirst(strFind,&ffblk,0);
   while(!done)
    { if(!(IsInFile(ffblk,NQWKFILE) || IsInFile(ffblk,FLRFILE)))
       { void Odpakiraj(char *),
	      OcistiWorkDir(),
	      PutFDataInFile(struct ffblk,char *);
	 char IsQwk(),
	      strFile[MAXPATH];

	 strcpy(strFile,Direktorij);
	 strcat(strFile,ffblk.ff_name);
	 Odpakiraj(strFile);

	 if(!IsQwk())
	  { if(!NekiDrugiDir)
	      PutFDataInFile(ffblk,NQWKFILE);
	    OcistiWorkDir();
	  }
	 else
	  { void Zapakiraj(char *),
		 Kopiraj(char *,char *);
	    char FiltrirajPaket(char *,CLista *,CLista *,
					        CLista *),
		 NewPath[MAXPATH];
	    struct ffblk GetNewffblk(char *);
	    CLista *PopuniListu(char *FileName);

	    if(!CListePopunjene)
	     { poc_F=PopuniListu(FROMFILE);
	       poc_T=PopuniListu(TOFILE);
	       poc_S=PopuniListu(SUBJFILE);
	       CListePopunjene=TRUE;
	     }

	    if(FiltrirajPaket(ffblk.ff_name,poc_F,poc_T,poc_S))
	     { void UpdateNdxFiles();

	       UpdateNdxFiles();
	       Zapakiraj(ffblk.ff_name);
	       Kopiraj(ffblk.ff_name,Direktorij);
	     }

	    // upisi podatke nove datoteke u datoteku filtriranih paketa

	    strcpy(NewPath,Direktorij);
	    strcat(NewPath,ffblk.ff_name);
	    if(!NekiDrugiDir)
	      PutFDataInFile(GetNewffblk(NewPath),FLRFILE);

	    OcistiWorkDir();
	  }
       }
      done=findnext(&ffblk);
    }
   if(CListePopunjene)
    { IzbrisiListu(poc_F);
      IzbrisiListu(poc_T);
      IzbrisiListu(poc_S);
    }

   _BEEP_H
   puts("\nFiltrirano!\n\n\n");
 }


void UpdateNdxFiles()
 {
   if(!chdir(WORKDIR))
    { FILE *fpMsg;

      if((fpMsg=fopen("MESSAGES.DAT","rb"))!=NULL)
       { int done;
	 ffblk ffblk;
	 char UserName[25],
	      *GetUserName();

	 strcpy(UserName,GetUserName());

	 done=findfirst("*.NDX",&ffblk,0);
	 while(!done)
	  { FILE *fpNdx;

	    if((fpNdx=fopen(ffblk.ff_name,"wb"))!=NULL)
	      { long rbrBloka;
		char IzbrisiNdx;
		MsgHeader Header;

		IzbrisiNdx=TRUE;

		fread(&Header,128,1,fpMsg);
		fread(&Header,128,1,fpMsg);
		rbrBloka=0;

		while(!feof(fpMsg))
		 { int BlNum;
		   if(atoi(ffblk.ff_name)==Header.ConferenceNum ||
		     (!strcmpi(ffblk.ff_name,"PERSONAL.NDX") &&
		      !strncmpi(Header.To,UserName,strlen(UserName)-1)))
		    { float IEEEToMSBIN(float),
			    f_out,f_in;

		      f_in=rbrBloka;
		      f_out=IEEEToMSBIN(f_in);

		      fwrite(&f_out,sizeof(float),1,fpNdx);
		      fwrite(&Header.ConferenceNum,sizeof(char),1,fpNdx);

		      IzbrisiNdx=FALSE;
		    }
		   //fseek(fpMsg,128*(atoi(Header.NumOfBlocks)-1),SEEK_CUR);
		   BlNum=atoi(Header.NumOfBlocks)-1;
		   while(BlNum)
		    { fseek(fpMsg,128,SEEK_CUR);
		      BlNum--;
		    }

		   if(!rbrBloka) rbrBloka=2;
		   rbrBloka+=atoi(Header.NumOfBlocks);

		   fread(&Header,128,1,fpMsg);
		 }

		fclose(fpNdx);

		if(IzbrisiNdx) unlink(ffblk.ff_name);

		rewind(fpMsg);
	      }
	    else Exit(5,"Programu je onemoguceno kreiranje NDX datoteke");

	    done=findnext(&ffblk);
	  }     			// while ima NDXa
	 fclose(fpMsg);
       }
      else Exit(4,"Programu je onemoguceno citanje MESSAGES.DAT datoteke");

      chdir("..");
    }
   else	Exit(2,"Programu je onemogucena promjena direktorija");
 }


char *GetUserName()
 { char UserName[25],
	i;
   FILE *fp;

   if((fp=fopen("CONTROL.DAT","rt"))!=NULL)
    {
      for(i=1;i<=7;fgets(UserName,26,fp),i++);

      fclose(fp);
    }
   else Exit(4,"Programu je onemoguceno citanje CONTROL.DAT datoteke");

   return(UserName);
 }


void IzbrisiListu(CLista *pocetak)
 { CLista *pposljednji,*brisanje;

   while(pocetak->pNext!=KRAJ_LISTE)
    {
      // nadji pretposljednji clan liste

      for(pposljednji=pocetak;pposljednji->pNext->pNext!=KRAJ_LISTE;
			      pposljednji=pposljednji->pNext);

      // postavi pokazivac za brisanje na posljednjeg clana liste

      brisanje=pposljednji->pNext;
      pposljednji->pNext=KRAJ_LISTE;    // pretposljednji proglasi posljednjim
      free((CLista *) brisanje); // oslobodi clana za brisanje
    }

   free((CLista *) pocetak);
   pocetak=KRAJ_LISTE;
 }


char FiltrirajPaket(char *FileName,CLista *poc_F,
				   CLista *poc_T,
				   CLista *poc_S)
 { FILE *RdFile;
   char RetVal;

   printf("\n%-*s ",12,FileName);

   RetVal=FALSE;

   if(!chdir(WORKDIR))
    { if((RdFile=fopen("MESSAGES.DAT","rb"))!=NULL)
       { char name[13];
	 FILE *WrFile;

	 tmpnam(name);
	 if((WrFile=fopen(name,"wb"))!=NULL)
	  { char String[129],
		 U_Listi(char *,CLista *);
	    MsgHeader Header;

	    fread(String,128,1,RdFile);	   // procitaj prvi 128B blok iz datoteke za citanje
	    fwrite(String,128,1,WrFile);   // upisi ucitani blok u datoteku za pisanje

	    fread(&Header,128,1,RdFile);
	    while(!feof(RdFile))
	     { if(U_Listi(Header.From,poc_F) || U_Listi(Header.To,poc_T) ||
		  U_Listi(Header.Subject,poc_S))
		{ int BlNum;

		  //fseek(RdFile,128*(atoi(Header.NumOfBlocks)-1),SEEK_CUR);
		  BlNum=atoi(Header.NumOfBlocks)-1;
		  while(BlNum)
		   { fseek(RdFile,128,SEEK_CUR);
		     BlNum--;
		   }

		  RetVal=TRUE;
		  printf(".");
		}
	       else
		{ unsigned int br;

		  fwrite(&Header,128,1,WrFile);

		  br=0;
		  while(br!=(atoi(Header.NumOfBlocks)-1))
		   { fread(String,128,1,RdFile);
		     fwrite(String,128,1,WrFile);

		     br++;
		   }
		}

	       fread(&Header,128,1,RdFile);
	     }                          // while(feof(RdFile))
	    fclose(WrFile);
	    fclose(RdFile);
	    if(RetVal)                  // ako je return value TRUE
	     { unlink("MESSAGES.DAT");
	       rename(name,"MESSAGES.DAT");
	     }
	    else                        // promjene nisu izvrsene
	     unlink(name);
	  }
	 else
	  Exit(5,"Programu je onemoguceno kreiranje TMP datoteke");
       }
      else
       Exit(4,"Programu je onemoguceno citanje MESSAGES.DAT datoteke");

      chdir("..");			// vrati stari workdir
    }
   else	Exit(2,"Programu je onemogucena promjena direktorija");

   return(RetVal);
 }


char U_Listi(char *Zadani,CLista *poc_Liste)
 { CLista *test;

   for(test=poc_Liste;test!=KRAJ_LISTE;test=test->pNext)
    if(!strncmpi(Zadani,test->Clan,25))
      return(TRUE);

   return(FALSE);
 }


CLista *PopuniListu(char *FileName)
 { FILE *fp;
   CLista *pocetak,*kraj,*novi;
   char String[26];

   pocetak=KRAJ_LISTE;

   if((fp=fopen(FileName,"rt"))!=NULL)
    { char br;

      fgets(String,27,fp);

      br=0;
      while(!feof(fp) && br<11)		// dok nije kraj datoteke; br treba!
       { novi=(CLista *) malloc(sizeof(CLista));
	 if(novi==NULL)
	  Exit(8,"Program nema dovoljno slobodne memorije");

	 strcpy(novi->Clan,String);
	 novi->pNext=KRAJ_LISTE;

	 if(pocetak==KRAJ_LISTE)
	  pocetak=kraj=novi;
	 else
	  { kraj->pNext=novi;		// zadnji element pokazuje na sljedeci
	    kraj=novi;			// novi postaje zadnji
	  }

	 fgets(String,27,fp);
	 br++;
       }

      fclose(fp);
    }

   return(pocetak);
 }

char IsInFile(ffblk ffblk,char *FileName)
 { FILE *fp;

   if((fp=fopen(FileName,"rt"))!=NULL)
    { char pronasao,is_nqwk;
      struct ffblk Ucitan;

      if(!strcmp(FileName,NQWKFILE))
       { is_nqwk=TRUE;
	 fscanf(fp,"%s",Ucitan.ff_name);
       }
      else
       { is_nqwk=FALSE;
	 fscanf(fp,"%s %ld %i %i",Ucitan.ff_name,&Ucitan.ff_fsize,
				 &Ucitan.ff_fdate,&Ucitan.ff_ftime);
       }

      pronasao=FALSE;
      while(!pronasao && !feof(fp))
       { if(!strcmp(Ucitan.ff_name,ffblk.ff_name))
	  { if(is_nqwk)
	     pronasao=TRUE;
	    else
	     { if(Ucitan.ff_fsize==ffblk.ff_fsize)
		{ if(Ucitan.ff_fdate==ffblk.ff_fdate)
		   { if(Ucitan.ff_ftime==ffblk.ff_ftime)
		      pronasao=TRUE;
		   }
		}
	     }
	  }

	 if(is_nqwk)
	  fscanf(fp,"%s",Ucitan.ff_name);
	 else
	  fscanf(fp,"\n%s %ld %i %i",Ucitan.ff_name,&Ucitan.ff_fsize,
				    &Ucitan.ff_fdate,&Ucitan.ff_ftime);
       }
      fclose(fp);
      return(pronasao);
    }
   else
    { if((fp=fopen(FileName,"wt"))!=NULL)
       { fclose(fp);
	 return(FALSE);
       }
      else
       Exit(5,"Programu je onemoguceno kreiranje DAT datoteke");
    }

   return(0);
 }


void Odpakiraj(char *FileName)
 { char ExeString[MAXPATH],
	br,pronasao;


   // potrazi '!' u DeArhu

   br=0;
   pronasao=FALSE;
   while(!pronasao && br<strlen(CfgData[2].data))
    { if(CfgData[2].data[br]=='!')
       pronasao=TRUE;
      else
       br++;
    }

   if(br==strlen(CfgData[2].data) && !pronasao)
    Exit(7,"Krivo konfiguriran parametar dearhivera");		//! - nije potreban perror


   // na njegovo mjesto ubaci kompletan path datoteke

   strncpy(ExeString,CfgData[2].data,br);
   ExeString[br]='\0';
   strcat(ExeString,FileName);
   strcat(ExeString,&CfgData[2].data[br+1]);
   strcat(ExeString," ");
   strcat(ExeString,WORKDIR);
   strcat(ExeString," > lstdearh.log");

   // printf("\n%s",ExeString);

   system(ExeString);
 }


char IsQwk()
 { FILE *fp;
   char FileName[MAXPATH];

   strcpy(FileName,WORKDIR);
   strcat(FileName,"\\CONTROL.DAT");

   if((fp=fopen(FileName,"rt"))!=NULL)
    { fclose(fp);
      return(TRUE);
    }
   else
    return(FALSE);
 }


void OcistiWorkDir()
 { ffblk ffblk;
   int done;
   char path[MAXPATH],
	FileName[MAXPATH];

   strcpy(path,".\\");
   strcat(path,WORKDIR);
   strcat(path,"\\");
   strcpy(FileName,path);
   strcat(path,"*.*");

   done = findfirst(path,&ffblk,0);
   while (!done)
   { char strNew[MAXPATH];

     strcpy(strNew,FileName);
     strcat(strNew,ffblk.ff_name);

     remove(strNew);
     done = findnext(&ffblk);
   }
 }


void PutFDataInFile(ffblk ffblk,char *FileName)
 { FILE *fp;

   if((fp=fopen(FileName,"at"))!=NULL)
    {
      if(!strcmp(FileName,NQWKFILE))
       fprintf(fp,"%s\n",ffblk.ff_name);
      else
       fprintf(fp,"%s %ld %i %i\n",ffblk.ff_name,ffblk.ff_fsize,
				   ffblk.ff_fdate,ffblk.ff_ftime);
      fclose(fp);
    }
   else
    Exit(5,"Programu je onemoguceno kreiranje DAT datoteke");
 }


void Zapakiraj(char *FileName)
 { char strExe[MAXPATH],
	br,pronasao;


   // potrazi '!' u Arhu

   br=0;
   pronasao=FALSE;
   while(!pronasao && br<strlen(CfgData[1].data))
    { if(CfgData[1].data[br]=='!')
       pronasao=TRUE;
      else
       br++;
    }

   if(br==strlen(CfgData[1].data) && !pronasao)
    Exit(6,"Krivo konfiguriran parametar arhivera");		//! - nije potreban perror


   // na njegovo mjesto ubaci kompletan path datoteke

   strncpy(strExe,CfgData[1].data,br);
   strExe[br]='\0';
   strcat(strExe,".\\");
   strcat(strExe,WORKDIR);
   strcat(strExe,"\\");
   strcat(strExe,FileName);
   strcat(strExe,&CfgData[1].data[br+1]);
   strcat(strExe," ");
   strcat(strExe,WORKDIR);
   strcat(strExe,"\\*.* > lstarh.log");

   // printf("\n%s",strExe);

   system(strExe);
 }


void Kopiraj(char *FileName,char *Direktorij)
 { char FromPath[MAXPATH],
	ToPath[MAXPATH];
   int file_copy(char *,char*);

   strcpy(FromPath,".\\");
   strcat(FromPath,WORKDIR);
   strcat(FromPath,"\\");
   strcat(FromPath,FileName);

   strcpy(ToPath,Direktorij);
   strcat(ToPath,FileName);

   // printf("\n%s %s",FromPath,ToPath);

   file_copy(FromPath,ToPath);
 }


ffblk GetNewffblk(char *NewPath)
 { ffblk ffblk;

   findfirst(NewPath,&ffblk,0);
   return(ffblk);
 }


/****************************************************************************/

int main(int argc,char *argv[])
 { void peglaj(),        		// pituravanje ekrana
	ChangeDir(char **argv),         // ulazak u dir u kojem se nalazi program
	Direktoriji(),		// kreiranje potrebnih dir za program
	KreirajCfg();		// kreiranje cfg datoteke
   char IsCfgSet(),
	AreFilesSet();

   ChangeDir(argv);

   unlink("lstarh.log");
   unlink("lstdearh.log");
   OcistiWorkDir();

   Direktoriji();
   KreirajCfg();
   CfgRead(CFGFILE, CfgData);

   if(IsCfgSet() && AreFilesSet() && strcmpi(argv[1],"cfg"))
    { void Filtriranje(char *Direktorij);

      if(argc==1)
       { printf(PRPT_MAIN);
	 Filtriranje(CfgData[0].data);
       }
      else if(argc>2 || !strcmp(argv[1],"/?"))
       { printf(PRPT_MAIN);
	 printf(PRPT_KAKO);
       }
      else
       { char dir[MAXPATH];

	 strcpy(dir,argv[1]);
	 printf(PRPT_MAIN);

	 if(argv[1][strlen(argv[1])-1]!='\\')
	  strcat(dir,"\\");

	 printf("\nFiltriram postu u direktoriju  %s\n",dir);
	 Filtriranje(dir);
       }
    }
   else
    { mouse_install();
      mouse_vert(0,23*8);
      set_mouse(1*8,0);

      _setcursortype(_NOCURSOR);
      textcolor(BLUE);
      textbackground(LIGHTGRAY);
      peglaj();

      osnovna();
    }

   Exit();
   return(0);
 }