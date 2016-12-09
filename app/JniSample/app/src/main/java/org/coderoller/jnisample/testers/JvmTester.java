package org.coderoller.jnisample.testers;

public class JvmTester {
    static {
        System.loadLibrary("native-lib");
    }

    private Object mResult = null;

    public native void cacheJvm();
    public native Object createObjectFromCachedJvm();
    public native void asyncOperation();

    public boolean waitForResult() {
        synchronized (this) {
            try {
                wait(5000);
            } catch (InterruptedException e) {
                return false;
            }
        }
        return mResult != null;
    }
}
