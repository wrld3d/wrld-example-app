import getopt
import os
import shutil
import sys
import traceback
import requests
import json
import xlrd

IMAGES_FOLDER = "images"
CATEGORIES = [u'stationery',
              u'toilets',
              u'print_station',
              u'emergency_exit']
MEETING_ROOM_STATUSES = [u'available',
                         u'available_soon',
                         u'occupied']

# UK bounds
MIN_LAT = 49.0
MAX_LAT = 61.0

MIN_LNG = -8.0
MAX_LNG = 2.5

MIN_DISTANCE = 0.0
MAX_DISTANCE = 3000.0

MIN_HEADING = 0
MAX_HEADING = 360

MIN_FLOOR = 0

def validate_column_names(xls_sheet, column_name_row, expected_columns):
    sheet_column_names = []

    for column_index in range(xls_sheet.ncols):
        column_name = xls_sheet.cell(column_name_row, column_index).value
        if not column_name:
            break
        sheet_column_names.append(column_name.encode('utf-8'))

    validated = expected_columns == sheet_column_names
    if not validated:
        print ("Unexpected column names.\nExpected: " + ",".join(expected_columns) + ";\nGot: " + ",".join(sheet_column_names))

    return validated

def gather_table_with_image(column_names, 
                            xls_sheet, 
                            first_data_row_number, 
                            available_in_app_col_index,
                            image_filename_col_index):
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            print("skipping row " + str(row_num))
            continue
        row_values = xls_sheet.row_values(row_num, 0, len(column_names) - 1)

        image_filename = row_values[image_filename_col_index]
        if image_filename:
            image_filename =  filename_to_jpg(image_filename)
            row_values[image_filename_col_index] = image_filename

        insert_values = [None] + row_values
        if len(insert_values) != len(column_names):
            raise ValueError("mismatched columns for row: " + insert_values)
        yield insert_values

def gather_table(column_names, 
                      xls_sheet, 
                      first_data_row_number, 
                      available_in_app_col_index):
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            print("skipping row " + str(row_num))
            continue
        row_values = xls_sheet.row_values(row_num, 0, len(column_names) - 1)

        insert_values = [None] + row_values
        if len(insert_values) != len(column_names):
            raise ValueError("mismatched columns for row: " + insert_values)
        yield insert_values

def is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
    available_in_app = xls_sheet.cell_value(row_num, available_in_app_col_index).encode('utf-8')
    return available_in_app == "Yes"

def validate_images(xls_sheet, first_data_row_number, image_column_index, available_in_app_col_index, image_dir):
    all_images_validated = True
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            continue
        image_filename = xls_sheet.cell_value(row_num, image_column_index)
        image_filename = image_filename.lstrip().rstrip()

        if image_filename != image_filename.lower():
            print("Image filename '%s' isn't in lower case" % image_filename)
            all_images_validated=False

        if image_filename:
            image_path = os.path.join(image_dir, image_filename)

            if not os.path.exists(image_path):
                print("Could not find image " + image_path)
                all_images_validated = False

    if not all_images_validated:
        print("Failed to find all image files")

    return all_images_validated

def validate_category_text_field(xls_sheet, poi_columns, column_name, first_data_row_number, available_in_app_col_index, categories):
    column_index = poi_columns.index(column_name)
    all_rows_validated = True
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            continue

        text_type = xls_sheet.cell_type(row_num, column_index)
        text_value = xls_sheet.cell_value(row_num, column_index).encode('utf-8')

        if not text_value:
            print ("empty cell found for required text field '%s', row %d " % (column_name, row_num))
            all_rows_validated = False

        if not text_value in categories:
            print("Unknown category " + text_value + " for row " + str(row_num))
            all_rows_validated = False

        if not text_type is xlrd.XL_CELL_TEXT:
            print ("non-text cell value '%s' found for required text field '%s', row %d " % (str(text_value), column_name, row_num))
            all_rows_validated = False

    if not all_rows_validated:
        print("Failed to validate all required text fields")

    return all_rows_validated

def validate_required_text_field(xls_sheet, poi_columns, column_name, first_data_row_number, available_in_app_col_index, allow_empty=False):
    column_index = poi_columns.index(column_name)
    all_rows_validated = True
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            continue

        text_type = xls_sheet.cell_type(row_num, column_index)
        text_value = xls_sheet.cell_value(row_num, column_index).encode('utf-8')

        if not text_value:
            if allow_empty:
                continue
            print ("empty cell found for required text field '%s', row %d " % (column_name, row_num))
            all_rows_validated = False

        if not text_type is xlrd.XL_CELL_TEXT:
            print ("non-text cell value '%s' found for required text field '%s', row %d " % (str(text_value), column_name, row_num))
            all_rows_validated = False

    if not all_rows_validated:
        print("Failed to validate all required text fields")

    return all_rows_validated

def validate_required_real_field(xls_sheet, poi_columns, column_name, first_data_row_number, available_in_app_col_index, min_val, max_val):
    column_index = poi_columns.index(column_name)
    all_rows_validated = True
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            continue

        cell_type = xls_sheet.cell_type(row_num, column_index)
        cell_value = xls_sheet.cell_value(row_num, column_index)

        if not cell_type is xlrd.XL_CELL_NUMBER:
            print ("non-number cell value '%s' found for required Real field '%s', row %d " % (str(cell_value), column_name, row_num))
            all_rows_validated = False

        if not min_val <= cell_value <= max_val:
            print ("cell value '%s' not in range (%f, %f) for field '%s', row %d " % (str(cell_value), min_val, max_val, column_name, row_num))
            all_rows_validated = False

    if not all_rows_validated:
        print("Failed to find all image files")

    return all_rows_validated

def validate_required_int_field(xls_sheet, poi_columns, column_name, first_data_row_number, available_in_app_col_index, min_val):
    column_index = poi_columns.index(column_name)
    all_rows_validated = True
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            continue

        cell_type = xls_sheet.cell_type(row_num, column_index)
        cell_value = xls_sheet.cell_value(row_num, column_index)

        if not cell_type is xlrd.XL_CELL_NUMBER:
            print ("non-number cell value '%s' found for required Int field '%s', row %d " % (str(cell_value), column_name, row_num))
            all_rows_validated = False

        if not min_val <= cell_value:
            print ("cell value '%s' is not above (%d) for field '%s', row %d " % (str(cell_value), min_val, column_name, row_num))
            all_rows_validated = False

    if not all_rows_validated:
        print("Failed to validate Int field")

    return all_rows_validated

def filename_to_jpg(image_filename):
    (base_image_filename, ext) = os.path.splitext(image_filename)
    return base_image_filename + '.jpg'

def collect_desks(xls_book, sheet_index, first_data_row_number, column_name_row):
    desks = {}
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    poi_columns = ['desk', 'latitude_degrees', 'longitude_degrees', 'interior_id', 'interior_floor']
    control_columns = ['available_in_app']
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)

    all_validated = True

    all_validated &= validate_column_names(xls_sheet, column_name_row, expected_columns)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated column names")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'desk', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated name column values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'latitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LAT, MAX_LAT)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title latitude_degrees values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'longitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LNG, MAX_LNG)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title longitude_degrees values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'interior_id', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior_id column values")

    all_validated &= validate_required_int_field(xls_sheet, poi_columns, 'interior_floor', first_data_row_number, available_in_app_col_index, MIN_FLOOR)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior floor number")

    if not all_validated:
        raise ValueError("failed validation")

    column_names = ['id'] + poi_columns
    for v in gather_table(column_names, xls_sheet, first_data_row_number, available_in_app_col_index):
        desk = {
            "desk":v[column_names.index('desk')],
            "lat":float(v[column_names.index('latitude_degrees')]),
            "lon":float(v[column_names.index('longitude_degrees')]),
   			"indoor_id":v[column_names.index('interior_id')],
  			"floor_id":int(v[column_names.index('interior_floor')]),
	       }
        desks[desk['desk']] = desk
    return desks

def collect_employee_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row, desks):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    poi_columns = ['name', 'job_title', 'image_filename', 'working_group', 'office_location', 'desk_code']
    control_columns = ['available_in_app']
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)

    all_validated = True

    all_validated &= validate_column_names(xls_sheet, column_name_row, expected_columns)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated column names")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'name', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated name column values")

    allow_empty = True
    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'job_title', first_data_row_number, available_in_app_col_index, allow_empty)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated job_title column values")

    all_validated &= validate_images(xls_sheet, first_data_row_number, poi_columns.index('image_filename'), available_in_app_col_index, src_image_folder_path)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated image_filename column values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'working_group', first_data_row_number, available_in_app_col_index, allow_empty)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated working_group column values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'office_location', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated office_location column values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'desk_code', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated desk_code column values")

    if not all_validated:
        raise ValueError("failed validation")

    column_names = ['id'] + poi_columns
    for v in gather_table_with_image(column_names, xls_sheet, first_data_row_number, available_in_app_col_index, poi_columns.index('image_filename')):
    	desk_code = v[column_names.index('desk_code')]
    	if not desk_code in desks:
    		print "WARNING: No desk found for {0} skipping employee {1}".format(desk_code, v[column_names.index('name')])
    	else:
	    	desk = desks[desk_code]
	    	yield {
	            "title":v[column_names.index('name')],
	            "subtitle":v[column_names.index('job_title')],
	            "category":"person",
	            "lat":desk['lat'],
	            "lon":desk['lon'],
	            "indoor":True,
	  			"indoor_id":desk['indoor_id'],
	  			"floor_id":desk['floor_id'],
	            "user_data":
	            {
	              "image_url":v[column_names.index('image_filename')],
	              "desk_code":desk_code,
	              "office_location":v[column_names.index('office_location')],
	              "working_group":v[column_names.index('working_group')]
	            }
	       }

def collect_meeting_room_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    poi_columns = ['name', 'image_filename', 'availability', 'interior_id', 'interior_floor', 'latitude_degrees', 'longitude_degrees', 'office_location']
    control_columns = ['available_in_app']
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)

    all_validated = True

    all_validated &= validate_column_names(xls_sheet, column_name_row, expected_columns)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated column names")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'name', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated name column values")

    all_validated &= validate_images(xls_sheet, first_data_row_number, poi_columns.index('image_filename'), available_in_app_col_index, src_image_folder_path)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated image_filename column values")

    all_validated &= validate_category_text_field(xls_sheet, poi_columns, 'availability', first_data_row_number, available_in_app_col_index, MEETING_ROOM_STATUSES)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated availability column values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'interior_id', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior_id column values")

    all_validated &= validate_required_int_field(xls_sheet, poi_columns, 'interior_floor', first_data_row_number, available_in_app_col_index, MIN_FLOOR)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior floor number")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'latitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LAT, MAX_LAT)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title latitude_degrees values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'longitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LNG, MAX_LNG)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title longitude_degrees values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'office_location', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated office_location column values")

    if not all_validated:
        raise ValueError("failed validation")

    poi_columns = ['name', 'image_filename', 'availability', 'interior_id', 'interior_floor', 'latitude_degrees', 'longitude_degrees', 'office_location']

    column_names = ['id'] + poi_columns
    for v in gather_table_with_image(column_names, xls_sheet, first_data_row_number, available_in_app_col_index, poi_columns.index('image_filename')):
        yield  {
            "title":v[column_names.index('name')],
            "subtitle":"",
            "category":"meeting_room",
            "lat":float(v[column_names.index('latitude_degrees')]),
            "lon":float(v[column_names.index('longitude_degrees')]),
            "indoor":True,
  			"indoor_id":v[column_names.index('interior_id')],
  			"floor_id":int(v[column_names.index('interior_floor')]),
            "user_data":
            {
              "image_url":v[column_names.index('image_filename')],
              "availability":v[column_names.index('availability')],
              "office_location":v[column_names.index('office_location')]
            }
       }

def collect_working_group_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    poi_columns = ['name', 'image_filename', 'description', 'interior_id', 'interior_floor', 'latitude_degrees', 'longitude_degrees', 'office_location']
    control_columns = ['available_in_app']
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)

    all_validated = True

    all_validated &= validate_column_names(xls_sheet, column_name_row, expected_columns)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated column names")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'name', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated name column values")

    all_validated &= validate_images(xls_sheet, first_data_row_number, poi_columns.index('image_filename'), available_in_app_col_index, src_image_folder_path)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated image_filename column values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'description', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated description column values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'interior_id', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior_id column values")

    all_validated &= validate_required_int_field(xls_sheet, poi_columns, 'interior_floor', first_data_row_number, available_in_app_col_index, MIN_FLOOR)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior floor number")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'latitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LAT, MAX_LAT)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title latitude_degrees values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'longitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LNG, MAX_LNG)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title longitude_degrees values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'office_location', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated office_location column values")

    if not all_validated:
        raise ValueError("failed validation")

    column_names = ['id'] + poi_columns
    for v in gather_table_with_image(column_names, xls_sheet, first_data_row_number, available_in_app_col_index, poi_columns.index('image_filename')):
    	yield {
            "title":v[column_names.index('name')],
            "subtitle":"",
            "category":"working_group",
            "lat":float(v[column_names.index('latitude_degrees')]),
            "lon":float(v[column_names.index('longitude_degrees')]),
            "indoor":True,
  			"indoor_id":v[column_names.index('interior_id')],
  			"floor_id":int(v[column_names.index('interior_floor')]),
            "user_data":
            {
              "image_url":v[column_names.index('image_filename')],
              "description":v[column_names.index('description')],
              "office_location":v[column_names.index('office_location')]
            }
       }

def collect_facility_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    poi_columns = ['name', 'category', 'image_filename', 'description', 'interior_id', 'interior_floor', 'latitude_degrees', 'longitude_degrees']
    control_columns = ['available_in_app']
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)

    all_validated = True

    all_validated &= validate_column_names(xls_sheet, column_name_row, expected_columns)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated column names")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'name', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated name column values")

    all_validated &= validate_category_text_field(xls_sheet, poi_columns, 'category', first_data_row_number, available_in_app_col_index, CATEGORIES)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated name category values")

    all_validated &= validate_images(xls_sheet, first_data_row_number, poi_columns.index('image_filename'), available_in_app_col_index, src_image_folder_path)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated image_filename column values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'description', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated description column values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'interior_id', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior_id column values")

    all_validated &= validate_required_int_field(xls_sheet, poi_columns, 'interior_floor', first_data_row_number, available_in_app_col_index, MIN_FLOOR)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior floor number")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'latitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LAT, MAX_LAT)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title latitude_degrees values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'longitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LNG, MAX_LNG)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title longitude_degrees values")

    if not all_validated:
        raise ValueError("failed validation")

    column_names = ['id'] + poi_columns
    for v in gather_table_with_image(column_names, xls_sheet, first_data_row_number, available_in_app_col_index, poi_columns.index('image_filename')):
        indoor_id = v[column_names.index('interior_id')]
        floor_id = int(v[column_names.index('interior_floor')])
        office_location = get_office_location_from_interior_and_floor(indoor_id, floor_id)
    	yield {
            "title":v[column_names.index('name')],
            "subtitle":"",
            "category":"facility",
            "lat":float(v[column_names.index('latitude_degrees')]),
            "lon":float(v[column_names.index('longitude_degrees')]),
            "indoor":True,
  			"indoor_id":indoor_id,
  			"floor_id":floor_id,
            "user_data":
            {
              "image_url":v[column_names.index('image_filename')],
              "subcategory":v[column_names.index('category')],
              "description":v[column_names.index('description')],
              "office_location":office_location
            }
       }

def get_office_location_from_interior_and_floor(interior_id, floor_id):
    interior_ids_to_names = {}
    interior_ids_to_names["swallow_lon_38finsbury"] = "38 Finsbury"
    interior_ids_to_names["swallow_lon_citygatehouse"] = "City Gate House"
    interior_ids_to_names["swallow_lon_50finsbury"] = "50 Finsbury"
    interior_ids_to_names["swallow_lon_parkhouse"] = "Park House"

    interior_floor_to_name = {}
    interior_floor_to_name["swallow_lon_38finsbury"] = ["Lower Ground Floor", "Ground Floor", "1st Floor", "2nd Floor", "3rd Floor", "4th Floor", "5th Floor", "6th Floor"]
    interior_floor_to_name["swallow_lon_citygatehouse"] = ["Lower Ground Floor", "Ground Floor", "1st Floor", "2nd Floor", "3rd Floor"]
    interior_floor_to_name["swallow_lon_50finsbury"] = ["Lower Ground Floor", "1st Floor", "2nd Floor", "3rd Floor", "4th Floor", "5th Floor", "6th Floor", "7th Floor"]
    interior_floor_to_name["swallow_lon_parkhouse"] = ["3rd Floor", "4th Floor", "5th Floor"]

    return interior_floor_to_name[interior_id][floor_id] + ", " + interior_ids_to_names[interior_id];

def collect_department_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row, departments):
    xls_sheet = xls_book.sheet_by_index(sheet_index)
    
    poi_columns = ['name', 'image_filename', 'description', 'interior_id', 'interior_floor', 'latitude_degrees', 'longitude_degrees']
    control_columns = ['available_in_app']
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)
    
    all_validated = True
    
    all_validated &= validate_column_names(xls_sheet, column_name_row, expected_columns)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated column names")
    
    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'name', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated name column values")
    
    all_validated &= validate_images(xls_sheet, first_data_row_number, poi_columns.index('image_filename'), available_in_app_col_index, src_image_folder_path)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated image_filename column values")
    
    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'description', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated description column values")
    
    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'interior_id', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior_id column values")
    
    all_validated &= validate_required_int_field(xls_sheet, poi_columns, 'interior_floor', first_data_row_number, available_in_app_col_index, MIN_FLOOR)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior floor number")
    
    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'latitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LAT, MAX_LAT)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title latitude_degrees values")
    
    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'longitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LNG, MAX_LNG)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title longitude_degrees values")
    
    if not all_validated:
        raise ValueError("failed validation")

    column_names = ['id'] + poi_columns    
    for v in gather_table_with_image(column_names, xls_sheet, first_data_row_number, available_in_app_col_index, poi_columns.index('image_filename')):
        department_name = v[column_names.index('name')]
        department_desks = []
        if department_name in departments:
            for employee in departments[department_name]:
                department_desks.append(employee["user_data"]["desk_code"])
    	yield {
            "title":department_name,
            "subtitle":"",
            "category":"department",
            "lat":float(v[column_names.index('latitude_degrees')]),
            "lon":float(v[column_names.index('longitude_degrees')]),
            "indoor":True,
  			"indoor_id":v[column_names.index('interior_id')],
  			"floor_id":int(v[column_names.index('interior_floor')]),
            "user_data":
            {
              "image_url":v[column_names.index('image_filename')],
              "description":v[column_names.index('description')],
              "desks":department_desks
            }
       }
    
def collect_office_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    poi_columns = ['name', 'latitude_degrees', 'longitude_degrees', 'distance', 'heading_degrees']
    control_columns = ['available_in_app']
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)

    all_validated = True

    all_validated &= validate_column_names(xls_sheet, column_name_row, expected_columns)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated column names")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'name', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated name column values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'latitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LAT, MAX_LAT)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title latitude_degrees values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'longitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LNG, MAX_LNG)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title longitude_degrees values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'distance', first_data_row_number, available_in_app_col_index, MIN_DISTANCE, MAX_DISTANCE)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title distance values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'heading_degrees', first_data_row_number, available_in_app_col_index, MIN_HEADING, MAX_HEADING)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title distance values")

    if not all_validated:
        raise ValueError("failed validation")

    column_names = ['id'] + poi_columns
    for v in gather_table(column_names, xls_sheet, first_data_row_number, available_in_app_col_index):
    	yield {
            "title":v[column_names.index('name')],
            "subtitle":"",
            "category":"office",
            "lat":float(v[column_names.index('latitude_degrees')]),
            "lon":float(v[column_names.index('longitude_degrees')]),
            "user_data":
            {
              "distance":float(v[column_names.index('distance')]),
              "heading_degrees":float(v[column_names.index('heading_degrees')])
            }
       }

def collect_transition_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    poi_columns = ['interior_id', 'interior_floor', 'latitude_degrees', 'longitude_degrees', 'target_interior_id', 'target_interior_floor', 'target_latitude_degrees', 'target_longitude_degrees']
    control_columns = ['available_in_app']
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)

    all_validated = True

    all_validated &= validate_column_names(xls_sheet, column_name_row, expected_columns)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated column names")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'interior_id', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior_id column values")

    all_validated &= validate_required_int_field(xls_sheet, poi_columns, 'interior_floor', first_data_row_number, available_in_app_col_index, MIN_FLOOR)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior floor number")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'latitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LAT, MAX_LAT)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated latitude_degrees values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'longitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LNG, MAX_LNG)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated longitude_degrees values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, 'target_interior_id', first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated target interior_id column values")

    all_validated &= validate_required_int_field(xls_sheet, poi_columns, 'target_interior_floor', first_data_row_number, available_in_app_col_index, MIN_FLOOR)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated target interior floor number")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'target_latitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LAT, MAX_LAT)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated target latitude_degrees values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, 'target_longitude_degrees', first_data_row_number, available_in_app_col_index, MIN_LNG, MAX_LNG)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated target longitude_degrees values")

    if not all_validated:
        raise ValueError("failed validation")

    column_names = ['id'] + poi_columns
    for v in gather_table(column_names, xls_sheet, first_data_row_number, available_in_app_col_index):
    	yield  {
            "title":"Transition",
            "subtitle":"Indoor Transition",
            "category":"transition",
            "lat":float(v[column_names.index('latitude_degrees')]),
            "lon":float(v[column_names.index('longitude_degrees')]),
            "indoor":True,
  			"indoor_id":v[column_names.index('interior_id')],
  			"floor_id":int(v[column_names.index('interior_floor')]),
            "user_data":
            {
              "target_interior_id":v[column_names.index('target_interior_id')],
              "target_interior_floor":int(v[column_names.index('target_interior_floor')]),
              "target_latitude_degrees":float(v[column_names.index('target_latitude_degrees')]),
              "target_longitude_degrees":float(v[column_names.index('target_longitude_degrees')])
            }
       }

def delete_existing_pois(poi_service_url, dev_auth_token):
	url = "{0}/pois/?token={1}".format(poi_service_url, dev_auth_token)
	response = requests.delete(url, verify=False)
	print "delete {1}: {0}".format(url, response.status_code)


def persist_entities(entities, poi_service_url, dev_auth_token, cdn_base_url):
    for entity in entities:
        if 'user_data' in entity:
            if 'image_url' in entity['user_data']:
                original = entity['user_data']['image_url']
                entity['user_data']['image_url'] = "{0}/images/{1}".format(cdn_base_url, original)

    url = "{0}/bulk/?token={1}".format(poi_service_url, dev_auth_token)
    response = requests.post(url, json={"create":entities}, verify=False)
    print "post {2}: {0}".format(url, {"create":entities}, response.status_code)


def build_db(src_xls_path, poi_service_url, dev_auth_token, cdn_base_url, verbose, stop_on_first_error):
    src_dir = os.path.normpath(os.path.dirname(src_xls_path))

    column_name_row = 0
    first_data_row_number = 1
    
    if not os.path.exists(src_xls_path):
        raise ValueError('file not found: ' + src_xls_path)

    src_image_folder_path = os.path.join(src_dir, IMAGES_FOLDER)

    if not os.path.exists(src_image_folder_path):
        raise ValueError("images folder not found: " + src_image_folder_path)

    xls_book =  xlrd.open_workbook(src_xls_path)

    sheet_index = 7

    desks = collect_desks(xls_book, sheet_index, first_data_row_number, column_name_row)

    entities = []
    departments = {}

    sheet_index = 0

    for e in collect_employee_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row, desks):
    	department = e['user_data']['working_group']
    	if not department in departments:
			departments[department] = []    		
    	departments[department].append(e)
    	entities.append(e)

    sheet_index = 1

    for e in collect_meeting_room_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    	entities.append(e)

    sheet_index = 2

    for e in collect_working_group_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    	entities.append(e)

    sheet_index = 3

    for e in collect_facility_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    	entities.append(e)

    sheet_index = 4

    for e in collect_office_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    	entities.append(e)

    sheet_index = 5

    for e in collect_transition_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row):
    	entities.append(e)
    
    sheet_index = 6
    
    for e in collect_department_table(xls_book, sheet_index, src_image_folder_path, verbose, first_data_row_number, column_name_row, departments):
    	entities.append(e)

    delete_existing_pois(poi_service_url, dev_auth_token)
    persist_entities(entities, poi_service_url, dev_auth_token, cdn_base_url)

def print_usage():
    print 'Usage: '
    print 'export_to_poi_service.py -i <input_xls_path> -u <poi_service_url> -k <dev_auth_token> [-v | -s]'
    print 'export_to_poi_service.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_xls_path      Filepath to source xls spreadsheet'
    print '-u --poi_service_url     URL to poi-service'
    print '-k --dev_auth_token      eeGeo Developer Auth Token'
    print '-h --help                Display this screen'
    print '-v --verbose             Verbose logging, including dump contents of resulting Poi table'
    print '-s --stop                Stop on first validation error'

def get_args(argv):
    input_xls_path = ''
    poi_service_url = ''
    dev_auth_token = ''
    cdn_base_url = ''
    verbose = False
    stop_on_first_error = False
    try:
        opts, args = getopt.getopt(argv,"hvsi:u:k:c:",["input_xls_path=","poi_service_url=","dev_auth_token=","cdn_base_url=","verbose","stop"])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print_usage()
            sys.exit()
        elif opt in ("-i", "--input_xls_path"):
            input_xls_path = arg
        elif opt in ("-u", "--poi_service_url"):
            poi_service_url = arg
        elif opt in ("-k", "--dev_auth_token"):
        	dev_auth_token = arg
        elif opt in ("-c", "--cdn_base_url"):
        	cdn_base_url = arg
        elif opt in ("-v", "--verbose"):
            verbose = True
        elif opt in ("-s", "--stop"):
            stop_on_first_error = True

    return input_xls_path, poi_service_url, dev_auth_token, cdn_base_url, verbose, stop_on_first_error

if __name__ == '__main__':
    try:
        src_xls_path, poi_service_url, dev_auth_token, cdn_base_url, verbose, stop_on_first_error = get_args(sys.argv[1:])

        print 'src_xls_path=' + src_xls_path
        print 'poi_service_url=' + poi_service_url

        build_db(src_xls_path, poi_service_url, dev_auth_token, cdn_base_url, verbose, stop_on_first_error)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
