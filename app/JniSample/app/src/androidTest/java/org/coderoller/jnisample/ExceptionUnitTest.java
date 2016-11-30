package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.ExceptionTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

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
    public void testMethodNotFoundException() {
        // TODO
    }

    @Test
    public void testFieldNotFoundException() {
        // TODO
    }

    @Test
    public void testMethodCallingException() {
        // TODO
    }

    @Test
    public void testConstructorException() {
        // TODO
    }

    @Test
    public void testArrayGetItemException() {
        // TODO
    }

    @Test
    public void testArraySetItemException() {
        // TODO
    }

    @Test
    public void testFieldGetException() {
        // TODO
    }

    @Test
    public void testFieldSetException() {
        // TODO
    }
}
