package net.hockeyapp.android;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.FilenameFilter;
import java.util.Date;
import java.util.UUID;

import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.mime.MultipartEntity;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;
import org.apache.http.HttpResponse;

import android.app.Activity;
import android.util.Log;

public class NativeCrashManager {
  public static void handleDumpFiles(Activity activity, String identifier) {
    String[] filenames = searchForDumpFiles();
    for (String dumpFilename : filenames) {
      String logFilename = createLogFile();
      if (logFilename != null) {
        uploadDumpAndLog(activity, identifier, dumpFilename, logFilename);
      }
    }
  }
  
  public static String createLogFile() {
    final Date now = new Date();

    try {
      // Create filename from a random uuid
      String filename = UUID.randomUUID().toString();
      String path = Constants.FILES_PATH + "/" + filename + ".faketrace";
      Log.d(Constants.TAG, "Writing unhandled exception to: " + path);
      
      // Write the stacktrace to disk
      BufferedWriter write = new BufferedWriter(new FileWriter(path));
      write.write("Package: " + Constants.APP_PACKAGE + "\n");
      write.write("Version Code: " + Constants.APP_VERSION + "\n");
      write.write("Version Name: " + Constants.APP_VERSION_NAME + "\n");
      write.write("Android: " + Constants.ANDROID_VERSION + "\n");
      write.write("Manufacturer: " + Constants.PHONE_MANUFACTURER + "\n");
      write.write("Model: " + Constants.PHONE_MODEL + "\n");
      write.write("Date: " + now + "\n");
      write.write("\n");
      write.write("MinidumpContainer");
      write.flush();
      write.close();
      
      return filename + ".faketrace";
    } 
    catch (Exception another) {
    }
    
    return null;
  }
  
  public static void uploadDumpAndLog(final Activity activity, final String identifier, final String dumpFilename, final String logFilename) {
    new Thread() {
      @Override
      public void run() {
        try {
          DefaultHttpClient httpClient = new DefaultHttpClient(); 
          HttpPost httpPost = new HttpPost("https://rink.hockeyapp.net/api/2/apps/" + identifier + "/crashes/upload");
          
          MultipartEntity entity = new MultipartEntity();
    
          File dumpFile = new File(Constants.FILES_PATH, dumpFilename);
          entity.addPart("attachment0", new FileBody(dumpFile));      
    
          File logFile = new File(Constants.FILES_PATH, logFilename);
          entity.addPart("log", new FileBody(logFile));      
    
          httpPost.setEntity(entity);
          
          HttpResponse response = httpClient.execute(httpPost);   
          
          String content = EntityUtils.toString(response.getEntity());

          int statuscode = response.getStatusLine().getStatusCode();
          String reason = response.getStatusLine().getReasonPhrase();
        }
        catch (Exception e) {
          e.printStackTrace();
        } 
        finally {
          activity.deleteFile(logFilename);
          activity.deleteFile(dumpFilename);
        }
      }
    }.start();
  } 
  
  private static String[] searchForDumpFiles() {
    if (Constants.FILES_PATH != null) {
      // Try to create the files folder if it doesn't exist
      File dir = new File(Constants.FILES_PATH + "/");
      boolean created = dir.mkdir();
      if (!created && !dir.exists()) {
        return new String[0];
      }
  
      // Filter for ".dmp" files
      FilenameFilter filter = new FilenameFilter() { 
        public boolean accept(File dir, String name) {
          return name.endsWith(".dmp"); 
        } 
      }; 
      return dir.list(filter);
    }
    else {
      Log.d(Constants.TAG, "Can't search for exception as file path is null.");
      return new String[0];
    }
  }
}
