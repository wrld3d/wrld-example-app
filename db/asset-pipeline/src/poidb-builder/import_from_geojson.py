import argparse
import os
import shutil
import sys
import traceback

import geojson
import xlwt

def list_geojsons(geojson_path):
    return [f for f in os.listdir(geojson_path) if f.endswith(".geojson")]

def column_sorter(key):
    split = key.split('_')
    return int(split[0])

def get_columns(data):
    feature = data.features[0]
    column_headers = feature.properties.keys()
    column_headers.sort(key=column_sorter)
    return column_headers

def add_column_headers(sheet, data):
    columns = get_columns(data)
    fidx = 0
    for column_header in columns:
      split = column_header.split('_')
      column_name = '_'.join(split[1:])
      sheet.write(0, fidx, column_name)
      fidx = fidx + 1

def populate_data(sheet, data):
    columns = get_columns(data)
    row = 1
    column = 0
    for feature in data.features:
        for column_name in columns:
            sheet.write(row, column, feature.properties[column_name])
            column = column + 1
        row = row + 1
        column = 0

def append_geojson_to_workbook(workbook, geojson_path, geojson_name):
    with open(geojson_path, "r") as geojson_stream:
      data = geojson.loads(geojson_stream.read())
      sheet = workbook.add_sheet(geojson_name)
      add_column_headers(sheet, data)
      populate_data(sheet, data)

def import_geojsons(geojson_path, dest_xls_path, verbose, stop_on_first_error):
    src_dir = os.path.normpath(os.path.dirname(geojson_path))

    if os.path.exists(dest_xls_path):
        raise ValueError("destination file {0} already exists".format(dest_xls_path))

    if not os.path.exists(src_dir):
        raise ValueError("source folder {0} not found".format(src_dir))

    book = xlwt.Workbook()

    geojsons = list_geojsons(geojson_path)
    for geojson in geojsons:
        print "Importing {0}".format(geojson)
        sheet_name = geojson.split('_')[1].split('.')[0]
        append_geojson_to_workbook(book, os.path.join(geojson_path, geojson), sheet_name)

    book.save(dest_xls_path)

def get_args(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument('-o', '--output_xls_path', help="Path to Excel file to write")
    parser.add_argument('-i', '--input_geojson_path', help="Path to geojsons to import")
    parser.add_argument('-s', '--stop', help="Stop on first validation failure")
    parser.add_argument('-v', dest='verbose', action='store_true')
    args = parser.parse_args()

    return args.input_geojson_path, args.output_xls_path, args.verbose, args.stop

if __name__ == '__main__':
    try:
        src_geojson_path, dest_xls_path, verbose, stop_on_first_error = get_args(sys.argv[1:])

        print 'src_geojson_path=' + src_geojson_path
        print 'dest_xls_path=' + dest_xls_path

        import_geojsons(src_geojson_path, dest_xls_path, verbose, stop_on_first_error)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
