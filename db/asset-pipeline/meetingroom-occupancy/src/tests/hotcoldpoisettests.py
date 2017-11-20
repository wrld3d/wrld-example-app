import unittest
import requests_mock
from hotcoldpoiset import HotColdPoiSet

class HotColdPoiSetTests(unittest.TestCase):
    def test_hot_cold_poi_set_properties(self):
        # Arrange
        hot = "http://londwayfapp01/search/v1.1/poisets/5"
        cold = "http://londwayfapp01/search/v1.1/poisets/6"

        # Act
        hot_cold = HotColdPoiSet(hot, cold, "G5MONCictZXp8hZLJvAvS6xGZo5EluaFKKil5CEfkBRsu2CA5XihAJ3x1NSbysNBrSqbO6pl92LSEjFq", hot, cold)

        # Assert
        self.assertEquals(hot_cold.hot, hot)
        self.assertEquals(hot_cold.cold, cold)

    @requests_mock.mock()
    def test_hot_cold_poi_set_determination(self, m):
        # Arrange
        hot = "http://londwayfapp01/search/v1.1/poisets/5"
        cold = "http://londwayfapp01/search/v1.1/poisets/6"
        hot_cold = HotColdPoiSet(hot, cold, "G5MONCictZXp8hZLJvAvS6xGZo5EluaFKKil5CEfkBRsu2CA5XihAJ3x1NSbysNBrSqbO6pl92LSEjFq")

        # Mock
        m.get(hot, json={'id':1, 'api_key_permissions':['k1']})
        m.get(cold, json={'id':2, 'api_key_permissions':[]})

        # Act
        hot_cold.determine_hot_cold()

        # Assert
        self.assertEquals(hot_cold.hot, hot)
        self.assertEquals(hot_cold.cold, cold)

    @requests_mock.mock()
    def test_hot_cold_poi_set_swapping(self, m):
        # Arrange
        hot = "http://londwayfapp01/search/v1.1/poisets/5"
        cold = "http://londwayfapp01/search/v1.1/poisets/6"
        hot_cold = HotColdPoiSet(hot, cold, "G5MONCictZXp8hZLJvAvS6xGZo5EluaFKKil5CEfkBRsu2CA5XihAJ3x1NSbysNBrSqbO6pl92LSEjFq", hot, cold, keys=["a"])

        m.get(hot, json={'id':1, 'api_key_permissions':['k1']})
        m.delete("{0}/k1".format(hot))
        m.post("{0}".format(cold))

        # Act
        hot_cold.swap()

        # Assert
        self.assertEquals(hot_cold.hot, cold)
        self.assertEquals(hot_cold.cold, hot)

if __name__ == '__main__':
    unittest.main()