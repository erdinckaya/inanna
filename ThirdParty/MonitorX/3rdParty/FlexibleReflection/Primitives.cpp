#include <SDL_types.h>
#include "Reflect.h"

namespace reflect {

//--------------------------------------------------------
// A type descriptor for int
//--------------------------------------------------------

    struct TypeDescriptor_Int : TypeDescriptor {
        TypeDescriptor_Int() : TypeDescriptor{"int", sizeof(int)} {
        }

        void dump(const void *obj, int /* unused */) const override {
            std::cout << "int{" << *(const int *) obj << "}";
        }

        std::string type(const void *obj) const override {
            return "int";
        }
    };

    template<>
    TypeDescriptor *getPrimitiveDescriptor<int>() {
        static TypeDescriptor_Int typeDesc;
        return &typeDesc;
    }

//--------------------------------------------------------
// A type descriptor for std::string
//--------------------------------------------------------

    struct TypeDescriptor_StdString : TypeDescriptor {
        TypeDescriptor_StdString() : TypeDescriptor{"std::string", sizeof(std::string)} {
        }

        void dump(const void *obj, int /* unused */) const override {
            std::cout << "std::string{\"" << *(const std::string *) obj << "\"}";
        }

        std::string type(const void *obj) const override {
            return "string";
        }
    };

    template<>
    TypeDescriptor *getPrimitiveDescriptor<std::string>() {
        static TypeDescriptor_StdString typeDesc;
        return &typeDesc;
    }

//--------------------------------------------------------
// A type descriptor for double
//--------------------------------------------------------

    struct TypeDescriptor_Double : TypeDescriptor {
        TypeDescriptor_Double() : TypeDescriptor{"double", sizeof(double)} {
        }

        void dump(const void *obj, int /* unused */) const override {
            std::cout << "double{" << *(const double *) obj << "}";
        }

        std::string type(const void *obj) const override {
            return "double";
        }
    };

    template<>
    TypeDescriptor *getPrimitiveDescriptor<double>() {
        static TypeDescriptor_Double typeDesc;
        return &typeDesc;
    }


//--------------------------------------------------------
// A type descriptor for float
//--------------------------------------------------------

    struct TypeDescriptor_Float : TypeDescriptor {
        TypeDescriptor_Float() : TypeDescriptor{"float", sizeof(float)} {
        }

        void dump(const void *obj, int /* unused */) const override {
            std::cout << "float{" << *(const float *) obj << "}";
        }

        std::string type(const void *obj) const override {
            return "float";
        }
    };

    template<>
    TypeDescriptor *getPrimitiveDescriptor<float>() {
        static TypeDescriptor_Float typeDesc;
        return &typeDesc;
    }

//--------------------------------------------------------
// A type descriptor for long
//--------------------------------------------------------

    struct TypeDescriptor_Long : TypeDescriptor {
        TypeDescriptor_Long() : TypeDescriptor{"long", sizeof(long)} {
        }

        void dump(const void *obj, int /* unused */) const override {
            std::cout << "long{" << *(const long *) obj << "}";
        }

        std::string type(const void *obj) const override {
            return "long";
        }
    };

    template<>
    TypeDescriptor *getPrimitiveDescriptor<long>() {
        static TypeDescriptor_Long typeDesc;
        return &typeDesc;
    }

//--------------------------------------------------------
// A type descriptor for bool
//--------------------------------------------------------

    struct TypeDescriptor_Bool : TypeDescriptor {
        TypeDescriptor_Bool() : TypeDescriptor{"bool", sizeof(bool)} {
        }

        void dump(const void *obj, int /* unused */) const override {
            std::cout << "bool{" << *(const bool *) obj << "}";
        }

        std::string type(const void *obj) const override {
            return "bool";
        }
    };

    template<>
    TypeDescriptor *getPrimitiveDescriptor<bool>() {
        static TypeDescriptor_Bool typeDesc;
        return &typeDesc;
    }



//--------------------------------------------------------
// A type descriptor for Uint8
//--------------------------------------------------------

    struct TypeDescriptor_Uint8 : TypeDescriptor {
        TypeDescriptor_Uint8() : TypeDescriptor{"int", sizeof(Uint8)} {
        }

        void dump(const void *obj, int /* unused */) const override {
            std::cout << "int{" << *(const Uint8 *) obj << "}";
        }

        std::string type(const void *obj) const override {
            return "int";
        }
    };

    template<>
    TypeDescriptor *getPrimitiveDescriptor<Uint8>() {
        static TypeDescriptor_Uint8 typeDesc;
        return &typeDesc;
    }


//--------------------------------------------------------
// A type descriptor for Uint32
//--------------------------------------------------------

    struct TypeDescriptor_Uint32 : TypeDescriptor {
        TypeDescriptor_Uint32() : TypeDescriptor{"int", sizeof(Uint32)} {
        }

        void dump(const void *obj, int /* unused */) const override {
            std::cout << "int{" << *(const Uint32 *) obj << "}";
        }

        std::string type(const void *obj) const override {
            return "int";
        }
    };

    template<>
    TypeDescriptor *getPrimitiveDescriptor<Uint32>() {
        static TypeDescriptor_Uint32 typeDesc;
        return &typeDesc;
    }


} // namespace reflect


