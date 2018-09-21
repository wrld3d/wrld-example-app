#!/bin/sh

TEAM_ID=$1

LOGIN_KEYCHAIN=~/Library/Keychains/login.keychain
TEMP_SIGNING_IDENTITIES="$(mktemp)"
TEMP_PEM="$(mktemp)"
TEMP_CERT_INFO="$(mktemp)"


function trap_exit {
    rm -f "${TEMP_SIGNING_IDENTITIES}"
    rm -f "${TEMP_PEM}"
    rm -f "${TEMP_CERT_INFO}"
}

trap 'trap_exit' EXIT


regExpName=".*\biPhone Developer\b.*"
regExpOrg=".*\b$TEAM_ID\b.*"

MATCHING_CERTIFICATE_NAME=""


security find-identity -v -p codesigning | awk -F\" '{ print $2 }' > "${TEMP_SIGNING_IDENTITIES}"

while read CERTIFICATE_NAME;
do
    security find-certificate -c "${CERTIFICATE_NAME}" -p ${LOGIN_KEYCHAIN} 2>/dev/null > "${TEMP_PEM}"
    if [ $? == 0 ] ; then
        #echo $CERTIFICATE_NAME  >&2
        certtool d ${TEMP_PEM} > "${TEMP_CERT_INFO}" 
        grep "$regExpName" ${TEMP_CERT_INFO} > /dev/null
        matchNameResult=$?
        #echo "matchNameResult is $matchNameResult" >&2
        grep "$regExpOrg" ${TEMP_CERT_INFO} > /dev/null
        matchOrgResult=$?
        #echo "matchOrgResult is $matchOrgResult" >&2
        if [ $matchNameResult == 0 ] && [ $matchOrgResult == 0 ] ; then
            MATCHING_CERTIFICATE_NAME=$CERTIFICATE_NAME
            break
        fi
    fi
done < "${TEMP_SIGNING_IDENTITIES}"



if [ -n "${MATCHING_CERTIFICATE_NAME}" ] ; then
    echo "${MATCHING_CERTIFICATE_NAME}"
    exit 0
else
    echo "Did not find match" >&2
    exit 1
fi



