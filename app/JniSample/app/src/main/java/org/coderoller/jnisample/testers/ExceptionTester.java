package org.coderoller.jnisample.testers;

public class ExceptionTester {
    static {
        System.loadLibrary("native-lib");
    }

    private Throwable mThrowable;

    public Throwable getThrowable() {
        return mThrowable;
    }

    public void setThrowable(Throwable throwable) {
        mThrowable = throwable;
    }

    public native void simulateClassNotFoundException();
}
