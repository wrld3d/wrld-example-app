import base64
import json
import getopt
import hmac
import requests
import sys

import zeep
from zeep import Client

from datetime import datetime

import logging.config


REQUEST_TIME_UTC = "requestTimeUtc"
APP_ID = "appId"
DEBUG_DATA = "debug_Data"
REQUEST_KEY = "requestKey"

MEETING_ROOM_TAG = "meeting_room"


class CustomTransport(zeep.Transport):
    def post(self, address, message, headers):
        headers[REQUEST_TIME_UTC] = unicode(datetime.utcnow())
        headers[APP_ID] = app_id

        key_input = message + "," + headers[REQUEST_TIME_UTC] + "," + headers[APP_ID]

        if debug_data:
            headers[DEBUG_DATA] = base64.b64encode(key_input)

        hmac_generator = hmac.new(app_secret)
        hmac_generator.update(key_input)
        headers[REQUEST_KEY] = base64.b64encode(hmac_generator.digest())

        # print "\n-----------"
        # print address
        # print "-----------"
        # print message
        # print "-----------"
        # print headers
        # print "-----------\n"
        return super(CustomTransport, self).post(address, message, headers)


def get_meeting_room_poi_dict(filename):
    meeting_room_poi_dict = {}

    with open(filename) as meeting_room_json_file:
        meeting_room_list_json = json.load(meeting_room_json_file)
        for meeting_room_json in meeting_room_list_json:
            meeting_room_poi_dict[meeting_room_json["user_data"]["space_id"]] = {"id": meeting_room_json["id"], "user_data": meeting_room_json["user_data"]}

    return meeting_room_poi_dict


def get_updated_meeting_room_poi_json(web_service_url, region_code, meeting_room_poi_dict):
    availability_states = ["available", "occupied", "available_soon"]

    transport = CustomTransport()
    client = Client(web_service_url, transport=transport)
    response = client.service.GetMeetingSpaceOccupancyDetails(region_code)

    if response is not None and response != "":
        meeting_room_list_json = json.loads(response)
        if "meetingSpaceOccupancyDetails" in meeting_room_list_json:
            for meeting_room_json in meeting_room_list_json["meetingSpaceOccupancyDetails"]:
                space_id = meeting_room_json["spaceId"]
                if meeting_room_poi_dict[space_id]:
                    user_data = meeting_room_poi_dict[space_id]["user_data"]
                    yield\
                        {
                            "id": meeting_room_poi_dict[space_id]["id"],
                            "user_data":
                            {
                                "image_url": user_data["image_url"],
                                "availability": availability_states[int(meeting_room_json["statusId"]) - 1],
                                "office_location": user_data["office_location"],
                                "space_id": user_data["space_id"],
                                "floor_name": user_data["floor_name"],
                                "short_description": user_data["short_description"],
                                "is_admin": user_data["is_admin"],
                                "capacity": user_data["capacity"],
                                "phone": user_data["phone"],
                                "tieline": user_data["tieline"],
                                "nexi": user_data["nexi"],
                                "is_occupancy_enabled": user_data["is_occupancy_enabled"],
                                "is_temporarily_deactivated": user_data["is_temporarily_deactivated"],
                                "notes": meeting_room_json["notes"]
                            }
                        }


def update_meeting_room_pois(meeting_room_json, poi_service_url, dev_auth_token):
    for meeting_room in meeting_room_json:
        if "user_data" in meeting_room:
            user_data = meeting_room["user_data"]
            meeting_room["user_data"] = json.dumps(user_data, ensure_ascii=False)

    if len(meeting_room_json) > 0:
        url = "{0}/bulk/?token={1}".format(poi_service_url, dev_auth_token)
        response = requests.post(url, json={"update": meeting_room_json}, verify=False)
        print "post {1}: {0}".format(url, response.status_code)
        # print {"update": meeting_room_json}
    else:
        print "no meeting room POIs to update"


def print_usage():
    print "Usage: "
    print "export_to_poi_service.py -u <poi_service_url> -k <dev_auth_token> -s <app_secret> -i <app_id> -r <region_code> -d <debug_data>"
    print "export_to_poi_service.py [-h | -help]"
    print
    print "Options: "
    print "-u --poi_service_url     URL to poi-service"
    print "-k --dev_auth_token      eeGeo Developer Auth Token"
    print "-s --app_secret          app secret for web service"
    print "-i --app_id              app id for web service"
    print "-r --region_code         region code for web service"
    print "-d --debug_data          send debug data to web service"
    print "-h --help                Display this screen"


def get_args(argv):
    poi_service_url = ""
    dev_auth_token = ""
    app_secret = ""
    app_id = ""
    region_code = ""
    debug_data = ""

    try:
        opts, args = getopt.getopt(argv, "hvsi:u:k:r:d", ["poi_service_url=", "dev_auth_token=", "app_secret=", "app_id=", "region_code=", "debug_data="])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == "-h":
            print_usage()
            sys.exit()
        elif opt in ("-u", "--poi_service_url"):
            poi_service_url = arg
        elif opt in ("-k", "--dev_auth_token"):
            dev_auth_token = arg
        elif opt in {"-s", "--app_secret"}:
            app_secret = arg
        elif opt in {"-i", "--app_id"}:
            app_id = arg
        elif opt in {"-r", "--region_code"}:
            region_code = arg
        elif opt in {"-d", "--debug_data"}:
            debug_data = arg

    return poi_service_url, dev_auth_token, app_secret, app_id, region_code, debug_data


if __name__ == "__main__":
    # logging.config.dictConfig({
    #     'version': 1,
    #     'formatters': {
    #         'verbose': {
    #             'format': '%(name)s: %(message)s'
    #         }
    #     },
    #     'handlers': {
    #         'console': {
    #             'level': 'DEBUG',
    #             'class': 'logging.StreamHandler',
    #             'formatter': 'verbose',
    #         },
    #     },
    #     'loggers': {
    #         'zeep.transports': {
    #             'level': 'DEBUG',
    #             'propagate': True,
    #             'handlers': ['console'],
    #         },
    #     }
    # })

    poi_service_url, dev_auth_token, app_secret, app_id, region_code, debug_data = get_args(sys.argv[1:])

    meeting_room_poi_dict = get_meeting_room_poi_dict("../generated/MeetingRoomPoiData.json")

    meeting_room_json = []
    for meeting_room in get_updated_meeting_room_poi_json("http://localhost/webservice/pythonservice?wsdl", region_code, meeting_room_poi_dict):
        meeting_room_json.append(meeting_room)

    update_meeting_room_pois(meeting_room_json, poi_service_url, dev_auth_token)
