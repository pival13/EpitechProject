#! /usr/bin/env python3

import base64
import random
import string
import sys

from flask import Flask, request

import AES_ECB
import AES_CBC

app = Flask(__name__)


@app.route('/')
def index():
    return "Hello !"


@app.route('/challenge10', methods=['POST'])
def challenge10():
    print("CHALLENGE 10")
    param = request.get_data()
    print(param)
    param_orig = base64.b64decode(param)
    print(param_orig)
    appened = param_orig + b"ABCDEFGH"
    print(appened)
    encrypted = AES_ECB.encryptAES_ECB(appened, b"--CRYPTOGRAPHY--")
    print(encrypted)
    encoded = base64.b64encode(encrypted)
    print(encoded)
    return encoded


@app.route('/challenge11/new_profile', methods=['POST'])
def challenge11():
    print("CHALLENGE 11/new profile")
    param = request.get_data()
    print(param)
    param_orig = base64.b64decode(param)
    print(param_orig)
    profile = profile_for(param_orig)
    print(profile)
    encrypted = AES_ECB.encryptAES_ECB(profile, b"--CROPTYGRYPHA--")
    print(encrypted)
    encoded = base64.b64encode(encrypted)
    print(encoded)
    return encoded


@app.route('/challenge11/validate', methods=['POST'])
def challenge11_validate():
    print("CHALLENGE 11/validate")
    param = request.get_data()
    param_orig = base64.b64decode(param)
    print(param_orig)
    decrypted = AES_ECB.decryptAES_ECB(param_orig, b"--CROPTYGRYPHA--")
    print(decrypted)
    if decrypted.find(b"role=admin") != -1:
        print("good")
        token = b"TheTokenIsHere!"
        encoded = base64.b64encode(token)
        return encoded
    else:
        print("false")
        return "Acces Denied"


@app.route('/challenge12', methods=['POST'])
def challenge12():
    print("CHALLENGE 12")
    param = request.get_data()
    print(param)
    param_orig = base64.b64decode(param)
    print(param_orig)
    appened = param_orig + b"CURVE"
    print(appened)
    appened = random_string(random.randint(1, 20))+appened
    print(appened)
    encrypted = AES_ECB.encryptAES_ECB(appened, b"--CRYPTOGRAPHY--")
    print(encrypted)
    encoded = base64.b64encode(encrypted)
    print(encoded)
    return encoded


@app.route('/challenge13/encrypt', methods=['POST'])
def challenge13():
    print("CHALLENGE 13")
    param = request.get_data()
    print(param)
    param_orig = base64.b64decode(param)
    print(param_orig)
    param_str = param_orig.decode()
    print(param_str)
    replaced = param_str.replace(';', '')
    replaced = replaced.replace('=', '')
    print(replaced)
    byte_replace = replaced.encode()
    with_presuffix = b"title=Announcement;content="+byte_replace+b";type=jibberjabber;"
    print(with_presuffix)
    encrypted = AES_CBC.encryptAES_CBC(with_presuffix, b"--CROPTYGRYPHA--", b"--CROPTOPGENIAL-")
    print(encrypted)
    encoded = base64.b64encode(encrypted)
    print(encoded)
    return encoded


@app.route('/challenge13/decrypt', methods=['POST'])
def challenge13_decrypt():
    print("CHALLENGE 13/decrypt")
    param = request.get_data()
    param_orig = base64.b64decode(param)
    decrypted = AES_CBC.decryptAES_CBC(param_orig, b"--CROPTYGRYPHA--", b"--CROPTOPGENIAL-")
    print(decrypted)
    if decrypted.find(b";admin=true;") != -1:
        print("good")
        token = b"TheTokenIsHere!"
        encoded = base64.b64encode(token)
        return encoded
    else:
        print("false")
        return "Acces Denied"


@app.route('/challenge14/encrypt', methods=['GET'])
def challenge14_encrypt():
    print("CHALLENGE 14")
    byte_string = b"C3c13stL3M3ss4g3"
    key = b"Gigue en delire-"
    IV= b"---ELFAMOSOIV---"
    encrypted = AES_CBC.encryptAES_CBC(byte_string, key, IV)
    print(encrypted)
    print(IV)
    to_return = base64.b64encode(IV) + b"\n" + base64.b64encode(encrypted)
    print(to_return)
    return to_return


@app.route('/challenge14/decrypt', methods=['POST'])
def challenge14_decrypt():
    print("CHALLENGE 14")
    param = request.get_data()
    print(param)
    splitted = param.split(b'\n')
    print(splitted)
    '''param_decode = param.decode()
    print(param_decode)
    splitted = param_decode.splitlines()
    print(splitted)'''
    IV = base64.b64decode(splitted[0])
    ciphertext = base64.b64decode(splitted[1])
    key = b"Gigue en delire-"
    decrypted = AES_CBC.decryptAES_CBC(ciphertext, key, IV)
    print(decrypted)
    if len(decrypted) % 16 == 0 and len(decrypted) != 0:
        return "Bad padding", 500
    return "OK", 200


def profile_for(param: bytes):
    profile = b"email="+param+b"&uid=10&role=user"
    return profile


RANDOM_STRING = None
def random_string(length):
    global RANDOM_STRING
    if not RANDOM_STRING:
        RANDOM_STRING = ''.join(random.choice(string.ascii_lowercase + string.ascii_uppercase + string.digits) for i in range(length)).encode()
    return RANDOM_STRING


if __name__ == '__main__':
    app.run(debug=True)
