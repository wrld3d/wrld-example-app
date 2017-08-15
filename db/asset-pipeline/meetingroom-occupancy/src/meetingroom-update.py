import getopt
import json
import requests
import sys

from zeep import Client


MEETING_ROOM_TAG = "meeting_room"


def get_interior_id_dict(filename):
    interior_id_dict = {}

    with open(filename) as interior_id_json_file:
        interior_id_list_json = json.load(interior_id_json_file)
        for interior_id_json in interior_id_list_json:
            interior_id_dict[interior_id_json["locationId"]] = interior_id_json["interior_id"]

    return interior_id_dict


def get_interior_floor_dict(filename):
    interior_id_floor_dict = {}

    with open(filename) as interior_floor_json_file:
        interior_floor_list_json = json.load(interior_floor_json_file)
        for interior_id_floor_json in interior_floor_list_json:
            interior_floor_dict = {}

            for interior_floor_json in interior_id_floor_json["floors"]:
                interior_floor_dict[interior_floor_json["floorName"]] = interior_floor_json["interior_floor"]

            interior_id_floor_dict[interior_id_floor_json["interior_id"]] = interior_floor_dict

    return interior_id_floor_dict


def get_location_dict(filename):
    location_dict = {}

    with open(filename) as location_json_file:
        location_list_json = json.load(location_json_file)
        for location_json in location_list_json:
            location_dict[str(location_json["spaceId"])] = {"lat": location_json["latitude_degrees"], "lon": location_json["longitude_degrees"]}

    return location_dict


def get_image_dict(filename):
    image_dict = {}

    with open(filename) as image_json_file:
        image_list_json = json.load(image_json_file)
        for image_json in image_list_json:
            image_dict[str(image_json["spaceId"])] = image_json["image_filename"]

    return image_dict


def get_meeting_room_definitions(web_service_url, region_code, interior_id_dict, interior_floor_dict, location_dict, image_dict):
    client = Client(web_service_url)
    response = client.service.GetMeetingSpaceDetails(region_code)

    if response is not None and response != "":
        meeting_room_list_json = json.loads(response)
        for meeting_room_json in meeting_room_list_json["meetingSpaceDetails"]:
            location_id = meeting_room_json["locationId"]
            space_id = meeting_room_json["spaceId"]
            interior_id = interior_id_dict[location_id]
            floor_name = meeting_room_json["floorName"]
            floor_id = interior_floor_dict[interior_id][floor_name]
            location = location_dict[str(space_id)]
            image = image_dict[str(space_id)]
            yield\
                {
                    "title": meeting_room_json["name"],
                    "subtitle": "",
                    "tags": MEETING_ROOM_TAG,
                    "lat": float(location["lat"]),
                    "lon": float(location["lon"]),
                    "indoor": True,
                    "indoor_id": interior_id,
                    "floor_id": int(floor_id),
                    "user_data":
                    {
                        "image_url": image,
                        "availability": "available",
                        "office_location": meeting_room_json["shortDescription"],
                        "space_id": space_id,
                        "floor_name": floor_name,
                        "short_description": meeting_room_json["shortDescription"],
                        "is_admin": bool(meeting_room_json["isAdmin"]),
                        "capacity": int(meeting_room_json["capacity"]),
                        "phone": meeting_room_json["phone"],
                        "tieline": meeting_room_json["tieline"],
                        "nexi": int(meeting_room_json["nexi"]),
                        "is_occupancy_enabled": bool(meeting_room_json["isOccupancyEnabled"]),
                        "is_temporarily_deactivated": bool(meeting_room_json["isTemporarilyDeactivated"])
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
    print "-r --region_code         region code for web service"
    print "-h --help                Display this screen"


def get_args(argv):
    poi_service_url = ""
    dev_auth_token = ""
    cdn_base_url = ""
    region_code = ""

    try:
        opts, args = getopt.getopt(argv, "hvsi:u:k:c:r:", ["poi_service_url=", "dev_auth_token=", "cdn_base_url=", "region_code="])
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
        elif opt in {"-r", "--region_code"}:
            region_code = arg

    return poi_service_url, dev_auth_token, cdn_base_url, region_code


if __name__ == "__main__":
    poi_service_url, dev_auth_token, cdn_base_url, region_code = get_args(sys.argv[1:])

    interior_id_dict = get_interior_id_dict("../data/InteriorIdMap.json")
    interior_floor_dict = get_interior_floor_dict("../data/InteriorFloorMap.json")
    location_dict = get_location_dict("../generated/LocationMap.json")
    image_dict = get_image_dict("../generated/ImageMap.json")

    meeting_room_json = []
    for meeting_room in get_meeting_room_definitions("../data/Service.wsdl", region_code, interior_id_dict, interior_floor_dict, location_dict, image_dict):
        meeting_room_json.append(meeting_room)

    delete_existing_meeting_room_pois(poi_service_url, dev_auth_token)

    add_meeting_room_pois(meeting_room_json, poi_service_url, dev_auth_token, cdn_base_url)

    save_meeting_room_json(poi_service_url, dev_auth_token, "../generated/MeetingRoomPoiData.json")
