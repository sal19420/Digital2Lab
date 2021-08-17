# Código de ejemplo AdafruitIO
# Universidad del Valle de Guatemala
# IE3027 - Electrónica Digital 2
# Josue Salazar 

# Adafruit IO
# https://io.adafruit.com/

# if Module not Found. Open Terminal/CMD and execute:
# pip3 install Adafruit_IO

from Adafruit_IO import Client, RequestError, Feed

ADAFRUIT_IO_KEY = "aio_VgUU94Hs5aIaFeEviP6nV1XetWNK"
ADAFRUIT_IO_USERNAME = "Josuech"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

while True:
    sensor1 = input("Coloque el valor del sensor 1: ")
    #Contador
    lab5s1_feed = aio.feeds('lab5s1')
    aio.send_data(lab5s1_feed.key, sensor1)
    cont_data = aio.receive(lab5s1_feed.key)
    print(f'Contador: {cont_data.value}')

    sensor2 = input("Coloque el valor del sensor 2: ")
    #Sensor temperatura
    lab5s2_feed = aio.feeds('lab5s2')
    aio.send_data(lab5s2_feed.key, sensor2)
    tempe_data = aio.receive(lab5s2_feed.key)
    print(f'Sensor de temperatura: {tempe_data.value}')
