#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"



 const UINT8 anim_selectable[] = {4,0,1,2,1};


// enum mirror why[]={V_MIRROR,NO_MIRROR};

void Start_Selector(){

SetSpriteAnim(THIS, anim_selectable, 15u);


}

void Update_Selector(){
  

}

void Destroy_Selector(){

}