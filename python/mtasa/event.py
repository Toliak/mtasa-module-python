from mtasa.core import test

REGISTERED_EVENTS = dict()


def add_event_handler(event_name: str):
    if event_name not in REGISTERED_EVENTS:
        REGISTERED_EVENTS[event_name] = []

    def decorator(callback):
        REGISTERED_EVENTS[event_name].append(callback)

        print(REGISTERED_EVENTS)
        return callback

    return decorator


def trigger_event(event_name: str):
    if event_name in REGISTERED_EVENTS:
        REGISTERED_EVENTS[event_name][0]()
    else:
        test(47362)