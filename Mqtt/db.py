# python3.6
import mysql.connector
import requests

# Konfigurasi Database
def connector():
    mydb = mysql.connector.connect(
        host="localhost",
        user="root",
        password="",
        database="smartaquascape"
        #  host="103.147.154.41",
        # user="iotdevel_iotdevel",
        # password="iotdevel123",
        # database="iotdevel_smartaquascape"
    )
    return mydb

def insertMonitoring(dataSensor):
    head, waterLevel, temperature, turbidity = dataSensor.split(':')
    turbidity, _ = turbidity.split(';')

    mydb = connector()
    mycursor = mydb.cursor()
    sql = "INSERT INTO monitoring (temperature, water_level, turbidity) VALUES (%s, %s, %s)"
    val = (temperature, waterLevel, turbidity)
    mycursor.execute(sql, val)
    mydb.commit()
    return

# def responMonitoring():
#     mydb = connector()
#     mycursor = mydb.cursor()
#     mycursor.execute("SELECT time_deliver FROM deliver_time")
#     myresult = mycursor.fetchall()
#     #print(myresult[0][0])
#     data = '\r\n{\r\n  "m2m:cin": {\r\n    "con": \r\n      \"{\r\n      \t \\"header\\": '+str(4)+',\r\n         \\"waktuPengiriman\\": \\"'+str(myresult[0][0])+'\\"\r\n      }\"\r\n    }\r\n}'
#     #print(data)
#     print("\nSending data to Antares...\n")
#     url = 'https://platform.antares.id:8443/~/antares-cse/antares-id/smartAquascape/TimeMonitoring'
#     headers = {'cache-control':'no-cache','Content-Type':'application/json;ty=4','X-M2M-Origin':'9fb52249c593c66d:b719370dce7d93b9','Accept':'application/json'}
#     response = requests.post(url,headers=headers,data=data)
#     return response

def buttonFeeder(stsFeeder):
    mydb = connector()
    mycursor = mydb.cursor()
    sql = "UPDATE feeder SET statusFeeder = %s WHERE id = %s"
    val = (stsFeeder, "1")
    mycursor.execute(sql, val)
    mydb.commit()
    return

def dataChecker(data, id):
    print(data)
    if data["header"] == 1: #1:WaterLevel:Temperature:Turbidity
        insertMonitoring(data["data"])
    elif data["header"] == 9:
        buttonFeeder(data["statusFeeder"])
        #print(str(head) + "\n" + str(waterLevel) + "\n" + str(temperature) + "\n" + str(turbidity))
    # elif data["header"] == 4:
    #     data = ""
    # elif data["header"] == 5:
    #     responMonitoring()
    