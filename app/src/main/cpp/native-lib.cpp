#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_wenping_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++ Android JNI Test3333333";
    return env->NewStringUTF(hello.c_str());
}
