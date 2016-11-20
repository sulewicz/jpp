package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.MethodTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class MethodUnitTest {
    private MethodTester mTester;

    @Before
    public void setUp() {
        mTester = new MethodTester();
    }

    @After
    public void tearDown() {
        mTester = null;
    }

    @Test
    public void testReturningObject() throws Exception {
        Object o = new Integer(3);
        mTester.setObject(o);
        assertEquals(o, mTester.callObjectMethod());
    }

    @Test
    public void testReturningVoid() throws Exception {
        assertTrue(mTester.callVoidMethod());
    }

    @Test
    public void testReturningBoolean() throws Exception {
        mTester.setBoolean(true);
        assertTrue(mTester.callBooleanMethod());
        mTester.setBoolean(false);
        assertFalse(mTester.callBooleanMethod());
    }

    @Test
    public void testReturningByte() throws Exception {
        mTester.setByte((byte) 10);
        assertEquals((byte) 10, mTester.callByteMethod());
    }

    @Test
    public void testReturningChar() throws Exception {
        mTester.setChar((char) 10);
        assertEquals((char) 10, mTester.callCharMethod());
    }
}
