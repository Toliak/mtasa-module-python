REGISTERED_EVENTS = dict()


def add_event_handler(event_name: str):
    with open("mods/deathmatch/logs/python.log", "a") as f:
        f.write(str('add event') + event_name + '\n')

    global REGISTERED_EVENTS

    if event_name not in REGISTERED_EVENTS:
        REGISTERED_EVENTS[event_name] = []

    def decorator(callback):
        REGISTERED_EVENTS[event_name].append(callback)

        print(REGISTERED_EVENTS)
        return callback

    return decorator


def trigger_event(event_name: str):
    global REGISTERED_EVENTS

    with open("mods/deathmatch/logs/python.log", "a") as f:
        f.write(str(REGISTERED_EVENTS))
        f.write('\n')
        f.write(event_name)
        f.write('\n')
        f.write(str(event_name in REGISTERED_EVENTS))
        f.write('\n')

    if event_name in REGISTERED_EVENTS:
        REGISTERED_EVENTS[event_name][0]()
    else:
        pass
        # test('47362')

    return 1