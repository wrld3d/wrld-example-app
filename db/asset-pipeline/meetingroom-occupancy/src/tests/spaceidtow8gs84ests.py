import unittest
from ddt import ddt, data
from tests.helpers import TestData
from feedmappings import SpaceIdToWGS84

@ddt
class SpaceIdToWGS84Tests(unittest.TestCase):
    TEST_LOCATION_MAP = {"231": {"lat": 51.512239328689, "lon": -0.090818687032888}, "232": {"lat": 51.5126901, "lon": -0.0917494}}

    @data(TestData(
        input=231,
        expects=True
        ),
        TestData(
        input=232,
        expects=True
        ),
        TestData(
        input=1442,
        expects=False
        )
    )
    def test_space_id_to_wgs84_contains_space_id(self, test_data):
        mapping = SpaceIdToWGS84(location_map=SpaceIdToWGS84Tests.TEST_LOCATION_MAP)
        self.assertEquals(mapping.contains_space_id(test_data.input), test_data.expects)

    @data(TestData(
        input=231,
        lat=51.512239328689,
        lon=-0.090818687032888
        ),
        TestData(
        input=232,
        lat=51.5126901,
        lon=-0.0917494
        )
    )
    def test_interior_mapping_get_interior_from_location(self, test_data):
        mapping = SpaceIdToWGS84(location_map=SpaceIdToWGS84Tests.TEST_LOCATION_MAP)
        self.assertEquals(mapping.get_lat_lon_for_spaceid(test_data.input)["lat"], test_data.lat)
        self.assertEquals(mapping.get_lat_lon_for_spaceid(test_data.input)["lon"], test_data.lon)

    def test_interior_mapping_populate_from_file_path_incorrect(self):
        mapping = SpaceIdToWGS84()
        self.assertRaises(Exception, mapping.populate_from_files, "invalid-path")

if __name__ == '__main__':
    unittest.main()