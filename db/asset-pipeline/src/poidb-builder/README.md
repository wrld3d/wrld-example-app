# Swallow POI DB pipeline
The Swallow POI DB Pipeline is derived from the original [V&A POI Pipeline](https://github.com/eegeo/design-in-motion-app) but is now heavily modified to support Swallow use cases

### Requirements
To run the Swallow POI DB Pipeline, you will require:
- python2.7
- pip

### Setup

```sh
$ pip install -r ../../pip_requirements
```
### Exporting the Excel Sheet to poi-service

The Swallow DB can be exported to [poi-service](https://github.com/eegeo/poi-service)
```sh
$ mkdir output_geojson/
$ python export_to_poi_service.py -i assets/swallow-pois.xls -u <poi_set_url:http://poi-staging.eegeo.com/poisets/16> -k <developer_auth_token> -a <local_asset_path> -v -c <cdn_asset_base_url>```
$ python export_to_poi_service.py -i assets/swallow-pois.xls -u http://poi-staging.eegeo.com/poisets/16 -k <developer_auth_token> -a assets_v112 -v -c http://cdn1.eegeo.com/swallow-pois/assets/v112
```

### Importing canonical Desk positions

The Swallow DB contains a sheet 'desks' - this is not the canonical source of desk positions. The canonical desk positions are stored in interior entity data in [interiors-gis](https://github.com/eegeo/interiors-gis/tree/master/interior-entity-data/private/swallow/gb)

A script is available to export the interiors-gis entity json to csv, which can then be imported into the excel sheet:

```sh
$ git clone git@github.com:eegeo/interiors-gis.git
$ python export_desk_positions.py -i interiors-gis/interior-entity-data/private/swallow/gb
```

### Exporting the Excel Sheet to geojson

The Swallow DB can be exported to geojson, which can be in turn loaded and edited in [QGIS](http://www.qgis.org/):
```sh
$ mkdir output_geojson/
$ python export_to_geojson.py -i ../../../asset-pipeline/src/poidb-builder/assets/swallow-pois.xls --output_geojson_path=output_geojson/
```

### Importing the Excel Sheet from geojson
The exported geojson can in turn be converted back to the excel sheet:
```sh
$ rm -rf ../../../asset-pipeline/src/poidb-builder/assets/swallow-pois.xls
$ python import_from_geojson.py -i output_geojson/ -o ../../../asset-pipeline/src/poidb-builder/assets/swallow-pois.xls 
```

### Editing in QGIS
You can load the exported geojson files in [QGIS](http://www.qgis.org/). Once edited, export back to geojson.

### Deprecation Warning
> Warning: Pending Deprecation
> Please note, the Swallow DB POI Pipeline will soon be replaced with a direct geojson venue schema, with import directly into a POI backend.
