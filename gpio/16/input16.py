import RPi.GPIO as GPIO
import time
import os
import smtplib

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(16, GPIO.IN)
GPIO.setup(21, GPIO.IN)
GPIO.setup(27, GPIO.OUT)
GPIO.output(27,0)

true = 1
leds=[5,17,22,23,24,27]
i=0
j=0
sender = 'gustavo.servelect@gmail.com'
receivers = ['rb_gustavo_fis@hotmail.com']
try:
	while(true):
	     GPIO.output(27, GPIO.input(16))
	     if (GPIO.input(21)==1):
		   j = j + 1
		   print "boton presionado", j
		   time.sleep(2)
	     
except KeyboardInterrupt:
	GPIO.cleanup()
