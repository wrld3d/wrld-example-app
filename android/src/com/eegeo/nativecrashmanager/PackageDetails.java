package com.eegeo.nativecrashmanager;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;

public class PackageDetails {
    public static String ANDROID_VERSION = null;
    public static String APP_VERSION = null;
    public static String APP_VERSION_NAME = null;
    public static String APP_PACKAGE = null;
    public static String PHONE_MODEL = null;
    public static String PHONE_MANUFACTURER = null;

    public static void loadFromContext(Context context) {
        ANDROID_VERSION = Build.VERSION.RELEASE;
        PHONE_MODEL = Build.MODEL;
        PHONE_MANUFACTURER = Build.MANUFACTURER;

        loadPackageData(context);
    }

    private static int loadBuildNumber(Context context, PackageManager packageManager) {
        try {
            ApplicationInfo appInfo = packageManager.getApplicationInfo(context.getPackageName(), 128);
            Bundle metaData = appInfo.metaData;
            if (metaData != null) {
                return metaData.getInt("buildNumber", 0);
            }
        } catch (Exception var4) {
            var4.printStackTrace();
        }

        return 0;
    }

    private static void loadPackageData(Context context) {
        if (context != null) {
            try {
                PackageManager packageManager = context.getPackageManager();
                PackageInfo packageInfo = packageManager.getPackageInfo(context.getPackageName(), 0);
                APP_PACKAGE = packageInfo.packageName;
                APP_VERSION = "" + packageInfo.versionCode;
                APP_VERSION_NAME = packageInfo.versionName;
                int buildNumber = loadBuildNumber(context, packageManager);
                if (buildNumber != 0 && buildNumber > packageInfo.versionCode) {
                    APP_VERSION = "" + buildNumber;
                }
            } catch (Exception var4) {
                Log.e("App center", "Exception thrown when accessing the package info:");
                var4.printStackTrace();
            }
        }
    }
}
