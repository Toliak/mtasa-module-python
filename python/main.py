from mtasa.core import test
from mtasa import event

from flask import Flask

app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello World from FLASK!'


@event.add_event_handler('myEvent1')
def callback_function():
    try:
        app.run(host='0.0.0.0')
        test(0)
    except Exception:
        test(-1)
