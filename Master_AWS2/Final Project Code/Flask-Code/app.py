from flask import Flask, render_template, Response, jsonify, request
from flask import escape
from flask import render_template, url_for,redirect
import requests
import json
import socket


app = Flask(__name__)
LAMBDA_ENDPOINT_PIKACHIU_EXTRACT = 'https://hud4tgsv6yje5xlxgfjn5uaqnq0pmval.lambda-url.us-east-1.on.aws/'
LAMBDA_ENDPOINT_PIKACHIU_UPDATE = 'https://cbl5cdrvxzm6gf2ga4qk5p5xbq0wrbkq.lambda-url.us-east-1.on.aws/'


def get_ip():
    host_name = socket.gethostname()
    ip_address = socket.gethostbyname(host_name)
    return ip_address



@app.route('/')
def index():
    ip = get_ip()
    return render_template('index.html', ip=ip)



@app.route('/stress-test')
def stress_test():
    pass

@app.route('/update')
def update():
    ID = request.args['ID']
    UpdateCount = request.args['UpdateCount']
    print(ID, UpdateCount)
    response = requests.get(LAMBDA_ENDPOINT_PIKACHIU_UPDATE, params = {'ID': ID, 'UpdateCount': UpdateCount})
    #response = requests.get('https://cbl5cdrvxzm6gf2ga4qk5p5xbq0wrbkq.lambda-url.us-east-1.on.aws?ID=11177035&UpdateCount=1')



    lambda_data = response.json()
    return json.dumps(lambda_data)

@app.route('/get_data_popkachiu')
def GetDataPopKaChiu():
    response = requests.get(LAMBDA_ENDPOINT_PIKACHIU_EXTRACT)
    lambda_data = response.json()
    return json.dumps(lambda_data)



if __name__ == '__main__':
    # app.run(debug=True)
    app.run(host="0.0.0.0", port=80, debug=True)
