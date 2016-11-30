#!usr/bin/env/ python
## apaga.py
#Importamos la libreria y le cambiamos el nombre a GPIO
import RPi.GPIO as GPIO
#Establecemos el sistema de numeracion que queremos,
#eb este caso el sistema BCM
GPIO.setmode(GPIO.BCM)
#Configuramos el pin GPIO 27 como una salida
GPIO.setup(27, GPIO.OUT)
#Apagamos el led
GPIO.output(27, GPIO.LOW)
#Y liberamos los GPIO
GPIO.cleanup()


