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

    private static void multiParamMethod(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d) {
        sObject = o;
        sBoolean = bool;
        sByte = b;
        sChar = c;
        sShort = s;
        sInt = i;
        sLong = l;
        sFloat = f;
        sDouble = d;
    }

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

    public static Object getObject() {
        return sObject;
    }

    public static void setObject(Object object) {
        sObject = object;
    }

    public static boolean isBoolean() {
        return sBoolean;
    }

    public static void setBoolean(boolean aBoolean) {
        sBoolean = aBoolean;
    }

    public static byte getByte() {
        return sByte;
    }

    public static void setByte(byte aByte) {
        sByte = aByte;
    }

    public static char getChar() {
        return sChar;
    }

    public static void setChar(char aChar) {
        sChar = aChar;
    }

    public static short getShort() {
        return sShort;
    }

    public static void setShort(short aShort) {
        sShort = aShort;
    }

    public static int getInt() {
        return sInt;
    }

    public static void setInt(int anInt) {
        sInt = anInt;
    }

    public static long getLong() {
        return sLong;
    }

    public static void setLong(long aLong) {
        sLong = aLong;
    }

    public static float getFloat() {
        return sFloat;
    }

    public static void setFloat(float aFloat) {
        sFloat = aFloat;
    }

    public static double getDouble() {
        return sDouble;
    }

    public static void setDouble(double aDouble) {
        sDouble = aDouble;
    }

    // Methods used for actual testing.

    public static boolean callVoidMethod() {
        callVoidMethodNative();
        boolean ret = sVoidCalled;
        sVoidCalled = false;
        return ret;
    }

    public static native void callMultiParamMethod(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double
            d);

    public static native Object callObjectMethod();

    public static native void callVoidMethodNative();

    public static native boolean callBooleanMethod();

    public static native byte callByteMethod();

    public static native char callCharMethod();

    public static native short callShortMethod();

    public static native int callIntMethod();

    public static native long callLongMethod();

    public static native float callFloatMethod();

    public static native double callDoubleMethod();
}
