package net.hockeyapp.android;

import java.io.File;
import java.io.FilenameFilter;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.UUID;

import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.protocol.HTTP;
import org.apache.http.util.EntityUtils;
import org.apache.http.HttpResponse;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.util.Log;

import com.microsoft.appcenter.Constants;

public class NativeCrashManager {

  public static void handleDumpFiles(Activity activity, String identifier) {
    PackageDetails.loadFromContext(activity);
    String[] filenames = searchForDumpFiles();
    for (String dumpFilename : filenames) {
      uploadCrashReport(activity, identifier, dumpFilename);
    }
  }

  public static String getCurrentDateInAppCenterFormat() {
    SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'");
    try{
      return sdf.format(new Date());
    }
    catch(Exception pe){
      return "";
    }
  }

  public static JSONObject getDeviceInfo() {

    JSONObject deviceObj = new JSONObject();
    try {
      deviceObj.put("appVersion", PackageDetails.APP_VERSION);
      deviceObj.put("appBuild", "1");
      deviceObj.put("sdkName", "appcenter.android");
      deviceObj.put("sdkVersion", "1.0.0");
      deviceObj.put("osName", "android");
      deviceObj.put("osVersion", PackageDetails.ANDROID_VERSION);
      deviceObj.put("model", PackageDetails.PHONE_MODEL);

      deviceObj.put("locale", "en-US");
    } catch (JSONException e) {
      e.printStackTrace();
    }
    return deviceObj;
  }

  public static JSONArray createJsonParams(String dumpFileName) {
    JSONArray jsonArray = new JSONArray();
    try {

      String currentDateTime = getCurrentDateInAppCenterFormat();
      String errorId = UUID.randomUUID().toString();
      String attachmentId = UUID.randomUUID().toString();

      JSONObject logObj = new JSONObject();
      logObj.put("type", "managedError");
      logObj.put("timestamp", currentDateTime);
      logObj.put("appLaunchTimestamp", currentDateTime);
      logObj.put("id", errorId);
      logObj.put("fatal", true);
      logObj.put("processName", "com.microsoft.appcenter.wrld.project");

      logObj.put("device", getDeviceInfo());
      logObj.put("userId", "<userid>");

      JSONObject exceptionObj = new JSONObject();
      exceptionObj.put("type", "CustomerIssueDynamicID");
      exceptionObj.put("frames", new JSONArray());

      logObj.put("exception", exceptionObj);

      jsonArray.put(logObj);

      JSONObject dumpFileDataObj = new JSONObject();
      dumpFileDataObj.put("type", "errorAttachment");
      dumpFileDataObj.put("contentType", "text/plain");
      dumpFileDataObj.put("timestamp", currentDateTime);
      dumpFileDataObj.put("data", readFileDataInBase64(dumpFileName));
      dumpFileDataObj.put("fileName", "minidump.dmp");
      dumpFileDataObj.put("errorId", errorId);
      dumpFileDataObj.put("id", attachmentId);

      dumpFileDataObj.put("device", getDeviceInfo());

      jsonArray.put(dumpFileDataObj);

    } catch (JSONException e) {
      e.printStackTrace();
    }

    return jsonArray;
  }

  public static void uploadCrashReport(final Activity activity, final String identifier, final String dumpFilename) {
    new Thread() {
      @Override
      public void run() {
        try {
          DefaultHttpClient httpClient = new DefaultHttpClient();
          HttpPost httpPost = new HttpPost("https://in.appcenter.ms/logs?Api-Version=1.0.0");

          httpPost.addHeader("Content-Type", "application/json");
          httpPost.addHeader("app-secret", identifier);
          httpPost.addHeader("install-id", "00000000-0000-0000-0000-000000000001");

          JSONObject jsonObj = new JSONObject();
          jsonObj.put("logs", createJsonParams(dumpFilename));

          String jsonString = jsonObj.toString();

          StringEntity entity = new StringEntity(jsonString, HTTP.UTF_8);
          entity.setContentType("application/json");

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
          activity.deleteFile(dumpFilename);
        }
      }
    }.start();


  }

  public static String readFileDataInBase64(String dumpFileName) {
    // TODO: read dump file and convert to Base64 String
    return "TnVsbCBwb2ludGVyIGV4Y2VwdGlvbiBmcm9tIEFuZHJvaWQgYXBw";
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
      return new String[0];
    }
  }
}
