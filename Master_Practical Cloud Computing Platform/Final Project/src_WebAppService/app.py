from flask import Flask, render_template, Response, jsonify, request
from flask import escape
from flask import render_template, url_for,redirect
import json


app = Flask(__name__)


global global_keep_result
global_keep_result = []
        

@app.route('/')
def index():
    global_keep_result.clear()
    return render_template('index.html')

@app.route('/getallresult', methods=['POST'])
def getallresult():
    # global_keep_result = []

    Timestamp = request.values.get('Timestamp')
    Name = request.values.get('Name')
    ReciptType = request.values.get('ReciptType')
    InvoiceID = request.values.get('InvoiceID')
    Result = request.values.get('Result')
    
    b = {'Timestamp': Timestamp,
         'Name' : Name,
         'ReciptType' : ReciptType,
         'InvoiceID' : InvoiceID,
         'Result' : Result
    } 

    global_keep_result.insert(0, b)

    return json.dumps(global_keep_result)


@app.route('/uploadImage', methods = ["POST", "GET"])
def uploadImage():
    imageData = request.values.get('imageData')
    print('Get!')
    return jsonify({'validate': 'ok'})


@app.route('/prize')
def prize():
    return render_template('prize.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True,port="5000")

