#!/bin/sh


if [ ! -f ~/dataimport/trigdesk.txt ]; then
   echo "ERROR. Cannot continue. Cannot find ~/dataimport/trigdesk.txt"
   exit 1
fi

rm -rf assets/employees.csv
rm -rf assets/departments.csv
python import_employees.py -i ~/dataimport/trigdesk.txt -o assets/employees.csv
python import_departments.py -i ~/dataimport/trigdesk.txt -o assets/departments.csv -d assets/swallow-pois.xls

python import_csv_to_xls.py -i assets/employees.csv -d assets/swallow-pois.xls -w EmployeePois
python import_csv_to_xls.py -i assets/departments.csv -d assets/swallow-pois.xls -w DepartmentPois -t str,str,str,str,int,float,float,str

./export_to_poi_service.sh assets/swallow-pois.xls https://londWayFApp01.eegeo.com/search/v1.1/poisets/1 G5MONCictZXp8hZLJvAvS6xGZo5EluaFKKil5CEfkBRsu2CA5XihAJ3x1NSbysNBrSqbO6pl92LSEjFq 170
