import getopt
import csv
import sys
import traceback
import xlrd
from xlutils.copy import copy as xls_copy


def clear_worksheet(worksheet):
    for row_index in worksheet.rows:
        row = worksheet.rows[row_index]
        max_col = row.get_max_col()
        row.write_blanks(0, max_col)

def get_value(column_idx, value, column_types):
    if column_types is None:
        return value

    if column_idx >= len(column_types):
        raise ValueError("invalid number of column types, expected at least {0}".format(column_idx))

    column_type = column_types[column_idx]
    if column_type.lower() == "str":
        return value
    elif column_type.lower() == "int":
        try:
            return int(value)
        except:
            raise ValueError("could not coerce {0} to int".format(value))
    elif column_type.lower() == "float":
        try:
            return float(value)
        except:
            raise ValueError("could not coerce {0} to float".format(value))
    else:
        raise ValueError("unknown column type: {0}".format(column_type))

def import_csv(input_csv_path, destination_xls_path, worksheet_name, column_types):
    readonly_workbook = xlrd.open_workbook(destination_xls_path, formatting_info=True)
    workbook = xls_copy(readonly_workbook)

    # xlwt doesn't have sheet_names()
    sheet_names = readonly_workbook.sheet_names()
    if worksheet_name in sheet_names:
        worksheet = workbook.get_sheet(sheet_names.index(worksheet_name))
    else:
        worksheet = workbook.add_sheet(worksheet_name)

    clear_worksheet(worksheet)

    with open(input_csv_path, 'rb') as input_csv_file:
        reader = csv.reader(input_csv_file)
        for r, row in enumerate(reader):
            for c, val in enumerate(row):
                worksheet.write(r, c, get_value(c, val, column_types) if r > 0 else val)

    workbook.save(destination_xls_path)


def print_usage():
    print 'Usage: '
    print 'import_csv_to_xls.py -i <input_csv_path> -d <destination_xls_path> -s <sheet_name> -t <column_types>'
    print 'import_csv_to_xls.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_csv_path         Path to exported csv of Swallow desks table'
    print '-d --destination_xls_path   Path of xls to add / replace sheet imported from input csv'
    print '-w --worksheet_name         Name of worksheet in destination xls to create or replace'
    print '-t --column_types           comma separated set of column types, supported types: <str, int, float>'


def get_args(argv):
    input_csv_path = ''
    destination_xls_path = ''
    worksheet_name = ''
    column_types = None
    try:
        opts, args = getopt.getopt(argv, "hi:d:w:t:", ["input_csv_path=", "destination_xls_path=", "worksheet_name=", "column_types="])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print_usage()
            sys.exit()
        elif opt in ("-i", "--input_csv_path"):
            input_csv_path = arg
        elif opt in ("-d", "--destination_xls_path"):
            destination_xls_path = arg
        elif opt in ("-w", "--worksheet_name"):
            worksheet_name = arg
        elif opt in ("-t", "--column_types"):
            column_types = arg

    return input_csv_path, destination_xls_path, worksheet_name, column_types

if __name__ == '__main__':
    try:
        input_csv_path, destination_xls_path, worksheet_name, column_types = get_args(sys.argv[1:])

        print 'input_csv_path=' + input_csv_path
        print 'destination_xls_path=' + destination_xls_path
        print 'worksheet_name=' + worksheet_name
        if column_types is not None:
            print 'column_types=' + column_types

        if column_types is not None:
            column_types = column_types.split(',')

        import_csv(input_csv_path, destination_xls_path, worksheet_name, column_types)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
