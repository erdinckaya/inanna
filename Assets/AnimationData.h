
#ifndef RESOURCEMANAGER_ANIMATIONS_H
#define RESOURCEMANAGER_ANIMATIONS_H

#include "Resources.h"

#include<string>
#include<string.h>

struct SpriteAnimData {
    virtual const char* Name() const = 0;
    virtual const int Speed() const = 0;
    virtual const int FrameSize() const = 0;
    virtual const ImageAsset KeyFrame(int index) const = 0;
};


struct DeathAnim : public SpriteAnimData {
    
    DeathAnim() :
        name("death"),
        frameSize(6),
        speed(10),
        keyFrames {
			 Resources::DEATH.DEATH_000
			,Resources::DEATH.DEATH_001
			,Resources::DEATH.DEATH_002
			,Resources::DEATH.DEATH_003
			,Resources::DEATH.DEATH_004
			,Resources::DEATH.DEATH_005
        }
    { }

    const char* name;
    const int speed;
    const int frameSize;
    ImageAsset keyFrames[6];
    
    const char* Name() const override {
        return name;
    }
    
    const int Speed() const override {
        return speed;
    }
    
    const int FrameSize() const override {
        return frameSize;
    }
    
    const ImageAsset KeyFrame(int index) const override {
        return keyFrames[index];
    }
    
    REFLECT()
};



struct AnimationData {
	static DeathAnim DEATH;

};

#endif //RESOURCEMANAGER_ANIMATIONS_H
