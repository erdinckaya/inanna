
#ifndef RESOURCEMANAGER_ANIMATIONS_H
#define RESOURCEMANAGER_ANIMATIONS_H

#include "Resources.h"

#include<string>
#include<string.h>


struct DeathSpriteAnim {
    
    DeathSpriteAnim() :
        name("death"),
        frameSize(6),
        speed(5),
        keyFrames{Resources::DEATH.DEATH_000, Resources::DEATH.DEATH_001, Resources::DEATH.DEATH_002, Resources::DEATH.DEATH_003, Resources::DEATH.DEATH_004, Resources::DEATH.DEATH_005}
    { }

    const char* name;
    ImageAsset keyFrames[6];
    const int frameSize;
    int speed;
    
    REFLECT()
};



struct Animations {
	static DeathSpriteAnim DEATH;

};

#endif RESOURCEMANAGER_ANIMATIONS_H
