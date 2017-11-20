import json
import requests
import sys

from feedconfig import FeedConfig
from hotcoldpoiset import HotColdPoiSet

def parse_employees():
    employees = {}
    with open("../generated/EmployeePoiData.json", "r") as f:
        employee_json = json.load(f)
        for employee in employee_json:
            if "user_data" in employee and "employee_uuid" in employee["user_data"]:
                employees[employee["user_data"]["employee_uuid"]] = employee
    return employees

def parse_desks():
    with open("../generated/DeskPoiData.json", "r") as f:
        return json.load(f)

def parse_desk_groups():
    with open("../generated/DeskGroupPoiData.json", "r") as f:
        return json.load(f)

def apply_employee_to_desk(desk, employee):
    desk["user_data"]["working_group"] = employee["user_data"]["working_group"]
    desk["user_data"]["picture_id"] = employee["user_data"]["picture_id"]
    desk["user_data"]["office_location"] = employee["user_data"]["office_location"]
    desk["user_data"]["deptCode"] = employee["user_data"]["deptCode"]
    desk["user_data"]["employee_uuid"] = employee["user_data"]["employee_uuid"]
    desk["user_data"]["image_url"] = employee["user_data"]["image_url"]
    desk["user_data"]["desk_code"] = employee["user_data"]["desk_code"]
    desk["user_data"]["employee_title"] = employee["title"]
    desk["user_data"]["employee_title"] = employee["title"]

def reconcile_assigned_employee(desks, employees):
    for desk in desks:
        if "user_data" in desk and "assigned_person" in desk["user_data"]:
            assigned_employee_uuid = int(desk["user_data"]["assigned_person"])
            if assigned_employee_uuid > 0 and assigned_employee_uuid in employees:
               apply_employee_to_desk(desk, employees[assigned_employee_uuid])
    return desks

def delete_existing_desk_pois(feedconfig, hotcold):
    url = "{0}/pois/?token={1}".format(hotcold.cold, feedconfig.wrld_dev_auth_token)
    response = requests.delete(url)
    print "delete {1}: {0}".format(url, response.status_code)

def add_desk_pois(desk_json, feedconfig, hotcold):
    if len(desk_json) > 0:
        url = "{0}/bulk/?token={1}".format(hotcold.cold, feedconfig.wrld_dev_auth_token)
        response = requests.post(url, json={"create": desk_json}, verify=False)
        print "post {1}: {0}, {2}".format(url, response.status_code, response.text)
    else:
        print "no desks POIs to add"

if __name__ == "__main__":
    feedconfig = FeedConfig.build()

    employees = parse_employees()
    desk_groups = parse_desk_groups()
    desks = parse_desks()
    desks = reconcile_assigned_employee(desks, employees)

    hotcold = HotColdPoiSet(feedconfig.poi_service_a_base_path, feedconfig.poi_service_b_base_path, feedconfig.wrld_dev_auth_token, keys=["6d27c9936af66fa250dbc30172d7fec4", "3ceebbe9943e604ee4ac39b3977be5e1", "065f472a5e1143fbef57d3a97b019ef9"])
    hotcold.determine_hot_cold()

    print "Hot is: {0}".format(hotcold.hot)
    print "Cold is: {0}".format(hotcold.cold)

    delete_existing_desk_pois(feedconfig, hotcold)

    all_pois = desks+desk_groups

    add_desk_pois(all_pois, feedconfig, hotcold)

    hotcold.swap()

    print "Hot is now: {0}".format(hotcold.hot)
    print "Cold is now: {0}".format(hotcold.cold)