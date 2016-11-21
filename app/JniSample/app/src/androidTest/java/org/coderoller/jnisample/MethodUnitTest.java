package org.coderoller.jnisample;

import android.support.test.espresso.core.deps.guava.primitives.Shorts;
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
        mTester.setByte(Byte.MIN_VALUE);
        assertEquals(Byte.MIN_VALUE, mTester.callByteMethod());
    }

    @Test
    public void testReturningChar() throws Exception {
        mTester.setChar(Character.MIN_VALUE);
        assertEquals(Character.MIN_VALUE, mTester.callCharMethod());
    }

    @Test
    public void testReturningShort() throws Exception {
        mTester.setShort(Short.MIN_VALUE);
        assertEquals(Short.MIN_VALUE, mTester.callShortMethod());
    }

    @Test
    public void testReturningInt() throws Exception {
        mTester.setInt(Integer.MIN_VALUE);
        assertEquals(Integer.MIN_VALUE, mTester.callIntMethod());
    }

    @Test
    public void testReturningLong() throws Exception {
        mTester.setLong(Long.MIN_VALUE);
        assertEquals(Long.MIN_VALUE, mTester.callLongMethod());
    }

    @Test
    public void testReturningFloat() throws Exception {
        mTester.setFloat(Float.MIN_VALUE);
        assertTrue(Float.MIN_VALUE == mTester.callFloatMethod());
    }

    @Test
    public void testReturningDouble() throws Exception {
        mTester.setDouble(Double.MIN_VALUE);
        assertTrue(Double.MIN_VALUE == mTester.callDoubleMethod());
    }

    @Test
    public void testToString() throws Exception {
        String testValue = "This is a test.";
        mTester.setString(testValue);
        assertEquals(testValue, mTester.callToString());
    }

    @Test
    public void testGetClass() throws Exception {
        assertTrue(mTester.callGetClass() == mTester.getClass());
    }
}
