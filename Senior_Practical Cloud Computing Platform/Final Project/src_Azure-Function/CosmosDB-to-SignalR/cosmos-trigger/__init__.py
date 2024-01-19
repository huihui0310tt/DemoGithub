import logging
import json
import azure.functions as func


def main(documents: func.DocumentList, signalRMessages: func.Out[str]) -> func.HttpResponse:
    logging.info('Trigger')
    signalRMessages.set(json.dumps({
    'target': 'newMessage',
    'arguments': [ str(documents) ]
    }))


