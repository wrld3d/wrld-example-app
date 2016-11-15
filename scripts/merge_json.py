import getopt
import os
import sys
import traceback
import json


def merge_json(input_json_path, output_json_path, merge_json_path):
    if not input_json_path:
        print '\nError: input_json_path not defined.\n'
        print_usage()
        sys.exit(1)

    if not output_json_path:
        print '\nError: output_json_path not defined.\n'
        print_usage()
        sys.exit(1)

    if not merge_json_path:
        print '\nError: merge_json_path not defined.\n'
        print_usage()
        sys.exit(1)

    if not os.path.exists(input_json_path):
        raise ValueError('input path not found: ' + input_json_path)

    if not os.path.exists(merge_json_path):
        raise ValueError('to merge path not found: ' + merge_json_path)

    if os.path.exists(output_json_path):
        raise ValueError('output already exists: ' + output_json_path)

    with open(output_json_path, 'w') as output_file:
        with open(input_json_path, 'r') as input_file:
            with open(merge_json_path, 'r') as merge_file:

                try:
                    input = json.load(input_file)
                except Exception as e:
                    print 'unable to parse json from input_json_path'
                    raise e

                try:
                    merge = json.load(merge_file)
                except Exception as e:
                    print 'unable to parse json from input_json_path'
                    raise e

                result = input.copy()
                result.update(merge)

                json.dump(result, output_file, indent=4)

    return


def print_usage():
    print 'Usage: '
    print 'merge_json.py -i <input_json_path> -o <output_json_path> -j <merge_json_path>'
    print 'merge_json.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_json_path       Path to input json file'
    print '-o --output_json_path      Path to output json file'
    print '-j --merge_json_path       Path to json file to merge / append'


def get_args(argv):
    input_json_path = ''
    output_json_path = ''
    merge_json_path = ''
    try:
        opts, args = getopt.getopt(argv, "hi:o:j:", ["input_json_path=", "output_json_path=", "merge_json_path="])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print_usage()
            sys.exit()
        elif opt in ("-i", "--input_json_path"):
            input_json_path = arg
        elif opt in ("-o", "--output_json_path"):
            output_json_path = arg
        elif opt in ("-j", "--merge_json_path"):
            merge_json_path = arg

    return input_json_path, output_json_path, merge_json_path


if __name__ == '__main__':
    try:
        input_json_path_param, output_json_path_param, merge_json_path_param = get_args(sys.argv[1:])

        print 'input_json_path: ' + input_json_path_param
        print 'output_json_path: ' + output_json_path_param
        print 'merge_json_path: ' + merge_json_path_param

        merge_json(input_json_path_param, output_json_path_param, merge_json_path_param)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
