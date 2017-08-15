import getopt
import os
import sys
import traceback
import xlrd
import json


IMAGES_FOLDER = "images"


# UK bounds
MIN_LAT = 49.0
MAX_LAT = 61.0

MIN_LNG = -8.0
MAX_LNG = 2.5

MIN_FLOOR = 0


def get_interior_id_dict(filename):
    interior_id_dict = {}

    with open(filename) as interior_id_json_file:
        interior_id_list_json = json.load(interior_id_json_file)
        for interior_id_json in interior_id_list_json:
            interior_id_dict[interior_id_json["interior_id"]] = interior_id_json["locationId"]

    return interior_id_dict


def get_interior_floor_dict(filename):
    interior_id_floor_dict = {}

    with open(filename) as interior_floor_json_file:
        interior_floor_list_json = json.load(interior_floor_json_file)
        for interior_id_floor_json in interior_floor_list_json:
            interior_floor_dict = {}

            for interior_floor_json in interior_id_floor_json["floors"]:
                interior_floor_dict[interior_floor_json["interior_floor"]] = interior_floor_json["floorName"]

            interior_id_floor_dict[interior_id_floor_json["interior_id"]] = interior_floor_dict

    return interior_id_floor_dict


def validate_column_names(xls_sheet, column_name_row, expected_columns):
    sheet_column_names = []

    for column_index in range(xls_sheet.ncols):
        column_name = xls_sheet.cell(column_name_row, column_index).value
        if not column_name:
            break
        sheet_column_names.append(column_name.encode("utf-8"))

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


def is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
    available_in_app = xls_sheet.cell_value(row_num, available_in_app_col_index).encode("utf-8")
    return available_in_app == "Yes"


def validate_images(xls_sheet, first_data_row_number, image_column_index, available_in_app_col_index, image_dir):
    all_images_validated = True
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            continue
        image_filename = xls_sheet.cell_value(row_num, image_column_index)
        image_filename = image_filename.lstrip().rstrip()

        if image_filename != image_filename.lower():
            print("Image filename \"%s\" isn't in lower case" % image_filename)
            all_images_validated=False

        if image_filename:
            image_path = os.path.join(image_dir, image_filename)

            if not os.path.exists(image_path):
                print("Could not find image " + image_path)
                all_images_validated = False

    if not all_images_validated:
        print("Failed to find all image files")

    return all_images_validated


def validate_required_text_field(xls_sheet, poi_columns, column_name, first_data_row_number, available_in_app_col_index, allow_empty=False):
    column_index = poi_columns.index(column_name)
    all_rows_validated = True
    for row_num in range(first_data_row_number, xls_sheet.nrows):
        if not is_row_available_in_app(xls_sheet, row_num, available_in_app_col_index):
            continue

        text_type = xls_sheet.cell_type(row_num, column_index)
        text_value = xls_sheet.cell_value(row_num, column_index).encode("utf-8")

        if not text_value:
            if allow_empty:
                continue
            print ("empty cell found for required text field \"%s\", row %d " % (column_name, row_num))
            all_rows_validated = False

        if not text_type is xlrd.XL_CELL_TEXT:
            print ("non-text cell value \"%s\" found for required text field \"%s\", row %d " % (str(text_value), column_name, row_num))
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
            print ("non-number cell value \"%s\" found for required Real field \"%s\", row %d " % (str(cell_value), column_name, row_num))
            all_rows_validated = False

        if not min_val <= cell_value <= max_val:
            print ("cell value \"%s\" not in range (%f, %f) for field \"%s\", row %d " % (str(cell_value), min_val, max_val, column_name, row_num))
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
            print ("non-number cell value \"%s\" found for required Int field \"%s\", row %d " % (str(cell_value), column_name, row_num))
            all_rows_validated = False

        if not min_val <= cell_value:
            print ("cell value \"%s\" is not above (%d) for field \"%s\", row %d " % (str(cell_value), min_val, column_name, row_num))
            all_rows_validated = False

    if not all_rows_validated:
        print("Failed to validate Int field")

    return all_rows_validated


def filename_to_jpg(image_filename):
    (base_image_filename, ext) = os.path.splitext(image_filename)
    return base_image_filename + ".jpg"


def collect_meeting_room_table(xls_book, sheet_index, src_image_folder_path, first_data_row_number, column_name_row, interior_id_dict, interior_floor_dict):
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    poi_columns = ["name", "image_filename", "availability", "interior_id", "interior_floor", "latitude_degrees", "longitude_degrees", "office_location"]
    control_columns = ["available_in_app"]
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)

    all_validated = True

    all_validated &= validate_column_names(xls_sheet, column_name_row, expected_columns)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated column names")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, "name", first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated name column values")

    all_validated &= validate_images(xls_sheet, first_data_row_number, poi_columns.index("image_filename"), available_in_app_col_index, src_image_folder_path)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated image_filename column values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, "interior_id", first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior_id column values")

    all_validated &= validate_required_int_field(xls_sheet, poi_columns, "interior_floor", first_data_row_number, available_in_app_col_index, MIN_FLOOR)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated interior floor number")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, "latitude_degrees", first_data_row_number, available_in_app_col_index, MIN_LAT, MAX_LAT)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title latitude_degrees values")

    all_validated &= validate_required_real_field(xls_sheet, poi_columns, "longitude_degrees", first_data_row_number, available_in_app_col_index, MIN_LNG, MAX_LNG)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated title longitude_degrees values")

    all_validated &= validate_required_text_field(xls_sheet, poi_columns, "office_location", first_data_row_number, available_in_app_col_index)
    if not all_validated and stop_on_first_error:
        raise ValueError("failed to validated office_location column values")

    if not all_validated:
        raise ValueError("failed validation")

    poi_columns = ["name", "image_filename", "availability", "interior_id", "interior_floor", "latitude_degrees", "longitude_degrees", "office_location"]

    column_names = ["id"] + poi_columns

    image_map = []
    location_map = []

    get_meeting_space_details = []
    get_meeting_space_occupancy_details = []

    availability_states = ["available", "occupied", "available_soon"]

    for v in gather_table_with_image(column_names, xls_sheet, first_data_row_number, available_in_app_col_index, poi_columns.index("image_filename")):
        interior_id = v[column_names.index("interior_id")]
        space_id = len(image_map)
        floor_id = int(v[column_names.index('interior_floor')])

        image_map.append({"spaceId": space_id, "image_filename": v[column_names.index("image_filename")]})
        location_map.append({"spaceId": space_id, "latitude_degrees": float(v[column_names.index("latitude_degrees")]), "longitude_degrees": float(v[column_names.index("longitude_degrees")])})

        get_meeting_space_details.append\
            (
                {
                    "locationId": interior_id_dict[interior_id],
                    "spaceId": space_id,
                    "floorName": interior_floor_dict[interior_id][floor_id],
                    "name": v[column_names.index("name")],
                    "shortDescription": v[column_names.index("office_location")],
                    "isAdmin": 0,
                    "capacity": 6,
                    "phone": "0203 525 2668",
                    "tieline": "807 2668",
                    "nexi": 1,
                    "isOccupancyEnabled": 0,
                    "isTemporarilyDeactivated": 0
                }
            )

        get_meeting_space_occupancy_details.append\
            (
                {
                    "spaceId": space_id,
                    "statusId": int(availability_states.index(str(v[column_names.index("availability")]))) + 1,
                    "notes": ""
                }
            )

    return image_map, location_map, get_meeting_space_details, get_meeting_space_occupancy_details


def build_map_files(src_xls_path, interior_id_dict, interior_floor_dict):
    src_dir = os.path.normpath(os.path.dirname(src_xls_path))

    column_name_row = 0
    first_data_row_number = 1
    
    if not os.path.exists(src_xls_path):
        raise ValueError("file not found: " + src_xls_path)

    src_image_folder_path = os.path.join(src_dir, IMAGES_FOLDER)

    if not os.path.exists(src_image_folder_path):
        raise ValueError("images folder not found: " + src_image_folder_path)

    xls_book = xlrd.open_workbook(src_xls_path)

    sheet_index = 1

    image_map, location_map, get_meeting_space_details, get_meeting_space_occupancy_details = collect_meeting_room_table(xls_book, sheet_index, src_image_folder_path, first_data_row_number, column_name_row, interior_id_dict, interior_floor_dict)

    with open("../generated/ImageMap.json", "w") as image_map_file:
        json.dump(image_map, image_map_file)

    with open("../generated/LocationMap.json", "w") as location_map_file:
        json.dump(location_map, location_map_file)

    # used for test web service, remove when proper web service is in place
    get_meeting_space_details_json = {"result": {"rCode": 0, "message": ""}, "meetingSpaceDetails":get_meeting_space_details}
    with open("../generated/GetMeetingSpaceDetails.json", "w") as get_meeting_space_details_file:
        json.dump(get_meeting_space_details_json, get_meeting_space_details_file)

    get_meeting_space_occupancy_details_json = {"result": {"rCode": 0, "message": ""}, "meetingSpaceOccupancyDetails": get_meeting_space_occupancy_details}
    with open("../generated/GetMeetingSpaceOccupancyDetails.json", "w") as get_meeting_space_occupancy_details_file:
        json.dump(get_meeting_space_occupancy_details_json, get_meeting_space_occupancy_details_file)


def print_usage():
    print "Usage: "
    print "export_to_poi_service.py -i <input_xls_path> [-s]"
    print "export_to_poi_service.py [-h | -help]"
    print
    print "Options: "
    print "-i --input_xls_path      Filepath to source xls spreadsheet"
    print "-h --help                Display this screen"
    print "-s --stop                Stop on first validation error"


def get_args(argv):
    input_xls_path = ""
    stop_on_first_error = False
    try:
        opts, args = getopt.getopt(argv,"hvsi:",["input_xls_path=","stop"])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == "-h":
            print_usage()
            sys.exit()
        elif opt in ("-i", "--input_xls_path"):
            input_xls_path = arg
        elif opt in ("-s", "--stop"):
            stop_on_first_error = True

    return input_xls_path, stop_on_first_error


if __name__ == "__main__":
    try:
        src_xls_path, stop_on_first_error = get_args(sys.argv[1:])

        interior_id_dict = get_interior_id_dict("../data/InteriorIdMap.json")
        interior_floor_dict = get_interior_floor_dict("../data/InteriorFloorMap.json")

        build_map_files(src_xls_path, interior_id_dict, interior_floor_dict)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
