import base64
import json
import hmac
import requests
import sys

from feedmappings import DeskMapping, SpaceIdToWGS84
from feedconfig import FeedConfig
import zeep
import hmactransport
import logging.config
from hmactransport import HmacTransport
from zeep import Client

EMPLOYEE_TAG = "person"
DEPARTMENT_TAG = "department"


def badge_update(feedconfig, ids):
    transport = HmacTransport()
    client = Client(feedconfig.soap_service_wsdl_url, transport=transport)
    response = client.service.GetEmpBadgeDetails(ids)

    raise Exception(response)

if __name__ == "__main__":
    feedconfig = FeedConfig.build()

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

    ids = ['1']
    badge_update(feedconfig, ids)