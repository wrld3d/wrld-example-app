function eegeo_test_func(func)
{
    return function(target, app)
    {
        UIATarget.onAlert = function onAlert(alert)
        {
            var title = alert.name();
            
            UIALogger.logWarning("Alert with title '" + title + "' encountered!");
            alert.defaultButton().tap();
            
            return false;
        }
        
        func(target, app);
    }
}

function condition_console_data(data)
{
    var split = data.split("\n");
    var sliced = split.slice(4, split.length-1);
    var joined = sliced.join("\n");
    return sliced.map(function(str) { return str.replace("cmd> ", "") });
}

function eegeo_debug_command(target, command)
{
    var host = target.host()
    var result = host.performTaskWithPathArgumentsTimeout("build-scripts/ios/debugserver.sh", [command], 5);
    return condition_console_data(result.stdout);
}