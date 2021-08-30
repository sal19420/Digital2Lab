# Código de ejemplo AdafruitIO
# Universidad del Valle de Guatemala
# IE3027 - Electrónica Digital 2
# Josue Salazar 

# Adafruit IO
# https://io.adafruit.com/

# if Module not Found. Open Terminal/CMD and execute:
# pip3 install Adafruit_IO

from Adafruit_IO import Client, RequestError, Feed
import serial
import time

envio = 184     #dato que viene desde la pág
nulo = 0        #valor nulo
nulo = str(nulo)#char nulo
temporal1 = 0
temporal2 = 0

#Defino nombre de comunicación
dev = serial.Serial("COM3",9600) 
dev.timeout = 3 #tiempo de espera para recibir datos
time.sleep(1) #para que establezca conexion

ADAFRUIT_IO_KEY = "aio_tkeZ37UwpsJNBsLPXLpUTO3fdXlv"
ADAFRUIT_IO_USERNAME = "Josuech"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

while True:
    with dev:   #utilice el COM serial
        #Contador
        lab5s1_feed = aio.feeds('lab5s2')
        #Sensor temperatura
        lab5s2_feed = aio.feeds('lab5s1')
        cont_data = aio.receive(lab5s1_feed.key)
        tempe_data = aio.receive(lab5s2_feed.key)
    
        valor = int(cont_data.value)
        dev.write(b's') #mando codigo de caracter
        val = dev.readline(3).decode('ascii') #recibo 2 bytes
        val = int(val)  #convierto a entero

        if(valor != temporal1 or val != temporal2):
            print(f'Temperatura: {cont_data.value}')
            print(f'Contador: {tempe_data.value} \n')

            if (valor < 10 and valor > -1):
                dev.write(nulo.encode('ascii')) #envio un cero
                dev.write(nulo.encode('ascii'))
                
            elif (valor <100 and valor > 9):
                dev.write(nulo.encode('ascii')) #envio un cero
            
            envio = str(int(cont_data.value))
            dev.write(envio.encode('ascii'))
            print("Escrito en pic: {} \n".format(envio))
            print("Escrito en AdaFruit: ")
            print(val)
            
            #cliente.send_data(mifeed.feed.key, valor a enviar) ; Esto para mandar dato y leer
            aio.send_data(lab5s2_feed.key, val)
            print('----------------------------------------------------')
            temporal1 = int(cont_data.value)
            temporal2 = int(tempe_data.value)

    
