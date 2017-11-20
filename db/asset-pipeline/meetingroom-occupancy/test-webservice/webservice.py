import base64
import json
import hmac
import os.path
import hashlib
from datetime import datetime
from flask import Flask
from flask_spyne import Spyne
from spyne.protocol.soap import Soap11
from spyne.model.primitive import Unicode, Integer
from spyne.model.complex import Iterable

from lxml import etree, objectify


SECRET_KEY = "secret"

SERVICE_URL = "/webservice/pythonservice"

REQUEST_HTTP_SUFFIX = "HTTP_"
REQUEST_TIME_UTC = "requestTimeUtc"
APP_ID = "appId"
PRIVATE_APP_ID = "Eegeo.RsrvMeetingRoom"
DEBUG_DATA = "debug_Data"
REQUEST_KEY = "requestKey"
HMAC_SECRET = "1234"

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
    def __prepare_hmac_request_message(envelope):
        # This seralized 'envelope' is a full SOAP request, with an XML tag, SOAP Envelope, SOAP Body, and fully namespaced SOAP request:
        #
        # """
        # <?xml version='1.0' encoding='utf-8'?>
        # <soap-env:Envelope xmlns:soap-env="http://schemas.xmlsoap.org/soap/envelope/">
        #   <soap-env:Body>
        #      <ns0:GetMeetingSpaceOccupancyDetails xmlns:ns0="tns">
        #        <ns0:regionCode>EMEA</ns0:regionCode>
        #      </ns0:GetMeetingSpaceOccupancyDetails>
        #   </soap-env:Body>
        # </soap-env:Envelope>
        # """
        #
        # The HMAC signature for Bloomberg requires just the SOAP body with no namespacing, i.e.:
        # """
        # <GetMeetingSpaceOccupancyDetails><regionCode>EMEA</regionCode></GetMeetingSpaceOccupancyDetails>
        # """
        #
        # The following few lines uses the python lxml library to strip the namespaces, and serialize only the SOAP Body ready for inclusion in the HMAC hash
        for elem in envelope.getiterator():
            if not hasattr(elem.tag, 'find'): continue 
            i = elem.tag.find('}')
            if i >= 0:
                elem.tag = elem.tag[i+1:]
        objectify.deannotate(envelope, cleanup_namespaces=True)
        return etree.tostring(envelope[0][0], pretty_print=False, xml_declaration=False, encoding='utf-8')

    @staticmethod
    def __get_http_head_body(ctx):
        header = {}
        header[REQUEST_TIME_UTC] = ctx.transport.req[REQUEST_HTTP_SUFFIX + REQUEST_TIME_UTC.upper()]
        header[APP_ID] = ctx.transport.req[REQUEST_HTTP_SUFFIX + APP_ID.upper()]
        header[DEBUG_DATA] = ctx.transport.req[REQUEST_HTTP_SUFFIX + DEBUG_DATA.upper()]

        header[REQUEST_KEY] = ctx.transport.req[REQUEST_HTTP_SUFFIX + REQUEST_KEY.upper()]
        hmac_signature_message = PythonSoapService.__prepare_hmac_request_message(ctx.in_document)

        hmac_input = hmac_signature_message + "," + str(header[REQUEST_TIME_UTC]) + "," + str(PRIVATE_APP_ID)
        hmac_generator = hmac.new(HMAC_SECRET, msg=hmac_input, digestmod=hashlib.sha256)
        request_key = base64.b64encode(hmac_generator.digest())

        #raise Exception("our request key {0}, their request key: {1}, our message: {2}, their message: {3}".format(request_key, header[REQUEST_KEY], hmac_input, header[DEBUG_DATA]))

        is_valid_key = header[REQUEST_KEY] == request_key

        return header, hmac_signature_message, is_valid_key

    @spyne.rpc(Unicode, _returns=Unicode)
    def GetMeetingSpaceDetails(ctx, regionCode):
        header, body, is_valid_key = PythonSoapService.__get_http_head_body(ctx)
        if not is_valid_key:
            return json.dumps({"result": "invalid key"})

        if regionCode == "EMEA":
            with open("test-webservice/App_Data/GetMeetingSpaceDetails.json") as meeting_room_json_file:
                return json.dumps(json.load(meeting_room_json_file))

        return json.dumps({"result": {"message": "", "rCode": 0}, "meetingSpaceDetails": []})

    @spyne.rpc(Unicode, _returns=Unicode)
    def GetMeetingSpaceOccupancyDetails(ctx, regionCode):
        header, body, is_valid_key = PythonSoapService.__get_http_head_body(ctx)
        if not is_valid_key:
            return json.dumps({"result": "invalid key"})

        if regionCode == "EMEA":
            with open("test-webservice/App_Data/GetMeetingSpaceOccupancyDetails.json") as meeting_room_json_file:
                return json.dumps(json.load(meeting_room_json_file))

        return json.dumps({"result": {"message": "", "rCode": 0}, "meetingSpaceOccupancyDetails": []})

    @spyne.rpc(Unicode, _returns=Unicode)
    def GetDeskDetails(ctx, regionCode):
        header, body, is_valid_key = PythonSoapService.__get_http_head_body(ctx)
        if not is_valid_key:
            return json.dumps({"result": "invalid key"})

        if regionCode == "EMEA":
            with open("test-webservice/App_Data/GetDeskDetails.json") as desk_json_file:
                return json.dumps(json.load(desk_json_file))

        return json.dumps({"result": {"message": "", "rCode": 0}, "deskDetails": []})

    @spyne.rpc(Unicode, _returns=Unicode)
    def GetEmployeeDetails(ctx, regionCode):
        header, body, is_valid_key = PythonSoapService.__get_http_head_body(ctx)
        if not is_valid_key:
            return json.dumps({"result": "invalid key"})

        if regionCode == "EMEA":
            with open("test-webservice/App_Data/GetEmployeeDetails.json") as employee_json_file:
                return json.dumps(json.load(employee_json_file))

        return json.dumps({"result": {"message": "", "rCode": 0}, "employeeDetails": []})

    @spyne.rpc(Integer.customize(max_occurs=10), _returns=Unicode)        
    def GetImage(ctx, image_ids):
        header, body, is_valid_key = PythonSoapService.__get_http_head_body(ctx)
        if not is_valid_key:
            return json.dumps({"result": "invalid key"})

        images = []
        for image_id in image_ids:
            image_path = os.path.join("../src/poidb-builder/assets/images/employee/", "{0}.jpg".format(image_id))
            if os.path.isfile(image_path):
                with open(image_path, "rb") as f:
                    image_data = base64.b64encode(f.read())
                    images.append({"imageId":image_id, "data":image_data})

        return json.dumps({"result": {"message": "", "rCode": 0}, "images": images})

    @spyne.rpc(Integer.customize(max_occurs=10), _returns=Unicode)        
    def GetEmpBadgeDetails(ctx, UUIDs):
        badge_infos = []
        for employee_uuid in UUIDs:
            badge_infos.append({"uuid":int(employee_uuid), "Badge":"IN:3QVS 14:46 10\/13", "BadgeInOut":1, "LogInStatus":2, "OUTStatus":""})
        return json.dumps({"result": {"message": "", "rCode": 0}, "empBadgeDetails": badge_infos})
    

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)
