#!/usr/bin/env bash

# this script requires installation of ply (python lex-yacc)
# http://www.dabeaz.com/ply/

android_result=0
ios_result=0

if [ -d "./android/libs/" ]; then
	python android/libs/naming_validator/check_member_names.py ./src/ ./android/jni
	android_result=$?
fi

if [ -d "./ios/Include/" ]; then
	# an 'ERROR: WRONG BRACE DEPTH' message is printed due to the objective-c in ios headers
	python ios/Include/naming_validator/check_member_names.py ./src/ ./ios/ios_src
	ios_result=$?
fi

if [ $ios_result == 0 ] && [ $android_result == 0 ] ; then
	exit 0
fi

exit 1