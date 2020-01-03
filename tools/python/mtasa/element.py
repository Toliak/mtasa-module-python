class Element:
    _id = None


class Vehicle(Element):
    plate = "asdas"


class Root:
    pass


def construct_element_by_id_and_name(uid, name):
    element = Element()
    element._id = uid

    return element
