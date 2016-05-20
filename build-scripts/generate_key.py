import os
import sys
import base64
import hashlib


def kdf(secret_key, salt):    
    dk = hashlib.pbkdf2_hmac('sha1', secret_key, salt, 10000, 128)
    return dk


if __name__ == '__main__':
    if len(sys.argv) is not 2:
        print "usage: generate_key.py <password>"
        sys.exit(-1)

    password = sys.argv[1]
    salt = os.urandom(24)
    derived_key = base64.standard_b64encode(kdf(password, salt))
    print derived_key
