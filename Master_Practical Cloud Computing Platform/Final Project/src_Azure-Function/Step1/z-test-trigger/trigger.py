# Passing Data into Our POST Request
import requests
import json

data = {'website' : 'This is website url',
        'name': 'Name',
        'timestamp': 'Time'}

resp = requests.post('http://localhost:7071/api/AzurePostReceiver',
                                             data=json.dumps(data))
print(resp)


