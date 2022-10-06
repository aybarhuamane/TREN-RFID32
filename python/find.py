# ACTUALIZADO 14/09
from weakref import ref
import pymongo
import time
import random
import paho.mqtt.client as mqtt
import pprint
from pymongo import MongoClient
# ------------------ MQTT ----------------------------------------
clientID = 'python_mongo' + str(random.randrange(100))
usernameMQTT = 'python'
passwordMQTT = 'python$+'

TOPIC_RAIZ= "data/"

TOPIC_PUBLISH_E = TOPIC_RAIZ + "encontrado"
TOPIC_SUBSCRIBE_E = TOPIC_PUBLISH_E

TOPIC_SUBSCRIBE_B = TOPIC_RAIZ + "buscar"
TOPIC_SUBSCRIBE_B2 = TOPIC_RAIZ + "buscar2"
TOPIC_SUBSCRIBE_I = TOPIC_RAIZ + "insertar"
TOPIC_SUBSCRIBE_B3 = TOPIC_RAIZ + "buscar3"

TOPIC_PUBLISH_E3 = TOPIC_RAIZ + "encontrado3"
TOPIC_SUBSCRIBE_E3 = TOPIC_PUBLISH_E3
#TOPIC_SUBSCRIBE = TOPIC_RAIZ + ""

#ipBroker = 'proyect.cloux.site'
#IP = '192.168.1.81' #'172.19.40.58' #DEL SERVER
#IP = 'iotx.cloux.site'
IP = '172.31.208.1'
ipBroker = IP
portMQTT = 1883
#topicSub = 'data/asa'  # +/#
#topicSub = 'data/#'
refer = 0
# ------------------ MONGO ----------------------------------------
username_Mongo="adminx"
password_Mongo="adminx"
port_Mongo=2700
DB_Mongo = 'uid'
coll_Mongo = 'clientes'
#url = 'mongodb://root:root@proyect.cloux.site:2700'
#url = 'mongodb://root:root@localhost:2700'

# url = "mongodb://root:root@mongo:27017"

#conexion = MongoClient(host="proyect.cloux.site", port=2700, username="root", password="root", serverSelectionTimeoutMS=1)
conexion = MongoClient(host=IP, port=port_Mongo, username=username_Mongo , password=password_Mongo , serverSelectionTimeoutMS=1)

db = conexion[DB_Mongo]    #BD
registro = db[coll_Mongo]  #collection
registro_2 = db['client']

# registro.insert_one({"DNI": 96384521, "NOMBRES": "AARON JOSUE", "APELLIDOS": "LOPEZ QUIJANDRIA"})
# registro.insert_one({"DNI": 69852145,"NOMBRES": "ERICK NELSON","APELLIDOS": "AYBAR HUAMAN"})
# persona3 = {"DNI": 15935782, "NOMBRES": "JACK DANIEL", "APELLIDOS": "ALIAGA BENDEZU"}
# persona4 = {"DNI": 35715964,"NOMBRES": "ROBIN BATMAN","APELLIDOS": "CASTRO MEJIA"}
# registro.insert_many([persona3, persona4])
# print(conexion.list_database_names())
# print(db.list_collection_names())
# print(registro.count_documents({}))


# Connection success callback
def on_connect(client, userdata, flags, rc):
    print('Connected with result code ' + str(rc))
    client.subscribe(TOPIC_SUBSCRIBE_B)  # SE SUSCRIBE Y ESCUCHA AL TOPICO
    client.subscribe(TOPIC_SUBSCRIBE_B2) 
    client.subscribe(TOPIC_SUBSCRIBE_B3) #NUEVO
    client.subscribe(TOPIC_SUBSCRIBE_I)
    client.subscribe(TOPIC_SUBSCRIBE_E)
   # client.subscribe(TOPIC_SUBSCRIBE_E3) #NUEVO

def mongo_insert(sms):
    registro.insert_one({
        'uid': sms,
        'nombre': 'ERICK NELSONE',
        'apellido': 'AYBAR HUAMAN ',
        'device': 'ESTACION CULTURA',
       # 'saldo': 24,  #   
        'status': '1', # 0 no baneado  , 1 baneado 
        # 'time': time.strftime("%H:%M:%S - %d/%m/%y")
        'time': time.strftime("%c")
    })
    print('insertando datos')


# ENVIO DE MENSAJES
def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload.decode("utf-8")))
    dato = msg.payload.decode("utf-8")
    topico = msg.topic
    try:
        if conexion:
            print("conexion establecida mongo")
            
            if topico == TOPIC_SUBSCRIBE_I:
                mongo_insert(dato)
                print("Se inserto correctamente:")
            elif topico == TOPIC_SUBSCRIBE_B:
                print("Busqueda:")
                myquery = { "uid": dato }
                mydoc = registro.find(myquery)
                for x in mydoc:
                  print(x)
            # elif topico == TOPIC_SUBSCRIBE_B2:
            #     for i in registro.find({ "uid": dato }):                                #BUSCANMOS POR UID QUE COINCIDEN
            #         print("Bienvenido(a) {} {}".format(i["nombre"], i["apellido"]))     # {} son los objetos que seran reemplazados
            #         #data_bd = "{} {}".format(i["nombre"], i["apellido"])
            #         #data_bd = "{}".format(i["uid"])                                    #ENVIAR SOLO UID
            #         #data_bd = "{},{}".format(i["uid"], i["saldo"])                   #ENVIAR UID Y SALDO
            #         #data_bd = "{},{},{}".format(i["uid"], i["saldo"],i["status"])    #funciona con saldo
            #         data_bd = "{},{}".format(i["uid"],i["status"])    #funciona 
            #         #estado = "{}".format(i["status"])
            #         #uid = "{}".format(i["uid"])
            #         # alacenar  = registro.format(i["nombre"], i["apellido"])
            #         print(data_bd)
            #         client.publish(TOPIC_PUBLISH_E,data_bd)
            #     #print(estado)
            #         #print(uid)
            
            elif topico == TOPIC_SUBSCRIBE_B3:
                    print("TOPIC3")
                    ref =0
                    consulta = registro_2.find({"results.uid":dato},{"results.$": True}) 
                    #print(consulta)
                    for i in consulta:
                        client.publish("data/grab","1")
                        #data_bde = "{}" .format(i["dni"])
                        pprint.pprint(i['results'][0]['estacion'])
                        pprint.pprint(i['results'][0]['dni'])
                        #pprint.pprint(i['results'][0]['status'])
                        #client.publish(TOPIC_PUBLISH_E3,i['results'][0]['status'])
                        pprint.pprint(i['results'][0]['uid'])
                        ref =1    
                    #conexion.close()
        client.publish("data/grab",str(ref))
        print(ref)          
    except:
        print("No se encontro la conexion mongo")


client = mqtt.Client(clientID)
client.username_pw_set(usernameMQTT, passwordMQTT)
# Specify callback function
client.on_connect = on_connect
client.on_message = on_message

client.connect(ipBroker, portMQTT, 60)
client.loop_forever()

