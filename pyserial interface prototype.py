import serial
import time

data = serial.Serial('com4',9600)

for x in range(20):
	for y in range(20):
		data.write(y)
		data.write(x)