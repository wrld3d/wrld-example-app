function eegeo_deactivate_app(target, number)
{
    var n = number;

    if (isNaN(n) || n < 0 || n > 20)
    {
        UIALogger.logMessage(n + " is not a suitable number, assigning five seconds to number");
        n = 5;
        target.delay(2);
    }
    return target.deactivateAppForDuration(n);
}

function eegeo_lock_app(target, number)
{
    var n = number;
    var s = target.name();
    var pattern = /simulator/i;
    
    if (pattern.test(s))
    {
    UIALogger.logMessage("Cannot run target.lockForDuration on simulator, must be device");
    return false;
    }
    
    if(isNaN(n) || n < 0 || n > 20)
    {
        UIALogger.logMessage(n + " is not a suitable number, assigning five seconds to number");
        n = 5;
        target.delay(2);
    }
    return target.lockForDuration(n);
}

function eegeo_get_app_location(target, lat, long)
{
    var eegeoLat = 56.460109;
    var eegeoLong = -2.978388;
    
    if(lat < -90 || lat > 90)
    {
        UIALogger.logMessage(lat + " is not a suitable number, assigning eeGeo's latitude");
        lat = eegeoLat;
    }
    
    if(long < -180 || long > 180)
    {
        UIALogger.logMessage(long + " is not a suitable number, assigning eeGeo's longitude");
        long = eegeoLong;
    }
    var coordinates = {latitude: lat, longitude: long};
    return eegeo_set_app_location(target, coordinates);
}

function eegeo_set_app_location(target, coordinates)
{
   return target.setLocation(coordinates);
}