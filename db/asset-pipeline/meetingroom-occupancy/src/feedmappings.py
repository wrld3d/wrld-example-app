import os
import json

class InteriorMapping:
    def __init__(self, interior_map={}, floor_map={}, desk_map={}):
        self.__interior_map = interior_map
        self.__floor_map = floor_map
        self.__desk_map = desk_map

    def populate_from_files(self, base_path):
        self.__populate_interior_map(os.path.join(base_path, "InteriorIdMap.json"), self.__interior_map)
        self.__populate_interior_map(os.path.join(base_path, "DeskPrefixMap.json"), self.__desk_map)
        self.__populate_floor_map(os.path.join(base_path, "InteriorFloorMap.json"))

    def __populate_interior_map(self, filename, mapping):
        if not os.path.isfile(filename):
            raise Exception("Cannot find %s, expected interior mapping of swallow locationIds -> WRLD interior Ids" % filename)
        with open(filename) as interior_id_json_file:
            interior_id_list_json = json.load(interior_id_json_file)
            for interior_id_json in interior_id_list_json:
                mapping[interior_id_json["locationId"]] = interior_id_json["interior_id"]

    def __populate_floor_map(self, filename):
        if not os.path.isfile(filename):
            raise Exception("Cannot find %s, expected floor mapping of swallow floor names to WRLD -> floor ids" % filename)        
        with open(filename) as interior_floor_json_file:
            interior_floor_list_json = json.load(interior_floor_json_file)
            for interior_id_floor_json in interior_floor_list_json:
                interior_floor_dict = {}

                for interior_floor_json in interior_id_floor_json["floors"]:
                    interior_floor_dict[interior_floor_json["floorName"]] = interior_floor_json["interior_floor"]

                self.__floor_map[interior_id_floor_json["interior_id"]] = interior_floor_dict

    def get_interior_from_location(self, location_id):
        return self.__interior_map[location_id]

    def contains_location(self, location_id):
        return location_id in self.__interior_map

    def get_desk_prefix_from_location(self, location_id):
        return self.__desk_map[location_id]    

    def contains_desk_prefix(self, location_id):
        return location_id in self.__desk_map

    def get_interior_floor_id(self, interior_id, floor_name):
        return self.__floor_map[interior_id][floor_name]

    def contains_floor(self, interior_id, floor_name):
        if interior_id in self.__floor_map:
            return floor_name in self.__floor_map[interior_id]
        return False

class DeskMapping:
    def __init__(self, desk_map={}):
        self.__desk_map = desk_map

    def populate_from_files(self, base_path):
        self.__populate_desk_map(os.path.join(base_path, "DeskPoiData.json"), self.__desk_map)

    def __populate_desk_map(self, filename, mapping):
        if not os.path.isfile(filename):
            raise Exception("Cannot find %s, expected desk mapping of desks space IDs" % filename)
        with open(filename) as desk_pois_json_file:
            desks_json = json.load(desk_pois_json_file)
            for desk_json in desks_json:
                if desk_json.has_key("title") and desk_json.has_key("user_data"):
                    try:
                        self.__desk_map[int(desk_json["user_data"]["assigned_person"])] = {"space_id":desk_json["user_data"]["space_id"], "desk_code":desk_json["title"], "indoor_id":desk_json["indoor_id"], "floor_id":desk_json["floor_id"]}
                    except Exception, e:
                        print desk_json

    def get_space_id_for_employee(self, employee_uuid):
        return self.__desk_map[int(employee_uuid)]["space_id"]

    def get_desk_code_for_employee(self, employee_uuid):
        return self.__desk_map[int(employee_uuid)]["desk_code"]

    def get_indoor_id_for_employee(self, employee_uuid):
        return self.__desk_map[int(employee_uuid)]["indoor_id"]

    def get_floor_id_for_employee(self, employee_uuid):
        return self.__desk_map[int(employee_uuid)]["floor_id"]      

    def contains_desk_for_employee(self, employee_uuid):
        return int(employee_uuid) in self.__desk_map

class SpaceIdToWGS84:
    def __init__(self, location_map={}):
        self.__location_map = location_map

    def populate_from_files(self, base_path):
        self.__populate_location_map(os.path.join(base_path, "LocationMap.json"))
        self.__populate_location_map(os.path.join(base_path, "DeskLocationMap.json"))

    def __populate_location_map(self, filename):
        if not os.path.isfile(filename):
            raise Exception("Cannot find %s, expected location map of swallow space IDs to swallow meeting rooms, run meetingroom-mapping-update.sh first")
        with open(filename) as location_json_file:
            location_list_json = json.load(location_json_file)
            for location_json in location_list_json:
                self.__location_map[str(location_json["spaceId"])] = {"lat": location_json["latitude_degrees"], "lon": location_json["longitude_degrees"]}

    def contains_space_id(self, space_id):
        return str(space_id) in self.__location_map

    def get_lat_lon_for_spaceid(self, space_id):
        return self.__location_map[str(space_id)]

class SpaceIdToHighlightId:
    def __init__(self, location_map={}):
        self.__location_map = location_map

    def populate_from_files(self, base_path):
        self.__populate_location_map(os.path.join(base_path, "LocationMap.json"))

    def __populate_location_map(self, filename):
        if not os.path.isfile(filename):
            raise Exception("Cannot find %s, expected location map of swallow space IDs to swallow meeting rooms, run meetingroom-mapping-update.sh first")
        with open(filename) as location_json_file:
            location_list_json = json.load(location_json_file)
            for location_json in location_list_json:
                self.__location_map[str(location_json["spaceId"])] = location_json["room"]

    def contains_highlight_id(self, space_id):
        return str(space_id) in self.__location_map

    def get_highlight_id_for_spaceid(self, space_id):
        return self.__location_map[str(space_id)]

class SpaceIdToImage:
    def __init__(self, location_map={}):
        self.__image_map = location_map

    def populate_from_files(self, base_path):
        self.__populate_image_map(os.path.join(base_path, "ImageMap.json"))

    def __populate_image_map(self, filename):
        if not os.path.isfile(filename):
            raise Exception("Cannot find %s, expected location map of swallow space IDs to swallow meeting rooms, run meetingroom-mapping-update.sh first")
        with open(filename) as image_json_file:
            image_list_json = json.load(image_json_file)
            for image_json in image_list_json:
                self.__image_map[str(image_json["spaceId"])] = image_json["image_filename"]

    def contains_image(self, space_id):
        return str(space_id) in self.__image_map

    def get_image_for_space_id(self, space_id):
        return self.__image_map[str(space_id)]        