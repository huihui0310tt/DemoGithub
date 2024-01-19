import json
import time
import urllib.request
import urllib.parse

from statistics import mean

def lambda_handler(event, context):
    # url = "http://finalelb-1316462922.us-east-1.elb.amazonaws.com/update"  # ?ID=1&UpdateCount=1
    url = "http://fargatelb-2135216444.us-east-1.elb.amazonaws.com//update"  # ?ID=1&UpdateCount=1

    num_requests = 500 
    response_times = []
    http_codes = {}

    for i in range(num_requests):
        user_id = f"test-{str(i).zfill(2)}"
        payload = {
            "ID": user_id,
            "UpdateCount": 1
        }
        
        url_get = url + '?ID=' + str(payload['ID']) + '&UpdateCount=' + str(payload['UpdateCount'])
        start_time = time.time()
        try:
            request = urllib.request.Request(url_get, method='GET')
            with urllib.request.urlopen(request) as response:
                response_code = response.getcode()
        except Exception as e:
            print(f"Error: {e}")
            response_code = 500  

        end_time = time.time()
        response_time = end_time - start_time

        response_times.append(response_time)
        http_codes[response_code] = http_codes.get(response_code, 0) + 1

    avg_response_time = mean(response_times)

    print(f"Average Response Time: {avg_response_time} seconds")
    print("HTTP Status Code Statistics:")
    for code, count in http_codes.items():
        print(f"  - {code}: {count} times")

    return {
        'statusCode': 200,
        'body': json.dumps('Stress test completed successfully!')
    }
