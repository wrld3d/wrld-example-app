### Requirements
To run the POI DB Pipeline, you will require:
- OS X (should work on windows, but untested)
- python >= 2.7.9

### Setup
Open a terminal in the directory containing this file (README.md)
```sh
$ (cd ../../ && ./setup.sh) 
```

If you encounter errors, try upgrading pip:
```sh
$ sudo pip install -U pip
```

### Exporting the Excel Sheet to poi-service (and upload assets)

The DB can be exported to [poi-service](https://github.com/eegeo/poi-service)

To run this bash script, you will need your poi set id, eegeo dev token, aws credentials and a version number.

Usage format:
```sh
./deploy_pois.sh <xls_path> https://<poi_service_url> <eegeo_dev_token> <cdn_url> <aws_s3_key> <aws_s3_secret> <version_number>
```

Usage example (you will need to insert the relevant credentials).
This example updates the poi set with id=20 and uploads the assets to a version 5 folder on the cdn. 
```sh
./deploy_pois.sh assets/ldc-pois.xls https://poi.eegeo.com/v1/poisets/20 INSERT_EEGEO_DEV_TOKEN_HERE http://cdn3.eegeo.com INSERT_AWS_KEY_HERE INSERT_AWS_SECRET_HERE 5
```

### Exporting the Excel Sheet to geojson

The DB can be exported to geojson, which can be in turn loaded and edited in [QGIS](http://www.qgis.org/):
```sh
$ mkdir output_geojson/
$ python export_to_geojson.py -i ../../../asset-pipeline/src/poidb-builder/assets/ldc-pois.xls --output_geojson_path=output_geojson/
```

### Importing the Excel Sheet from geojson
The exported geojson can in turn be converted back to the excel sheet:
```sh
$ rm -rf ../../../asset-pipeline/src/poidb-builder/assets/ldc-pois.xls
$ python import_from_geojson.py -i output_geojson/ -o ../../../asset-pipeline/src/poidb-builder/assets/ldc-pois.xls 
```

### Editing in QGIS
You can load the exported geojson files in [QGIS](http://www.qgis.org/). Once edited, export back to geojson.
