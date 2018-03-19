import csv
import json
import getopt
import os
import sys
import shutil
import subprocess

class Config:
    def __init__(self, production_config_path="", 
                       locations_csv_path="",
                       config_password="",
                       output_folder=""):
        self.__production_config_path = production_config_path
        self.__locations_csv_path = locations_csv_path
        self.__config_password = config_password
        self.__output_folder = output_folder

    @property
    def production_config_path(self):
        return self.__production_config_path

    @property
    def config_password(self):
        return self.__config_password

    @property
    def locations_csv_path(self):
        return self.__locations_csv_path

    @property
    def output_folder(self):
        return self.__output_folder

    def from_argv(self):
        if len(sys.argv[1:]) == 0:
            Config.__print_usage()
            sys.exit(-1)            
            return False
        try:
            opts, args = getopt.getopt(sys.argv[1:], "h", ["production_config_path=", "locations_csv_path=", "config_password=", "output_folder="])
        except getopt.GetoptError, e:
            print e
            Config.__print_usage()
            sys.exit(-1)            
            return False
        for opt, arg in opts:
            if opt == "-h":
                Config.__print_usage()
                sys.exit(-1)
            elif opt in ("--production_config_path"):
                self.__production_config_path = arg
            elif opt in ("--locations_csv_path"):
                self.__locations_csv_path = arg
            elif opt in ("--config_password"):
                self.__config_password = arg                
            elif opt in ("--output_folder"):
                self.__output_folder = arg
        return True

    @staticmethod
    def __print_usage():
        print "Generate desktop configuration files for various Swallow sites."
        print "Input is locations.csv in format: "
        print ""
        print "Usage: location,lat,lon,heading"
        print ""
        print "poke-desktop.py -p <poi_service_a_base_path> -k <dev_auth_token> .."
        print "poke-desktop.py [-h | -help]"
        print
        print "Options: "
        print "--production_config_path         Path to Windows Desktop production configuration"
        print "--locations_csv_path             Path to locations.csv defining site locations"
        print "--config_password                Password for config encryption"
        print "--output_folder                  Folder to output conventionally named configs"
        print "-h --help"

if __name__ == "__main__":
    config = Config()
    config.from_argv()

    if not os.path.exists(config.locations_csv_path):
        print "Cannot find kiosk csv at {0}".format(config.locations_csv_path)
        sys.exit(-1)

    if not os.path.exists(config.production_config_path):
        print "Cannot find windows configuration at csv at {0}".format(config.production_config_path)
        sys.exit(-1)        

    if os.path.exists(config.output_folder):
        shutil.rmtree(config.output_folder)

    os.makedirs(config.output_folder)
    backup_prod_config = os.path.join(config.output_folder, "project_swallow_production_config.json")
    shutil.copyfile(config.production_config_path, backup_prod_config)

    with open(config.production_config_path, 'rb') as production_config:
        configuration = json.loads(production_config.read())

    with open(config.locations_csv_path, 'rb') as csvfile:
        reader = csv.DictReader(csvfile, delimiter=',', quotechar='"')
        secret_key=subprocess.check_output(["python", "./build-scripts/generate_key.py", config.config_password])

        for row in reader:
            encrypted_file_path = os.path.join(config.output_folder, "{0}.encrypted_config.json".format(row["location"]))

            configuration["start_location_latitude"] = float(row["lat"])
            configuration["start_location_longitude"] = float(row["lon"])
            configuration["start_location_orientation_degrees"] = float(row["heading"])
            with open(config.production_config_path, 'w') as production_config:
                production_config.write(json.dumps(configuration, indent=4))

            shutil.copyfile(config.production_config_path, os.path.join(config.output_folder, "{0}.json".format(row["location"])))
            subprocess.call(["python", "build-scripts/encrypt_config.py", "-i", config.production_config_path, "-o", encrypted_file_path, "-s", secret_key])