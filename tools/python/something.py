try:
    from mtasa import event
    from mtasa.core import test

    # _mtasa_core.test(111)


    def some_function(a, b):
        return a - b


    @event.add_event_handler('myEvent1')
    def callback_function():
        test(5558)

except Exception as e:
    with open("mods/deathmatch/logs/python.log", "w") as f:
        f.write(str(e))