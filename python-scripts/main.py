try:
    from something import some_function
    from mtasa.core import test

    print(test(99990))
    print(some_function(1,2))

except Exception as e:
    print(e)