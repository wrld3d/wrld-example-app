test(
  "Wait for app to load",
  eegeo_test_func(
     function(target, app)
     {
        target.delay(20.0);
                  
        var memstats = eegeo_debug_command(target, "stats.mem");
        assertTrue(memstats[0].indexOf("Mem Used:") > -1);
    }
  )
);

