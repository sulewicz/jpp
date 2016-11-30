# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/array_tester.cpp
             src/main/cpp/class_tester.cpp
             src/main/cpp/exception_tester.cpp
             src/main/cpp/method_tester.cpp
             src/main/cpp/object_tester.cpp
             src/main/cpp/static_method_tester.cpp
             src/main/cpp/jpp/Array.cpp
             src/main/cpp/jpp/Cache.cpp
             src/main/cpp/jpp/Class.cpp
             src/main/cpp/jpp/Env.cpp
             src/main/cpp/jpp/Object.cpp
             src/main/cpp/jpp/internal/type.cpp)

target_compile_options(native-lib PRIVATE -fexceptions)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
