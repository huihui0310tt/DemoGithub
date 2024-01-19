import azure.functions as func
import logging

def main(req: func.HttpRequest, connectionInfo) -> func.HttpResponse:
    logging.info(connectionInfo)
    return func.HttpResponse(connectionInfo)