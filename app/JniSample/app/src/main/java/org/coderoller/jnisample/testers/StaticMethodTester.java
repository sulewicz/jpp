package org.coderoller.jnisample.testers;

public class StaticMethodTester {
    static {
        System.loadLibrary("native-lib");
    }

    private static Object sObject = null;
    private static boolean sVoidCalled = false;
    private static boolean sBoolean = false;
    private static byte sByte = 0;
    private static char sChar = 0;
    private static short sShort = 0;
    private static int sInt = 0;
    private static long sLong = 0;
    private static float sFloat = 0;
    private static double sDouble = 0;

    // Methods invoked from native layer.

    private static Object objectMethod() {
        return sObject;
    }

    private static void voidMethod() {
        sVoidCalled = true;
    }

    private static boolean booleanMethod() {
        return sBoolean;
    }

    private static byte byteMethod() {
        return sByte;
    }

    private static char charMethod() {
        return sChar;
    }

    private static short shortMethod() {
        return sShort;
    }

    private static int intMethod() {
        return sInt;
    }

    private static long longMethod() {
        return sLong;
    }

    private static float floatMethod() {
        return sFloat;
    }

    private static double doubleMethod() {
        return sDouble;
    }

    // Helper methods used by unit tests.

    public static void reset() {
        sObject = null;
        sVoidCalled = false;
        sBoolean = false;
        sByte = 0;
        sChar = 0;
        sShort = 0;
        sInt = 0;
        sLong = 0;
        sFloat = 0;
        sDouble = 0;
    }

    public static void setObject(Object o) {
        sObject = o;
    }

    public static void setBoolean(boolean b) {
        sBoolean = b;
    }

    public static void setByte(byte b) {
        sByte = b;
    }

    public static void setChar(char c) {
        sChar = c;
    }

    public static void setShort(short s) {
        sShort = s;
    }

    public static void setInt(int i) {
        sInt = i;
    }

    public static void setLong(long l) {
        sLong = l;
    }

    public static void setFloat(float f) {
        sFloat = f;
    }

    public static void setDouble(double d) {
        sDouble = d;
    }

    // Methods used for actual testing.

    public static Object callObjectMethod() {
        return callObjectMethodNative();
    }

    public static boolean callVoidMethod() {
        callVoidMethodNative();
        boolean ret = sVoidCalled;
        sVoidCalled = false;
        return ret;
    }

    public static boolean callBooleanMethod() {
        return callBooleanMethodNative();
    }

    public static byte callByteMethod() {
        return callByteMethodNative();
    }

    public static char callCharMethod() {
        return callCharMethodNative();
    }

    public static short callShortMethod() {
        return callShortMethodNative();
    }

    public static int callIntMethod() {
        return callIntMethodNative();
    }

    public static long callLongMethod() {
        return callLongMethodNative();
    }

    public static float callFloatMethod() {
        return callFloatMethodNative();
    }

    public static double callDoubleMethod() {
        return callDoubleMethodNative();
    }

    private static native Object callObjectMethodNative();

    private static native void callVoidMethodNative();

    private static native boolean callBooleanMethodNative();

    private static native byte callByteMethodNative();

    private static native char callCharMethodNative();

    private static native short callShortMethodNative();

    private static native int callIntMethodNative();

    private static native long callLongMethodNative();

    private static native float callFloatMethodNative();

    private static native double callDoubleMethodNative();
}
