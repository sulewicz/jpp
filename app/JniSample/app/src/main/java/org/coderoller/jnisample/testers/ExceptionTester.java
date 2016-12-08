package org.coderoller.jnisample.testers;

public class ExceptionTester {
    static {
        System.loadLibrary("native-lib");
    }

    public ExceptionTester() {}

    public ExceptionTester(RuntimeException e) {
        throw e;
    }

    private Throwable mThrowable;

    public Throwable getThrowable() {
        return mThrowable;
    }

    public void setThrowable(Throwable throwable) {
        mThrowable = throwable;
    }

    public void notImplemented() {
        throw new UnsupportedOperationException();
    }

    public static void staticNotImplemented() {
        throw new UnsupportedOperationException();
    }

    public native void simulateClassNotFoundException();

    public native void simulateNoSuchMethodError();

    public native void simulateNoSuchStaticMethodError();

    public native void simulateUnsupportedOperationException();

    public native void simulateStaticUnsupportedOperationException();

    public native void throwException(Class<?> aClass);

    public native void simulateConstructorException(RuntimeException e);

    public native void simulateNoSuchConstructorException();

    public native Object getNonExistingField();

    public native void setNonExistingField(Object o);

    public native Object safeGetItem(Object[] array, int idx);

    public native void safeSetItem(Object[] array, int idx, Object item);
}
