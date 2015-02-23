#!/bin/sh
librarypath=$(pwd)/ios/
tuneup_js_tests=$(pwd)/tests/EndToEnd/iOS/testsuite.js
targetName=ExampleApp
productName="ExampleApp"
productVersion=i386
logfilename="testoutput.log"
simulatorType="iPad 2 (8.1 Simulator)"
currentDirectory=`pwd`
endToEndOutput=$currentDirectory/EndToEndResults
endToEndTrace=$currentDirectory/EndToEndResults/etoe.trace
logfilename=$endToEndOutput/testresults.log

function killSimulator {
	# try a polite request first so that the process can clean up
	killall "iPhone Simulator"

	if [ $? != 0 ] ; then
		# hard kill, not a pretty please.
		killall -9 "iPhone Simulator"
	fi
}

killSimulator

(cd $librarypath && xcodebuild -target $targetName -arch "i386" -sdk "iphonesimulator" PRODUCT_NAME="$productName" PRODUCT_VERSION=$productVersion)

rm -rf $endToEndOutput
mkdir $endToEndOutput

instruments -w "$simulatorType" -D $endToEndTrace -t /Applications/Xcode.app/Contents/Applications/Instruments.app/Contents/PlugIns/AutomationInstrument.xrplugin/Contents/Resources/Automation.tracetemplate "$currentDirectory/ios/build/Release-iphonesimulator/ExampleApp.app" -e UIASCRIPT tests/EndToEnd/iOS/testsuite.js -e UIARESULTSPATH $endToEndOutput 2>&1 | tee $logfilename

killSimulator

egrep -q "Fail:" $logfilename
grepResult=$?

if [ $grepResult = 0 ] ; then
	# grep found a failure
        echo "END TO END TESTS FAILED"
	exit 1;
else
        echo "END TO END TESTS PASSED"
	exit 0;
fi
