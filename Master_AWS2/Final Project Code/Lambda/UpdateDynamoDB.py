import json
import boto3
from botocore.exceptions import ClientError
from decimal import Decimal
from boto3.dynamodb.conditions import Key

def lambda_handler(event, context):
    table_name = 'Dynamo-PopKaChiu'

    dynamodb = boto3.resource('dynamodb')
    table = dynamodb.Table(table_name)

    try:
        # 從GET請求中獲取ID和Update數
        id = event.get('queryStringParameters', {}).get('ID')
        update_count = event.get('queryStringParameters', {}).get('UpdateCount')

        if id is None or update_count is None:
            return {
                'statusCode': 400,
                'body': json.dumps({
                    'status': 'error',
                    'message': 'Missing ID or UpdateCount in the request.'
                })
            }
        # id='11177035';update_count='2'
        # 檢查是否有這個ID
        response = table.query(
            KeyConditionExpression=Key('ID').eq(id)
        )

        items = response.get('Items', [])
        if items:
            # 如果有這個ID，將Update數加到現有值上
            existing_item = items[0]
            existing_count = int(existing_item.get('Sum', 0))
            new_count = existing_count + int(update_count)
            print(new_count)
            
            
            table.update_item(
                Key={'ID': id},
                UpdateExpression='SET #s = :val',
                ExpressionAttributeValues={':val': new_count}, 
                ExpressionAttributeNames={'#s': "Sum"}
            )
        else:
            # 如果沒有這個ID，創建新的項目
            table.put_item(
                Item={
                    'ID': id,
                    'Sum': int(update_count)
                }
            )

        return {
            'statusCode': 200,
            'body': json.dumps({
                'status': 'success',
                'message': 'Data updated successfully.'
            })
        }

    except ClientError as e:
        error_message = f"Error processing request: {e}"
        print(error_message)

        return {
            'statusCode': 500,
            'body': json.dumps({
                'status': 'error',
                'message': 'Error processing request.',
                'error_details': error_message
            })
        }
