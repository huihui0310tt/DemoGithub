import logging
import json
import azure.functions as func
from azure.cosmos import CosmosClient

class COSMOSDB:
    def __init__(self):
        self.endpoint = 'https://11177035finaldb.documents.azure.com:443/'
        self.key = '1GFLgFQBNkkPBwZ1H32sCo96teGNa53iu08JAwOkICcezFBw4Q3qz61IYekQxUAIFu1ZW37q9NkBACDbkdt4pQ=='
        self.client = CosmosClient(url=self.endpoint, credential=self.key)
        self.database = self.client.get_database_client("Receipt_DB")
        self.container = self.database.get_container_client("receipt")
        
    def setter(self, input_data):
        self.container.upsert_item(input_data)

    def getter(self, qid):
        QUERY = "SELECT * FROM receipt r WHERE r.id = @id"
        params = [dict(name="@id", value=qid)]
        items = self.container.query_items(
            query=QUERY, parameters=params, enable_cross_partition_query=True
        )

        for item in items:
            print(json.dumps(item, indent=True))

            id = item['id']
            SpecialPrize = item['SpecialPrize']
            GrandPrize = item['GrandPrize']
            FirstPrize1 = item['FirstPrize1']
            FirstPrize2 = item['FirstPrize2']
            FirstPrize3 = item['FirstPrize3']
            Additional_Sixth_Prize = str(item['Additional_Sixth_Prize'])
        return id, SpecialPrize, GrandPrize, FirstPrize1, FirstPrize2, FirstPrize3, Additional_Sixth_Prize

    
    def checkprize(self, InvoiceId, SpecialPrize, GrandPrize, FirstPrize1, FirstPrize2, FirstPrize3, Additional_Sixth_Prize):
        if InvoiceId == SpecialPrize:
            return 'SpecialPrize'
        elif InvoiceId == GrandPrize:
            return 'GrandPrize'
        elif InvoiceId == FirstPrize1 or InvoiceId == FirstPrize2 or InvoiceId == FirstPrize3:
            return 'FirstPrize'
        elif InvoiceId[1:] == FirstPrize1[1:] or InvoiceId[1:] == FirstPrize2[1:] or InvoiceId[1:] == FirstPrize3[1:]:
            return 'SecondPrize'
        elif InvoiceId[2:] == FirstPrize1[2:] or InvoiceId[2:] == FirstPrize2[2:] or InvoiceId[2:] == FirstPrize3[2:]:
            return 'ThirdPrize'        
        elif InvoiceId[3:] == FirstPrize1[3:] or InvoiceId[3:] == FirstPrize2[3:] or InvoiceId[3:] == FirstPrize3[3:]:
            return 'FourthPrize'        
        elif InvoiceId[4:] == FirstPrize1[4:] or InvoiceId[4:] == FirstPrize2[4:] or InvoiceId[4:] == FirstPrize3[4:]:
            return 'FifthPrize'
        elif InvoiceId[5:] == FirstPrize1[5:] or InvoiceId[5:] == FirstPrize2[5:] or InvoiceId[5:] == FirstPrize3[5:]:
            return 'SixthPrize'
        elif Additional_Sixth_Prize != 'None':
            if InvoiceId[5:] == Additional_Sixth_Prize:
                return 'SixthPrize'
            else: 
                return 'No Prize QQ'
        else:
            return 'No Prize QQ'




def main(req: func.HttpRequest, signalRMessages: func.Out[str]) -> None:
    # input request message body should be:
    # {
    #     Timestamp (string),
    #     Name (string),
    #     ReciptType(string), eg.('New', 'Traditional')
    #     qid(string), eg.('2021_03-04')
    #     InvoiceID ('59518187')
    # }
    logging.info('Python HTTP trigger function processed a request.')
    req_body = json.loads(req.get_body().decode('utf-8'))

    db = COSMOSDB() 
    id, SpecialPrize, GrandPrize, FirstPrize1, FirstPrize2, FirstPrize3, Additional_Sixth_Prize = db.getter(req_body['qid'])
    result = db.checkprize(req_body['InvoiceID'], SpecialPrize, GrandPrize, FirstPrize1, FirstPrize2, FirstPrize3, Additional_Sixth_Prize)

    message_to_be_print = {
        'Timestamp': req_body['Timestamp'],
        'Name': req_body['Name'],
        'ReciptType': req_body['ReciptType'],
        'InvoiceID': req_body['InvoiceID'],
        'Result': result
    }

    signalRMessages.set(json.dumps({
        'target': 'newMessage',
        'arguments': [ json.dumps(message_to_be_print) ]
    })
    )
   