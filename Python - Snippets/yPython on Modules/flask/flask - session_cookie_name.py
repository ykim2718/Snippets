"""
y, 2024.7.3
flask - session_cookie_name.py
"""

from flask import Flask
import types

app = Flask(__name__)
if False:
    app.session_cookie_name = 'y_'
else:
    app.config.update(SESSION_COOKIE_NAME='y_flask')
    setattr(Flask, 'session_cookie_name', property(lambda self: self.config['SESSION_COOKIE_NAME']))
print(f"{app.session_cookie_name=}")


@app.route("/")
def home():
    session_cookie_name = app.session_cookie_name
    # AttributeError: 'Flask' object has no attribute 'session_cookie_name'
    return f"The session cookie name is: {session_cookie_name}"


if __name__ == "__main__":
    app.run()
