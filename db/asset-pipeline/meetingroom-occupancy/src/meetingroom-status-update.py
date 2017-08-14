import getopt
import json
import requests
import sys

from zeep import Client


MEETING_ROOM_TAG = "meeting_room"


def get_meeting_room_poi_dict(filename):
    meeting_room_poi_dict = {}

    with open(filename) as meeting_room_json_file:
        meeting_room_list_json = json.load(meeting_room_json_file)
        for meeting_room_json in meeting_room_list_json:
            meeting_room_poi_dict[meeting_room_json["user_data"]["space_id"]] = {"id": meeting_room_json["id"], "user_data": meeting_room_json["user_data"]}

    return meeting_room_poi_dict


def get_updated_meeting_room_poi_json(web_service_url, region_code, meeting_room_poi_dict):
    availability_states = ["available", "occupied", "available_soon"]

    client = Client(web_service_url)
    response = client.service.GetMeetingSpaceOccupancyDetails(region_code)

    if response is not None and response != "":
        meeting_room_list_json = json.loads(response)
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
    print "export_to_poi_service.py -u <poi_service_url> -k <dev_auth_token>"
    print "export_to_poi_service.py [-h | -help]"
    print
    print "Options: "
    print "-u --poi_service_url     URL to poi-service"
    print "-k --dev_auth_token      eeGeo Developer Auth Token"
    print "-r --region_code         region code for web service"
    print "-h --help                Display this screen"


def get_args(argv):
    poi_service_url = ""
    dev_auth_token = ""
    region_code = ""

    try:
        opts, args = getopt.getopt(argv, "hvsi:u:k:", ["poi_service_url=", "dev_auth_token=", "cdn_base_url=", "region_code="])
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
        elif opt in {"-r", "--region_code"}:
            region_code = arg

    return poi_service_url, dev_auth_token, region_code


if __name__ == "__main__":
    poi_service_url, dev_auth_token, region_code = get_args(sys.argv[1:])

    meeting_room_poi_dict = get_meeting_room_poi_dict("../generated/MeetingRoomPoiData.json")

    meeting_room_json = []
    for meeting_room in get_updated_meeting_room_poi_json("../data/Service.wsdl", region_code, meeting_room_poi_dict):
        meeting_room_json.append(meeting_room)

    update_meeting_room_pois(meeting_room_json, poi_service_url, dev_auth_token)
