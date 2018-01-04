import csv
import json
import getopt
import os
import sys
import shutil

class Config:
    def __init__(self, production_kiosk_config_path="", 
                       kiosks_csv_path="",
                       output_folder=""):
        self.__production_kiosk_config_path = production_kiosk_config_path
        self.__kiosks_csv_path = kiosks_csv_path
        self.__output_folder = output_folder

    @property
    def production_kiosk_config_path(self):
        return self.__production_kiosk_config_path

    @property
    def kiosks_csv_path(self):
        return self.__kiosks_csv_path

    @property
    def output_folder(self):
        return self.__output_folder

    def from_argv(self):
        if len(sys.argv[1:]) == 0:
            Config.__print_usage()
            sys.exit(-1)            
            return False
        try:
            opts, args = getopt.getopt(sys.argv[1:], "h", ["production_kiosk_config_path=", "kiosks_csv_path=", "output_folder="])
        except getopt.GetoptError, e:
            print e
            Config.__print_usage()
            sys.exit(-1)            
            return False
        for opt, arg in opts:
            if opt == "-h":
                Config.__print_usage()
                sys.exit(-1)
            elif opt in ("--production_kiosk_config_path"):
                self.__production_kiosk_config_path = arg
            elif opt in ("--kiosks_csv_path"):
                self.__kiosks_csv_path = arg
            elif opt in ("--output_folder"):
                self.__output_folder = arg
        return True

    @staticmethod
    def __print_usage():
        print "Generate kiosk configuration files conventionally named after their hostname."
        print "Input is kiosks.csv in format: "
        print ""
        print "Usage: machine,lat,lon,indoor,floor,heading"
        print ""
        print "poke-kiosk.py -p <poi_service_a_base_path> -k <dev_auth_token> .."
        print "poke-kiosk.py [-h | -help]"
        print
        print "Options: "
        print "--production_kiosk_config_path   Path to Windows Kiosk production configuration"
        print "--kiosks_csv_path                Path to kiosks.csv defining kiosk locations"
        print "--output_folder                  Folder to output conventionally named configs"
        print "-h --help"

if __name__ == "__main__":
    config = Config()
    config.from_argv()

    if not os.path.exists(config.kiosks_csv_path):
        print "Cannot find kiosk csv at {0}".format(config.kiosks_csv_path)
        sys.exit(-1)

    if not os.path.exists(config.production_kiosk_config_path):
        print "Cannot find windows configuration at csv at {0}".format(config.production_kiosk_config_path)
        sys.exit(-1)        

    if os.path.exists(config.output_folder):
        shutil.rmtree(config.output_folder)

    os.makedirs(config.output_folder)

    with open(config.production_kiosk_config_path, 'rb') as production_config:
        configuration = json.loads(production_config.read())

    with open(config.kiosks_csv_path, 'rb') as csvfile:
        reader = csv.DictReader(csvfile, delimiter=',', quotechar='"')
        for row in reader:
            configuration["fixed_indoor_location"]["latitude"] = float(row["lat"])
            configuration["fixed_indoor_location"]["longitude"] = float(row["lon"])
            configuration["fixed_indoor_location"]["interior_id"] = row["indoor"]
            configuration["fixed_indoor_location"]["floor_index"] = int(row["floor"])
            configuration["fixed_indoor_location"]["orientation_degrees"] = float(row["heading"])
            with open(os.path.join(config.output_folder, "{0}.config".format(row["machine"])), "w") as f:
                f.write(json.dumps(configuration, indent=4))