import socket

class logCellData():
	def __init__(self, fileOutput='data.txt', 
				ipAddress='', portConnection='3333', 
				) -> None:
		self.file = open(fileOutput,"w")
		self.ipAddress = ipAddress
		self.port 	= portConnection
		self.bufferSize = 25
		self.fileBuffer = 50

	def connectSensor(self) -> None:
		# Set up file
		self.file.write("Time\tData\n")

		# Set up connection
		print("Start connection")
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.socket.bind((self.ipAddress, self.port))
		self.socket.listen(1)

	def acceptData(self) -> None:
		self.conn, self.addr = self.socket.accept()
		print("Connection accepted")

		dataStorage = ""
		i = 0
		print("Ready to test....")
		try:
			while(True):
				rawData = self.conn.recv(self.bufferSize)
				#print(rawData.decode())
				##print(int.from_bytes(rawData, byteorder='big'))
				dataStorage += rawData.decode()
				if (i > self.fileBuffer):
					#print("LOL")
					self.file.write(dataStorage)
					dataStorage = ""
					i = 0
				i += 1

		except KeyboardInterrupt:
			print("Closing connection")
			self.conn.close()
			self.file.write(dataStorage)
			self.file.close()

		finally:
			print("Unknown Error: Closing connection")
			self.conn.close()
			self.file.write(dataStorage)
			self.file.close()


	def setIpAddress(self) -> None:
		pass

	def setPort(self) -> None:
		pass 

	def setFile(self) -> None:
		pass

	def setBuffer(self) -> None:
		pass