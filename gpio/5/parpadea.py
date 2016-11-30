#!usr/bin/env/ python
## parpadea.py
#Importamos la libreria y le cambiamos el nombre a GPIO
import RPi.GPIO as GPIO

#Necesario para los delays
import time

#Establecemos el sistema de numeracion que queremos,
#eb este caso el sistema BCM
GPIO.setmode(GPIO.BCM)
#Configuramos el pin GPIO 5 como una salida
GPIO.setup(5, GPIO.OUT)

#Encendemos y apagamos el led 5 veces
for i in range(0,5):

	GPIO.output(5, GPIO.HIGH)
	time.sleep(10)
	GPIO.output(5, GPIO.LOW)
	time.sleep(10)
#Y liberamos los GPIO
GPIO.cleanup()
