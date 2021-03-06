import json

from mtasa import core
from mtasa.element import Element


def accept_string(string):
    return type(string) == str


def accept_number(number):
    return type(number) == float


def accept_map(dictionary):
    return type(dictionary) == dict


def echo(*args):
    with open("mods/deathmatch/logs/python.log", "a") as f:
        f.write(str(args))
        f.write('\n')

    return args


def callback(*args):
    return core.call('callbackFromPython', 1, *args)


def throw_exception():
    raise RuntimeError("Test error")


def call_element_method_dimension(element):
    x = core.call_method(element, "getDimension", 1)
    return x
