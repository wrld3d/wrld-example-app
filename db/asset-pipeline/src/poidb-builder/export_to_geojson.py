import argparse
import os
import shutil
import sys
import traceback

import geojson
from geojson import Point, Feature, FeatureCollection
import xlrd

def export_to_geojson(src_xls_path, dest_geojson_path, verbose, stop_on_first_error):
    src_dir = os.path.normpath(os.path.dirname(src_xls_path))
    dest_dir = os.path.normpath(os.path.dirname(dest_geojson_path))

    if src_dir is dest_dir:
        raise ValueError("source and dest dirs are the same")

    if dest_dir is '.':
        raise ValueError("cannot use destination path of . specify via -o, i.e. -o ./my_destionation_folder/")
    
    if not os.path.exists(src_xls_path):
        raise ValueError('file not found: ' + src_xls_path)

    if os.path.exists(dest_dir):
        print("cleaning destination folder: " + dest_dir)
        shutil.rmtree(dest_dir)

    print("creating dest folder: " + dest_dir)
    os.makedirs(dest_dir)

    xls_book =  xlrd.open_workbook(src_xls_path)

    for sheet_idx in range(0, xls_book.nsheets):
        _export_sheet(xls_book, sheet_idx, dest_geojson_path, verbose, stop_on_first_error)

def _export_sheet(xls_book, sheet_index, dest_geojson_path, verbose, stop_on_first_error):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    table_name = xls_sheet.name

    print("Exporting {0}".format(str(table_name)))

    column_name_row = 0
    column_names = []
    features = []
    first_data_row_number = 1

    num_columns = 0
    for i in range(0, xls_sheet.ncols):
        value = xls_sheet.cell_value(0, num_columns)
        if value != "":
            column_names.append(value)
            num_columns = num_columns + 1

    lat_col = column_names.index('latitude_degrees')
    lon_col = column_names.index('longitude_degrees')
    print("Column Names: {0}".format(column_names))

    for row_num in range(first_data_row_number, xls_sheet.nrows):
        row_values = xls_sheet.row_values(row_num, 0, num_columns)
        lat = row_values[lat_col]
        lon = row_values[lon_col]

        properties = {}
        column_idx = 0
        for column_name in column_names:         
            properties["{0}_{1}".format(column_idx, column_name)] = row_values[column_idx]
            column_idx = column_idx + 1

        point = Point((lon, lat))
        feature = Feature(geometry=point, properties=properties)
        features.append(feature)
        
        print("{0},{1} => {2}".format(lat, lon, row_values))

    geojson_path = os.path.join(dest_geojson_path, "{0}_{1}".format(sheet_index, table_name))

    with open(geojson_path + ".geojson", "w") as f:
        f.write(geojson.dumps(FeatureCollection(features), indent=4, sort_keys=True))

def get_args(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument('-o', '--output_geojson_path', help="Path to geojson export folder")
    parser.add_argument('-i', '--input_xls_path', help="Path to excel sheet to convert")
    parser.add_argument('-s', '--stop', help="Stop on first validation failure")
    parser.add_argument('-v', dest='verbose', action='store_true')
    args = parser.parse_args()

    return args.input_xls_path, args.output_geojson_path, args.verbose, args.stop

if __name__ == '__main__':
    try:
        src_xls_path, dest_geojson_path, verbose, stop_on_first_error = get_args(sys.argv[1:])

        print 'src_xls_path=' + src_xls_path
        print 'dest_geojson_path=' + dest_geojson_path

        export_to_geojson(src_xls_path, dest_geojson_path, verbose, stop_on_first_error)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
