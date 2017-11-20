from flask import Flask
from flask import request
from flask import render_template
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/test_program', methods=['POST'])
def test_program():
    return request.form['code']
