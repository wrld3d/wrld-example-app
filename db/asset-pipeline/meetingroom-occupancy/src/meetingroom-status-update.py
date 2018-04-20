import base64
import json
import getopt
import hmac
import requests
import sys

from hotcoldpoiset import HotColdPoiSet
from feedconfig import FeedConfig
import zeep
import hmactransport
from hmactransport import HmacTransport
from zeep import Client

import logging.config

MEETING_ROOM_TAG = "meeting_room"

def get_meeting_room_poi_dict(filename):
    meeting_room_poi_dict = {}

    with open(filename) as meeting_room_json_file:
        meeting_room_list_json = json.load(meeting_room_json_file)
        for meeting_room_json in meeting_room_list_json:
            meeting_room_poi_dict[meeting_room_json["user_data"]["space_id"]] = {"id": meeting_room_json["id"], "user_data": meeting_room_json["user_data"]}

    return meeting_room_poi_dict


def get_updated_meeting_room_poi_json(region, site, feedconfig, meeting_room_poi_dict):
    availability_states = ["available", "occupied", "available_soon"]

    transport = HmacTransport()
    client = Client(feedconfig.soap_service_wsdl_url, transport=transport)
    response = client.service.GetMeetingSpaceOccupancyDetails(region, site)

    if response is not None and response != "":
        meeting_room_list_json = {}
        if type(response) is str:
            meeting_room_list_json = json.loads(response)      
        else:
            meeting_room_list_json = zeep.helpers.serialize_object(response)
        if "meetingSpaceOccupancyDetails" in meeting_room_list_json:
            for meeting_room_json in meeting_room_list_json["meetingSpaceOccupancyDetails"]:
                space_id = meeting_room_json["spaceId"]
                if space_id in meeting_room_poi_dict:
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
                                "notes": meeting_room_json["notes"],
                                "highlight_id": user_data["highlight_id"]
                            }
                        }
                else:
                    print "Skipping Room NOSPACE %s" % space_id


def update_meeting_room_pois(meeting_room_json, feedconfig, hotcold):
    if len(meeting_room_json) > 0:
        url = "{0}/bulk/?token={1}".format(hotcold.hot, feedconfig.wrld_dev_auth_token)
        response = requests.post(url, json={"update": meeting_room_json}, verify=False)
        print "post {1}: {0}".format(url, response.status_code)
    else:
        print "no meeting room POIs to update"

if __name__ == "__main__":
    feedconfig = FeedConfig.build()
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

    hotcold = HotColdPoiSet(feedconfig.poi_service_a_base_path, feedconfig.poi_service_b_base_path, feedconfig.wrld_dev_auth_token, keys=["6d27c9936af66fa250dbc30172d7fec4", "3ceebbe9943e604ee4ac39b3977be5e1", "065f472a5e1143fbef57d3a97b019ef9"])
    hotcold.determine_hot_cold()

    meeting_room_poi_dict = get_meeting_room_poi_dict("../generated/MeetingRoomPoiData.json")

    meeting_room_json = []
    for region in feedconfig.soap_regions:
        for site in feedconfig.soap_regions[region]:  
            for meeting_room in get_updated_meeting_room_poi_json(region, site, feedconfig, meeting_room_poi_dict):
                meeting_room_json.append(meeting_room)

    update_meeting_room_pois(meeting_room_json, feedconfig, hotcold)