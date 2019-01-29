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


        GameKey GetKey(const std::string &keyStr) {
            GameKey key = GameKey::InValid;
            for (int i = 0; i < GameKey::NumOfGameKey; ++i) {
                if (StringKeys[i] == keyStr) {
                    key = (GameKey) i;
                    break;
                }
            }
            return key;
        }

        void Init(const std::string &dataFile) {
            std::ifstream file(dataFile);
            json j;
            file >> j;

            json jKeycode = j["key_code"];
            for (int i = 0; i < GameKey::NumOfGameKey; ++i) {
                StringKeys[i] = jKeycode[i].get<std::string>();
            }

            json moves = j["moves"];
            const int size = static_cast<const int>(moves.size());
            for (int i = 0; i < size; ++i) {
                json move = moves[i];
                SpecialMoveKeyData data;
                data.Id = (SpecialMoveKey) i;
                data.Duration = move["duration"].get<int>();
                const int keySize = static_cast<const int>(move["keys"].size());
                for (int k = 0; k < keySize; ++k) {
                    auto keyStr = move["keys"][k].get<std::string>();
                    data.Keys.push_back(GetKey(keyStr));
                }
                SpecialMoveKeys.push_back(data);
            }
            printf("12313\n");
        }

        std::string StringKeys[GameKey::NumOfGameKey];
        std::vector<SpecialMoveKeyData> SpecialMoveKeys;
    };
}

#endif //INANNA_KEYPATTERNS_H
