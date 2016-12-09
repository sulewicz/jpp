package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.JvmTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class JvmUnitTest {
    private JvmTester mTester;

    @Before
    public void setUp() {
        mTester = new JvmTester();
    }

    @After
    public void tearDown() {
        mTester = null;
    }

    @Test
    public void testVmCaching() {
        mTester.cacheJvm();
        Object object = mTester.createObjectFromCachedJvm();
        assertNotNull(object);
    }

    @Test
    public void testThreadAttaching() {
        mTester.cacheJvm();
        mTester.asyncOperation();
        assertTrue(mTester.waitForResult());
    }
}
