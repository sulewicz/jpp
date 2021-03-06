/*
 * Copyright (C) 2017 Szymon Ulewicz.
 * Distributed under MIT license, see LICENSE file for details.
 */

#pragma once

#include <jni.h>
#include <unordered_map>
#include <string>
#include "Class.h"

namespace jpp {
    class Env;
    /**
    * \brief TODO: Add documentation.
    *
    * TODO: Add documentation.
    */
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
