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
                "title": meeting_room_json["name"],
                "subtitle": "",
                "tags": MEETING_ROOM_TAG,
                "lat": float(meeting_room_json["latitude_degrees"]),
                "lon": float(meeting_room_json["longitude_degrees"]),
                "indoor": True,
                "indoor_id": meeting_room_json["interior_id"],
                "floor_id": int(meeting_room_json["interior_floor"]),
                "user_data":
                {
                    "image_url": meeting_room_json["image_filename"],
                    "availability": "available",
                    "office_location": meeting_room_json["office_location"],
                    "mid": meeting_room_json["mid"]
                }
            }


def delete_existing_meeting_room_pois(poi_service_url, dev_auth_token):
    url = "{0}/pois/?token={1}".format(poi_service_url, dev_auth_token)
    response = requests.get(url)
    print "get {1}: {0}".format(url, response.status_code)

    if response.status_code == 200:
        meeting_room_poi_list = response.json()
        # print meeting_room_poi_list

        entities = []
        for meeting_room_poi in meeting_room_poi_list:
            if meeting_room_poi["tags"] == MEETING_ROOM_TAG:
                if "mid" in meeting_room_poi["user_data"]:
                    entities.append(int(meeting_room_poi["id"]))

        if len(entities) > 0:
            url = "{0}/bulk/?token={1}".format(poi_service_url, dev_auth_token)
            response = requests.post(url, json={"delete": entities}, verify=False)
            print "delete {1}: {0}".format(url, response.status_code)
            # print {"delete": entities}
        else:
            print "no meeting room POIs deleted"


def add_meeting_room_pois(meeting_room_json, poi_service_url, dev_auth_token, cdn_base_url):
    for meeting_room in meeting_room_json:
        if "user_data" in meeting_room:
            if "image_url" in meeting_room["user_data"]:
                original = meeting_room["user_data"]["image_url"]
                meeting_room["user_data"]["image_url"] = "{0}/images/{1}".format(cdn_base_url, original)

            user_data = meeting_room["user_data"]
            meeting_room["user_data"] = json.dumps(user_data, ensure_ascii=False)

    if len(meeting_room_json) > 0:
        url = "{0}/bulk/?token={1}".format(poi_service_url, dev_auth_token)
        response = requests.post(url, json={"create": meeting_room_json}, verify=False)
        print "post {1}: {0}".format(url, response.status_code)
        # print {"create": meeting_room_json}
    else:
        print "no meeting room POIs to add"


def save_meeting_room_json(poi_service_url, dev_auth_token, filename):
    url = "{0}/pois/?token={1}".format(poi_service_url, dev_auth_token)
    response = requests.get(url)
    print "get {1}: {0}".format(url, response.status_code)

    if response.status_code == 200:
        meeting_room_poi_list = response.json()

        meeting_room_list = []
        for meeting_room_poi in meeting_room_poi_list:
            if meeting_room_poi["tags"] == MEETING_ROOM_TAG:
                if "user_data" in meeting_room_poi:
                    meeting_room_list.append({"id": meeting_room_poi["id"], "user_data": meeting_room_poi["user_data"]})

        with open(filename, "w") as file:
            json.dump(meeting_room_list, file)


def print_usage():
    print "Usage: "
    print "export_to_poi_service.py -u <poi_service_url> -k <dev_auth_token>"
    print "export_to_poi_service.py [-h | -help]"
    print
    print "Options: "
    print "-u --poi_service_url     URL to poi-service"
    print "-k --dev_auth_token      eeGeo Developer Auth Token"
    print "-c --cdn_base_url        base URL of CDN"
    print "-h --help                Display this screen"


def get_args(argv):
    poi_service_url = ""
    dev_auth_token = ""
    cdn_base_url = ""

    try:
        opts, args = getopt.getopt(argv, "hvsi:u:k:c:", ["poi_service_url=", "dev_auth_token=", "cdn_base_url="])
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
        elif opt in ("-c", "--cdn_base_url"):
            cdn_base_url = arg

    return poi_service_url, dev_auth_token, cdn_base_url


if __name__ == "__main__":
    poi_service_url, dev_auth_token, cdn_base_url = get_args(sys.argv[1:])

    meeting_room_json = []
    for meeting_room in get_meeting_room_definitions("../data/meetingroom-definition.json"):
        meeting_room_json.append(meeting_room)

    delete_existing_meeting_room_pois(poi_service_url, dev_auth_token)

    add_meeting_room_pois(meeting_room_json, poi_service_url, dev_auth_token, cdn_base_url)

    save_meeting_room_json(poi_service_url, dev_auth_token, "../data/meetingroom-poi-data.json")
