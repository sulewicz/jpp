#pragma once

#include <jni.h>
#include <unordered_map>
#include <string>
#include "Class.h"

namespace jpp {
    class Env;
    class Cache {
    public:
        Cache();
        ~Cache();
        Class get_class(Env *env, const char *class_name);
        Class add_class(Env *env, const char *class_name, jclass _jclass);
        void clear(Env *env);
    private:
        std::unordered_map<std::string, jclass> m_jclass_cache;
    };
}
