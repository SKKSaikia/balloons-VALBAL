#from multiprocessing.connection import Listener, Client
import threading
import queue
import sys
import zmq

#port = 5556
#address = ('localhost', 6000)
#temp_addr = '/tmp/serialpipe'


close_bytes = b'~~close~~'

receive_addr = "ipc:///tmp/ser_pub.pipe"
send_addr = "ipc:///tmp/ser_pull.pipe"

class ConsumerSocket:

	def __init__(self, topic):

		self.topic = topic

		self.read_bytes = queue.Queue() # thread-safe queue where stuff is dumped
		self.read_msg = b""


		# socket stuff
		context = zmq.Context()

		self.consumer_sender = context.socket(zmq.PUB)
		self.consumer_sender.connect(send_addr)

		listen_thread = threading.Thread(name='listen_thread', target = self._listen)
		listen_thread.start()

		# register new listener with the publisher
		print("serial_interface.py __init__: Registering new listener with publisher")
		self.write(self.topic, b'\x02')



	def _listen(self):
		# constantly polling the socket to see if anything new comes in

		# keep the socket in the same thread it's being used in
		context = zmq.Context()
		consumer_receiver = context.socket(zmq.SUB)
		consumer_receiver.connect(receive_addr)

		print("serial_interface.py _listen: Looking for topic", self.topic)
		consumer_receiver.setsockopt(zmq.SUBSCRIBE, self.topic)
		
		while(True):

			print("serial_interface.py _listen: Waiting for message")
			full_msg = consumer_receiver.recv() # blocking
			print("serial_interface.py _listen: Got a message: ", full_msg)
			topic, msg = full_msg.split(b" ", 1)
			

			if topic == self.topic:
				# msg = full_msg[len(self.topic)+1:] # add one for the space -> we remove the topic label

				self.read_bytes.put(msg)


				if msg == close_bytes:
					consumer_receiver.close()
					print("Socket Closed")
					break

	def read(self, num_bytes=1):
		# read a number of bytes from the socket stream
		if len(self.read_msg) - num_bytes <= 0:
			self.read_msg += self.read_bytes.get(True) # blocking
		result = self.read_msg[:num_bytes]
		self.read_msg = self.read_msg[num_bytes:]
		return result


	def write(self, msg, code=b'\x00'):
		if code == close_bytes:
			print("not sending any message: ", self.write_msg)
			#self.consumer_sender.send(self.topic + b' ' + self.write_msg)
			#self.consumer_sender.send(self.topic + b' ' + code)
			#self.client_conn.send(self.write_msg)
			#self.client_conn.send(data)
		else:
			print("serial_interface.py write: sending message over ipc: ", msg, "with code", code)
			self.consumer_sender.send(b'w ' + code + msg) # w is the topic for 'write'

			# self.write_msg += data
			# if len(self.write_msg) > 256:
			# 	#self.client_conn.send(self.write_msg)
			# 	self.pub_socket.send(topic + b' ' + self.write_msg)
			# 	self.write_msg = b""






