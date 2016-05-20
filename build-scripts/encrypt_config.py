import getopt
import os
import sys
import traceback
import json
import base64
import hashlib
import hmac


def __encrypt_decrypt_xor(message, key):
    result = []
    key_len = len(key)
    for i in range(len(message)):
        result.append(ord(message[i]) ^ ord(key[i % key_len]))

    return ''.join(chr(c) for c in result)


def __encrypted_base64(message, key):
    return base64.standard_b64encode(__encrypt_decrypt_xor(message, key))


def __decrypted_base64(base64_encoded, key):
    return __encrypt_decrypt_xor(base64.standard_b64decode(base64_encoded), key)


def encrypt_config(input_config_path, output_config_path, secret_key):
    
    if not input_config_path:
        print '\nError: input_config_path not defined.\n'
        print_usage()
        sys.exit(1)

    if not output_config_path:
        print '\nError: output_config_path not defined.\n'
        print_usage()
        sys.exit(1)

    if not secret_key:
        print '\nError: secret_key not defined.\n'
        print_usage()
        sys.exit(1)

    if not os.path.exists(input_config_path):
        raise ValueError('path not found: ' + input_config_path)

    if os.path.exists(output_config_path):
        raise ValueError('output already exists: ' + output_config_path)

    with open(output_config_path, 'w') as output_config_file:
        with open(input_config_path, 'r') as input_config_file:

            config_json = json.load(input_config_file)

            plain_text = json.dumps(config_json)
            cipher_text = __encrypted_base64(plain_text, secret_key)

            digest = hmac.new(secret_key, plain_text, hashlib.sha1).hexdigest()

            result_json = {'Encrypted': cipher_text, 'HMAC_SHA1': digest}

            json.dump(result_json, output_config_file, indent=4)

    return


def print_usage():
    print 'Usage: '
    print 'encrypt_config.py -i <input_config_path> -o <output_config_path> -s <secret_key>'
    print 'encrypt_config.py [-h | -help]'
    print
    print 'Options: '
    print '-i --input_config_path       Path to input config json file'
    print '-o --output_config_path      Path to output config json file'
    print '-s --secret_key              encryption secret key'


def get_args(argv):
    input_config_path = ''
    output_config_path = ''
    secret_key = ''
    try:
        opts, args = getopt.getopt(argv, "hi:o:s:", ["input_config_path=", "output_config_path=", "secret_key="])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print_usage()
            sys.exit()
        elif opt in ("-i", "--input_config_path"):
            input_config_path = arg
        elif opt in ("-o", "--output_config_path"):
            output_config_path = arg
        elif opt in ("-s", "--secret_key"):
            secret_key = arg

    return input_config_path, output_config_path, secret_key

if __name__ == '__main__':
    try:
        input_config_path_param, output_config_path_param, secret_key_param = get_args(sys.argv[1:])

        print 'input_config_path: ' + input_config_path_param
        print 'output_config_path: ' + output_config_path_param
        print 'secret_key: ' + secret_key_param

        decoded_secret_key = base64.standard_b64decode(secret_key_param)

        encrypt_config(input_config_path_param, output_config_path_param, decoded_secret_key)
    except Exception as e:
        _, _, exc_traceback = sys.exc_info()
        print(str(traceback.format_exc(exc_traceback)))
        sys.exit(1)
