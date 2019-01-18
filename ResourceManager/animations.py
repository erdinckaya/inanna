import os


animations_file_str_h = """
#ifndef RESOURCEMANAGER_ANIMATIONS_H
#define RESOURCEMANAGER_ANIMATIONS_H

#include "Resources.h"

#include<string>
#include<string.h>

%s

struct Animations {
%s
};

#endif RESOURCEMANAGER_ANIMATIONS_H
"""


animation_str = """
struct %sSpriteAnim {
    
    %sSpriteAnim() :
        name(\"%s\"),
        frameSize(%d),
        speed(%d),
        keyFrames{%s}
    { }

    const char* name;
    ImageAsset keyFrames[%d];
    const int frameSize;
    int speed;
    
    REFLECT()
};

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
        animation_fields_str += "\tstatic %sSpriteAnim %s;\n" % (name.title(), name.upper())
        animation_defination_cpp_str += "%sSpriteAnim Animations::%s;\n" %(name.title(), name.upper())
        i = 0
        framSize = len(anim["images"])
        keyframes = "Resources::%s.%s" % (name.upper(), anim["images"][0].upper())
        for image in anim["images"]:
            if i != 0:
                keyframes += """, Resources::%s.%s""" % (name.upper(), image.upper())
            i += 1

        result_str = animation_str % (name.title(), name.title(), name, framSize, anim["speed"], keyframes, framSize)
        animation_defination_str += result_str


def write_animations(path):
    h_file_str = animations_file_str_h % (animation_defination_str, animation_fields_str)
    animations_path = os.path.join(path + "/Assets", "Animations.h")
    with open(animations_path, 'w') as h_file:
        h_file.write(h_file_str)

    cpp_file_template_str = """
#include "Animations.h"

%s
    
"""

    animations_cpp_path = os.path.join(path + "/Assets", "Animations.cpp")
    cpp_file_str = cpp_file_template_str %  animation_defination_cpp_str;
    with open(animations_cpp_path, 'w') as cpp_file:
        cpp_file.write(cpp_file_str)

