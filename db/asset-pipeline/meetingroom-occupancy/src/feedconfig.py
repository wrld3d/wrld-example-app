import os
import json
import hmactransport
import sys
import getopt

class FeedConfig:
    def __init__(self, 
                 poi_service_a_base_path="", 
                 poi_service_b_base_path="", 
                 wrld_dev_auth_token="",
                 hmac_secret="",
                 hmac_public_app_id="",
                 hmac_private_app_id="",
                 soap_service_wsdl_url="",
                 soap_regions="EMEA=GB033",
                 debug=False,
                 cdn_base_path=""
                ):
        self.__poi_service_a_base_path = poi_service_a_base_path
        self.__poi_service_b_base_path = poi_service_b_base_path
        self.__wrld_dev_auth_token = wrld_dev_auth_token
        self.__hmac_secret = hmac_secret
        self.__hmac_public_app_id = hmac_public_app_id
        self.__hmac_private_app_id = hmac_private_app_id
        self.__soap_service_wsdl_url = soap_service_wsdl_url
        self.__soap_regions = self.__parse_soap_regions(soap_regions)
        self.__debug = debug
        self.__cdn_base_path = cdn_base_path
        self.__additional_args = {}

    def __parse_soap_regions(self, soap_region):
        regions = {}
        for r in soap_region.split(":"):
            splits = r.split("=")
            region_name = splits[0].replace("-", " ")
            location_codes = splits[1].split(",")
            regions[region_name] = location_codes
        return regions

    @property
    def poi_service_a_base_path(self):
        return self.__poi_service_a_base_path

    @property
    def poi_service_b_base_path(self):
        return self.__poi_service_b_base_path  

    @property
    def wrld_dev_auth_token(self):
        return self.__wrld_dev_auth_token

    @property
    def hmac_secret(self):
        return self.__hmac_secret

    @property
    def hmac_public_app_id(self):
        return self.__hmac_public_app_id

    @property
    def hmac_private_app_id(self):
        return self.__hmac_private_app_id

    @property
    def soap_service_wsdl_url(self):
        return self.__soap_service_wsdl_url

    @property
    def debug(self):
        return self.__debug

    @property
    def soap_regions(self):
        return self.__soap_regions

    @property
    def cdn_base_path(self):
        return self.__cdn_base_path

    def has_additional_arg(self, arg_name):
        return arg_name in self.__additional_args

    def get_additional_arg(self, arg_name):
        return self.__additional_args[arg_name]

    @staticmethod
    def build(additional_args=[]):
        feed_config = FeedConfig()
        if not feed_config.from_argv(sys.argv[1:], additional_args):
            feed_config.from_configuration("../data/Config.json")
        feed_config.apply_hmac()
        return feed_config

    def from_argv(self, argv, additional_args):
        if len(argv) == 0:
            return False
        try:
            opts, args = getopt.getopt(argv, "h", ["soap_service_wsdl_url=", "poi_service_a_base_path=", "poi_service_b_base_path=", "wrld_dev_auth_token=", "hmac_secret=", "public_app_id=", "private_app_id=", "region_code=", "debug=", "cdn_base_url="]+additional_args)
        except getopt.GetoptError, e:
            raise Exception(str(e))
            FeedConfig.__print_usage()
            return False
        for opt, arg in opts:
            if opt == "-h":
                print_usage()
                sys.exit(-1)
            elif opt in ("--soap_service_wsdl_url"):
                self.__soap_service_wsdl_url = arg                
            elif opt in ("--poi_service_a_base_path"):
                self.__poi_service_a_base_path = arg
            elif opt in ("--poi_service_b_base_path"):
                self.__poi_service_b_base_path = arg                
            elif opt in ("--wrld_dev_auth_token"):
                self.__wrld_dev_auth_token = arg
            elif opt in {"--hmac_secret"}:
                self.__hmac_secret = arg
            elif opt in {"--public_app_id"}:
                self.__hmac_public_app_id = arg
            elif opt in {"--private_app_id"}:
                self.__hmac_private_app_id = arg                
            elif opt in {"--region_code"}:
                self.__soap_regions = self.__parse_soap_regions(arg)
            elif opt in {"--debug"}:
                self.__debug = arg
            elif opt in ("--cdn_base_url"):
                self.__cdn_base_path = arg
            else:
                for additional_arg in additional_args:
                    additional_arg_name = additional_arg.replace("=","")
                    if opt in "--{0}".format(additional_arg_name):
                        print "{0} => {1}".format(additional_arg_name, arg)
                        self.__additional_args[additional_arg_name] = arg
                        break
        return True

    @staticmethod
    def __print_usage():
        print "Usage: "
        print "export_to_poi_service.py -p <poi_service_a_base_path> -k <dev_auth_token> .."
        print "export_to_poi_service.py [-h | -help]"
        print
        print "Options: "
        print "--soap_service_wsdl_url   URL to web service WSDL"
        print "--poi_service_a_base_path URL to poi-service A"
        print "--poi_service_b_base_path URL to poi-service B"
        print "--wrld_dev_auth_token     WLRD Developer Auth Token"
        print "--hmac_secret             private key for HMCA"
        print "--public_app_id           public app id for HMAC"
        print "--private_app_id          private app id for HMAC"
        print "--region_code             region code for web service"
        print "--debug                   send debug data to web service and console"
        print "--cdn_base_url            base URL of CDN"
        print "-h --help                    Display this screen"                

    def from_configuration(self, filename):
        if not os.path.isfile(filename):
            raise Exception("Cannot find configuration file %s")
        with open(filename, "r") as f:
            json = json.loads(f.read())
            self.__poi_service_a_base_path = json["poi_service_a_base_path"]
            self.__poi_service_b_base_path = json["poi_service_b_base_path"]
            self.__wrld_dev_auth_token = json["wrld_dev_auth_token"]
            self.__hmac_secret = json["hmac_secret"]
            self.__hmac_public_app_id = json["hmac_public_app_id"]
            self.__hmac_private_app_id = json["hmac_private_app_id"]
            self.__soap_service_wsdl_url = json["soap_service_wsdl_url"]
            self.__soap_regions = self.__parse_soap_regions(json["soap_region"])
            self.__debug = json["debug"]
            self.__cdn_base_path = json["cdn_base_path"]

    def apply_hmac(self):
        hmactransport.PUBLIC_APP_ID = self.__hmac_public_app_id
        hmactransport.PRIVATE_APP_ID = self.__hmac_private_app_id
        hmactransport.HMAC_SECRET = self.__hmac_secret
        hmactransport.HMAC_DEBUG = self.__debug

    def __repr__(self):
        rep = ""
        for k in self.__dict__.keys():
            rep += "%s => %s\n" % (k, self.__dict__[k])
        return rep