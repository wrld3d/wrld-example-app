import base64
import json
import hmac
import requests
import sys

from feedmappings import DeskMapping, SpaceIdToWGS84
from feedconfig import FeedConfig
from hotcoldpoiset import HotColdPoiSet
import zeep
import hmactransport
from hmactransport import HmacTransport
from zeep import Client

EMPLOYEE_TAG = "person"
DEPARTMENT_TAG = "department"

def verify_employee(employee_json, desk_mapping, space_id_to_wgs84):
    employee_uuid = employee_json["uuid"]
    first_name = employee_json["FirstName"]
    last_name = employee_json["LastName"]
    employee_tuple = (employee_uuid,first_name,last_name)
    if not desk_mapping.contains_desk_for_employee(employee_uuid):
        raise Exception("Skipping Employee NODESK %s(%s %s)" % employee_tuple)
    space_id = desk_mapping.get_space_id_for_employee(employee_uuid)
    if not space_id_to_wgs84.contains_space_id(space_id):
        raise Exception("Skipping Employee NOSPCID %s - %s(%s %s)" % (space_id,employee_tuple))
    return True

def get_employee_definitions(site, feedconfig, desk_mapping, space_id_to_wgs84):
    transport = HmacTransport()
    client = Client(feedconfig.soap_service_wsdl_url, transport=transport)
    response = client.service.GetEmployeeDetails(feedconfig.soap_region, site)

    if response is not None and response != "":
        employee_list = {}
        if type(response) is str:
            employee_list = json.loads(response)
        else:
            employee_list = zeep.helpers.serialize_object(response)
        if "employeeDetails" in employee_list:
            for employee_json in employee_list["employeeDetails"]:
                try:
                    verify_employee(employee_json, desk_mapping, space_id_to_wgs84)
                except Exception, e:
                    print e
                    continue
                employee_uuid = employee_json["uuid"]
                first_name = employee_json["FirstName"]
                last_name = employee_json["LastName"]
                desk_code = desk_mapping.get_desk_code_for_employee(employee_uuid)
                
                space_id = desk_mapping.get_space_id_for_employee(employee_uuid)
                location = space_id_to_wgs84.get_lat_lon_for_spaceid(space_id)

                interior_id = desk_mapping.get_indoor_id_for_employee(employee_uuid)
                floor_id = desk_mapping.get_floor_id_for_employee(employee_uuid)

                image_url = "{0}/{1}.jpg".format(feedconfig.cdn_base_path, employee_json["PictureId"])

                yield \
                {
                    "title":"{0} {1}".format(first_name, last_name),
                    "subtitle":"",
                    "tags":EMPLOYEE_TAG,
                    "lat": float(location["lat"]),
                    "lon": float(location["lon"]),
                    "indoor":True,
                    "indoor_id":interior_id,
                    "floor_id":floor_id,
                    "user_data":
                    {
                      "image_url":image_url,
                      "desk_code":desk_code,
                      "office_location":"",
                      "working_group":employee_json["DeptDescription"],
                      "deptCode":employee_json["DeptCode"],
                      "picture_id":employee_json["PictureId"],
                      "employee_uuid":employee_json["uuid"]
                    }
               }

def get_department_definitions(feedconfig, employees):
    departments = {}

    for employee in employees:
        department_code = employee["user_data"]["deptCode"]
        department_description = employee["user_data"]["working_group"]
        desk_code = employee["user_data"]["desk_code"]
        if not department_code in departments:
            departments[department_code] = {"description":department_description, "location":employee, "members":[]}
        departments[department_code]["members"].append(desk_code)

    for department_code in departments.keys():
        department = departments[department_code]
        image_url = "{0}/images/{1}".format(feedconfig.cdn_base_path, "poi_view_person.png")
        yield \
        {
            "title":department["description"],
            "subtitle":"",
            "tags":DEPARTMENT_TAG,
            "lat": department["location"]["lat"],
            "lon": department["location"]["lon"],
            "indoor":True,
            "indoor_id":department["location"]["indoor_id"],
            "floor_id":department["location"]["floor_id"],
            "user_data":
            {
              "image_url":image_url,
              "description":department["description"],
              "desks":department["members"]
            }
       }        

def delete_existing_employee_pois(feedconfig, hotcold):
    url = "{0}/pois/?token={1}".format(hotcold.cold, feedconfig.wrld_dev_auth_token)
    response = requests.delete(url)
    print "delete {1}: {0}".format(url, response.status_code)

def add_employee_pois(employee_json, feedconfig, hotcold):
    if len(employee_json) > 0:
        url = "{0}/bulk/?token={1}".format(hotcold.cold, feedconfig.wrld_dev_auth_token)
        response = requests.post(url, json={"create": employee_json}, verify=False)
        print "post {1}: {0}, {2}".format(url, response.status_code, response.text)
    else:
        print "no employee POIs to add"

def save_employee_json(feedconfig, filename):
    with open(filename, "w") as file:
        json.dump(all_pois, file)

if __name__ == "__main__":
    feedconfig = FeedConfig.build()

    hotcold = HotColdPoiSet(feedconfig.poi_service_a_base_path, feedconfig.poi_service_b_base_path, feedconfig.wrld_dev_auth_token, keys=["6d27c9936af66fa250dbc30172d7fec4", "3ceebbe9943e604ee4ac39b3977be5e1", "065f472a5e1143fbef57d3a97b019ef9"])
    hotcold.determine_hot_cold()

    print "Hot is: {0}".format(hotcold.hot)
    print "Cold is: {0}".format(hotcold.cold)

    desk_mapping = DeskMapping()
    desk_mapping.populate_from_files("../generated")
    space_id_to_wgs84 = SpaceIdToWGS84()
    space_id_to_wgs84.populate_from_files("../generated")

    employees = []
    sites = ["GB033", "GB025", "GB006", "GB032", "GB012"]
    for site in sites:
        for employee in get_employee_definitions(site, feedconfig, desk_mapping, space_id_to_wgs84):
            employees.append(employee)

    departments = []
    for department in get_department_definitions(feedconfig, employees):
        departments.append(department)

    all_pois = employees+departments

    delete_existing_employee_pois(feedconfig, hotcold)

    add_employee_pois(all_pois, feedconfig, hotcold)

    hotcold.swap()

    print "Hot is now: {0}".format(hotcold.hot)
    print "Cold is now: {0}".format(hotcold.cold)    

    save_employee_json(employees, "../generated/EmployeePoiData.json")
    save_employee_json(departments, "../generated/DepartmentPoiData.json")