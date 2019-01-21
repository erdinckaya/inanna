
#ifndef RESOURCEMANAGER_ANIMATIONS_H
#define RESOURCEMANAGER_ANIMATIONS_H

#include "Resources.h"

#include<string>
#include<string.h>
#include<vector>

template<typename C>
struct SpriteAnim {
    
    template<typename ... T>
    explicit SpriteAnim(const char* name, const int speed, T ...args) : name(name), speed(speed), keyFrames{C(args)...} {} 

    const char* name;
    const int speed;
    std::vector<ImageAsset> keyFrames;
    
    REFLECT()
};

typedef SpriteAnim<ImageAsset> SpriteAnimData;

struct AnimationData {
	static SpriteAnim<ImageAsset> DEATH;

};

#endif //RESOURCEMANAGER_ANIMATIONS_H
