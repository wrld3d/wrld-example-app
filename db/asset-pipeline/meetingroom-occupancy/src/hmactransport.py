import zeep
import hmac
import hashlib
import base64
import time
from zeep.wsdl.utils import etree_to_string
from lxml import etree, objectify

VERSION = "1.2"
VERSION_HEADER = "com.bloomberg.bas-serviceVersion"
REQUEST_TIME_UTC = "requestTimeUtc"
APP_ID = "appId"
DEBUG_DATA = "debug_Data"
REQUEST_KEY = "requestKey"
PUBLIC_APP_ID = 0
PRIVATE_APP_ID = 0
HMAC_SECRET = "secret"
HMAC_DEBUG = True

class HmacTransport(zeep.Transport):
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

    def post_xml(self, address, envelope, headers):
        headers[REQUEST_TIME_UTC] = str(int(time.time()))
        headers[APP_ID] = str(PUBLIC_APP_ID)
        headers[VERSION_HEADER] = VERSION

        # message is the default serialized SOAP request Body, just as zeep would do. We send this over the wire.
        message = etree_to_string(envelope)
        hmac_signature_message = HmacTransport.__prepare_hmac_request_message(envelope)
      
        hmac_input = hmac_signature_message + "," + str(headers[REQUEST_TIME_UTC]) + "," + str(PRIVATE_APP_ID)

        if HMAC_DEBUG:
            headers[DEBUG_DATA] = base64.b64encode(hmac_input)

        hmac_generator = hmac.new(HMAC_SECRET, msg=hmac_input, digestmod=hashlib.sha256)
        headers[REQUEST_KEY] = base64.b64encode(hmac_generator.digest())

        if HMAC_DEBUG:
            print "\n-----------"
            print address
            print "-----------"
            print hmac_signature_message
            print "-----------"
            print headers
            print "-----------\n"
        return super(HmacTransport, self).post(address, message, headers)