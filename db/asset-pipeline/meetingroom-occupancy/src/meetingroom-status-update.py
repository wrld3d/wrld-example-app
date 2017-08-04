import getopt
import json
import requests
import sys


MEETING_ROOM_TAG = "meeting_room"


def get_meeting_room_definitions(filename):
    with open(filename) as meeting_room_json_file:
        meeting_room_list_json = json.load(meeting_room_json_file)
        for meeting_room_json in meeting_room_list_json:
            yield {
                "id": meeting_room_json["id"],
                "user_data": meeting_room_json["user_data"]
            }


def get_meeting_room_status_definitions(data_filename, status_filename):
    meeting_room_poi_list = []
    for meeting_room_definition in get_meeting_room_definitions(data_filename):
        meeting_room_poi_list.append(meeting_room_definition)
    # print meeting_room_poi_list

    with open(status_filename) as meeting_room_json_file:
        meeting_room_list_json = json.load(meeting_room_json_file)
        for meeting_room_json in meeting_room_list_json:
            for meeting_room_poi in meeting_room_poi_list:
                if meeting_room_poi["user_data"]["mid"] == meeting_room_json["mid"]:
                    yield {
                        "id": meeting_room_poi["id"],
                        "user_data":
                        {
                            "image_url": meeting_room_poi["user_data"]["image_url"],
                            "availability": meeting_room_json["availability"],
                            "office_location": meeting_room_poi["user_data"]["office_location"],
                            "mid": meeting_room_json["mid"]
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
    print "export_to_poi_service.py -u <poi_service_url> -k <dev_auth_token>"
    print "export_to_poi_service.py [-h | -help]"
    print
    print "Options: "
    print "-u --poi_service_url     URL to poi-service"
    print "-k --dev_auth_token      eeGeo Developer Auth Token"
    print "-h --help                Display this screen"


def get_args(argv):
    poi_service_url = ""
    dev_auth_token = ""

    try:
        opts, args = getopt.getopt(argv, "hvsi:u:k:", ["poi_service_url=", "dev_auth_token=", "cdn_base_url="])
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

    return poi_service_url, dev_auth_token


if __name__ == "__main__":
    poi_service_url, dev_auth_token = get_args(sys.argv[1:])

    meeting_room_json = []
    for meeting_room in get_meeting_room_status_definitions("../data/meetingroom-poi-data.json", "../data/meetingroom-status-definition.json"):
        meeting_room_json.append(meeting_room)

    update_meeting_room_pois(meeting_room_json, poi_service_url, dev_auth_token)
