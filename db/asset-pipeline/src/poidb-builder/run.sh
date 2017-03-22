#!/bin/bash

set -u

function process_failure {
   echo "Failed at $1"
   exit 1
}

trap 'process_failure $LINENO' ERR

readonly poisetAurl="http://londWayFApp01/search/v1.1/poisets/1"
readonly poisetBurl="http://londWayFApp01/search/v1.1/poisets/2"
readonly appApiKey1="6d27c9936af66fa250dbc30172d7fec4"
readonly appApiKey2="3ceebbe9943e604ee4ac39b3977be5e1"
readonly authToken="G5MONCictZXp8hZLJvAvS6xGZo5EluaFKKil5CEfkBRsu2CA5XihAJ3x1NSbysNBrSqbO6pl92LSEjFq"

function clear_api_keys() {
   curl -s -XDELETE $1/$appApiKey1?token=$authToken
   curl -s -XDELETE $1/$appApiKey2?token=$authToken
}

function add_api_keys() {
   postA="{\"apikey\":\"$appApiKey1\"}"
   postB="{\"apikey\":\"$appApiKey2\"}"
   curl -s -XPOST $1?token=$authToken -d $postA 
   curl -s -XPOST $1?token=$authToken -d $postB  
}

function report_status() {
   echo "**********"
   echo $1
   echo "**********"
}

if [ ! -f ~/dataimport/trigdesk.txt ]; then
   echo "Cannot continue. Cannot find ~/dataimport/trigdesk.txt"
   exit 0
fi

poisetA=`curl -s $poisetAurl?token=$authToken`
stagingPoiSet=$poisetAurl
livePoiSet=$poisetBurl

if grep -q "$appApiKey1" <<< "$poisetA" ; then
  stagingPoiSet=$poisetBurl
  livePoiSet=$poisetAurl
fi

report_status "Writing updated POI data to staging area: $stagingPoiSet"

rm -rf assets/employees.csv
rm -rf assets/departments.csv
python import_employees.py -i ~/dataimport/trigdesk.txt -o assets/employees.csv
python import_departments.py -i ~/dataimport/trigdesk.txt -o assets/departments.csv -d assets/swallow-pois.xls

python import_csv_to_xls.py -i assets/employees.csv -d assets/swallow-pois.xls -w EmployeePois
python import_csv_to_xls.py -i assets/departments.csv -d assets/swallow-pois.xls -w DepartmentPois -t str,str,str,str,int,float,float,str

./export_to_poi_service.sh assets/swallow-pois.xls $stagingPoiSet $authToken 170

timestamp=$(date +%Y%m%d%H%M%S)
mv ~/dataimport/trigdesk.txt ~/dataimport/trigdesk-imported-$timestamp.txt

report_status "Data Imported. Disabling old live: $livePoiSet Live poi set is now $stagingPoiSet"

clear_api_keys $livePoiSet
add_api_keys $stagingPoiSet
