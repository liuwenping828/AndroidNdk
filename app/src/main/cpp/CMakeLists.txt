# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
# 设置生成本机库所需的CMAKE的最低版本。

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
# 创建和命名库，将其设置为静态或共享，并提供指向其源代码的相对路径。
# 您可以定义多个库，而cmake会为您构建它们。Gradle会自动打包与您的APK共享的库。

add_library(
        # Sets the name of the library.
        # 设置库的名称。
        native-lib

        # Sets the library as a shared library.
        # 将库设置为共享库。
        SHARED
        # 将库设置为静态库。
        # STATIC

        # Provides a relative path to your source file(s).
        # 提供源文件的相对路径。
        native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
# 搜索指定的预建库并将路径存储为变量。因为默认情况下，cmake在搜索路径中包含系统库，
# 所以只需指定要添加的公共NDK库的名称。cmake在完成其生成之前验证库是否存在

find_library(
        # Sets the name of the path variable.
        #　设置路径变量的名称。
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        # 指定要CMAKE定位的NDK库的名称。
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
# 指定库cmake应链接到目标库。可以链接多个库，例如在此生成脚本中定义的库、预生成的第三方库或系统库。

target_link_libraries(
        # Specifies the target library.
        # 指定目标库
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        # 将目标库链接到包含在NDK中的日志库。
        ${log-lib})