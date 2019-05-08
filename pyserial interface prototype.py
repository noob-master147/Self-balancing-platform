import serial
import time

data = serial.Serial('/dev/ttyACM0',9600)
x=0
for x in range(50):
	a = chr(x)
	data.write(a.encode())
	print(x)
	time.sleep(.5)		
