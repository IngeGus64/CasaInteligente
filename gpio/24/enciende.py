#!usr/bin/env/ python
## enciende.py
#Importamos la libreria y le cambiamos el nombre a GPIO
import RPi.GPIO as GPIO
#Establecemos el sistema de numeracion que queremos,
#eb este caso el sistema BCM
GPIO.setmode(GPIO.BCM)
#Configuramos el pin GPIO 24 como una salida
GPIO.setup(24, GPIO.OUT)
#Encendemos el led
GPIO.output(24, GPIO.HIGH)

