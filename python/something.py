from mtasa import event
from mtasa.core import test


def some_function(a, b):
    return a - b


@event.add_event_handler('myEvent1')
def callback_function():
    test(5558)