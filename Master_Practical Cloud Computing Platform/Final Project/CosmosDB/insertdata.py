import os
import json
from azure.cosmos import CosmosClient, PartitionKey


class COSMOSDB:
    def __init__(self):
        self.endpoint = 'https://11177035finaldb.documents.azure.com:443/'
        self.key = '1GFLgFQBNkkPBwZ1H32sCo96teGNa53iu08JAwOkICcezFBw4Q3qz61IYekQxUAIFu1ZW37q9NkBACDbkdt4pQ=='
        self.client = CosmosClient(url=self.endpoint, credential=self.key)
        self.database = self.client.get_database_client("Receipt_DB")
        self.container = self.database.get_container_client("receipt")

    def setter(self, input_data):
        self.container.upsert_item(input_data)


# endpoint = 'https://11177035finaldb.documents.azure.com:443/'
# key = '1GFLgFQBNkkPBwZ1H32sCo96teGNa53iu08JAwOkICcezFBw4Q3qz61IYekQxUAIFu1ZW37q9NkBACDbkdt4pQ=='

# client = CosmosClient(url=endpoint, credential=key)
# database = client.create_database_if_not_exists(id="Receipt_DB")
# container = database.create_container_if_not_exists(
#     id="receipt", partition_key=PartitionKey(path="/id"), offer_throughput=600
# )

a = COSMOSDB()

newItem = [
    {"id": "2022_09-10",    "SpecialPrize": "11174120",    "GrandPrize": "59276913",    "FirstPrize1": "18079936",    "FirstPrize2": "20591738",    "FirstPrize3": "64500205",    "Additional_Sixth_Prize": "None"},
    {"id": "2022_07-08",    "SpecialPrize": "05701942",    "GrandPrize": "97718570",    "FirstPrize1": "88400675",    "FirstPrize2": "73475574",    "FirstPrize3": "53038222",    "Additional_Sixth_Prize": "None"},
    {"id": "2022_05-06",    "SpecialPrize": "46438476",    "GrandPrize": "54769852",    "FirstPrize1": "17858097",    "FirstPrize2": "94045042",    "FirstPrize3": "05236836",    "Additional_Sixth_Prize": "None"},
    {"id": "2022_03-04",    "SpecialPrize": "32220402",    "GrandPrize": "99194290",    "FirstPrize1": "16525386",    "FirstPrize2": "28467179",    "FirstPrize3": "27854976",    "Additional_Sixth_Prize": "None"},
    {"id": "2022_01-02",    "SpecialPrize": "18927486",    "GrandPrize": "82050976",    "FirstPrize1": "46596321",    "FirstPrize2": "75704516",    "FirstPrize3": "48632657",    "Additional_Sixth_Prize": "None"},
    {"id": "2021_11-12",    "SpecialPrize": "31150905",    "GrandPrize": "28564531",    "FirstPrize1": "05754219",    "FirstPrize2": "52891675",    "FirstPrize3": "45327106",    "Additional_Sixth_Prize": "252"},
    {"id": "2021_09-10",    "SpecialPrize": "14872301",    "GrandPrize": "37250799",    "FirstPrize1": "71086085",    "FirstPrize2": "53645821",    "FirstPrize3": "46626911",    "Additional_Sixth_Prize": "916"},
    {"id": "2021_07-08",    "SpecialPrize": "52604932",    "GrandPrize": "20102509",    "FirstPrize1": "39173725",    "FirstPrize2": "34997398",    "FirstPrize3": "98953723",    "Additional_Sixth_Prize": "634"},
    {"id": "2021_05-06",    "SpecialPrize": "51118051",    "GrandPrize": "37385202",    "FirstPrize1": "27461411",    "FirstPrize2": "99831976",    "FirstPrize3": "10229515",    "Additional_Sixth_Prize": "747"},
    {"id": "2021_03-04",    "SpecialPrize": "59518250",    "GrandPrize": "81016847",    "FirstPrize1": "22884739",    "FirstPrize2": "80660537",    "FirstPrize3": "62637675",    "Additional_Sixth_Prize": "187"},
    {"id": "2021_01-02",    "SpecialPrize": "80325690",    "GrandPrize": "95201943",    "FirstPrize1": "64613291",    "FirstPrize2": "00581856",    "FirstPrize3": "63105417",    "Additional_Sixth_Prize": "295"},
]

for i in newItem:
    a.setter(i)
