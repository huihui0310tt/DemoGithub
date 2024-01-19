import logging
from PIL import Image
import io
import azure.functions as func
import json
from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
from msrest.authentication import ApiKeyCredentials
from azure.core.credentials import AzureKeyCredential
from azure.ai.formrecognizer import DocumentAnalysisClient
import cv2
import base64
import numpy as np
import requests


def main(req: func.HttpRequest, signalRMessages: func.Out[str]) -> None:

    ENDPOINT = 'https://japaneast.api.cognitive.microsoft.com/'
    prediction_key = 'ff8af224aae64d97b0c06f456afc4010'
    project_id = '6b91c603-e121-45b9-8ae7-6a4f5a5abeee'
    model_name = 'Iteration3'
    Have_Identify = False

    endpoint = 'https://team1-final.cognitiveservices.azure.com/'
    key = 'b06b3151b3504dd4869d6ac77c2d66c7'

    logging.info('Python HTTP trigger function processed a request.')
    req_body = json.loads(req.get_body().decode('utf-8'))
    print(req_body)
    print(type(req_body))


    document_analysis_client = DocumentAnalysisClient(endpoint=endpoint, credential=AzureKeyCredential(key))

    credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(ENDPOINT, credentials )
    results = predictor.detect_image(project_id, model_name, base64.b64decode(req_body['imageData']))
    message_to_be_print = ''
#--------------------------------------
    for prediction in results.predictions:
        if prediction.probability > 0.90:
            print("\t" + prediction.tag_name +
                ": {0:.2f}%".format(prediction.probability * 100))
            # print(prediction)
            print()

        #  ########### CUT IMAGE ################
            img = cv2.imread(img_path)
            left = int(prediction.bounding_box.left * img.shape[1])
            top = int(prediction.bounding_box.top * img.shape[0])
            width = int((prediction.bounding_box.width + 0.1) * img.shape[1])
            height = int((prediction.bounding_box.height + 0.1) * img.shape[0])
            cropped = img[top:height, left:width]
            imgb = cv2.imencode('.jpg', cropped)[1].tobytes()

        # ################## FOR RECOGNIZE ###############

            poller = document_analysis_client.begin_analyze_document(
                    "Invoice3", document=imgb, locale="en-US"
                )
            invoices = poller.result()

            invoice = invoices.documents[0]
            Invoice_number = invoice.fields.get("Invoice number")
            if Invoice_number:
                number = Invoice_number.value
                print("Invoice_number:", Invoice_number.value)

        # Invoice Date
            Invoice_Date = invoice.fields.get("Invoice Date")
            if Invoice_Date:
                date = Invoice_Date.value
                print("Invoice Date", Invoice_Date.value)

            numberT = ''.join(x for x in number if x.isdigit())
            print(numberT)
            dateT = ''.join(x for x in date if x.isdigit())
            dateC = dateT[0:6]
            print(dateC[0:4])
            print(dateC[4:6])

            if dateC[0:4] == '2021':
                sendid = '2021'
            else:
                sendid = '2022'

            if dateC[4:6] == '01' or dateC[4:6] == '02':
                sendid = sendid + '_01-02'
            elif dateC[4:6] == '03' or dateC[4:6] == '04':
                sendid = sendid + '_03-04'
            elif dateC[4:6] == '05' or dateC[4:6] == '06':
                sendid = sendid + '_05-06'
            elif dateC[4:6] == '07' or dateC[4:6] == '08':
                sendid = sendid + '_07-08'
            elif dateC[4:6] == '09' or dateC[4:6] == '10':
                sendid = sendid + '_09-10'
            elif dateC[4:6] == '11' or dateC[4:6] == '12':
                sendid = sendid + '_11-12'


            print(sendid)

            data = {'Timestamp' : '20221535',
                    'Name': 'Name3',
                    'ReciptType': 'New',
                    'qid': sendid,
                    'InvoiceID': numberT}
            requests.post('https://11177035analyze.azurewebsites.net/api/httptrigger', data=json.dumps(data))


#--------------------------------------

    if Have_Identify:
        signalRMessages.set(json.dumps({
            'target': 'newMessage',
            'arguments': [ message_to_be_print ]
        }))
    else:
        signalRMessages.set(json.dumps({
            'target': 'newMessage',
            'arguments': [ 'No probability > 50%, please try again.' ]
        }))
