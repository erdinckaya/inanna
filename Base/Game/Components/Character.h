#include <utility>

#include <utility>

//
// Created by misterdortnal on 23.01.2019.
//

#ifndef INANNA_CHARACTER_H
#define INANNA_CHARACTER_H

namespace Inanna {
    struct Character {
        explicit Character(std::string id) : id(std::move(id)) {}

        const std::string id;
    };
}

#endif //INANNA_CHARACTER_H
