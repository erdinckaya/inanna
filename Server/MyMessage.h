//
// Created by misterdortnal on 20.11.2018.
//

#ifndef INANNA_MYMESSAGE_H
#define INANNA_MYMESSAGE_H

#include <yojimbo.h>

class MyMessage : public yojimbo::Message {
public:
    int m_data;
    char text[100];

    MyMessage() :
            m_data(0) {}

    template<typename Stream>
    bool Serialize(Stream &stream) {
        serialize_int(stream, m_data, 0, 512);
        serialize_string(stream, text, (int) strlen(text) + 1);
        return true;
    }

    YOJIMBO_VIRTUAL_SERIALIZE_FUNCTIONS();
};


#endif //INANNA_MYMESSAGE_H
