# rc4 simulator
# checks out 2nd-byte frequencies of rc4 stream
# spring 2016 | ecs 127 | prof rogaway

import os # for random 16-byte gen

# generate stream
def create_stream(s):
	i = 0; j = 0
	while True:
		i = (i + 1) % 256
		j = (j + s[i]) % 256
		s[i], s[j] = s[j], s[i]
		k = s[ (s[i] + s[j]) % 256 ]
		# return k
		yield k

# initialize
def init_stream():
	s = []
	# get random 16-byte string
	k = os.urandom(16)

	for i in range(0, 256):
		s.append(i)

	j = 0
	for i in range(0, 256):
		j = (j + s[i] + k[i % len(k)]) % 256
		# swap S[i] and S[j]
		s[i], s[j] = s[j], s[i]

	return s

freq = {}
# total 2nd-bytes
total = 0
for repeat in range(10001):
	# create a new stream w/ rand key, per repeat
	stream = create_stream(init_stream())

	# go through our 16 bytes
	for i in range(0, 16):
		# step through stream
		val = hex(next(stream))
		# 0, 1 <- i = 1 is 2nd byte
		if i == 1:
			total = total + 1

			if val in freq:
				freq[val] = freq[val] + 1
			else:
				freq[val] = 1

	# end for
# end for

#print(freq)

# count the number of times i <- {0, ..., 9}
zero_nine_count = 0
for i in range(0, 10):
	zero_nine_count += 1

	str_char = "0x" + str(i)
	print(str_char + ": " + str(freq[str_char]))

# what is our end probability, p_i?
print("Probability of 2nd byte being in {0, ..., 9}:")
print(str((zero_nine_count/total)*100) + "%")

highest = str(max(freq, key=freq.get))
print("Key with highest frequency: " + highest)
print(str(freq[highest]) + " occurrences of " + str(total))