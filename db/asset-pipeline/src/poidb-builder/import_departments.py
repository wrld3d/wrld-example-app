import getopt
import os
import csv
import random
import sys
import traceback
from math import sqrt
from itertools import groupby
import operator
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


def sqr_distance(a, b):
    v = tuple(map(operator.sub, a, b))
    v = tuple(map(operator.mul, v, v))
    dot = sum(v)
    return dot


def distance(a, b):
    sqr_dist = sqr_distance(a, b)
    dist = sqrt(sqr_dist)
    return dist


def cluster_points(points, cluster_centres):
    clusters = {}
    for point in points:
        error_for_centres = []
        for keyed_centre in enumerate(cluster_centres):
            delta = distance(point, keyed_centre[1])
            error_for_centres.append((keyed_centre[0], delta))

        best = min(error_for_centres, key=lambda _x: _x[1])
        best_cluster_key = best[0]

        if best_cluster_key in clusters:
            clusters[best_cluster_key].append(point)
        else:
            clusters[best_cluster_key] = [point]
    return clusters


def calc_mean(points):
    num_points = len(points)
    if num_points < 1:
        raise ValueError("must have at least one point")
    summed = tuple(sum(x) for x in zip(*points))
    mean = tuple((x / num_points) for x in summed)
    return mean


def calc_sum_square_deviations(points):
    mean = calc_mean(points)
    ssd = sum(sqr_distance(point, mean) for point in points)
    return ssd


def calc_population_standard_deviation(points):
    num_points = len(points)
    ssd = calc_sum_square_deviations(points)
    variance = ssd / num_points
    std_dev = sqrt(variance)
    return std_dev


def calc_cluster_centers(clusters):
    cluster_centres = []
    keys = sorted(clusters.keys())
    for key in keys:
        points = clusters[key]
        mean = calc_mean(points)
        cluster_centres.append(mean)
    return cluster_centres


def centre_sets_are_equal(a, b):
    return set([tuple(x) for x in a]) == set([tuple(x) for x in b])


def k_means_cluster(points, k):
    random.seed(1)
    cluster_centres = random.sample(points, k)
    clusters = {}
    has_converged = False

    while not has_converged:
        prev_cluster_centres = cluster_centres
        clusters = cluster_points(points, cluster_centres)
        cluster_centres = calc_cluster_centers(clusters)
        has_converged = centre_sets_are_equal(cluster_centres, prev_cluster_centres)

    sorted_clusters = sorted(clusters.items(), key=lambda x: len(x[1]), reverse=True)
    sorted_centres = list(map(lambda cluster: cluster_centres[cluster[0]], sorted_clusters))

    return sorted_centres, sorted_clusters


def pick_cluster_centre(cluster_centres, clusters, max_error):
    primary_cluster_centre = cluster_centres[0]
    primary_cluster = clusters[0]

    delta_for_points = []
    points = primary_cluster[1]
    for point in points:
        delta = distance(point, primary_cluster_centre)
        delta_for_points.append((point, delta))

    lowest_delta = min(delta_for_points, key=lambda _x: _x[1])
    if lowest_delta[1] > max_error:
        # if distance of closest desk to centre is greater than max_error, just use closest desk position
        primary_cluster_centre = lowest_delta[0]

    lat = primary_cluster_centre[0]
    lng = primary_cluster_centre[1]
    return lat, lng


class DepartmentRowAggregator:
    def __init__(self):
        self.__known_departments = {}

    def add(self, department, desk):
        if department not in self.__known_departments:
            self.__known_departments[department] = []
        self.__known_departments[department].append(desk)

    def resolve(self, desks):
        for department in self.__known_departments:
            desks_in_department = self.__known_departments[department]

            if len(desks_in_department) < 1:
                raise ValueError('No desks in department')

            grouped_by_floor = desk_ids_grouped_by_floor(desks_in_department)

            ordered_by_desk_count_ascending = sorted(grouped_by_floor, key=lambda x: len(x[1]), reverse=True)

            primary_floor_and_desk_ids = ordered_by_desk_count_ascending[0]

            interior_id, interior_floor = FLOOR_IDS_TO_EEGEO_IDS[primary_floor_and_desk_ids[0]]

            latitude_degrees, longitude_degrees = desks.position_from_desk_set(primary_floor_and_desk_ids[1])

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

def desk_ids_grouped_by_floor(desk_ids):
    desks_with_floor_id = list(map(lambda x: (x, floor_id_from_desk_id(x)), desk_ids))
    ordered_by_floor_id = sorted(desks_with_floor_id, key=operator.itemgetter(1))
    grouped_by_floor_id = groupby(ordered_by_floor_id, key=operator.itemgetter(1))

    grouped_desks = []
    for key, group in grouped_by_floor_id:
        desks_for_group = list(map(operator.itemgetter(0), group))
        grouped_desks.append((key, desks_for_group))

    return grouped_desks


class DeskPositions:
    def __init__(self):
        self.__known_desks = {}

    def add(self, desk, latitude_degrees, longitude_degrees):
        if not desk in self.__known_desks:
            self.__known_desks[desk] = (latitude_degrees, longitude_degrees)

    def __build_desk_points(self, desks):
        desk_points = []
        for d in desks:
            if d not in self.__known_desks:
                raise ValueError('Unknown desk: ' + d)
            known_desk_latitude, known_desk_longitude = self.__known_desks[d]
            desk_centre = (known_desk_latitude, known_desk_longitude)
            desk_points.append(desk_centre)
        return desk_points

    def position_from_desk_set(self, desks):
        if len(desks) < 1:
            raise ValueError('desk set is empty')

        desk_points = self.__build_desk_points(desks)

        std_dev = calc_population_standard_deviation(desk_points)
        cluster_scale = 1e-5
        cluster_k = int(sqrt(std_dev/cluster_scale))
        cluster_k = min(max(1, cluster_k), len(desk_points))
        cluster_centres, clusters = k_means_cluster(desk_points, cluster_k)

        max_error = 1e-4
        lat, lng = pick_cluster_centre(cluster_centres, clusters, max_error)
        return lat, lng


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
