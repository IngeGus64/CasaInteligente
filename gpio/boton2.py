import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(16, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(20, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

def botonPresionado(valor):
	print('Scored! %s '%valor)
	print(time.time())

GPIO.add_event_detect(16, GPIO.FALLING, callback=lambda x: botonPresionado(50), bouncetime=2000)
GPIO.add_event_detect(20, GPIO.FALLING, callback=lambda x: botonPresionado(50), bouncetime=2000)
