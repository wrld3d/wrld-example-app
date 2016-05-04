import getopt
import os
import csv
import sys
import traceback

BUILDING_IDS_TO_NAMES = {
    'GB006': 'City Gate House',
    'GB012': '50 Finsbury Square',
    'GB025': '38 Finsbury Square',
    'GB032': 'Park House'
}

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

IGNORED_FLOOR_IDS = ['CG06']

FLOOR_IDS_TO_DESCRIPTIONS = {
    '38FS-G': "Ground Floor",
    '38FS01': "1st Floor",
    '38FS02': "2nd Floor",
    '38FS03': "3rd Floor",
    '38FS04': "4th Floor",
    '38FS05': "5th Floor",
    '38FS06': "6th Floor",
    'FS01': "1st Floor",
    'FS02': "2nd Floor",
    'FS03': "3rd Floor",
    'FS04': "4th Floor",
    'FS05': "5th Floor",
    'FS06': "6th Floor",
    'FS07': "7th Floor",
    'CG0G': "Ground Floor",
    'CG0G-R01': "Lower Ground Floor",
    'CG01': "1st Floor",
    'CG02': "2nd Floor",
    'CG03': "3rd Floor",
    'PKH-3': "3rd Floor",
    'PKH04': "4th Floor",
    'PKH05': "5th Floor"
}


def floor_id_from_desk_id(desk_id):
    split = desk_id.split("-")
    return '-'.join(split[0:-1])


def collate_desks(reader):
    for src_row in reader:
        if len(src_row) != len(EXPECTED_INPUT_FIELDS):
            raise ValueError('unexpected input fields for: ' + src_row)

        building_id = src_row[EXPECTED_INPUT_FIELDS['IO #']]
        if building_id not in BUILDING_IDS_TO_NAMES:
            continue

        first_name = src_row[EXPECTED_INPUT_FIELDS['Occupant First Name']]
        second_name = src_row[EXPECTED_INPUT_FIELDS['Occupant Second Name']]

        if not first_name and not second_name:
            continue

        name = " ".join([first_name, second_name])

        desk_id = src_row[EXPECTED_INPUT_FIELDS['Desk Number']]

        floor_id = floor_id_from_desk_id(desk_id)
        if floor_id in IGNORED_FLOOR_IDS:
            continue

        if floor_id not in FLOOR_IDS_TO_DESCRIPTIONS:
            raise ValueError('unknown floor for desk id: ' + desk_id)

        location_description = ", ".join([FLOOR_IDS_TO_DESCRIPTIONS[floor_id], BUILDING_IDS_TO_NAMES[building_id]])

        dest_row = {'name': name,
                    'job_title': src_row[EXPECTED_INPUT_FIELDS['Occupant Organization']],
                    'image_filename': "icon_person.png",
                    'working_group': src_row[EXPECTED_INPUT_FIELDS['Occupant Organization']],
                    'office_location': location_description,
                    'desk_code': desk_id}

        yield dest_row


def import_employees(input_desks_csv_path, output_csv_path):
    if input_desks_csv_path == '':
        print '\nError: input_desks_csv_path not defined.\n'
        print_usage()
        sys.exit(1)

    if output_csv_path == '':
        print '\nError: output_csv_path not defined.\n'
        print_usage()
        sys.exit(1)

    if not os.path.exists(input_desks_csv_path):
        raise ValueError('path not found: ' + input_desks_csv_path)

    if os.path.exists(output_csv_path):
        raise ValueError('output already exists: ' + output_csv_path)

    with open(output_csv_path, 'wb') as output_csv_file:
        dest_columns = ['name', 'job_title', 'image_filename', 'working_group', 'office_location', 'desk_code']
        writer = csv.DictWriter(output_csv_file, fieldnames=dest_columns)

        with open(input_desks_csv_path, 'rb') as input_csv_file:
            reader = csv.reader(input_csv_file, delimiter='|')

            header = dict(zip(dest_columns, dest_columns))
            writer.writerow(header)
            for row in collate_desks(reader):
                writer.writerow(row)

    print "Done. Wrote {0}".format(output_csv_path)


def print_usage():
    print 'Usage: '
    print 'import_employees.py -i <input_desks_csv_path> -o <output_csv_path>'
    print 'import_employees.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_desks_csv_path         Path to exported csv of Swallow desks table'
    print '-o --output_csv_path                  Output EmployeePois csv path'


def get_args(argv):
    input_desks_csv_path = ''
    output_csv_path = ''
    try:
        opts, args = getopt.getopt(argv, "hi:o:", ["input_desks_csv_path=", "output_csv_path="])
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

    return input_desks_csv_path, output_csv_path


if __name__ == '__main__':
    try:
        input_desks_csv_path, output_csv_path = get_args(sys.argv[1:])

        print 'input_desks_csv_path=' + input_desks_csv_path
        print 'output_csv_path=' + output_csv_path

        import_employees(input_desks_csv_path, output_csv_path)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
