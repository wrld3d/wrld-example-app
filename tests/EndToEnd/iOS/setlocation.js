test(
     "Set location",
     eegeo_test_func(
        function(target, app)
        {
        eegeo_get_app_location(target, 56.460109, -2.978388);
        }
    )
);

