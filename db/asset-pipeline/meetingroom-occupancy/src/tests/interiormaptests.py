import unittest
from ddt import ddt, data
from tests.helpers import TestData
from feedmappings import InteriorMapping

@ddt
class InteriorMapTests(unittest.TestCase):
    TEST_DATA_INTERIOR_MAP = {"GB025":"swallow_lon_38finsbury","GB006":"swallow_lon_citygatehouse","GB012":"swallow_lon_50finsbury","GB032":"swallow_lon_parkhouse","GB033":"swallow_lon_wallbrooksquare","WPH01":"westport_house"}
    TEST_DATA_DESK_MAP = {"GB025":"38FS","GB006":"CGH","GB012":"FS","GB032":"PH","GB033":"3QVS-","WPH01":"WPH"}
    TEST_FLOOR_MAP = {"swallow_lon_38finsbury":{"00 - Ground Floor":1,"01 - First Floor":2}}

    @data(TestData(
        input="GB025",
        expects=True
        ),
        TestData(
        input="GB006",
        expects=True
        ),
        TestData(
        input="GB012",
        expects=True
        ),
        TestData(
        input="GB032",
        expects=True
        ),
        TestData(
        input="GB033",
        expects=True
        ),
        TestData(
        input="WPH01",
        expects=True
        ),
        TestData(
        input="GB123",
        expects=False
        )
    )
    def test_interior_mapping_contains_location(self, test_data):
        mapping = InteriorMapping(interior_map=InteriorMapTests.TEST_DATA_INTERIOR_MAP)
        self.assertEquals(mapping.contains_location(test_data.input), test_data.expects)

    @data(TestData(
        input="GB025",
        expects="swallow_lon_38finsbury"
        ),
        TestData(
        input="GB006",
        expects="swallow_lon_citygatehouse"
        ),
        TestData(
        input="GB012",
        expects="swallow_lon_50finsbury"
        ),
        TestData(
        input="GB032",
        expects="swallow_lon_parkhouse"
        ),
        TestData(
        input="GB033",
        expects="swallow_lon_wallbrooksquare"
        ),
        TestData(
        input="WPH01",
        expects="westport_house"
        )
    )
    def test_interior_mapping_get_interior_from_location(self, test_data):
        mapping = InteriorMapping(interior_map=InteriorMapTests.TEST_DATA_INTERIOR_MAP)
        self.assertEquals(mapping.get_interior_from_location(test_data.input), test_data.expects)

    @data(TestData(
        input="GB025",
        expects=True
        ),
        TestData(
        input="GB006",
        expects=True
        ),
        TestData(
        input="GB012",
        expects=True
        ),
        TestData(
        input="GB032",
        expects=True
        ),
        TestData(
        input="GB033",
        expects=True
        ),
        TestData(
        input="WPH01",
        expects=True
        ),
        TestData(
        input="GB123",
        expects=False
        )
    )
    def test_interior_mapping_contains_desk_prefix(self, test_data):
        mapping = InteriorMapping(desk_map=InteriorMapTests.TEST_DATA_DESK_MAP)
        self.assertEquals(mapping.contains_desk_prefix(test_data.input), test_data.expects)

    @data(TestData(
        input="GB025",
        expects="38FS"
        ),
        TestData(
        input="GB006",
        expects="CGH"
        ),
        TestData(
        input="GB012",
        expects="FS"
        ),
        TestData(
        input="GB032",
        expects="PH"
        ),
        TestData(
        input="GB033",
        expects="3QVS-"
        ),
        TestData(
        input="WPH01",
        expects="WPH"
        )
    )
    def test_interior_mapping_get_interior_from_location(self, test_data):
        mapping = InteriorMapping(desk_map=InteriorMapTests.TEST_DATA_DESK_MAP)
        self.assertEquals(mapping.get_desk_prefix_from_location(test_data.input), test_data.expects)        

    @data(TestData(
        input_interior="swallow_lon_38finsbury",
        input_floor_name="00 - Ground Floor",
        expects=True
        ),
        TestData(
        input_interior="swallow_lon_38finsbury",
        input_floor_name="01 - First Floor",
        expects=True
        ),
        TestData(
        input_interior="swallow_lon_38finsbury",
        input_floor_name="02 - Second Floor",
        expects=False
        ),
        TestData(
        input_interior="unknown_interior",
        input_floor_name="03 - Third Floor",
        expects=False
        )
    )
    def test_interior_mapping_contains_floor(self, test_data):
        mapping = InteriorMapping(floor_map=InteriorMapTests.TEST_FLOOR_MAP)
        self.assertEquals(mapping.contains_floor(test_data.input_interior, test_data.input_floor_name), test_data.expects)

    @data(TestData(
        input_interior="swallow_lon_38finsbury",
        input_floor_name="00 - Ground Floor",
        expects=1
        ),
        TestData(
        input_interior="swallow_lon_38finsbury",
        input_floor_name="01 - First Floor",
        expects=2
        )
    )
    def test_interior_mapping_get_interior_floor_id(self, test_data):
        mapping = InteriorMapping(floor_map=InteriorMapTests.TEST_FLOOR_MAP)
        self.assertEquals(mapping.get_interior_floor_id(test_data.input_interior, test_data.input_floor_name), test_data.expects)

    def test_interior_mapping_populate_from_file_path_incorrect(self):
        mapping = InteriorMapping()
        self.assertRaises(Exception, mapping.populate_from_files, "invalid-path")

if __name__ == '__main__':
    unittest.main()