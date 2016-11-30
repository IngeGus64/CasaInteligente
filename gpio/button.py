#!/usr/bin/env python

import time
import RPi.GPIO as GPIO
GPIO.setwarnings(False)


def buttonEventHandler(pin):
	print "Manejo evento del boton"
	GPIO.output(17,1)

	time.sleep(1)

	GPIO.output(17,0)

def botonPresionado(valor):
        print('Scored! %s '%valor)
        print(time.time())


def main():
	
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(16,GPIO.IN)
	GPIO.setup(20,GPIO.IN)
	GPIO.setup(5,GPIO.OUT)
	GPIO.setup(17,GPIO.OUT)

#	GPIO.output(17,1)

#	GPIO.add_event_detect(20,GPIO.FALLING)
	GPIO.add_event_detect(16, GPIO.FALLING, callback=lambda x: botonPresionado(50), bouncetime=2000)
	GPIO.add_event_detect(20, GPIO.FALLING, callback=lambda x: botonPresionado(50), bouncetime=2000)
#	GPIO.add_event_callback(20,buttonEventHandler,100)
	GPIO.output(17,0)
	GPIO.output(5,0)	

	while 1:

	#	if GPIO.input(20):
			GPIO.output(5,1)
			GPIO.output(17,0)
			print "boton On"
			time.sleep(1)
	#	else:
			GPIO.output(5,0)
                        GPIO.output(17,1)
                        print "boton Off"
			time.sleep(1)
	#	time.sleep(0.1)

	print "boton presionado"

	GPIO.cleanup()

if __name__=="__main__":
	main()

