import base64
import json
import hmac
import requests
import sys

from feedmappings import InteriorMapping, SpaceIdToWGS84
from feedconfig import FeedConfig
from hotcoldpoiset import HotColdPoiSet
import zeep
import hmactransport
from hmactransport import HmacTransport
from zeep import Client

DESK_TAG = "desk"

def get_desk_name(desk_json, interior_mapping):
    location_id = desk_json["locationId"]
    desk_prefix = "Unknown"
    if interior_mapping.contains_desk_prefix(location_id):
        desk_prefix = interior_mapping.get_desk_prefix_from_location(location_id)
    name = desk_json["name"]
    if name is None:
        name = "Unknown"
    floor = desk_json["floor"]
    if floor is None:
        floor = "Unknown"
    if floor == "Gnd":
        if location_id == "GB006":
            floor = "0G"
        else:
            floor = "-G"            
    return "{0}{1}-{2}".format(desk_prefix, floor.strip(), name.strip())

def verify_desk(desk_json, interior_mapping, space_id_to_wgs84):
    location_id = desk_json["locationId"]
    space_id = desk_json["spaceId"]
    floor_name = desk_json["floorName"]
    desk_name = get_desk_name(desk_json, interior_mapping)
    desk_tuple = (desk_name,space_id,location_id)
    if not interior_mapping.contains_location(location_id):
        raise Exception("Skipping Desk NOINTER %s(%s) in %s" % desk_tuple)
    if not space_id_to_wgs84.contains_space_id(space_id):
        raise Exception("Skipping Desk NOSPCID %s(%s) in %s" % desk_tuple)
    if not interior_mapping.contains_floor(interior_mapping.get_interior_from_location(location_id), floor_name):
        raise Exception("Skipping Desk NOFLOOR %s(%s) in %s" % desk_tuple)
    return True

def get_desk_definitions(region, site, feedconfig, interior_mapping, space_id_to_wgs84):
    transport = HmacTransport()
    client = Client(feedconfig.soap_service_wsdl_url, transport=transport)
    response = client.service.GetDeskDetails(region, site)

    if response is not None and response != "":
        desk_list = {}
        if type(response) is str:
            desk_list = json.loads(response)
        else:
            desk_list = zeep.helpers.serialize_object(response)
        if "deskDetails" in desk_list:
            for desk_json in desk_list["deskDetails"]:
                try:
                    verify_desk(desk_json, interior_mapping, space_id_to_wgs84)
                except Exception, e:
                    print e
                    continue
                location_id = desk_json["locationId"]
                space_id = desk_json["spaceId"]
                highlight_id = "S{0}".format(space_id)
                interior_id = interior_mapping.get_interior_from_location(location_id)
                floor_name = desk_json["floorName"]
                floor_id = interior_mapping.get_interior_floor_id(interior_id, floor_name)
                assigned_person = int(desk_json["assignedPersonUuid"])
                location = space_id_to_wgs84.get_lat_lon_for_spaceid(space_id)
                image = "none" #TODO
                yield\
                    {
                        "title": get_desk_name(desk_json, interior_mapping),
                        "subtitle": "",
                        "tags": DESK_TAG,
                        "lat": float(location["lat"]),
                        "lon": float(location["lon"]),
                        "indoor": True,
                        "indoor_id": interior_id,
                        "floor_id": int(floor_id),
                        "user_data":
                        {
                            "image_url": image,
                            "availability": "available",
                            "space_id": space_id,
                            "entity_highlight": [highlight_id],
                            "floor_name": floor_name,
                            "assigned_person": assigned_person,
                        }
                    }

def get_desk_groups(feedconfig, desks):
    desk_groups = {}
    desk_group_data = {}

    desk_highlight_colors = {
        "A": [0.0, 255.0, 0.0, 255.0],
        "B": [0.0, 128.0, 0.0, 255.0],
        "C": [0.0, 255.0, 0.0, 255.0],
        "D": [0.0, 128.0, 0.0, 255.0],
        "E": [0.0, 255.0, 0.0, 255.0],
        "F": [0.0, 128.0, 0.0, 255.0],
        "G": [0.0, 255.0, 0.0, 255.0],
        "H": [0.0, 128.0, 0.0, 255.0],
        "I": [0.0, 255.0, 0.0, 255.0],
        "J": [0.0, 128.0, 0.0, 255.0],
        "K": [0.0, 255.0, 0.0, 255.0]
    }

    for desk in desks:
        desk_name = desk["title"]
        desk_higlight_id = desk["user_data"]["entity_highlight"][0]
        if "3QVS" in desk_name:
            desk_group_name = desk_name[:9].replace("3QVS-","")

            floor_id = int(desk["floor_id"])

            desk_group = desk_group_name[-1:]
            highlight_color_group = desk_group if desk_highlight_colors.has_key(desk_group) else "A"

            if desk_group_name not in desk_groups:
                desk_group_data[desk_group_name] = [sys.maxint, -sys.maxint - 1]
                desk_groups[desk_group_name] = {
                    "title": desk_group_name,
                    "subtitle": "",
                    "tags": "desk_group",
                    "lat": float(desk["lat"]),
                    "lon": float(desk["lon"]),
                    "indoor": True,
                    "indoor_id": desk["indoor_id"],
                    "floor_id": floor_id,
                    "user_data":
                        {
                            "desks": [],
                            "entity_highlight_color":desk_highlight_colors[highlight_color_group]
                        }}

            min_desk_id = desk_group_data[desk_group_name][0]
            max_desk_id = desk_group_data[desk_group_name][1]
            desk_id = int(desk_name[9:])
            if desk_id < min_desk_id:
                min_desk_id = desk_id
            elif desk_id > max_desk_id:
                max_desk_id = desk_id
            desk_group_data[desk_group_name][0] = min_desk_id
            desk_group_data[desk_group_name][1] = max_desk_id
            desk_groups[desk_group_name]["title"] = "{0}{1}-{2}".format(desk_group_name, min_desk_id, max_desk_id)                
            desk_groups[desk_group_name]["user_data"]["desks"].append(desk_higlight_id)

    for desk_group in desk_groups.keys():
        yield desk_groups[desk_group]

def save_desk_json(desks, filename):
    with open(filename, "w") as file:
        json.dump(desks, file)

if __name__ == "__main__":
    feedconfig = FeedConfig.build()

    interior_mapping = InteriorMapping()
    interior_mapping.populate_from_files("../data")
    space_id_to_wgs84 = SpaceIdToWGS84()
    space_id_to_wgs84.populate_from_files("../generated")

    desks = []
    for region in feedconfig.soap_regions:
        for site in feedconfig.soap_regions[region]:
            for desk in get_desk_definitions(region, site, feedconfig, interior_mapping, space_id_to_wgs84):
                desks.append(desk)

    desk_groups = []
    for desk_group in get_desk_groups(feedconfig, desks):
        desk_groups.append(desk_group)

    save_desk_json(desks, "../generated/DeskPoiData.json")
    save_desk_json(desk_groups, "../generated/DeskGroupPoiData.json")