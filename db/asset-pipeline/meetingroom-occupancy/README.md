# Swallow Feed Integration

## SOAP Webservice

The Swallow Feed is a SOAP webservice implemented by Swallow engineers, and available to us on-prem.

A 'test' service is available off-prem under the `test-webservice` folder but this does not directly mirror the on-prem service. It's our own implementation of the Specification to unblock local development.

### SOAP Webservice specifications

Latest [WSDL](https://www.w3.org/TR/wsdl) & [XSD](https://en.wikipedia.org/wiki/XML_Schema_(W3C)) can be found under the `spec` folder

## Authentication

Authentication is achieved via [HMAC](https://en.wikipedia.org/wiki/Hash-based_message_authentication_code)

The following are required:
1. A private key (one exists for `dev` one exists for `prod`). 
2. A spoof application ID, sent nakedly over a `appId` http header
3. A real application ID, encoded in the HMAC signature

The Private Keys and application IDs cannot leave Swallow's network. Contact details to obtain them are:
1. Camille Sarder <csholl@bloomberg.net> (Engineering Manager)
2. Sumir Chandra <schandra8@bloomberg.net> (Engineering Lead)
3. Vinod Arige <varige1@bloomberg.net> (Engineer)

## Installation

`pip install -r pip-requirements`

## Setup - Meeting Room Primary Keys

A join is required between WRLD's canonical representation of Meeting Rooms, and Swallow's canonical representation of Meeting Rooms. The spreadsheet `../src/poidb-builder/assets/swallow-pois.xls` contains a column `space_id` which is Swallow's Primary Key.

**TODO**: Automate the updating of the canonical primary keys...

Once the spreadsheet contains canonical spaceIds, run the Data Scripts

## Data Scripts

```sh
$ mkdir generated
$ ./meetingroom-mapping-update.sh ../../src/poidb-builder/assets/swallow-pois.xls
```

This parses the xml and generates canonical mapping files for the Feed Scripts. 

**TODO**: this is likely to be improved over time.

## Feed Scripts - Private Keys and App Ids

There are two secret parts, and one public part of the HMAC authenticaiton handshake:

1. Public App Id - sent over a Http Header
2. Private App Id - used in the HMAC signature
3. Secret - Used in the HMAC signature

There are `dev` and `prod` versions of the Secret. These can be found in passwordstate under the notes field of `swallow feed private keys`

## Feed Scripts - Arguments

All feed scripts can be executed with the same command line arguments:

```sh
$ POI_SERVICE_URL=<URL to POI set, i.e. https://poi.wrld3d.com/v1.1/poisets/1903>
$ FEED_SERVICE_WSDL=<URL to Bloomberg Feed WSDL>
$ DEV_AUTH_TOKEN=<WRLD dev token with access to POI set above>
$ APP_SECRET=<the app private key>
$ PUBLIC_APP_ID=<the spoof app Id>
$ PRIVATE_APP_ID=<the real app Id>
$ REGION_CODE=EMEA
$ DEBUG=True
$ CDN_BASE_URL=<base CDN path for assets, i.e. http://swallowcontent/swallow-pois/assets/v234>
$ ./script.sh $POI_SERVICE_URL $DEV_AUTH_TOKEN $FEED_SERVICE_WSDL $APP_SECRET $PUBLIC_APP_ID $PRIVATE_APP_ID $REGION_CODE $DEBUG $CDN_BASE_URL
```
## Script - Update POIs - Meeting Rooms

```sh
$ ./meetingroom-update.sh args
```

This script will update meeting rooms from the feed. It requires meetingroom-mapping-update.sh to have been run first.

The script deletes all meeting room points of interest, re-creates them, and persists a mapping of spaceId -> POI for subsequent scripts.

The intent is that this is run nightly.

## Script - Update POIs - Meeting Room Occupancy

```sh
$ ./meetingroom-status-update.sh args
```

This script will update meeting room occupancy user_data from the feed. It requires meetingroom-update.sh to have been run first.

The script calls a batch update to all pois from the spaceId -> POI mapping, updating the meeting room occupancy from the feed.

The intent is that this is run every minute or so.