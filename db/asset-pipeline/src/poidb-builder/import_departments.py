import getopt
import os
import csv
import sys
import traceback
import xlrd

EXPECTED_INPUT_FIELDS = {
    'IO #': 0,
    'Building': 1,
    'Desk Number': 2,
    'Floor': 3,
    'Space Class': 4,
    'Occupant UUID': 5,
    'Occupant First Name': 6,
    'Occupant Second Name': 7,
    'Occupant Organization': 8
}

VALID_BUILDING_IDS = ['GB006', 'GB012', 'GB025', 'GB032']

IGNORED_FLOOR_IDS = ['CG06']

FLOOR_IDS_TO_EEGEO_IDS = {
             '38FS-G':('swallow_lon_38finsbury',1),
             '38FS01':('swallow_lon_38finsbury',2),
             '38FS02':('swallow_lon_38finsbury',3),
             '38FS03':('swallow_lon_38finsbury',4),
             '38FS04':('swallow_lon_38finsbury',5),
             '38FS05':('swallow_lon_38finsbury',6),
             '38FS06':('swallow_lon_38finsbury',7),
             'FS01':('swallow_lon_50finsbury',1),
             'FS02':('swallow_lon_50finsbury',2),
             'FS03':('swallow_lon_50finsbury',3),
             'FS04':('swallow_lon_50finsbury',4),
             'FS05':('swallow_lon_50finsbury',5),
             'FS06':('swallow_lon_50finsbury',6),
             'FS07':('swallow_lon_50finsbury',7),
             'CG0G':('swallow_lon_citygatehouse',1),
             'CG0G-R01':('swallow_lon_citygatehouse',1),
             'CG01':('swallow_lon_citygatehouse',2),
             'CG02':('swallow_lon_citygatehouse',3),
             'CG03':('swallow_lon_citygatehouse',4),
             'PKH-3':('swallow_lon_parkhouse',0),
             'PKH04':('swallow_lon_parkhouse',1),
             'PKH05':('swallow_lon_parkhouse',2)
    }

class DepartmentRowAggregator:
    def __init__(self):
        self.__known_departments = {}

    def add(self, department, desk):
        if not department in self.__known_departments:
            self.__known_departments[department] = []
        self.__known_departments[department].append(desk)

    def resolve(self, desks):
        for department in self.__known_departments:
            desks_in_department = self.__known_departments[department]
            latitude_degrees, longitude_degrees = desks.position_from_desk_set(desks_in_department)
            interior_id, interior_floor = desks.primary_building_and_floor_from_desk_set(desks_in_department)

            dest_row = {'name': department,
                    'image_filename': "icon_person.png",
                    'description': department,
                    'interior_id': interior_id,
                    'interior_floor': interior_floor,
                    'latitude_degrees': latitude_degrees,
                    'longitude_degrees': longitude_degrees,
                    'available_in_app': 'Yes'}

            yield dest_row

def floor_id_from_desk_id(desk_id):
    split = desk_id.split("-")
    return '-'.join(split[0:-1])

class DeskPositions:
    def __init__(self):
        self.__known_desks = {}

    def add(self, desk, latitude_degrees, longitude_degrees):
        if not desk in self.__known_desks:
            self.__known_desks[desk] = (latitude_degrees, longitude_degrees)

    def position_from_desk_set(self, desks):
        if len(desks) < 1:
            raise ValueError('No desks in deparmtment')
        count = 0
        latitude_degrees = 0.0
        longitude_degrees = 0.0
        for d in desks:
            if not d in self.__known_desks:
                raise ValueError('Unknown desk: ' + d)
            known_desk_latitude, known_desk_longitude = self.__known_desks[d]
            latitude_degrees += known_desk_latitude
            longitude_degrees += known_desk_longitude
            count += 1
        return (latitude_degrees / float(count), longitude_degrees / float(count))

    def primary_building_and_floor_from_desk_set(self, desks):
        if len(desks) < 1:
            raise ValueError('No desks in deparmtment')
        counts = {}
        for d in desks:
            floor_id = floor_id_from_desk_id(d)
            if not floor_id in counts:
                counts[floor_id] = 0
            counts[floor_id] += 1

        max_value = -1
        max_floor = ''
        for floor_id in counts:
            if counts[floor_id] > max_value:
                max_value = counts[floor_id]
                max_floor = floor_id

        return FLOOR_IDS_TO_EEGEO_IDS[floor_id]

def collate_departments(reader):
    for src_row in reader:
        if len(src_row) != len(EXPECTED_INPUT_FIELDS):
            raise ValueError('unexpected input fields for: ' + src_row)

        building_id = src_row[EXPECTED_INPUT_FIELDS['IO #']]
        if building_id not in VALID_BUILDING_IDS:
            continue

        department = src_row[EXPECTED_INPUT_FIELDS['Occupant Organization']]
        desk_id = src_row[EXPECTED_INPUT_FIELDS['Desk Number']]
        floor_id = floor_id_from_desk_id(desk_id)

        if floor_id in IGNORED_FLOOR_IDS:
            continue

        if not department or not desk_id:
            continue

        yield department, desk_id

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

def collate_desks(swallow_xls_db):
    all_desk_positions = DeskPositions()
    xls_book =  xlrd.open_workbook(swallow_xls_db)

    column_name_row = 0
    first_data_row_number = 1
    sheet_index = 7

    desks = {}
    xls_sheet = xls_book.sheet_by_index(sheet_index)

    poi_columns = ['desk', 'latitude_degrees', 'longitude_degrees', 'interior_id', 'interior_floor']
    control_columns = ['available_in_app']
    expected_columns = poi_columns + control_columns
    available_in_app_col_index = len(poi_columns)

    column_names = ['id'] + poi_columns
    for v in gather_table(column_names, xls_sheet, first_data_row_number, available_in_app_col_index):
        desk = {
            "desk":v[column_names.index('desk')],
            "lat":float(v[column_names.index('latitude_degrees')]),
            "lon":float(v[column_names.index('longitude_degrees')]),
            "indoor_id":v[column_names.index('interior_id')],
            "floor_id":int(v[column_names.index('interior_floor')]),
           }
        all_desk_positions.add(desk['desk'], desk['lat'], desk['lon'])

    return all_desk_positions

def import_departments(input_desks_csv_path, output_csv_path, swallow_xls_db):
    if input_desks_csv_path == '':
        print '\nError: input_desks_csv_path not defined.\n'
        print_usage()
        sys.exit(1)

    if output_csv_path == '':
        print '\nError: output_csv_path not defined.\n'
        print_usage()
        sys.exit(1)

    if swallow_xls_db == '':
        print '\nError: swallow_xls_db not defined.\n'
        print_usage()
        sys.exit(1)

    if not os.path.exists(input_desks_csv_path):
        raise ValueError('path not found: ' + input_desks_csv_path)

    if not os.path.exists(swallow_xls_db):
        raise ValueError('path not found: ' + swallow_xls_db)

    if os.path.exists(output_csv_path):
        raise ValueError('output already exists: ' + output_csv_path)

    departments = DepartmentRowAggregator()
    desks = collate_desks(swallow_xls_db)

    with open(output_csv_path, 'wb') as output_csv_file:
        dest_columns = ['name','image_filename','description','interior_id','interior_floor','latitude_degrees','longitude_degrees','available_in_app']
        writer = csv.DictWriter(output_csv_file, fieldnames=dest_columns)

        with open(input_desks_csv_path, 'rb') as input_csv_file:
            reader = csv.reader(input_csv_file, delimiter='|')

            header = dict(zip(dest_columns, dest_columns))
            writer.writerow(header)
            for department, desk in collate_departments(reader):
                departments.add(department, desk)
    
        for row in departments.resolve(desks):
            writer.writerow(row)

    print "Done. Wrote {0}".format(output_csv_path)


def print_usage():
    print 'Usage: '
    print 'collate_departments.py -i <input_desks_csv_path> -o <output_csv_path> -d <swallow_xls_db>'
    print 'collate_departments.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_desks_csv_path         Path to exported csv of Swallow desks table'
    print '-o --output_csv_path              Output DepartmentsPois csv path'
    print '-d --swallow_xls_db              Path to swallow swallow xls poi db'

def get_args(argv):
    input_desks_csv_path = ''
    output_csv_path = ''
    swallow_xls_db = ''
    try:
        opts, args = getopt.getopt(argv, "hi:o:d:", ["input_desks_csv_path=", "output_csv_path=", "swallow_xls_db="])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print_usage()
            sys.exit()
        elif opt in ("-i", "--input_desks_csv_path"):
            input_desks_csv_path = arg
        elif opt in ("-o", "--output_csv_path"):
            output_csv_path = arg
        elif opt in ("-d", "--swallow_xls_db"):
            swallow_xls_db = arg

    return input_desks_csv_path, output_csv_path, swallow_xls_db

if __name__ == '__main__':
    try:
        input_desks_csv_path, output_csv_path, swallow_xls_db = get_args(sys.argv[1:])

        print 'input_desks_csv_path=' + input_desks_csv_path
        print 'output_csv_path=' + output_csv_path
        print 'swallow_xls_db=' + swallow_xls_db

        import_departments(input_desks_csv_path, output_csv_path, swallow_xls_db)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
