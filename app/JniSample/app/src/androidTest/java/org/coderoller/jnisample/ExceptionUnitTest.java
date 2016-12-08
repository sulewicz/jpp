package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.ExceptionTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

@RunWith(AndroidJUnit4.class)
public class ExceptionUnitTest {
    private ExceptionTester mTester;

    @Before
    public void setUp() {
        mTester = new ExceptionTester();
    }

    @After
    public void tearDown() {
        mTester = null;
    }

    @Test
    public void testClassNotFoundException() {
        mTester.simulateClassNotFoundException();
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof ClassNotFoundException);
    }

    @Test
    public void testNoSuchMethodError() {
        mTester.simulateNoSuchMethodError();
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof NoSuchMethodError);
    }

    @Test
    public void testNoSuchStaticMethodError() {
        mTester.simulateNoSuchStaticMethodError();
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof NoSuchMethodError);
    }

    @Test
    public void testFieldNotFoundException() {
        // TODO
    }

    @Test
    public void testMethodCallingException() {
        mTester.simulateUnsupportedOperationException();
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof UnsupportedOperationException);
    }

    @Test
    public void testStaticMethodCallingException() {
        mTester.simulateStaticUnsupportedOperationException();
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof UnsupportedOperationException);
    }

    @Test
    public void testThrowingExceptionFromNative() {
        try {
            mTester.throwException(IllegalArgumentException.class);
            fail();
        } catch (Throwable t) {
            assertTrue(t instanceof IllegalArgumentException);
        }
    }

    @Test
    public void testConstructorException() {
        mTester.simulateConstructorException(new RuntimeException());
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof RuntimeException);
    }

    @Test
    public void testNoSuchConstructorException() {
        mTester.simulateNoSuchConstructorException();
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof NoSuchMethodError);
    }

    @Test
    public void testArrayGetItemException() {
        final Object[] array = new Object[] { "a", "b" };
        Object item = mTester.safeGetItem(array, 1);
        assertEquals(item, array[1]);
        assertNull(mTester.getThrowable());
        item = mTester.safeGetItem(array, 2);
        assertNull(item);
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof ArrayIndexOutOfBoundsException);
    }

    @Test
    public void testArraySetItemException() {
        final Object[] array = new Object[] { "a", "b" };
        mTester.safeSetItem(array, 1, "c");
        assertEquals("c", array[1]);
        assertNull(mTester.getThrowable());
        mTester.safeSetItem(array, 2, "d");
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof ArrayIndexOutOfBoundsException);
    }

    @Test
    public void testFieldGetException() {
        mTester.getNonExistingField();
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof NoSuchFieldError);
    }

    @Test
    public void testFieldSetException() {
        mTester.setNonExistingField(null);
        assertNotNull(mTester.getThrowable());
        assertTrue(mTester.getThrowable() instanceof NoSuchFieldError);
    }

    @Test
    public void testStaticFieldGetException() {
        // TODO
    }

    @Test
    public void testStaticFieldSetException() {
        // TODO
    }
}
