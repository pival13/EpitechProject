#! /usr/bin/env python3

def pad(s: bytes, size: int) -> bytes:
    diff = size - len(s) % size
    if diff == size: return s
    return s + diff * bytes([diff])

def unpad(s: bytes) -> bytes:
    last = s[-1]
    if len(s) >= last and s[-last:] == last * bytes([last]):
        return s[:-last]
    return s