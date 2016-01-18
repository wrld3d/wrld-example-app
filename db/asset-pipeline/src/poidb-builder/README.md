# Swallow POI DB pipeline
The Swallow POI DB Pipeline is derived from the [V&A POI Pipeline](https://github.com/eegeo/design-in-motion-app)

### Requirements
To run the Swallow POI DB Pipeline, you will require:
- python2.7
- pip

### Setup

```sh
$ pip install -r ../../pip_requirements
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
