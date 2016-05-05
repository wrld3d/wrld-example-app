import getopt
import os
import shutil
import sqlite3
import sys
import traceback
from PIL import Image
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
MIN_LAT = 30.0
MAX_LAT = 61.0

MIN_LNG = -200.0
MAX_LNG = 2.5

MIN_DISTANCE = 0.0
MAX_DISTANCE = 3000.0

MIN_HEADING = 0
MAX_HEADING = 360

MIN_FLOOR = 0


def make_create_table_command(table_name, column_names, column_types):
    zipped = zip(column_names, column_types)
    comma_separated_column_names_with_types = ', '.join([' '.join(pair) for pair in zipped])

    sql_create_table_command = u'create table "' + \
                               table_name + \
                               '"  (' +\
                               comma_separated_column_names_with_types + \
                               ');'
    return sql_create_table_command


def create_table(db_cursor, table_name, column_names, column_types):
    sql_create_table_cmd = make_create_table_command(table_name, column_names, column_types)
    db_cursor.execute(sql_create_table_cmd)


def to_relative_image_path(dest_image_relative_dir, image_filename):
    image_filename = image_filename.lstrip().rstrip()
    return os.path.normcase(os.path.join(dest_image_relative_dir, image_filename)).replace("\\","/")

def insert_into_table_with_image_column(db_cursor, 
                                        table_name, 
                                        column_names, 
                                        xls_sheet, 
                                        first_data_row_number, 
                                        available_in_app_col_index,
                                        image_filename_col_index,
                                        dest_image_relative_dir):
    placeholder_fields = ['?'] * len(column_names)
    comma_separated_placeholder_fields = ','.join(placeholder_fields)
    sql_insert_row_cmd = u'INSERT INTO "' +\
                         table_name +\
                         '" VALUES (' +\
                         comma_separated_placeholder_fields +\
                         ');'

    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            print("skipping row " + str(row_num))
            continue
        row_values = xls_sheet.row_values(row_num, 0, len(column_names) - 1)

        image_filename = row_values[image_filename_col_index]
        if image_filename:
            image_filename =  filename_to_jpg(image_filename)
            row_values[image_filename_col_index] = to_relative_image_path(dest_image_relative_dir, image_filename)

        insert_values = [None] + row_values
        if len(insert_values) != len(column_names):
            raise ValueError("mismatched columns for row: " + insert_values)
        db_cursor.execute(sql_insert_row_cmd, insert_values)

def insert_into_table(db_cursor, 
                      table_name, 
                      column_names, 
                      xls_sheet, 
                      first_data_row_number, 
                      available_in_app_col_index):
    placeholder_fields = ['?'] * len(column_names)
    comma_separated_placeholder_fields = ','.join(placeholder_fields)
    sql_insert_row_cmd = u'INSERT INTO "' +\
                         table_name +\
                         '" VALUES (' +\
                         comma_separated_placeholder_fields +\
                         ');'

    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            print("skipping row " + str(row_num))
            continue
        row_values = xls_sheet.row_values(row_num, 0, len(column_names) - 1)

        insert_values = [None] + row_values
        if len(insert_values) != len(column_names):
            raise ValueError("mismatched columns for row: " + insert_values)
        db_cursor.execute(sql_insert_row_cmd, insert_values)

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

def validate_required_text_field(xls_sheet, poi_columns, column_name, first_data_row_number, available_in_app_col_index):
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

def scale_image_to_width(img, width):
    h_scale = (width / float(img.size[0]))
    v_size = int( float(img.size[1]) * float(h_scale) )
    return img.resize((width, v_size), Image.ANTIALIAS)

def filename_to_jpg(image_filename):
    (base_image_filename, ext) = os.path.splitext(image_filename)
    return base_image_filename + '.jpg'

def build_images(xls_sheet, first_data_row_number, image_column_index, available_in_app_col_index, src_image_dir, dest_image_dir, verbose):
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            continue

        image_filename = xls_sheet.cell_value(row_num, image_column_index)
        image_filename = image_filename.lstrip().rstrip()
        if image_filename:
            src_image_path = os.path.join(src_image_dir, image_filename)

            dst_image_filename = filename_to_jpg(image_filename)
            dest_image_path = os.path.join(dest_image_dir, dst_image_filename)

            img = Image.open(src_image_path)
            max_output_width = 1024
            if img.size[0] > max_output_width:
                if verbose:
                    print "Scaling width from %d to %d" % (img.size[0], max_output_width)
                img = scale_image_to_width(img, max_output_width)

            if verbose:
                print ("Convert " + src_image_path + " to " + dest_image_path)
            img.save(dest_image_path, "JPEG")

def validate_table_exists(db_cursor, table_name):
    db_cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")

    result_row = db_cursor.fetchone()
    while result_row != None:
        if result_row[0] == table_name:
            return
        else:
            result_row = db_cursor.fetchone()

    raise ValueError("Failed to create table")


def log_result_info(db_cursor, table_name, verbose):
    print('Created table: ' + table_name)
    db_cursor.execute("SELECT COUNT(*) FROM " + table_name)
    row_count = db_cursor.fetchone()[0]
    print("row_count: " + str(row_count))

    if verbose:
        for row in db_cursor.execute("SELECT * FROM " + table_name):
            print(row)


def build_defibrilator_table(xls_book, sheet_index, db_cursor, connection, src_image_folder_path, dest_image_dir, verbose, first_data_row_number, column_name_row, dest_image_relative_dir):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    table_name = xls_sheet.name

    print(str(table_name))

    poi_columns = ['name', 'image_filename', 'interior_id', 'interior_floor', 'latitude_degrees', 'longitude_degrees']
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

    build_images(xls_sheet, first_data_row_number, poi_columns.index('image_filename'), available_in_app_col_index, src_image_folder_path, dest_image_dir, verbose)

    column_names = ['id'] + poi_columns
    column_types = ['INTEGER PRIMARY KEY', 'TEXT', 'TEXT', 'TEXT', 'TEXT', 'INTEGER', 'REAL', 'REAL']
    create_table(db_cursor, table_name, column_names, column_types)

    insert_into_table_with_image_column(db_cursor, table_name, column_names, xls_sheet, first_data_row_number, available_in_app_col_index, poi_columns.index('image_filename'), dest_image_relative_dir)

    connection.commit()

    validate_table_exists(db_cursor, table_name)

    log_result_info(db_cursor, table_name, verbose)

    connection.commit()

def build_transition_table(xls_book, sheet_index, db_cursor, connection, src_image_folder_path, dest_image_dir, verbose, first_data_row_number, column_name_row, dest_image_relative_dir):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    table_name = xls_sheet.name

    print(str(table_name))

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
    column_types = ['INTEGER PRIMARY KEY', 'TEXT', 'INTEGER', 'REAL', 'REAL', 'TEXT', 'INTEGER', 'REAL', 'REAL']
    create_table(db_cursor, table_name, column_names, column_types)

    insert_into_table(db_cursor, table_name, column_names, xls_sheet, first_data_row_number, available_in_app_col_index)

    connection.commit()

    validate_table_exists(db_cursor, table_name)

    log_result_info(db_cursor, table_name, verbose)

    connection.commit()

def build_db(src_xls_path, dest_db_path, dest_assets_relative_path, verbose, stop_on_first_error):
    print("sqlite3.sqlite_version " + sqlite3.sqlite_version)
    print("sqlite3.version " + sqlite3.version)

    src_dir = os.path.normpath(os.path.dirname(src_xls_path))
    dest_dir = os.path.normpath(os.path.dirname(dest_db_path))

    if src_dir is dest_dir:
        raise ValueError("source and dest dirs are the same")

    column_name_row = 0
    first_data_row_number = 1
    
    if not os.path.exists(src_xls_path):
        raise ValueError('file not found: ' + src_xls_path)

    src_image_folder_path = os.path.join(src_dir, IMAGES_FOLDER)

    if not os.path.exists(src_image_folder_path):
        raise ValueError("images folder not found: " + src_image_folder_path)

    if os.path.exists(dest_dir):
        print("cleaning destination folder: " + dest_dir)
        shutil.rmtree(dest_dir)

    dest_image_relative_dir = os.path.normcase(os.path.join(dest_assets_relative_path, IMAGES_FOLDER)).replace("\\","/")

    dest_image_dir = os.path.normpath(os.path.join(dest_dir, dest_image_relative_dir))
    print("creating dest folder: " + dest_image_dir)
    os.makedirs(dest_image_dir)

    connection = sqlite3.connect(dest_db_path)
    db_cursor = connection.cursor()

    xls_book =  xlrd.open_workbook(src_xls_path)

    sheet_index = 0

    build_defibrilator_table(xls_book, sheet_index, db_cursor, connection, src_image_folder_path, dest_image_dir, verbose, first_data_row_number, column_name_row, dest_image_relative_dir)

    db_cursor.close()
    connection.close()

def print_usage():
    print 'Usage: '
    print 'poi_database_builder.py -i <input_xls_path> -o <output_db_path> -a <output_asset_relative_path> [-v | -s]'
    print 'poi_database_builder.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_xls_path      Filepath to source xls spreadsheet'
    print '-o --output_db_path      Filepath to dest sqlite3 db file'
    print '-h --help                Display this screen'
    print '-v --verbose             Verbose logging, including dump contents of resulting Poi table'
    print '-s --stop                Stop on first validation error'

def get_args(argv):
    input_xls_path = ''
    output_db_path = ''
    output_assets_path = ''
    verbose = False
    stop_on_first_error = False
    try:
        opts, args = getopt.getopt(argv,"hvsi:o:a:",["input_xls_path=","output_db_path=","output_assets_path=","verbose","stop"])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print_usage()
            sys.exit()
        elif opt in ("-i", "--input_xls_path"):
            input_xls_path = arg
        elif opt in ("-o", "--output_db_path"):
            output_db_path = arg
        elif opt in ("-a", "--output_assets_path"):
            output_assets_path = arg
        elif opt in ("-v", "--verbose"):
            verbose = True
        elif opt in ("-s", "--stop"):
            stop_on_first_error = True

    return input_xls_path, output_db_path, output_assets_path, verbose, stop_on_first_error

if __name__ == '__main__':
    try:
        src_xls_path, dest_db_path, dest_assets_relative_path, verbose, stop_on_first_error = get_args(sys.argv[1:])

        print 'src_xls_path=' + src_xls_path
        print 'dest_db_path=' + dest_db_path

        build_db(src_xls_path, dest_db_path, dest_assets_relative_path, verbose, stop_on_first_error)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
