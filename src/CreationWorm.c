#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Print.h"
extern Sprite *Creation;

extern UINT8 creation_shift;
const INT8 wshotdirections[4][2] = {
    {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
extern BYTE CreationDead;
typedef struct
{
    UINT8 orientation; //L U R D
    UINT8 fliptime;
    INT8 vx;
    INT8 vy;
} CUSTOM_DATA;
BYTE flipanimworm = 0;

UINT8 worm_fixedOrientation;
// void CreateWorm(UINT8 cwx,UINT8 cwy,Sprite* cwParent, UINT8 cwOrientation){
//     //  spr;
//   Sprite* spr= SpriteManagerAdd(CreationWorm,cwx,cwy);
//  CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
//  data->parent =cwParent;
//   data->orientation=cwOrientation;
//   data->
//  //return spr;
// }

void Start_CreationWorm()
{
    CUSTOM_DATA *data = (CUSTOM_DATA *)THIS->custom_data;

    data->fliptime = 0;
}

void OrientWorm()
{

    CUSTOM_DATA *data = (CUSTOM_DATA *)THIS->custom_data;

    worm_fixedOrientation = (data->orientation + creation_shift) % 4;

    switch (worm_fixedOrientation)
    {
    case 0:
        if (flipanimworm == 0)
        {
            if (data->orientation != 3)
            {
                SetFrame(THIS, 1);
                THIS->mirror = NO_MIRROR;
            }
            else
            {
                SetFrame(THIS, 5);
                THIS->mirror = V_MIRROR;
            }
        }
        else
        {
            if (data->orientation != 3)
            {
                SetFrame(THIS, 0);
                THIS->mirror = NO_MIRROR;
            }
            else
            {
                SetFrame(THIS, 5);
                THIS->mirror = NO_MIRROR;
            }
        }

        break;
    case 1:
        if (flipanimworm == 0)
        {
            if (data->orientation != 3)
            {
                SetFrame(THIS, 3);
                THIS->mirror = NO_MIRROR;
            }
            else
            {
                SetFrame(THIS, 4);
                THIS->mirror = HV_MIRROR;
            }
        }
        else
        {
            if (data->orientation != 3)
            {
                SetFrame(THIS, 2);
                THIS->mirror = NO_MIRROR;
            }
            else
            {
                SetFrame(THIS, 4);
                THIS->mirror = H_MIRROR;
            }
        }
        break;
    case 2:
        if (flipanimworm == 0)
        {
            if (data->orientation != 3)
            {
                SetFrame(THIS, 1);
                THIS->mirror = V_MIRROR;
            }
            else
            {
                SetFrame(THIS, 5);
            }
        }
        else
        {
            if (data->orientation != 3)
            {
                SetFrame(THIS, 0);
                THIS->mirror = V_MIRROR;
            }
            else
            {
                SetFrame(THIS, 5);
                THIS->mirror = H_MIRROR;
            }
        }
        break;
    case 3:
        if (flipanimworm == 0)
        {
            if (data->orientation != 3)
            {
                SetFrame(THIS, 3);
                THIS->mirror = H_MIRROR;
            }
            else
            {
                SetFrame(THIS, 4);
                THIS->mirror = NO_MIRROR;
            }
        }
        else
        {
            if (data->orientation != 3)
            {
                SetFrame(THIS, 2);
                THIS->mirror = H_MIRROR;
            }
            else
            {
                SetFrame(THIS, 4);
                THIS->mirror = V_MIRROR;
            }
        }
        break;
    default:
        THIS->mirror = NO_MIRROR;
        break;
    }

    if (data->fliptime > 20)
        flipanimworm = 1;
    if (data->fliptime > 40)
    {
        flipanimworm = 0;
        data->fliptime = 0;
    }

    data->fliptime++;
}

void Update_CreationWorm()
{

    CUSTOM_DATA *data = (CUSTOM_DATA *)THIS->custom_data;

    OrientWorm(); //i dont want to call this on update but if we're doing turning stuff it might be easiest

    THIS->x = Creation->x + wshotdirections[(data->orientation + creation_shift) % 4][0] * 16;
    THIS->y = Creation->y + wshotdirections[(data->orientation + creation_shift) % 4][1] * 16;

    if (Creation == NULL)
        SpriteManagerRemoveSprite(THIS);
}
void Destroy_CreationWorm()
{
}
