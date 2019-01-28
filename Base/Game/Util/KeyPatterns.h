//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_KEYPATTERNS_H
#define INANNA_KEYPATTERNS_H

#include <string>
#include <fstream>
#include <set>
#include "../../../ThirdParty/json.h"
#include "GameKey.h"
#include "SpecialMoveKeyData.h"

namespace Inanna {

    using json = nlohmann::json;

    struct KeyPatterns {

        void Init(const std::string &dataFile) {
            std::ifstream file(dataFile);
            json j;
            file >> j;

            json jKeycode = j["key_code"];
            for (int i = 0; i < GameKey::NumOfGameKey; ++i) {
                StringKeys[i] = jKeycode[i].get<std::string>();
            }

            json moves = j["key_code"];
            const int size = static_cast<const int>(moves.size());
            for (int i = 0; i < size; ++i) {
                json move = moves[i];

            }

        }


        std::string StringKeys[GameKey::NumOfGameKey];
        std::vector<SpecialMoveKeyData> SpecialMoveKeys;
    };
}

#endif //INANNA_KEYPATTERNS_H
