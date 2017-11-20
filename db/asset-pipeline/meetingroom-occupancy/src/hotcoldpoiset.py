import requests

class HotColdPoiSet:
    def __init__(self, a_url, b_url, token, hot_url=None, cold_url=None, provider=requests, keys=[]):
        self.__a_url = a_url
        self.__b_url = b_url
        self.__token = token
        self.__hot = hot_url
        self.__cold = cold_url
        self.__provider = provider
        self.__api_keys = keys

    @property
    def hot(self):
        if self.__hot is None:
            raise Exception("Call determine_hot_cold first")
        return self.__hot

    @property
    def cold(self):
        if self.__cold is None:
            raise Exception("Call determine_hot_cold first")
        return self.__cold

    def determine_hot_cold(self):
        url = "{0}?token={1}".format(self.__a_url, self.__token)
        response = self.__provider.get(url)
        response_json = response.json()
        if len(response_json["api_key_permissions"]) > 0:
            self.__hot = self.__a_url
            self.__cold = self.__b_url
        else:
            self.__hot = self.__b_url
            self.__cold = self.__a_url

    def swap(self):
        url = "{0}?token={1}".format(self.hot, self.__token)
        response = self.__provider.get(url)
        for old_key_json in response.json()["api_key_permissions"]:
            old_key = old_key_json["app_api_key"]
            delete_url = "{0}/{1}?token={2}".format(self.hot, old_key, self.__token)
            self.__provider.delete(delete_url)
        for new_key in self.__api_keys:
            delete_url = "{0}/{1}?token={2}".format(self.hot, new_key, self.__token)
            create_url = "{0}?token={1}".format(self.cold, self.__token)
            self.__provider.delete(delete_url)
            self.__provider.post(create_url, json={"apikey": new_key}, verify=False)
        old_hot = self.__hot
        self.__hot = self.__cold
        self.__cold = old_hot