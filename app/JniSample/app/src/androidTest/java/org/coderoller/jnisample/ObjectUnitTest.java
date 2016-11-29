package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.ObjectTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class ObjectUnitTest {
    private ObjectTester mTester;

    @Before
    public void setUp() {
        mTester = new ObjectTester();
    }

    @After
    public void tearDown() {
        mTester = null;
    }

    @Test
    public void testEquality() {
        Object a = new Object();
        Object b = new Object();
        assertTrue(mTester.checkEquality(a, a));
        assertFalse(mTester.checkEquality(a, b));
        assertFalse(mTester.checkEquality(a, null));
        assertFalse(mTester.checkEquality(null, b));
        assertTrue(mTester.checkEquality(null, null));
    }

    @Test
    public void testInstanceOf() {
        Object object = new Object();
        Integer integer = new Integer(3);
        assertTrue(mTester.isInstanceOf(object, Object.class));
        assertTrue(mTester.isInstanceOf(integer, Integer.class));
        assertTrue(mTester.isInstanceOf(integer, Object.class));
        assertFalse(mTester.isInstanceOf(object, Integer.class));
        assertFalse(mTester.isInstanceOf(null, Object.class));
        assertFalse(mTester.isInstanceOf(null, Integer.class));
        assertFalse(mTester.isInstanceOf(null, null));
    }

    @Test
    public void testCastTo() {
        assertTrue(mTester.castTo(new Object(), Object.class));
        assertTrue(mTester.castTo(new Integer(3), Object.class));
        assertFalse(mTester.castTo(new Object(), Integer.class));
        assertFalse(mTester.castTo(new String(), Integer.class));
        assertFalse(mTester.castTo(null, Object.class));
        assertFalse(mTester.castTo(null, Integer.class));
        assertFalse(mTester.castTo(null, null));
    }
}
