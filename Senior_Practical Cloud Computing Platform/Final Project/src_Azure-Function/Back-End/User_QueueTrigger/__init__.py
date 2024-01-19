import logging
import json
import azure.functions as func
import random
from azure.cosmos import exceptions, CosmosClient, PartitionKey
from azure.storage.queue import  QueueClient, TextBase64DecodePolicy, TextBase64EncodePolicy


async def main(msg: func.QueueMessage, signalRMessages: func.Out[str]) -> None:
    logging.info('Python queue trigger function processed a queue item: %s',
                 msg.get_body().decode('utf-8'))

    req = msg.get_body().decode('utf-8')
    payload = json.loads(req)


    signalRMessages.set(json.dumps({
        'target': 'newMessage',
        'arguments': [ str(payload['id']) + ' : ' + str(payload['message'] ) ]
    }))
    if checkinstr(payload['message']) is True :
        Push_Msg(payload, queue_name='bot-input')

def Push_Msg(payload, queue_name):
    logging.info({payload["id"]})
    logging.info({payload["message"]})

    connect_str = "DefaultEndpointsProtocol=https;AccountName=10727211storagefunction;AccountKey=TjWwogu/SyP88UmG6lYktozivFAazS7+HsCfkea88JsZHRJkiC4oTCmcqeXOmi/JpuzFig9V+LdKE6eFMaLynQ==;EndpointSuffix=core.windows.net"
    queue_client = QueueClient.from_connection_string(
                        conn_str=connect_str, queue_name= queue_name,
                        message_encode_policy = TextBase64EncodePolicy(),
                        message_decode_policy = TextBase64DecodePolicy()
                    )
    queue_client.send_message(json.dumps(payload))


def checkinstr(content: str) -> bool:
        # result = 0 : 
        # 只是單純聊天內容
            # eg. "Hi", "Hello World!"
        
        # result = 1 : 
        # 初始化
            # eg. "!init"      
            
        # result = 2 :
        # 查看'自身'Point   
            # eg. "!point"

        # result = 3 : 
        # 賭Type1 ( "!賭 {real_num}" )
            # "!賭 1"   "!賭 100"   "!賭 1000"    
    
        # result = 4 : 
        # 賭Type2 ( "!賭 {real_num}%" )
            # "!賭 1%"   "!賭 100%"   "!賭 1000%" 

        # result = 5 :
        # 賭Type3 ("!賭 All")
        # All in
    """output payload
            payload:{"type": int,"content": int or NoneType}
    eg.     payload:{"type": 0, "content": None}  "Hi"
    eg.     payload:{"type": 1, "content": None}  !init
    eg.     payload:{"type": 2, "content": None}  !point
    eg.     payload:{"type": 3, "content": 100}  !gamble 100
    eg.     payload:{"type": 4, "content": 100}  !gamble 100%
    eg.     payload:{"type": 5, "content": None} !gamble All
    """
    chat_split = content.split()
    print(chat_split)


    if len(chat_split) >= 1 and chat_split[0] == '!init' :
        return True

    elif len(chat_split) >= 1 and chat_split[0] == '!point' :
        return True

    elif len(chat_split) >= 2 and chat_split[0] == '!gamble' :

        if chat_split[1].isdigit():
            return True

        elif chat_split[1][:-1].isdigit() and chat_split[1][-1] == '%' :
            return True

        elif chat_split[1] == 'All':
            return True
    
    return False