#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StatePressStart)\
_STATE(StateGame)\
_STATE(StateSynthesizer)\
_STATE(StateThanks)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, player)\
_SPRITE_DMG(Worm,worm)\
_SPRITE_DMG(Blob,blob)\
_SPRITE_DMG(Machine,machine)\
_SPRITE_DMG(SpritePlayerHead, playerHead)\
_SPRITE_DMG(Selector,selector)\
_SPRITE_DMG(Button,button)\
_SPRITE_DMG(Scanned,scanned)\
_SPRITE_DMG(CreationHead0,creationheadzero)\
_SPRITE_DMG(CreationHead1,creationheadone)\
_SPRITE_DMG(CreationHead2,creationheadtwo)\
_SPRITE_DMG(CreationHead2e,creationheadelbow)\
_SPRITE_DMG(CreationHead3,creationheadthree)\
_SPRITE_DMG(CreationHead4,creationheadfour)\
_SPRITE_DMG(CreationEye,creationeye)\
_SPRITE_DMG(CreationWorm,creationworm)\
_SPRITE_DMG(CreationCrab,creationcrab)\
_SPRITE_DMG(CreationBlob,creationblob)\
_SPRITE_DMG(Spit,spit)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif