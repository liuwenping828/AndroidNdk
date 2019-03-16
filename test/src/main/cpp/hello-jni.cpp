#include <jni.h>
#include <string>
#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "ZARD"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__) // 定义LOGF类型
#endif

void crash() {
    int *p = NULL;
    *p = 1;
    printf("%d\n", *p);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_wenping_test_Test_stringFromJNITest(JNIEnv *env, jclass type) {

//    crash();
//    std::string hello = "我是坂井泉水的最爱";
//    return env->NewStringUTF(hello.c_str());

#if defined(__arm__)
#if defined(__ARM_ARCH_7A__)
#if defined(__ARM_NEON__)
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a/NEON (hard-float)"
#else
#define ABI "armeabi-v7a/NEON"
#endif
#else
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a (hard-float)"
#else
#define ABI "armeabi-v7a"
#endif
#endif
#else
#define ABI "armeabi"
#endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif

    // 输出Log 信息
    LOGD("Log from JNI ....");
    LOGI("Log from JNI ....");
    LOGW("Log from JNI ....");
    LOGE("Log from JNI ....");
    LOGF("Log from JNI ....");

    // 格式化输入日志
    char *name = "zard";
    LOGD("My name is %s.", name);

    //用C语言格式
//    return (*env)->NewStringUTF(env, "Hello JNI !");
    //C++格式
//    return env->NewStringUTF((char *)"Hello JNI !");

    //C++格式
    return env->NewStringUTF((char *) "Hello from JNI !  Compiled with ABI " ABI ".");

    // 抛出空指针异常
//    env=NULL;
//    return env->NewStringUTF("from c++");


}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_wenping_test_Test_unimplementedStringFromJNI(JNIEnv *env, jclass type) {

    return env->NewStringUTF("this is Test");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wenping_test_Test_callStaticMethod__I(JNIEnv *env, jclass type, jint i) {

    // 找到对应的类
    jclass cls_hello = env->FindClass("com/wenping/test/Test");
    if (cls_hello == NULL) {
        return;
    }

    // 找到对应的方法
    jmethodID mtd_static_method = env->GetStaticMethodID(cls_hello, "staticMethod",
                                                         "(Ljava/lang/String;)V");
    if (mtd_static_method == NULL) {
        return;
    }

    // 找到对应的成员变量
    jfieldID fild_name = env->GetStaticFieldID(cls_hello, "NAME", "Ljava/lang/String;");
    if (fild_name == NULL) {
        return;
    }

    jstring name = env->NewStringUTF("tom");
    // 对成员变量进行设置值
    env->SetStaticObjectField(cls_hello, fild_name, name);


    jstring data = env->NewStringUTF("call java static method");
    if (data == NULL) {
        return;
    }

    // 调用java层的方法
    env->CallStaticVoidMethod(cls_hello, mtd_static_method, data);


    // 异常处理
    if (env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        jclass cls_exception = env->FindClass("java/lang/Exception");

        env->ThrowNew(cls_exception,"Call java static method ndk error");
        return;
    }

    // 删除引用
    env->DeleteLocalRef(cls_hello);
    env->DeleteLocalRef(data);
    env->DeleteLocalRef(name);


}

extern "C"
JNIEXPORT void JNICALL
Java_com_wenping_test_Test_callStaticMethod__JLjava_lang_String_2(JNIEnv *env, jclass type, jlong i,
                                                                  jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);

    // TODO

    env->ReleaseStringUTFChars(str_, str);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wenping_test_Test_callInstanceMethod__I(JNIEnv *env, jobject instance, jint i) {

    // 找到对应的类
    jclass cls_hello = env->FindClass("com/wenping/test/Test");
    if (cls_hello == NULL) {
        return;
    }

    // 找到对应的方法
    jmethodID mtd_method = env->GetMethodID(cls_hello, "method",
                                            "(Ljava/lang/String;)V");
    if (mtd_method == NULL) {
        return;
    }

    // 找到对应的构造方法
    jmethodID mtd_construct = env->GetMethodID(cls_hello, "<init>", "()V");
    if (mtd_construct == NULL) {
        return;
    }

    // 创建相应的对象
    jobject object = env->NewObject(cls_hello, mtd_construct, NULL);
    if (object == NULL) {
        return;
    }

    // 找到对应的成员变量
    jfieldID field_address = env->GetFieldID(cls_hello, "address", "Ljava/lang/String;");
    if (field_address == NULL) {
        return;
    }
    jstring address = env->NewStringUTF("Beijing");
    if (address == NULL) {
        return;
    }
    // 对成员变量进行设置值
    env->SetObjectField(object, field_address, address);

    jstring message = env->NewStringUTF("call instance method");
    // 调用方法
    env->CallVoidMethod(object, mtd_method, message);

    // 删除引用
    env->DeleteLocalRef(message);
    env->DeleteLocalRef(cls_hello);
    env->DeleteLocalRef(object);
    env->DeleteLocalRef(address);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_wenping_test_Test_callInstanceMethod__Ljava_lang_String_2J(JNIEnv *env, jobject instance,
                                                                    jstring str_, jlong i) {
    const char *str = env->GetStringUTFChars(str_, 0);

    // TODO

    env->ReleaseStringUTFChars(str_, str);
}