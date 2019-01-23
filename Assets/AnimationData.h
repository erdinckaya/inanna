
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
    
    friend inline bool operator==(const SpriteAnim& lhs, const SpriteAnim& rhs) {
		return strcmp(lhs.name == rhs.name) == 0;
	}

	friend inline bool operator!=(const SpriteAnim& lhs, const SpriteAnim& rhs) {
		return !(lhs == rhs);
	}
    
    REFLECT()
};

typedef SpriteAnim<ImageAsset> SpriteAnimData;

struct AnimationData {
	static SpriteAnim<ImageAsset> DEATH;
	static SpriteAnim<ImageAsset> KYO_LITTLE_KICK;
	static SpriteAnim<ImageAsset> KYO_IDLE;
	static SpriteAnim<ImageAsset> KYO_MOVE_BACK;
	static SpriteAnim<ImageAsset> KYO_MOVE_FORWARD;
	static SpriteAnim<ImageAsset> KYO_SALUTE;

};

#endif //RESOURCEMANAGER_ANIMATIONS_H
