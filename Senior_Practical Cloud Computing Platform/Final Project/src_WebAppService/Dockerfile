FROM mcr.microsoft.com/azure-functions/python:4-python3.8

WORKDIR /app

ADD . /app

RUN pip install -r requirements.txt
EXPOSE 5000 2222
CMD python app.py