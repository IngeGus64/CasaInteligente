#!usr/bin/env/ python
## enciende.py
#Importamos la libreria y le cambiamos el nombre a GPIO
import RPi.GPIO as GPIO

#Necesario para los delays
import time

#Establecemos el sistema de numeracion que queremos,
#eb este caso el sistema BCM
GPIO.setmode(GPIO.BCM)
#Configuramos el pin GPIO 22 como una salida
GPIO.setup(22, GPIO.OUT)

#Encendemos y apagamos el led 5 veces
for i in range(0,5):

	GPIO.output(22, GPIO.HIGH)
	time.sleep(1)
	GPIO.output(22, GPIO.LOW)
	time.sleep(1)
#Y liberamos los GPIO
GPIO.cleanup()


