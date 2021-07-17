#! /usr/bin/env python3

from padder import pad, unpad
from Crypto.Cipher import AES
from base64 import b64decode, b64encode

def encryptAES_ECB(decrypt: bytes, key: bytes):
    crypter = AES.new(key, AES.MODE_ECB)
    encrypt = crypter.encrypt(pad(decrypt, 16))
    return encrypt

def decryptAES_ECB(encrypt: bytes, key: bytes):
    crypter = AES.new(key, AES.MODE_ECB)
    decrypt = crypter.decrypt(encrypt)
    return unpad(decrypt)


from sys import argv, stderr, exc_info

if __name__ == '__main__':
    if len(argv) != 2:
        print(f"Expected 1 argument, but got {len(argv)-1}", file=stderr)
        exit(84)
    try:
        with open(argv[1]) as f:
            content = f.read().split('\n')
            if len(content) == 3 and len(content[2]) == 0: content = content[:2]
            if len(content) != 2:
                print("Invalid file: expected exactly 2 lines", file=stderr)
                exit(84)
            for i in range(1, len(content)):
                print(b64encode(decryptAES_ECB(b64decode(content[1]), bytes.fromhex(content[0]))).decode())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)