//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_USERKEYCONTAINER_H
#define INANNA_USERKEYCONTAINER_H

#include <vector>
#include "UserKey.h"

namespace Inanna {
    struct UserKeyContainer {
        explicit UserKeyContainer() = default;

        std::vector<UserKey> buffer;
    };
}

#endif //INANNA_USERKEYCONTAINER_H
