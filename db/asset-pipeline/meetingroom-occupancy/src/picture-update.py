import base64
import json
import hmac
import requests
import sys

from retrying import retry
from feedmappings import DeskMapping, SpaceIdToWGS84
from feedconfig import FeedConfig
import zeep
import hmactransport
import logging.config
from hmactransport import HmacTransport
from zeep import Client
import paramiko
from paramiko import SSHClient
from scp import SCPClient

EMPLOYEE_TAG = "person"
DEPARTMENT_TAG = "department"

def verify_employee(employee_json):
    return True

def gather_picture_ids(feedconfig, existing_pictures):
    with open("../generated/EmployeePoiData.json", "r") as f:
        employees_json = json.loads(f.read())
        for employee_json in employees_json:
            if "picture_id" in employee_json["user_data"]:
                picture_id = employee_json["user_data"]["picture_id"]
                if not int(picture_id) in existing_pictures:
                    yield picture_id

@retry
def get_picture_batch_call(feedconfig, ids):
    transport = HmacTransport()
    client = Client(feedconfig.soap_service_wsdl_url, transport=transport)
    response = client.service.GetImage(ids)
    return response

def gather_picture_batch(feedconfig, ids):
    transport = HmacTransport()
    client = Client(feedconfig.soap_service_wsdl_url, transport=transport)
    if len(ids) == 0:
        return
    response = get_picture_batch_call(feedconfig, ids)

    if response is not None and response != "":
        images_list = {}
        if type(response) is str:
            images_list = json.loads(response)
        else:
            images_list = zeep.helpers.serialize_object(response)
        if "images" in images_list:
            for image in images_list["images"]:
                yield image

def get_scp(feedconfig):
    scp_host = feedconfig.get_additional_arg("scp_host")
    scp_username = feedconfig.get_additional_arg("scp_username")
    scp_dest_path = feedconfig.get_additional_arg("scp_dest_path")
    scp_private_key_path = feedconfig.get_additional_arg("scp_private_key_path")
    if "C:/Program Files/Git" in scp_dest_path:
        scp_dest_path = scp_dest_path.replace("C:/Program Files/Git", "")

    print "scp_host: {0}".format(scp_host)
    print "scp_username: {0}".format(scp_username)
    print "scp_dest_path: {0}".format(scp_dest_path)
    print "scp_private_key_path: {0}".format(scp_private_key_path)

    ssh = SSHClient()
    ssh.load_system_host_keys()
    private_key = paramiko.RSAKey.from_private_key_file(scp_private_key_path)
    ssh.connect(scp_host, username=scp_username, pkey=private_key)

    # SCPCLient takes a paramiko transport as its only argument
    scp = SCPClient(ssh.get_transport())
    return scp

def scp_images_batch(feedconfig,images, scp):
    if len(images) == 0:
        return
    scp_dest_path = feedconfig.get_additional_arg("scp_dest_path")
    for image in images:
        scratch_path = "scratch.jpg"
        dest_path = "{0}/{1}.jpg".format(scp_dest_path, image["imageId"])
        with open(scratch_path, "wb") as f:
            f.write(image["data"])
        print "copy {0} => {1} {2}".format(scratch_path, dest_path, len(image["data"]))
        scp.put(scratch_path, dest_path)


def build_picture_filter():
    filter = {}
    with open("../pictures-ls", "r") as f:
        for line in f.readlines():
            filter[int(line.split(".")[0])] = True
    return filter


if __name__ == "__main__":
    additional_args=["scp_host=", "scp_username=", "scp_dest_path=", "scp_private_key_path="]
    feedconfig = FeedConfig.build(additional_args=additional_args)

    for additional_arg in additional_args:
        if not feedconfig.has_additional_arg(additional_arg.replace("=", "")):
            raise Exception("Must specify command line argument {0}".format(additional_arg))
    """
    logging.config.dictConfig({
        'version': 1,
        'formatters': {
            'verbose': {
                'format': '%(name)s: %(message)s'
            }
        },
        'handlers': {
            'console': {
                'level': 'DEBUG',
                'class': 'logging.StreamHandler',
                'formatter': 'verbose',
            },
        },
        'loggers': {
            'zeep.transports': {
                'level': 'DEBUG',
                'propagate': True,
                'handlers': ['console'],
            },
        }
    })
    """
    scp = get_scp(feedconfig)
    i = 0
    pictures = []
    existing_pictures = build_picture_filter()
    for picture in gather_picture_ids(feedconfig, existing_pictures):
        if picture > 0:
           pictures.append(picture)
        i += 1
        if i > 29:
           j = 0
           images = []
           for image in gather_picture_batch(feedconfig, pictures):
               images.append(image)
               j += 1
               if j > 10:
                  scp_images_batch(feedconfig, images, scp)
                  images = []
                  j = 0

           scp_images_batch(feedconfig, images, scp)

           i = 0
           pictures = []

    images = []
    for image in gather_picture_batch(feedconfig, pictures):
        images.append(image)
    scp_images_batch(feedconfig, images, scp)