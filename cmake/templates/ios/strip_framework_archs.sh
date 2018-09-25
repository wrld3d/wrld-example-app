#!/bin/sh

FRAMEWORK_FILE=$1
VALID_ARCHS=$2

framework_archs="$(lipo -info ${FRAMEWORK_FILE} | awk -F': ' '{ print $3 }')"
echo "framework_archs for ${FRAMEWORK_FILE} are ${framework_archs}" >&2
for arch in $framework_archs; do
    if ! [[ "${VALID_ARCHS}" == *"$arch"* ]]; then
        lipo -remove "$arch" -output "$FRAMEWORK_FILE" "$FRAMEWORK_FILE" || exit 1
    fi
done


exit 0
