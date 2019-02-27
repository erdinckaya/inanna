//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_USERKEY_H
#define INANNA_USERKEY_H

#include "../Util/GameKey.h"

namespace Inanna {
    struct UserKey {
        explicit UserKey() : key(GameKey::InValid), time(0), down(false) {}

        explicit UserKey(int key, Uint32 time, bool down) : key(key), time(time), down(down) {}

        int key;
        Uint32 time;
        bool down;

        std::string ToString() {
            return std::to_string(key) + ", " + std::to_string(time) + ", " + std::to_string(down);
        }

        friend inline bool operator==(const UserKey& lhs, const UserKey& rhs) {
            return lhs.key == rhs.key && lhs.down == rhs.down && lhs.time == rhs.time;
        }

        friend inline bool operator!=(const UserKey& lhs, const UserKey& rhs) {
            return !(lhs == rhs);
        }

        REFLECT()
    };
}

#endif //INANNA_USERKEY_H
