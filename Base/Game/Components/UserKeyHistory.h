//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_USERKEYCONTAINER_H
#define INANNA_USERKEYCONTAINER_H

#include <vector>
#include "UserKey.h"

namespace Inanna {
    struct UserKeyHistory {
        explicit UserKeyHistory() = default;

        std::vector<UserKey> buffer;

        REFLECT()
    };
}

#endif //INANNA_USERKEYCONTAINER_H
