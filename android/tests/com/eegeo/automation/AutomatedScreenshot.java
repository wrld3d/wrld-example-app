package com.eegeo.automation;

import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;

import com.eegeo.mobileexampleapp.BackgroundThreadActivity;

import org.junit.BeforeClass;
import org.junit.ClassRule;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import tools.fastlane.screengrab.Screengrab;
import tools.fastlane.screengrab.UiAutomatorScreenshotStrategy;
import tools.fastlane.screengrab.locale.LocaleTestRule;

@RunWith(AndroidJUnit4.class)
public class AutomatedScreenshot {
    @ClassRule
    public static final LocaleTestRule localeTestRule = new LocaleTestRule();

    @Rule
    public ActivityTestRule<BackgroundThreadActivity> activityRule = new ActivityTestRule<>(BackgroundThreadActivity.class);

    @BeforeClass
    public static void beforeAll() {
        Screengrab.setDefaultScreenshotStrategy(new UiAutomatorScreenshotStrategy());
    }

    private void WaitForFastlane() throws InterruptedException {
        Thread.sleep(5000);
    }

    @Test
    public void run() throws InterruptedException {
        final BackgroundThreadActivity activity = activityRule.getActivity();
        synchronized (activity.screenshotsCompletedLock) {
            activity.screenshotsCompletedLock.wait();
        }
        WaitForFastlane();
    }
}
