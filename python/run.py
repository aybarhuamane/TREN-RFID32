# ACTUALIZADO 14/10
# MULTI DEVICES
import random
from time import sleep
import paho.mqtt.client as mqtt
import pprint
from pymongo import MongoClient
from pymongo.errors import ConnectionFailure
# ------------------ MQTT ----------------------------------------
clientID = 'python_mongo' + str(random.randrange(100))
usernameMQTT = 'python'
passwordMQTT = 'python$+'
#device/+/estacion/+/data/#
TOPIC_RAIZ= "device/+/estacion/+/data/"
TOPIC_SUBSCRIBE_B3 = TOPIC_RAIZ + "buscar"
TOPIC_PUBLISH_E3 = "encontrado"
IP = '127.0.0.1'
ipBroker = IP
portMQTT = 1883

refer = 0
# ------------------ MONGO ----------------------------------------

DB_Mongo = 'hikary'
coll_Mongo = 'blacklist'

def mongo_conect():
   # conexion = MongoClient(host=IP, port =27017, username="operador",password="mimamamemima#123$$")
    conexion = MongoClient(host=IP, port =27017, username="mqttoper",password="&LmRBXu8*zV3")
#1913466089
    return conexion 
db = mongo_conect()[DB_Mongo]    #BD
registro = db[coll_Mongo]  #collection

def on_connect(client, userdata, flags, rc):
    #print('Connected with result code ' + str(rc))
    client.subscribe(TOPIC_SUBSCRIBE_B3) 
    if rc == 0:
      print("Connection Correct Mqtt!." + str(rc))
    else:
      print("Connection Failed Mqtt" + str(rc))
   # client.subscribe(TOPIC_SUBSCRIBE_E3) #NUEVO
def on_disconnect(client, userdata, rc):
     if rc != 0:
        print("Unexpected MQTT disconnection. auto-reconnect")  

try:
    info = mongo_conect().server_info()
    print('Conexion Exitosa a la bd!')
    #print(info)
except  ConnectionFailure:
    print("Server not available")

# ENVIO DE MENSAJES
def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload.decode("utf-8")))
    dato = msg.payload.decode("utf-8")
    topico = msg.topic
    
    mongo_conect()
    print("Conexion Abierta!")
   
    string_list = topico.split('/') #device/+/estacion/+/data/#
    num = len(string_list) -1

    consulta = registro.find({"items.nro_interno":dato},{"items.$": True})
    resultss = list(consulta)
    print('***********************************   ' + string_list[1] + '    **************************************')
    if string_list[num] == 'buscar': #DECUID:
    #if topico == TOPIC_SUBSCRIBE_B3: #DECUID:
        grabando_topic = string_list[0]+'/'+ string_list[1]+'/'+ string_list[2]+'/'+ string_list[3]+'/'+ string_list[4]+'/' + TOPIC_PUBLISH_E3  #topic:  python/clientid1/encontrado3
        print("CONSULTANDO A MONGO: "+ topico)

        print(dato)
        if len(resultss )==0:
            print("******NO Se encontro****")
            client.publish(grabando_topic,"0")
        else: 
          print("****se encontro***")       
  
          for i in registro.find({"items.nro_interno":dato},{"items.$": True}):
            #client.publish("data/grab","1")
            #print(i)
            #data_bde = "{}" .format(i["dni"])
            pprint.pprint(i['items'][0]['nro_interno'])
            pprint.pprint(i['items'][0]['estado'])
          
            client.publish(grabando_topic,i['items'][0]['estado'])  #SE ENVIA POR OTRO TOPICO PARA EVITAR HACER BUCLES
            print("Se envio: " + str(grabando_topic)+" " + str(i['items'][0]['estado']))
          #  refe = 1  
    mongo_conect().close()
    print("************************** conexion cerrada ******************************************* \n\n ")              
client = mqtt.Client(clientID)
client.username_pw_set(usernameMQTT, passwordMQTT)
client.connect(ipBroker, portMQTT, 60)
# Specify callback function
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
#client.connect(ipBroker, portMQTT, 60)
client.loop_forever()

