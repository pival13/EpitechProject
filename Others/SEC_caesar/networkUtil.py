#! /usr/bin/env python3

from requests import Session
from base64 import b64encode

SESSION = None
HOST = "127.0.0.1"
PORT = 5000
URL = f"http://{HOST}:{PORT}/"

def getSession():
    global SESSION
    if SESSION:
        return SESSION
    else:
        SESSION = Session()
        return SESSION

def getBlockSize(endpoint: str):
    size = None
    indexSize = None
    for i in range(1, 64):
        resp = getSession().post(url=endpoint, data=b64encode(b"A"*i)).content
        if size == None: size = len(resp)
        elif indexSize == None and size != len(resp):
            indexSize = i
            size = len(resp)
        elif size != len(resp):
            return i - indexSize
    raise ValueError('Block size is greater than 32 bytes')
