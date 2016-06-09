import getopt
import os
import sys
import traceback
import json

def merge_json(input_json_path, output_json_path, json_to_merge):
    
    if not input_json_path:
        print '\nError: input_json_path not defined.\n'
        print_usage()
        sys.exit(1)

    if not output_json_path:
        print '\nError: output_json_path not defined.\n'
        print_usage()
        sys.exit(1)

    if not json_to_merge:
        print '\nError: json_to_merge not defined.\n'
        print_usage()
        sys.exit(1)

    if not os.path.exists(input_json_path):
        raise ValueError('path not found: ' + input_json_path)

    if os.path.exists(output_json_path):
        raise ValueError('output already exists: ' + output_json_path)

    try:
        to_merge = json.loads(json_to_merge)
    except Exception as e:
        print 'unable to parse merge_json'
        raise e

    with open(output_json_path, 'w') as output_file:
        with open(input_json_path, 'r') as input_file:

            try:
                input = json.load(input_file)
            except Exception as e:
                print 'unable to parse json from input_json_path'
                raise e

            result = input.copy()
            result.update(to_merge)

            json.dump(result, output_file, indent=4)

    return


def print_usage():
    print 'Usage: '
    print 'merge_json.py -i <input_json_path> -o <output_json_path> -j <json_to_merge>'
    print 'merge_json.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_json_path       Path to input json file'
    print '-o --output_json_path      Path to output json file'
    print '-j --json_to_merge         json to merge / append'


def get_args(argv):
    input_json_path = ''
    output_json_path = ''
    json_to_merge = ''
    try:
        opts, args = getopt.getopt(argv, "hi:o:j:", ["input_json_path=", "output_json_path=", "json_to_merge="])
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
        elif opt in ("-j", "--json_to_merge"):
            json_to_merge = arg

    return input_json_path, output_json_path, json_to_merge

if __name__ == '__main__':
    try:
        input_json_path_param, output_json_path_param, json_to_merge_param = get_args(sys.argv[1:])

        print 'input_json_path: ' + input_json_path_param
        print 'output_json_path: ' + output_json_path_param
        print 'json_to_merge: ' + json_to_merge_param


        merge_json(input_json_path_param, output_json_path_param, json_to_merge_param)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
