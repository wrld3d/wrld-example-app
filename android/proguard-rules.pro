-verbose

# Skip all steps performed by ProGuard
-dontshrink
-dontoptimize
-dontobfuscate
-dontpreverify

# Keep public methods on public classes
-keep public class com.eegeo.entrypointinfrastructure.** {public *;}
-keep public class com.eegeo.view.OnPauseListener {public *;}
-keep public class com.google.android.gms.** { public *; }
-keep public class org.scribe.services.DatatypeConverterEncoder { public *; }
-keep public class com.senion.stepinside.sdk.** { public *; }

# Hide "________: can't find referenced class ________"
-dontwarn com.google.android.gms.**
-dontwarn com.senion.stepinside.sdk.internal**
-dontwarn org.scribe.services.DatatypeConverterEncoder

# Hide "duplicate definition of library class [________]"
-dontnote android.net.http.**
-dontnote org.apache.http.**

# Hide "Note: ________: can't find dynamically referenced class ________"
# Hide "the configuration keeps the entry point ________, but not the descriptor class ________"
-dontnote com.google.android.gms.**
-dontnote com.senion.stepinside.sdk.**
