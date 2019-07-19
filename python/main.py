from mtasa.core import test
from mtasa import event

try:
    from something import some_function

    print(test(99990))
    print(some_function(1, 2))

except Exception as e:
    print(e)


@event.add_event_handler('myEvent1')
def callback_function():
    print(test(666))
