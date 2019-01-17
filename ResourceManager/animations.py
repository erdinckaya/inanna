
animations_file_str = """
#ifndef RESOURCEMANAGER_ANIMATIONS_H
#define RESOURCEMANAGER_ANIMATIONS_H

#include "Resources.h"

#include<string>
#include<string.h>


#endif RESOURCEMANAGER_ANIMATIONS_H
"""


animation_str = """
struct %sAnim {
    
    %s() {
        name = \"%s\";
        frameSize = %d;
        speed = %d;
        keyFrames = {%s};
    }

    const char* name;
    ImageAsset[%d] keyFrames;
    const int frameSize;
    int speed;
    
    REFLECT()
};

"""


def create_animations(meta):
    if "anims" not in meta:
        return
    anims = meta["anims"]

    result_str = ""
    for anim in anims:
        name = anim["name"]
        i = 0
        framSize = len(anim["images"])
        keyframes = "Resources::%s.%s" % (name.upper(), anim["images"][0].upper())
        for image in anim["images"]:
            if i != 0:
                keyframes += """, Resources::%s.%s""" % (name.upper(), image.upper())
            i += 1

        result_str = animation_str % (name.title(), name.title(), name, framSize, anim["speed"], keyframes, framSize)

    print(result_str)


animations_class_str = """

struct Animations {
    
}

"""