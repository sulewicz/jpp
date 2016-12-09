package org.coderoller.jnisample.testers;

public class StaticFieldTester {
    static {
        System.loadLibrary("native-lib");
    }

    // All types

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
    private static Object[] sObjectArray = null;
    private static byte[] sByteArray = null;

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
        sObjectArray = null;
        sByteArray = null;
    }

    // Methods used for actual testing.

    public static native Object setAndGetObjectField(Object o);

    public static native boolean setAndGetBooleanField(boolean b);

    public static native byte setAndGetByteField(byte b);

    public static native char setAndGetCharField(char c);

    public static native short setAndGetShortField(short s);

    public static native int setAndGetIntField(int i);

    public static native long setAndGetLongField(long l);

    public static native float setAndGetFloatField(float f);

    public static native double setAndGetDoubleField(double d);

    public static native Object[] setAndGetObjectArrayField(Object[] o);

    public static native byte[] setAndGetByteArrayField(byte[] b);
}
