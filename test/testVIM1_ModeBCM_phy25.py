import RPi.GPIO as GPIO
import time

GpioW  = 15

def setup():
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(GpioW,GPIO.OUT)
	GPIO.output(GpioW,GPIO.HIGH)

def blink():
	while True:
		GPIO.output(GpioW, GPIO.HIGH)
		time.sleep(5)
		GPIO.output(GpioW, GPIO.LOW)
		time.sleep(5)

def shutdown():
	GPIO.cleanup()


if __name__ == '__main__':
	print("Test with RPI GPIO")
	setup()
	try:
		blink()
	except:
		shutdown()
