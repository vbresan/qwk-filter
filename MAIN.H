#ifndef	_MAIN_H_
#define	_MAIN_H_

#include <alloc.h>


#define KRAJ_LISTE (CLista *) NULL

#define PRPT_MAIN "\n\n\n\t\t  QWK Filter  1.0   (c) 1998\n\ne-mail:                             \n\n"
#define PRPT_KAKO "\nPokretanja programa:\t(1) qwkfltr\n                  \t(2) qwkfltr neki_direktorij\n                  \t(3) qwkfltr cfg\n\n(1) pokretanje filtera sa konfiguriranim parametrima\n(2) filtriranje paketa u direktoriju neki_direktorij\n(3) pokretanje konfiguracije filtera\n"


struct CLista
 { char Clan[26];
   CLista *pNext;
 };


struct MsgHeader
 { char StatusFlag;         		//
   char MsgNum[7];          		// ASCII
   char Date[8];            		// ASCII
   char Time[5];            		// ASCII
   char To[25];             		//
   char From[25];           		//
   char Subject[25];        		// (mixed case)
   char Password[12];       		//
   char ReferenceMsgNum[8]; 		// ASCII
   char NumOfBlocks[6];     		// ASCII
   char Flag;               		//
   unsigned int ConferenceNum;		// unsigned word
   unsigned int LogicalMsgNum;          // unsigned word
   char HasTag;                         //
 };

#endif