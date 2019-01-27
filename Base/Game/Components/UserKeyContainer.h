//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_USERKEYCONTAINER_H
#define INANNA_USERKEYCONTAINER_H

#include "../../Util/CircularBuffer.h"
#include "UserKey.h"

namespace Inanna {
    struct UserKeyContainer {
        explicit UserKeyContainer() : buffer(30) {}

        CircularBuffer<UserKey> buffer;
    };
}

#endif //INANNA_USERKEYCONTAINER_H
