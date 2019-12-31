from mtasa.core import test
from mtasa import event


@event.add_event_handler('myEvent1')
def callback_function():
    try:
        test('0')
    except Exception:
        test('-1')
