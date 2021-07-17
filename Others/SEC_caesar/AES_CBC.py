#! /usr/bin/env python3

from padder import pad, unpad
from AES_ECB import encryptAES_ECB, decryptAES_ECB
from xor import xor
from base64 import b64decode, b64encode

def encryptAES_CBC(decrypt: bytes, key: bytes, iv: bytes):
    if len(iv) != 16:
        raise ValueError('IV must have a 16 bytes block size.')
    decrypt = pad(decrypt, 16)
    encrypt = bytes()
    for i in range(int(len(decrypt) / 16)):
        block = xor(decrypt[i*16:(i+1)*16], iv if i == 0 else encrypt[(i-1)*16:i*16])
        encrypt += encryptAES_ECB(block, key)
    return encrypt

def decryptAES_CBC(encrypt: bytes, key: bytes, iv: bytes):
    if len(iv) != 16:
        raise ValueError('IV must have a 16 bytes block size.')
    if len(encrypt) % 16 != 0:
        raise ValueError('The encrypted data must be 16 bytes padded.')
    middecrypt = pad(decryptAES_ECB(encrypt, key), 16)
    decrypt = bytes()
    for i in range(int(len(encrypt) / 16)):
        decrypt += xor(middecrypt[i*16:(i+1)*16], iv if i == 0 else encrypt[(i-1)*16:i*16])
    return unpad(decrypt)


from sys import argv, stderr, exc_info

if __name__ == '__main__':
    if len(argv) != 2:
        print(f"Expected 1 argument, but got {len(argv)-1}", file=stderr)
        exit(84)
    try:
        with open(argv[1]) as f:
            content = f.read().split('\n')
            if len(content) == 4 and len(content[3]) == 0: content = content[:3]
            if len(content) != 3:
                print("Invalid file: expected exactly 3 lines", file=stderr)
                exit(84)
            print(b64encode(decryptAES_CBC(b64decode(content[2]), bytes.fromhex(content[0]), bytes.fromhex(content[1]))).decode())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)