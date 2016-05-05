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

def import_csv(input_csv_path, destination_xls_path, worksheet_name):
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
                worksheet.write(r, c, val)

    workbook.save(destination_xls_path)


def print_usage():
    print 'Usage: '
    print 'import_csv_to_xls.py -i <input_csv_path> -d <destination_xls_path> -s <sheet_name>'
    print 'import_csv_to_xls.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_csv_path         Path to exported csv of Swallow desks table'
    print '-d --destination_xls_path   Path of xls to add / replace sheet imported from input csv'
    print '-w --worksheet_name             Name of worksheet in destination xls to create or replace'


def get_args(argv):
    input_csv_path = ''
    destination_xls_path = ''
    worksheet_name = ''
    try:
        opts, args = getopt.getopt(argv, "hi:d:w:", ["input_csv_path=", "destination_xls_path=", "worksheet_name="])
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

    return input_csv_path, destination_xls_path, worksheet_name


if __name__ == '__main__':
    try:
        input_csv_path, destination_xls_path, worksheet_name = get_args(sys.argv[1:])

        print 'input_csv_path=' + input_csv_path
        print 'destination_xls_path=' + destination_xls_path
        print 'worksheet_name=' + worksheet_name

        import_csv(input_csv_path, destination_xls_path, worksheet_name)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
