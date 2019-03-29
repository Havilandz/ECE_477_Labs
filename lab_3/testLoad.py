#! /usr/bin/python3
import os
for i in range(100000000000000):
	f = open("test.txt", "w+")

	for j in range(10):
		f.write("THIS IS A TEST")
	f.close()
	os.remove("test.txt")
