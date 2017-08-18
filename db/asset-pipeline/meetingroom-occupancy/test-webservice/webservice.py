import base64
import json
import hmac
#import logging


from datetime import datetime
from flask import Flask
from flask_spyne import Spyne
from spyne.protocol.soap import Soap11
from spyne.model.primitive import Unicode

from lxml import etree


SECRET_KEY = "secret"

SERVICE_URL = "/webservice/pythonservice"

REQUEST_HTTP_SUFFIX = "HTTP_"
REQUEST_TIME_UTC = "requestTimeUtc"
APP_ID = "appId"
DEBUG_DATA = "debug_Data"
REQUEST_KEY = "requestKey"


app = Flask(__name__)
spyne = Spyne(app)


#h = logging.StreamHandler()
#rl = logging.getLogger()
#rl.setLevel(logging.DEBUG)
#rl.addHandler(h)


class PythonSoapService(spyne.Service):
    __service_url_path__ = SERVICE_URL
    __in_protocol__ = Soap11(validator='lxml')
    __out_protocol__ = Soap11()

    @staticmethod
    def get_http_head_body(ctx):
        header = {}
        header[REQUEST_TIME_UTC] = ctx.transport.req[REQUEST_HTTP_SUFFIX + REQUEST_TIME_UTC.upper()]
        header[APP_ID] = ctx.transport.req[REQUEST_HTTP_SUFFIX + APP_ID.upper()]
        header[DEBUG_DATA] = ctx.transport.req[REQUEST_HTTP_SUFFIX + DEBUG_DATA.upper()]

        request_key = ctx.transport.req[REQUEST_HTTP_SUFFIX + REQUEST_KEY.upper()]
        body = "<?xml version='1.0' encoding='utf-8'?>\n" + etree.tostring(ctx.in_document, pretty_print=False)

        hmac_generator = hmac.new(SECRET_KEY)
        hmac_generator.update(body + "," + header[REQUEST_TIME_UTC] + "," + header[APP_ID])
        header[REQUEST_KEY] = base64.encodestring(hmac_generator.digest())[:-1]

        is_valid_key = header[REQUEST_KEY] == request_key

        return header, body, is_valid_key

    @spyne.rpc(Unicode, _returns=Unicode)
    def GetMeetingSpaceDetails(ctx, region_code):
        header, body, is_valid_key = PythonSoapService.get_http_head_body(ctx)
        if not is_valid_key:
            return json.dumps({"result": "invalid key"})

        if region_code == "EMEA":
            with open("test-webservice/App_Data/GetMeetingSpaceDetails.json") as meeting_room_json_file:
                return json.dumps(json.load(meeting_room_json_file))

        return json.dumps({"result": {"message": "", "rCode": 0}, "meetingSpaceDetails": []})

    @spyne.rpc(Unicode, _returns=Unicode)
    def GetMeetingSpaceOccupancyDetails(ctx, region_code):
        header, body, is_valid_key = PythonSoapService.get_http_head_body(ctx)
        if not is_valid_key:
            return json.dumps({"result": "invalid key"})

        if region_code == "EMEA":
            with open("test-webservice/App_Data/GetMeetingSpaceOccupancyDetails.json") as meeting_room_json_file:
                return json.dumps(json.load(meeting_room_json_file))

        return json.dumps({"result": {"message": "", "rCode": 0}, "meetingSpaceOccupancyDetails": []})


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=80)
