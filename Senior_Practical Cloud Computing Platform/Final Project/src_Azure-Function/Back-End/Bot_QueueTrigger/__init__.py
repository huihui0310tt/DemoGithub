import logging
import json
import azure.functions as func
import random
from azure.cosmos import exceptions, CosmosClient, PartitionKey
from azure.storage.queue import  QueueClient, TextBase64DecodePolicy, TextBase64EncodePolicy


def main(msg: func.QueueMessage, signalRMessages: func.Out[str]) -> None:
    logging.info('Python queue trigger function processed a queue item: %s',
                 msg.get_body().decode('utf-8'))
    
    payload = json.loads(msg.get_body().decode('utf-8'))

    # Push_Msg(payload)
    
    bot_payload = Check_Instruction(payload)

    # if bot_payload["message"] != None:
    #     Push_Msg(bot_payload)
    signalRMessages.set(json.dumps({
        'target': 'newMessage',
        'arguments': [ str(bot_payload['id']) + ' : ' + str(bot_payload['message'] ) ]
    }))


def Push_Msg(payload):
    logging.info({payload["id"]})
    logging.info({payload["message"]})

    connect_str = "DefaultEndpointsProtocol=https;AccountName=10727211storagefunction;AccountKey=TjWwogu/SyP88UmG6lYktozivFAazS7+HsCfkea88JsZHRJkiC4oTCmcqeXOmi/JpuzFig9V+LdKE6eFMaLynQ==;EndpointSuffix=core.windows.net"
    queue_client = QueueClient.from_connection_string(
                        conn_str=connect_str, queue_name='bot-output',
                        message_encode_policy = TextBase64EncodePolicy(),
                        message_decode_policy = TextBase64DecodePolicy()
                    )
    queue_client.send_message(json.dumps(payload))


def Check_Instruction(content) :
    """
    payload:{"id": "Phil", "message": "Hi"}
    """
    logging.info('Activity_Check_Instruction')

    parameter_init_point = 1000
    parameter_prob = 0.6  # 60%的成功率

    cosmosdb = COSMOSDB()
    bot_msg = None
    instr_payload = checkinstr(content["message"])
    logging.info({instr_payload["type"]})
    logging.info({instr_payload["content"]})

    if instr_payload["type"] == 0:
        pass # normal chat
    elif instr_payload["type"] == 1:
        cosmosdb.setter(content["id"], parameter_init_point)
        bot_msg = f'init successful'
    elif instr_payload["type"] == 2:
        bot_msg = str(content["id"]) + '\'s points is : ' + str(cosmosdb.getter(content["id"]))
    elif instr_payload["type"] == 3 or instr_payload["type"] == 4 or instr_payload["type"] == 5:

        try:
            user_point = cosmosdb.getter(content["id"])
            logging.info({user_point})
            if instr_payload["type"] == 3:
                bargain_point = instr_payload["content"]
            elif instr_payload['type'] == 4:
                bargain_point = int(user_point * (instr_payload["content"]/100) )
            elif instr_payload['type'] == 5:
                bargain_point = user_point

            if bargain_point > user_point:
                bot_msg = content["id"] + ", You only have " + str(user_point) + " points!"
            elif ( probability(parameter_prob)):
                cosmosdb.setter(content["id"], user_point + bargain_point )
                bot_msg = content["id"] + ' has won ' + str(bargain_point) + ' points!'
            else:
                cosmosdb.setter(content["id"], user_point - bargain_point )
                bot_msg = content["id"] + ' Failed!' + str(bargain_point) + ' points!(σ′▽‵)′▽‵)σ'

        except:
            bot_msg = content["id"] + " Please Init First!"



    return {"id": "bot", "message": bot_msg}
 
def probability(prob) -> bool:
    
    if random.random() <= prob :
        return True 
    else :
        return False


def checkinstr(content: str) -> int:
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
        return {"type": 1,"content" : None}

    elif len(chat_split) >= 1 and chat_split[0] == '!point' :
        return {"type": 2,"content" : None}

    elif len(chat_split) >= 2 and chat_split[0] == '!gamble' :

        if chat_split[1].isdigit():
            return {"type": 3,"content" : int(chat_split[1])}

        elif chat_split[1][:-1].isdigit() and chat_split[1][-1] == '%' :
            return {"type": 4,"content" : int(chat_split[1][:-1])}

        elif chat_split[1] == 'All':
            return {"type": 5, "content": None}
    
    return {"type": 0, "content": None}



class COSMOSDB:
    def __init__(self):
        self.endpoint = "https://10727211cosmosdb.documents.azure.com:443/"
        self.key = 'xMwp2clEKFxOAQx8il2Lls2M9WbDmEkRptwFSRmeG1Nc5fC7s6F1YIxWJpEbDZsfFApcLggFTivagL3dSnzkxQ=='
        self.client = CosmosClient(self.endpoint, self.key)
        self.database = self.client.get_database_client('FinalDataBase')
        self.container = self.database.get_container_client("FinalContainer")

    def getter(self, id: str) -> int:        

        items = list(self.container.query_items(
            query="SELECT * FROM r WHERE r.id=@id",
            parameters=[
                { "name":"@id", "value": id }
            ],
            enable_cross_partition_query=True
        ))

        if len(items) == 0 :
            raise Exception
        else:
            return items[0]['point']


    def setter(self, setter_id: str, setter_point: int) -> None:

        person_items = {'id': setter_id ,'point': setter_point}
        self.container.upsert_item(body=person_items)