#!/bin/sh
function is_windows {
    # running on msys (basically the git provided shell we use on windows)
    if [ "$OSTYPE" == "msys" ]; then
        windows=true
    else
        windows=false        
    fi
    
    local ret=$windows
    echo "$ret"
}