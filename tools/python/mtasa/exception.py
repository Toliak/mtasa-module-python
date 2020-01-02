import traceback


def traceback_to_string(*args):
    traceback_list = traceback.format_exception(*args)
    return ''.join(traceback_list[1:-1])[:-1]
