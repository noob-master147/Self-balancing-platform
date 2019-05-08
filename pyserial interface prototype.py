import serial
import time

data = serial.Serial('/dev/ttyACM0',9600)

for x in range(20):
	for y in range(20):
		x = str(x)
		y = str(y)
		data.write(x.encode())
		data.write(y.encode())

		
