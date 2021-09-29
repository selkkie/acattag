#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"

#include "Keys.h"
extern BYTE door;
 extern Sprite* sprite_body;
 const UINT8 anim_wwalk[] = {2,0,1};
 const UINT8 anim_widle[] = {1,0};

enum mirror why[]={V_MIRROR,NO_MIRROR};

void Start_SpritePlayerHead(){
SetSpriteAnim(THIS, anim_widle, 3u);
THIS->mirror = why[door];

}

void Update_SpritePlayerHead(){
  
    THIS->x = sprite_body->x;
    THIS->y = sprite_body->y - 16u;
			//Choose idle anim or walk
			if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
				SetSpriteAnim(THIS, anim_wwalk, 10u);
			} else {
				SetSpriteAnim(THIS, anim_widle, 3u);
			}
    	if(KEY_PRESSED(J_RIGHT)) {
		SetSpriteAnim(THIS, anim_wwalk, 3u);
		THIS->mirror = NO_MIRROR;
	
	} else if(KEY_PRESSED(J_LEFT)) {
        SetSpriteAnim(THIS, anim_wwalk, 3u);
		THIS->mirror = V_MIRROR;

	}

	// if(KEY_PRESSED(J_LEFT) || KEY_PRESSED(J_RIGHT)){
	// 	SetSpriteAnim(THIS, anim_wwalk, 14u);
	// } else {
	// 	SetSpriteAnim(THIS, anim_widle, 9u);
	// }

	// THIS->x = sprite_body->x;
	// THIS->y = sprite_body->y + 13u;

	
	// if(sprite_body->flags == OAM_VERTICAL_FLAG) {
	// 	THIS->flags = OAM_VERTICAL_FLAG;
	// } else if(sprite_body->flags == 0u) {
	// 	THIS->flags = 0u;
	// }
}

void Destroy_SpritePlayerHead(){

}