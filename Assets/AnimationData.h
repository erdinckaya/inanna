
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

    std::string name;
    float speed;
    std::vector<ImageAsset> keyFrames;
    
    friend inline bool operator==(const SpriteAnim& lhs, const SpriteAnim& rhs) {
		return lhs.name.compare(rhs.name) == 0;
	}

	friend inline bool operator!=(const SpriteAnim& lhs, const SpriteAnim& rhs) {
		return !(lhs == rhs);
	}
    
	REFLECT_TEMPLATE(SpriteAnim, C)
						REFLECT_STRUCT_MEMBER_TEMPLATE(name)
						REFLECT_STRUCT_MEMBER_TEMPLATE(speed)
						REFLECT_STRUCT_MEMBER_TEMPLATE(keyFrames)
	REFLECT_STRUCT_END()
};
REFLECT_STRUCT_INIT_TEMPLATE(SpriteAnim)

typedef SpriteAnim<ImageAsset> SpriteAnimData;

struct AnimationData {
	static SpriteAnim<ImageAsset> DEATH;
	static SpriteAnim<ImageAsset> KYO_CROUCH;
	static SpriteAnim<ImageAsset> KYO_LITTLE_FIST;
	static SpriteAnim<ImageAsset> KYO_LITTLE_KICK;
	static SpriteAnim<ImageAsset> KYO_IDLE;
	static SpriteAnim<ImageAsset> KYO_JUMP;
	static SpriteAnim<ImageAsset> KYO_JUMP_BACK;
	static SpriteAnim<ImageAsset> KYO_MOVE_BACK;
	static SpriteAnim<ImageAsset> KYO_MOVE_FORWARD;
	static SpriteAnim<ImageAsset> KYO_RUN;
	static SpriteAnim<ImageAsset> KYO_SALUTE;

};

#endif //RESOURCEMANAGER_ANIMATIONS_H
