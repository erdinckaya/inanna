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

            json moves = j["moves"];
            const int size = static_cast<const int>(moves.size());
            for (int i = 0; i < size; ++i) {
                json move = moves[i];
                SpecialMoveKeyData data;
                data.Id = SpecialMoveKey::_from_integral(i);
                data.Duration = move["duration"].get<int>();
                const int keySize = static_cast<const int>(move["keys"].size());
                for (int k = 0; k < keySize; ++k) {
                    auto keyStr = move["keys"][k].get<std::string>();
                    data.Keys.push_back(GameKey::_from_string(keyStr.c_str()));
                }
                SpecialMoveKeys.push_back(data);
            }
        }

        std::vector<SpecialMoveKeyData> SpecialMoveKeys;
    };
}

#endif //INANNA_KEYPATTERNS_H
