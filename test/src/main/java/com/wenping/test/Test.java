package com.wenping.test;

import android.util.Log;

public class Test {

    private static String NAME = "zard";

    private String address = "address";

    static {
        System.loadLibrary("hello-jni");
    }

    public static native String stringFromJNITest();

    public static void logMessages(String data) {
        Log.d("zard", data);
    }

    public static void staticMethod(String data) {
        logMessages(data);
        logMessages(NAME);
    }

    public void method(String data) {
        logMessages(data);
        logMessages(address);
    }

    public static native void callStaticMethod(int i);

    public static native void callStaticMethod(long i, String str);

    public native void callInstanceMethod(int i);

    public native void callInstanceMethod(String str, long i);


    public static native String unimplementedStringFromJNI();
}
