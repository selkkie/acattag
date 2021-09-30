#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Print.h"
extern Sprite* Creation;
extern UINT8 creation_shift;

const INT8 bshotdirections[4][2]={
    {-1,0},{0,-1},{1,0},{0,1}
};

typedef struct {
    UINT8 orientation; //L U R D
    UINT8 fliptime;
     INT8 vx;
    INT8 vy;

}CUSTOM_DATA;

UINT8 cb_frameskip =0;

UINT8 blob_fixedOrientation;
void Start_CreationBlob(){

}


void OrientBlob(){
  CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
     blob_fixedOrientation = (data->orientation+creation_shift)%4;

  
    switch(blob_fixedOrientation){
        case 0:
        if(data->orientation != 3){SetFrame(THIS,0);
        THIS->mirror=NO_MIRROR;}
        else{
            SetFrame(THIS,5);
            THIS->mirror=V_MIRROR;
        }

        break;
        case 1:
         if(data->orientation != 3){SetFrame(THIS,2);
           THIS->mirror=NO_MIRROR;}
           else{
               SetFrame(THIS,4);
               THIS->mirror=H_MIRROR;
           }
        break;
        case 2:
         if(data->orientation != 3){SetFrame(THIS,0);
         THIS->mirror=V_MIRROR;}
         else{
             SetFrame(THIS,5);
         }
        break;
        case 3:
         if(data->orientation != 3){SetFrame(THIS,2);
           THIS->mirror=H_MIRROR;}
        else{
            SetFrame(THIS,0);
        THIS->mirror=NO_MIRROR;
        }
        break;
        default: THIS->mirror=NO_MIRROR;break;

    }
}



void Update_CreationBlob(){
CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

data->fliptime++;
if(data->fliptime==50){
    SetFrame(THIS,((THIS->anim_frame+1)%2)+(data->orientation%2));
    data->fliptime=0;
  
   Sprite* spt = SpriteManagerAdd(Spit,THIS->x,THIS->y);
    CUSTOM_DATA* spitdata = (CUSTOM_DATA*)spt->custom_data;
    spitdata->orientation = data->orientation;
     spitdata->vx = bshotdirections[(data->orientation+creation_shift)%4][0];
      spitdata->vy = bshotdirections[(data->orientation+creation_shift)%4][1];

    // spitdata->vx=10;
    // spitdata->vy=0;

}

OrientBlob();//i dont want to call this on update but if we're doing turning shit it might be easiest


THIS->x= Creation->x+bshotdirections[(data->orientation+creation_shift)%4][0]*16;
THIS->y= Creation->y+bshotdirections[(data->orientation+creation_shift)%4][1]*16;


}
void Destroy_CreationBlob(){

}

