import json
import boto3
from botocore.exceptions import ClientError
from decimal import Decimal


def lambda_handler(event, context):
    table_name = 'Dynamo-PopKaChiu'

    dynamodb = boto3.resource('dynamodb')
    results = {}
    try:
        table = dynamodb.Table(table_name)

        response = table.scan()

        items = response.get('Items', [])

        for item in items:
          
            results[item['ID']] = str(item['Sum'])
            print(item)

        return json.dumps(results)

    except ClientError as e:
        error_message = f"Error retrieving items from DynamoDB: {e}"
        print(error_message)

        return {
            'statusCode': 500,
            'body': json.dumps({
                'status': 'error',
                'message': 'Error retrieving items from DynamoDB.',
                'error_details': error_message
            })
        }
