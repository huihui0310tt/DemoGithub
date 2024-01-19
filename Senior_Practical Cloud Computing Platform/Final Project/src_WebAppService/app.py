import flask
from flask import Flask, escape, request
from flask import render_template, url_for,redirect
from azure.cosmos import  CosmosClient, PartitionKey
from azure.storage.queue import  QueueClient, TextBase64DecodePolicy, TextBase64EncodePolicy
import logging, json

app = Flask(__name__)

# @app.route("/<name>")
# def flask(name):
#     return "Hello "+name+"!, You cannot access this page."


@app.route('/')
def home():
    return redirect(url_for('login'))

@app.route('/login')
def login():
    return render_template('login.html')


@app.route('/get_cosmosdb', methods=['GET', 'POST'])
def get_cosmosdb():
    endpoint = "https://10727211cosmosdb.documents.azure.com:443/"
    key = 'xMwp2clEKFxOAQx8il2Lls2M9WbDmEkRptwFSRmeG1Nc5fC7s6F1YIxWJpEbDZsfFApcLggFTivagL3dSnzkxQ=='
    client = CosmosClient(endpoint, key)
    database = client.get_database_client('FinalDataBase')
    container = database.get_container_client("FinalContainer")

    items = list(container.query_items(
        query="SELECT r.id, r.point FROM r ORDER BY r.point DESC",
        enable_cross_partition_query=True
    ))


    for i in range(len(items)):
        items[i]['no'] = i+1    

    return json.dumps(items)



@app.route('/index',methods=['POST','GET'])
def index():
    if request.method =='POST':
        name=request.values['user']	
    return render_template('index.html', **locals())

@app.route('/index_getdata',methods=['POST','GET'])
def index_getdata():
    if request.method =='POST':
        chat_name = request.form.get("chat_name")
        todchat_content = request.form.get("chat_content")
        print('Name is :', chat_name)
        print('content is :', todchat_content)
        connect_str = "DefaultEndpointsProtocol=https;AccountName=10727211storagefunction;AccountKey=TjWwogu/SyP88UmG6lYktozivFAazS7+HsCfkea88JsZHRJkiC4oTCmcqeXOmi/JpuzFig9V+LdKE6eFMaLynQ==;EndpointSuffix=core.windows.net"

        queue_client = QueueClient.from_connection_string(
                        conn_str=connect_str, queue_name= 'user-input',
                        message_encode_policy = TextBase64EncodePolicy(),
                        message_decode_policy = TextBase64DecodePolicy()
                    )
        payload = {
            'id': chat_name,
            'message': todchat_content
        }
        
        queue_client.send_message(json.dumps(payload))

    return render_template('index.html')

def get_cosmosdb():
    endpoint = "https://10727211cosmosdb.documents.azure.com:443/"
    key = 'xMwp2clEKFxOAQx8il2Lls2M9WbDmEkRptwFSRmeG1Nc5fC7s6F1YIxWJpEbDZsfFApcLggFTivagL3dSnzkxQ=='
    client = CosmosClient(endpoint, key)
    database = client.get_database_client('FinalDataBase')
    container = database.get_container_client("FinalContainer")

    items = list(container.query_items(
        query="SELECT r.id, r.point FROM r ORDER BY r.point DESC",
        enable_cross_partition_query=True
    ))

    return items

# run app
if __name__ == "__main__":
    
    app.run(host='0.0.0.0', port=5000, debug=True)
    # app.run(host='127.0.0.1', port=5000, debug=True)