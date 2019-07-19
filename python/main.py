from mtasa.core import test

try:
    from something import some_function

    print(test(99990))
    print(some_function(1, 2))

except Exception as e:
    print(e)


def callback_function():
    print(test(666))