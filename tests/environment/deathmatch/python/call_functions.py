import json

from mtasa import element


def accept_string(string):
    return type(string) == str


def accept_number(number):
    return type(number) == float


def accept_map(dictionary):
    return type(dictionary) == dict


def echo(*args):
    return args
