import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;

import com.eegeo.mobileexampleapp.BackgroundThreadActivity;
import com.eegeo.mobileexampleapp.R;

import org.junit.BeforeClass;
import org.junit.ClassRule;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import tools.fastlane.screengrab.Screengrab;
import tools.fastlane.screengrab.locale.LocaleTestRule;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.matcher.ViewMatchers.withId;

@RunWith(AndroidJUnit4.class)
public class DoScreengrab {
    @ClassRule
    public static final LocaleTestRule localeTestRule = new LocaleTestRule();

    @Rule
    public ActivityTestRule<BackgroundThreadActivity> activityRule = new ActivityTestRule<>(BackgroundThreadActivity.class);

    @BeforeClass
    public static void beforeAll() {
    }

    @Test
    public void screengrab() throws InterruptedException {
        Thread.sleep(8000);
        onView(withId(R.id.search_menu_drag_button_view)).perform(click());
        Screengrab.screenshot("after_button_click");
    }
}