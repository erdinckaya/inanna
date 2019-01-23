import os


animations_file_str_h = """
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
    int speed;
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
%s
};

#endif //RESOURCEMANAGER_ANIMATIONS_H
"""

animation_fields_str = ""
animation_defination_str = ""
animation_defination_cpp_str = ""


def create_animations(meta):
    if "anims" not in meta:
        return
    anims = meta["anims"]
    global animation_fields_str
    global animation_defination_str
    global animation_defination_cpp_str


    for anim in anims:
        result_str = ""
        name = anim["name"]
        animation_fields_str += "\tstatic SpriteAnim<ImageAsset> %s;\n" % (name.upper())
        constructor_str = "(\"%s\", %d" % (name, anim["speed"])
        for image in anim["images"]:
            constructor_str += """, Resources::%s.%s""" % (name.upper(), image.upper())
        constructor_str += ");\n"

        animation_defination_cpp_str += "SpriteAnim<ImageAsset> AnimationData::%s" %(name.upper())
        animation_defination_cpp_str += constructor_str


def write_animations(path):
    h_file_str = animations_file_str_h % (animation_fields_str)
    animations_path = os.path.join(path + "/Assets", "AnimationData.h")
    with open(animations_path, 'w') as h_file:
        h_file.write(h_file_str)

    cpp_file_template_str = """
#include "AnimationData.h"

%s
    
"""

    animations_cpp_path = os.path.join(path + "/Assets", "AnimationData.cpp")
    cpp_file_str = cpp_file_template_str %  animation_defination_cpp_str;
    with open(animations_cpp_path, 'w') as cpp_file:
        cpp_file.write(cpp_file_str)

