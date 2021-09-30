#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include <gb/gb.h>
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Palette.h"
#include "Keys.h"
#include "Sound.h"
#include "Music.h"
#include "Print.h"
#include "Palette.h"
#include "rand.h"
#include <stdlib.h>

DECLARE_MUSIC(synthesizer);
IMPORT_MAP(menu_high_map);

IMPORT_TILES(terminalfont);

Sprite* selector1;//|-
Sprite* selector2;//-|
Sprite* selector3;//|_
Sprite* selector4;//_|

Sprite* slotWorm;
Sprite* slotCrab;
Sprite* slotDrip;

Sprite* slotArmL;
Sprite* slotHead;
Sprite* slotArmR;
Sprite* slotFoot;

Sprite* body;

const char* codons[]= {"'","(",")","-"};

UINT8 sframeskip = 0;
extern BYTE dosynthesis;
extern BYTE frommachine;
extern BYTE scanventory[];
//worm,crab,blob
		char snum[5];
const UINT8 VPD[14][2]= {
	{32,8},{48,8},{64,8},{80,8},{96,8},{112,8},{128,8},
	{88,48},
	{72,64},{88,64},{104,64},
	{88,80},{128,96},
	{88,112}
	};
const UINT8 ValidPositions[] = 
{1,2,3,4,5,6,7,
12,
21,22,23,
32,33,
42};
UINT8 CurrentPosition;
const INT8 sizes[14][2] = {
	{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
	{0,0},
	{0,0},{0,0},{0,0},
	{0,0},{-8,-8},
	{40,5}
	};

INT8 scanselection = -1;
//UINT8 bordertiles[] = {3,4,5,11,13,18,24,25,26,27};

UINT8 creationPieces[] = {1,3,3,0}; //ARML, UP, ARMR, DOWN
char* pnames[] = {"","WORM","CRAB","BLOB"};

 const UINT8 ac1[] = {6,0,1,2,3,4,5}; //god i dont fxngngk understand c why did i decide to do this, duplicating everything everywhere hurts me so
const UINT8 ac2[] = {6,3,4,5,2,4,1};
const UINT8 stopac[] = {2,6,6};

void ShowMessage(char* w1, char* w2){
 	  PRINT_POS(2,6);
 	Printf(w1);
 PRINT_POS(2,7);
 	Printf(w2);

}
void HideMessage(){
	PRINT_POS(2,6);
 	Printf("    ");
 PRINT_POS(2,7);
 		Printf("    ");
}

void CheckSelect(){
HideMessage();


switch(CurrentPosition){
	case 0: if(scanventory[0]) ShowMessage("WORM","");break;
	case 1: if(scanventory[1]) ShowMessage("CRAB","");break;
	case 2: if(scanventory[2]) ShowMessage("BLOB","");break;
	case 7: ShowMessage(pnames[creationPieces[1]],"Head");break;
	case 8: ShowMessage(pnames[creationPieces[0]],"Arm");break;
	case 9: ShowMessage("BASE","BODY");break;
	case 10: ShowMessage(pnames[creationPieces[2]],"Arm");break;
	case 11:  ShowMessage(pnames[creationPieces[3]],"LEGS");break;
	case 12: ShowMessage("EXIT","");break;
	case 13: ShowMessage("MAKE","IT!!");break;
}

}
void UpdatePieces(){
	SetFrame(slotArmL,creationPieces[0]);
	SetFrame(slotHead,creationPieces[1]);
	SetFrame(slotArmR,creationPieces[2]);
	SetFrame(slotFoot,creationPieces[3]);
	CheckSelect();
	
}
void START() {
initrand(delta_time);
    	OBP0_REG = PAL_DEF(3,2,1,0);
	BGP_REG = PAL_DEF(3,2,1,0);
	 
	   WX_REG = 7;
	   WY_REG = 144;
 //CurrentPosition= scanventory[0]+scanventory[1]+scanventory[2]; //make it always show up one to the right so i dont have to fix the textbox
	 CurrentPosition = 0; //haha jk the problem of selector mismatch would kick in and that's so much worse
    InitScroll(BANK(menu_high_map), &menu_high_map, 0, 0);


	//selector1=SpriteManagerAdd(Selector,39,14);
	selector1=SpriteManagerAdd(Selector,32,8);
	selector2=SpriteManagerAdd(Selector,160,0); //i guess we're using these as indicators now
	selector3=SpriteManagerAdd(Selector,160,0);
	selector4=SpriteManagerAdd(Selector,32,8);
	selector2->mirror=H_MIRROR;
	selector3->mirror=V_MIRROR;
	selector4->mirror=HV_MIRROR;
	slotWorm=SpriteManagerAdd(Scanned,32,8);
	
	
	//SPRITE_SET_PALETTE(Scanned,PAL_DEF(0,1,2,3));
	slotCrab=SpriteManagerAdd(Scanned,48,8);
    slotDrip= SpriteManagerAdd(Scanned,64,8);

	slotArmL = SpriteManagerAdd(Scanned,72,64);
	slotArmR = SpriteManagerAdd(Scanned,104,64);
	slotFoot =  SpriteManagerAdd(Scanned,88,80);
	slotHead =SpriteManagerAdd(Scanned,88,48);

	body = SpriteManagerAdd(Scanned,88,64);
	SetFrame(body,4);
	 INIT_FONT(terminalfont,PRINT_BKG);

	  PlayMusic(synthesizer,1);



	if (scanventory[0] == 1)SetFrame(slotWorm,1);
	if (scanventory[1] == 1)SetFrame(slotCrab,2);
	if (scanventory[2] == 1)SetFrame(slotDrip,3);
	
UpdatePieces();

}




void UpdatePosition(){

	selector1->x = VPD[CurrentPosition][0];
	selector1->y = VPD[CurrentPosition][1];
	// selector2->x = VPD[CurrentPosition][0]+sizes[CurrentPosition][0];
	// selector2->y = VPD[CurrentPosition][1];
	// selector3->x = VPD[CurrentPosition][0];
	// selector3->y = VPD[CurrentPosition][1]+sizes[CurrentPosition][1];
	//I have literally no clue why these two doesn't work but the one below does, it makes no sense whatsoever to me. possibly some quirk of mirroring?
	selector4->x = VPD[CurrentPosition][0]+sizes[CurrentPosition][0];
	selector4->y = VPD[CurrentPosition][1]+sizes[CurrentPosition][1];

// char snum[5];
// iota(CurrentPosition, snum);
// PRINT_POS(0,0);
// Printf(snum);
CheckSelect();

}
void UpdateSelection(){
	if(scanselection==-1){
	selector2->x = 160;
	selector2->y = 0;
	selector3->x =160;
	selector3->y =0;
	}
	else{
	selector2->x = VPD[scanselection][0];
	selector2->y = VPD[scanselection][1];
	selector3->x = VPD[scanselection][0];
	selector3->y = VPD[scanselection][1];
	}


}
// INT8 valueinarray(UINT8 val, UINT8 arr[])
// {
//     int i;
//     for(i = 0; i < sizeof(arr) ; i++)
//     {
// 		PRINT_POS(0,15);
// 		Printf("x");
// 		iota(arr[i],snum);
// 		Printf(snum);
//         if(arr[i] == val)
//             return i;
//     }
//     return -1;
// }


void CODONS(){

	
	int codenum = abs(rand()%4);

		PRINT_POS(2,15);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(3,15);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(4,15);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(5,15);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(2,14);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(3,14);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(4,14);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(5,14);
	Printf(codons[codenum]);

codenum = abs(rand()%4);
		PRINT_POS(2,13);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(3,13);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(4,13);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(5,13);
	Printf(codons[codenum]);
codenum = abs(rand()%4);

codenum = abs(rand()%4);
		PRINT_POS(2,12);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(3,12);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(4,12);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(5,12);
	Printf(codons[codenum]);
codenum = abs(rand()%4);

codenum = abs(rand()%4);
		PRINT_POS(2,11);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(3,11);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(4,11);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
		PRINT_POS(5,11);
	Printf(codons[codenum]);
codenum = abs(rand()%4);
	// int z;
	// int a;
	// for (z=11;z<15;z++){
	// 	for (a=2;z<6;a++){
	// 		PRINT_POS(1,4);
	// 		Printf(a);
	// 		PRINT_POS(1,6);
	// 		Printf(z);
	// 		//Printf(codons[0]);
	// 		codenum = rand()%4;PRINT_POS(0,5);	
	// 	}
	// } why doesn't this work? who knows, fuck me
	

}


void UPDATE() {
	
	sframeskip++;
	if(sframeskip>5){
		sframeskip = 0;
		
			CODONS();
	}

	//start to exit, as convenient as it is, confuses some players, i'm disabling it for now to force people to find the exit button
    // 	if(KEY_PRESSED(J_START)){ 
	// PlayFx(CHANNEL_1, 4, 0x7C, 0x87, 0x53, 0x66,0x86);
	// SetState(StateGame);
	// }

if(KEY_TICKED(J_B)||KEY_TICKED(J_SELECT)){
	if(CurrentPosition<3 && scanventory[CurrentPosition]==1){
		PlayFx(CHANNEL_1, 4, 0x7C, 0x87, 0x53, 0x66,0x86);
		//also add check for hascreat... maybe we make that an array of bytes
		if(scanselection != CurrentPosition)scanselection = CurrentPosition;
		else scanselection = -1;
		UpdateSelection();
		
	}
	else if (CurrentPosition>6 && CurrentPosition<12){
		PlayFx(CHANNEL_1, 4, 0x7C, 0x87, 0x53, 0x66,0x86);
		switch(CurrentPosition){
			case 7:
				if(creationPieces[1]!=scanselection+1)creationPieces[1]=scanselection+1;
				else creationPieces[1]=0;
				break;
			case 8:
				if(creationPieces[0]!=scanselection+1)creationPieces[0]=scanselection+1;
				else creationPieces[0]=0;
				break;
			case 10:
				if(creationPieces[2]!=scanselection+1)creationPieces[2]=scanselection+1;
				else creationPieces[2]=0;
				break;
			case 11:
				if(creationPieces[3]!=scanselection+1)creationPieces[3]=scanselection+1;
				else creationPieces[3]=0;
				break;
			default:break;
			
		}
		UpdatePieces();
		
		
	}
	else if (CurrentPosition == 12){
		frommachine = 1;
		SetState(StateGame);}
	else if (CurrentPosition == 13){
			frommachine = 1;
			dosynthesis = 1;
		SetState(StateGame);
	
		}//and then also add creation on spawn, probs with another external

}
		
		if(KEY_TICKED(J_LEFT)){
			if(CurrentPosition!=0){
				CurrentPosition--;
				UpdatePosition();
			}
						else{
				CurrentPosition=13;UpdatePosition();
			}

		}
		else if(KEY_TICKED(J_RIGHT)){
			if(CurrentPosition!=13){
				CurrentPosition++;
				UpdatePosition();
			
			}
						else{
				CurrentPosition=0;UpdatePosition();
			}

		}
			else if(KEY_TICKED(J_UP)){
				if(CurrentPosition!=0){
				CurrentPosition--;
				UpdatePosition();
			}
						else{
				CurrentPosition=13;UpdatePosition();
			}

		}
			else if(KEY_TICKED(J_DOWN)){

				
				if(CurrentPosition!=13){
				CurrentPosition++;
				UpdatePosition();
			}
			else{
				CurrentPosition=0;UpdatePosition();
			}
		/*	
		//	if(ValidPositions[CurrentPosition]!=41){//why did i do it differently this time did i just forget to update this
			if(CurrentPosition!=13){
				UINT8 m;
				
				m = ValidPositions[CurrentPosition]+10;
				if(valueinarray(m,ValidPositions)!=-1){
					PRINT_POS(0,3);
					Printf("valid");
					CurrentPosition= m+1;
					UpdatePosition();
				}
				else if(valueinarray(m-(m%10)+2,ValidPositions)!=-1){
					PRINT_POS(0,3);
					Printf("invalid");
					//my head hurts
					CurrentPosition = m;
					UpdatePosition();
				//CurrentPosition=valueinarray(m-(m%10)+2,ValidPositions)+1;
				}
				INT8 x = valueinarray(m,ValidPositions);
				INT8 y = valueinarray(m-(m%10)+2,ValidPositions);
				iota(x, snum);
						PRINT_POS(0,0);
					Printf(snum);
					iota(y, snum);
							PRINT_POS(0,1);
					Printf(snum);
				
			}*/

		}
		
	
	


}

