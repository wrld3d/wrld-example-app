import getopt
import os
import shutil
import sys
import json
import traceback
import fnmatch

swallow_50fs = 'swallow_lon_50finsbury'
swallow_ph = 'swallow_lon_parkhouse'
swallow_cgh = 'swallow_lon_citygatehouse'
swallow_38fs = 'swallow_lon_38finsbury'
interior_definitions = {
             '38FS-G':(swallow_38fs,1),
             '38FS01':(swallow_38fs,2),
             '38FS02':(swallow_38fs,3),
             '38FS03':(swallow_38fs,4),
             '38FS04':(swallow_38fs,5),
             '38FS05':(swallow_38fs,6),
             '38FS06':(swallow_38fs,7),
             'FS01':(swallow_50fs,1),
             'FS02':(swallow_50fs,2),
             'FS03':(swallow_50fs,3),
             'FS04':(swallow_50fs,4),
             'FS05':(swallow_50fs,5),
             'FS06':(swallow_50fs,6),
             'FS07':(swallow_50fs,7),
             'CG0G':(swallow_cgh,1),
             'CG0G-R01':(swallow_cgh,1),
             'CG01':(swallow_cgh,2),
             'CG02':(swallow_cgh,3),
             'CG03':(swallow_cgh,4),
             'PKH-3':(swallow_ph,0),
             'PKH04':(swallow_ph,1),
             'PKH05':(swallow_ph,2)
    }

def interior_from_desk_id(desk_id):
    split = desk_id.split("-")
    identifier = '-'.join(split[0:-1])
    return interior_definitions[identifier]

def collate(json_file):
    with open(json_file, "r") as f:
        structure = json.loads(f.read())
        for feature in structure:
            yield feature

def collate_desks(input_desk_entity_path):
    jsons = []
    for root, dirnames, filenames in os.walk(input_desk_entity_path):
        for filename in fnmatch.filter(filenames, '*.json'):
            jsons.append(os.path.join(root, filename))

    for j in jsons:
        for desk in collate(j):
            lon_lat = desk['geometry']['coordinates']
            desk_id = desk['properties']['name']
            interior_id, floor_id = interior_from_desk_id(desk_id)
            yield desk_id, lon_lat[1], lon_lat[0], interior_id, floor_id

def import_desks(input_desk_entity_path, output_csv_path):
    if input_desk_entity_path == '':
        print '\nError: input_desk_entity_path not defined.\n'
        print_usage()
        sys.exit(1)

    if output_csv_path == '':
        print '\nError: output_csv_path not defined.\n'
        print_usage()
        sys.exit(1)

    if not os.path.exists(input_desk_entity_path):
        raise ValueError('path not found: ' + input_desk_entity_path)

    if os.path.exists(output_csv_path):
        raise ValueError('output already exists: ' + output_csv_path)

    with open(output_csv_path,"w") as f:
        f.write("desk,latitude_degrees,longitude_degrees,interior_id,interior_floor\n")
        for desk_id, lat, lon, interior_id, floor_id in collate_desks(input_desk_entity_path):
            f.write("{0},{1},{2},{3},{4}\n".format(desk_id, lat, lon, interior_id, floor_id))

    print "Done. Wrote {0}".format(output_csv_path)

def print_usage():
    print 'Usage: '
    print 'import_desk_positions.py -i <input_desk_entity_path> -o <output_csv_path>'
    print 'import_desk_positions.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_desk_entity_path           Path to entity data within interiors-gis repo'
    print '-o --output_csv_path                  Output csv path'

def get_args(argv):
    input_desk_entity_path = ''
    output_csv_path = ''
    try:
        opts, args = getopt.getopt(argv,"hi:o:",["input_desk_entity_path=","output_csv_path="])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print_usage()
            sys.exit()
        elif opt in ("-i", "--input_desk_entity_path"):
            input_desk_entity_path = arg
        elif opt in ("-o", "--output_csv_path"):
            output_csv_path = arg

    return input_desk_entity_path, output_csv_path

if __name__ == '__main__':
    try:
        input_desk_entity_path, output_csv_path = get_args(sys.argv[1:])

        print 'input_desk_entity_path=' + input_desk_entity_path
        print 'output_csv_path=' + output_csv_path

        import_desks(input_desk_entity_path, output_csv_path)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)