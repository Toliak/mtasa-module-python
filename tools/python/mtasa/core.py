def call(function_name, return_args_amount, *args):
    from _mtasa_core import _mtasa_call

    return _mtasa_call(function_name, return_args_amount, *args)


def call_method(object, method_name, return_args_amount, *args):
    from _mtasa_core import _mtasa_call_method

    return _mtasa_call_method(object, method_name, return_args_amount, *args)
