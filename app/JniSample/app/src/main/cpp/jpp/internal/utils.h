#pragma once

#include "type.h"
#include <jni.h>
#include <string>
#include <sstream>
#include <functional>

namespace jpp {
    namespace internal {
        template<class Type, class ... Types>
        std::string generate_signature(Type return_type, Types ... args) {
            std::ostringstream stream;
            stream << "(";
            using List= int[];
            (void) List{0, ((void) (stream << type_to_str(args)), 0) ...};
            stream << ")" << type_to_str(return_type);
            return stream.str();
        }
    }
}
