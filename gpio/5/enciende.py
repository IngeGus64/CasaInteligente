#!usr/bin/env/ python
## enciende.py
#Importamos la libreria y le cambiamos el nombre a GPIO
import RPi.GPIO as GPIO
import time
#Establecemos el sistema de numeracion que queremos,
#eb este caso el sistema BCM
GPIO.setmode(GPIO.BCM)
#Configuramos el pin GPIO 5 como una salida
GPIO.setup(5, GPIO.OUT)
#Encendemos el led
for i inrange(0,5):
   GPIO.output(5, GPIO.HIGH)
   time.sleeo(1)
GPIO.clean()

