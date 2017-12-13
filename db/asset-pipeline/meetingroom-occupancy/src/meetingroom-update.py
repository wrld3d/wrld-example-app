import base64
import json
import hmac
import requests
import sys

from feedmappings import InteriorMapping, SpaceIdToWGS84, SpaceIdToHighlightId, SpaceIdToImage
from feedconfig import FeedConfig
from hotcoldpoiset import HotColdPoiSet
import zeep
import hmactransport
from hmactransport import HmacTransport
from zeep import Client

MEETING_ROOM_TAG = "meeting_room"
TRAINING_ROOM_TAG = "training_room education"
TRAINING_ROOM_SPACE_CLASS_ID = 303

def verify_meeting_room(meeting_room_json, interior_mapping, space_id_to_wgs84):
    location_id = meeting_room_json["locationId"]
    space_id = meeting_room_json["spaceId"]
    room_name = meeting_room_json["name"]
    floor_name = meeting_room_json["floorName"]
    room_tuple = (room_name,space_id,location_id)    
    if not interior_mapping.contains_location(location_id):
        raise Exception("Skipping Room NOINTER %s(%s) in %s" % room_tuple)
    if not space_id_to_wgs84.contains_space_id(space_id):
        raise Exception("Skipping Room NOSPCID %s(%s) in %s" % room_tuple)
    if not interior_mapping.contains_floor(interior_mapping.get_interior_from_location(location_id), floor_name):
        raise Exception("Skipping Room NOFLOOR %s(%s) in %s" % room_tuple)
    return True

def process_room(meeting_room_json, feedconfig, interior_mapping, image_mapping, space_id_to_wgs84, space_id_to_highlight_id):
    location_id = meeting_room_json["locationId"]
    space_id = meeting_room_json["spaceId"]
    interior_id = interior_mapping.get_interior_from_location(location_id)
    floor_name = meeting_room_json["floorName"]
    floor_id = interior_mapping.get_interior_floor_id(interior_id, floor_name)
    location = space_id_to_wgs84.get_lat_lon_for_spaceid(space_id)
    highlight_id = meeting_room_json["name"]
    space_class_id = -1
    if "spaceClassId" in meeting_room_json:
        space_class_id = meeting_room_json["spaceClassId"]
    if space_id_to_highlight_id.contains_highlight_id(space_id):
        highlight_id = space_id_to_highlight_id.get_highlight_id_for_spaceid(space_id)
    else:
        raise Exception("Unable to find highlight for {0},{1}".format(space_id, meeting_room_json["name"]))
    image_url = "{0}/images/{1}".format(feedconfig.cdn_base_path, "placeholder.jpg")
    if image_mapping.contains_image(space_id):
        image_url = "{0}/images/{1}".format(feedconfig.cdn_base_path, image_mapping.get_image_for_space_id(space_id))
    return\
        {
            "title": meeting_room_json["name"],
            "subtitle": "",
            "tags": TRAINING_ROOM_TAG if space_class_id == TRAINING_ROOM_SPACE_CLASS_ID else MEETING_ROOM_TAG,
            "lat": float(location["lat"]),
            "lon": float(location["lon"]),
            "indoor": True,
            "indoor_id": interior_id,
            "floor_id": int(floor_id),
            "user_data":
            {
                "image_url": image_url,
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
                "highlight_id": highlight_id,
                "is_occupancy_enabled": bool(meeting_room_json["isOccupancyEnabled"]),
                "is_temporarily_deactivated": bool(meeting_room_json["isTemporarilyDeactivated"])
            }
        }


def get_meeting_room_definitions(region, site, feedconfig, interior_mapping, image_mapping, space_id_to_wgs84, space_id_to_highlight_id):
    transport = HmacTransport()
    client = Client(feedconfig.soap_service_wsdl_url, transport=transport)
    response = client.service.GetMeetingSpaceDetails(region, site)

    if response is not None and response != "":
        meeting_room_list = {}
        if type(response) is str:
            meeting_room_list = json.loads(response)
        else:
            meeting_room_list = zeep.helpers.serialize_object(response)
        if "meetingSpaceDetails" in meeting_room_list:
            for meeting_room_json in meeting_room_list["meetingSpaceDetails"]:
                try:
                    verify_meeting_room(meeting_room_json, interior_mapping, space_id_to_wgs84)
                except Exception, e:
                    print e
                    continue
                yield process_room(meeting_room_json, feedconfig, interior_mapping, image_mapping, space_id_to_wgs84, space_id_to_highlight_id)

def delete_existing_meeting_room_pois(feedconfig, hotcold):
    url = "{0}/pois/?token={1}".format(hotcold.cold, feedconfig.wrld_dev_auth_token)
    response = requests.delete(url)
    print "delete {1}: {0}".format(url, response.status_code)

def add_meeting_room_pois(meeting_room_json, feedconfig, hotcold):
    if len(meeting_room_json) > 0:
        url = "{0}/bulk/?token={1}".format(hotcold.cold, feedconfig.wrld_dev_auth_token)
        response = requests.post(url, json={"create": meeting_room_json}, verify=False)
        print "post {1}: {0}".format(url, response.status_code)
        # print {"create": meeting_room_json}
    else:
        print "no meeting room POIs to add"


def save_meeting_room_json(feedconfig, hotcold, filename):
    url = "{0}/pois/?token={1}".format(hotcold.hot, feedconfig.wrld_dev_auth_token)
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

if __name__ == "__main__":
    feedconfig = FeedConfig.build()

    hotcold = HotColdPoiSet(feedconfig.poi_service_a_base_path, feedconfig.poi_service_b_base_path, feedconfig.wrld_dev_auth_token, keys=["6d27c9936af66fa250dbc30172d7fec4", "3ceebbe9943e604ee4ac39b3977be5e1", "065f472a5e1143fbef57d3a97b019ef9"])
    hotcold.determine_hot_cold()

    print "Hot is: {0}".format(hotcold.hot)
    print "Cold is: {0}".format(hotcold.cold)

    interior_mapping = InteriorMapping()
    interior_mapping.populate_from_files("../data")
    space_id_to_wgs84 = SpaceIdToWGS84()
    space_id_to_wgs84.populate_from_files("../generated")
    space_id_to_highlight_id = SpaceIdToHighlightId()
    space_id_to_highlight_id.populate_from_files("../generated")
    image_mapping = SpaceIdToImage()
    image_mapping.populate_from_files("../generated")

    meeting_room_json = []
    for region in feedconfig.soap_regions:
        for site in feedconfig.soap_regions[region]:    
            for meeting_room in get_meeting_room_definitions(region, site, feedconfig, interior_mapping, image_mapping, space_id_to_wgs84, space_id_to_highlight_id):
                meeting_room_json.append(meeting_room)
                print "Adding Room: {0}\n".format(meeting_room)

    delete_existing_meeting_room_pois(feedconfig, hotcold)

    add_meeting_room_pois(meeting_room_json, feedconfig, hotcold)

    hotcold.swap()

    print "Hot is now: {0}".format(hotcold.hot)
    print "Cold is now: {0}".format(hotcold.cold)

    save_meeting_room_json(feedconfig, hotcold, "../generated/MeetingRoomPoiData.json")