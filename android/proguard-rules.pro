-dontobfuscate
-verbose

-keep class com.eegeo.entrypointinfrastructure.INativeMessageRunner

-keep class com.eegeo.** { *; }
-dontwarn com.eegeo.**

-keep class com.google.android.gms.* { public *; }
-dontwarn com.google.android.gms.**

-keep public class java.lang.management.* { public *; }
-dontwarn java.lang.management.**

-keep class sun.misc.Unsafe { *; }
-dontwarn sun.misc.Unsafe

-keep class org.apache.http.** { *; }
-keep class org.apache.james.mime4j.** { *; }
-dontwarn org.apache.http.**
-dontwarn org.apache.james.mime4j.**

-keep class com.flurry.sdk.i
-dontwarn com.flurry.sdk.i

-keep class org.codehaus.mojo.**
-dontwarn org.codehaus.mojo.**

-keep class javax.xml.bind.*
-dontwarn javax.xml.bind.*

-keep class android.net.http.*
-dontwarn android.net.http.*

-keep public interface org.easymock.** { *; }
-dontwarn org.easymock.**
-keep class org.jmock.core.Constraint { *; }
-dontwarn org.jmock.core.Constraint 
-keep class junit.framework.TestCase { *; }
-dontwarn junit.framework.TestCase
-keep class junit.runner.BaseTestRunner { *; }
-dontwarn junit.runner.BaseTestRunner 

-dontwarn android.test.**
-dontwarn android.support.test.**

-keep class org.hamcrest.** { *; }
-dontwarn org.hamcrest.**

-keep class org.junit.** { *; }
-dontwarn org.junit.**

-keep class junit.** { *; }
-dontwarn junit.**

-keep class javax.lang.model.element.** { *; }
-dontwarn javax.lang.model.element.**

-keep class com.senionlab.** { *; }

-keep class com.indooratlas.** { *; }
-dontwarn com.indooratlas.**