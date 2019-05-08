import serial
import time

data = serial.Serial('/dev/ttyACM0',9600)

for x in range(20):
	for y in range(20):
		data.write(y)
		data.write(x)
