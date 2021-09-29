
#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
typedef struct {
	INT8 vy;
} CUSTOM_DATA;
 const UINT8 anim_spin[] = {3,0,1,2};
 const UINT8 animopen[] = {5,3,4,5,6,7};
void Start_Machine(){
SetSpriteAnim(THIS, anim_spin, 10u);
// CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
// 	data->vy = 1;
}
void Update_Machine(){
    // CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	// if(TranslateSprite(THIS, 0, data->vy)) {
	// 	data->vy = -data->vy;
	// }
}
void Destroy_Machine(){

}