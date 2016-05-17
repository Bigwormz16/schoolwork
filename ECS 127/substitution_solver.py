# homework 2 | ECS 127 | Rogaway | Spring 2016
# cb: ian rosner
# date: 4/10/16

# create frequency table of 2-letter pairs
# using war and peace .txt file
# decode message using freqs to calc plausability

import math
import random

def compute_plausability(message, freqDict):
	# returns ln(pl(message))
	prob = 0
	for i in range(0, len(message) - 1):
		# filter out comma newline
		if (message[i] + message[i+1]) == ",\n":
			pass

		# count newline as a space
		if (message[i] == "\n"):
			prob += freqDict[" " + message[i+1]]
			continue

		# check if tuple is not in dict
		if not (message[i] + message[i+1]) in freqDict:
			# less plausible if this doesn't appear in our
			# frequencies, so subtract a fixed amount.
			prob -= 12
		else:
			prob += freqDict[(message[i] + message[i+1])]

	return prob
# end func

def rand_swap(key):
	# pick two points within string, swap, return
	p1 = random.randint(0, len(key) - 1)

	# ensure we don't get the same point again
	while True:
		p2 = random.randint(0, len(key) - 1)
		if p2 != p1:
			break

	listkey = list(key)
	# in-place swap
	listkey[p1], listkey[p2] = listkey[p2], listkey[p1]
	# debug msg
	#print("swapping " + listkey[p1] + " with " + listkey[p2])
	return ''.join(listkey)
# end func

def decode(original, key):
	# input: original - message to be decoded
	# 		 key - {a ... z}-ordered 1-to-1 mapping
	# returns decoded message as string

	alphabet = "abcdefghijklmnopqrstuvwxyz"

	# using an associative array for ease
	cipher = {}
	for i in range(0, len(alphabet)):
		cipher[alphabet[i]] = key[i]

	decoded_msg = []
	for char in original:
		if char.isalpha():
			decoded_msg.append(cipher[char])
		else:
			decoded_msg.append(char)
	# end for

	return ''.join(decoded_msg)
# end func

def attempt_solve(freq):
	# attempts to find a key for enc_msg
	# ALGORITHM - as seen in
	# compute pl(f)
	# change to f* by making a random transposition of values f assigns to two symbol
	# compute pl(f*); if larger than pl(f), accept f*
	# if not, flip a pl(f*)/pl(f) coin - if heads, accept f*
	# else, stay at f
	enc_msg = """qkne l knixw tkn onixenw iytxrerjnx,
qkne tkn uxrray, tkn almbxny, qnxn xiemnw le crobjey hnarxn jn,
qkne l qiy ykrqe tkn ckixty iew wlimxijy, tr iww, wlvlwn, iew jniybxn tknj,
qkne l ylttlem knixw tkn iytxrerjnx qknxn kn onctbxnw qltk jbck iuuoibyn le tkn
onctbxn xrrj,
krq yrre beiccrbetihon l hncijn tlxnw iew ylcd,
tloo xlylem iew molwlem rbt l qiewnxnw raa hz jzynoa,
le tkn jzytlcio jrlyt elmkt ilx, iew axrj tljn tr tljn,
orrdnw bu le unxanct ylonecn it tkn ytixy."""

	# make a random key
	key = "abcdefghijklmnopqrstuvwxyz"
	temp = list(key)
	random.shuffle(temp)
	key = ''.join(temp)

	msg = decode(enc_msg, key)
	pl = compute_plausability(msg, freq)

	
	won = 0; lost = 0;
	for i in range(0, 10000):
		new_key = rand_swap(key) # f -> f*
		new_msg = decode(enc_msg, new_key)
		new_pl = compute_plausability(new_msg, freq) # pl(f*)
		print("pl: " + str(new_pl) + " | " + new_key)
		print(new_msg)

		if new_pl > pl:
			# accept these values
			pl = new_pl
			key = new_key
			msg = new_msg
		else:
			# flip a pl(f*)/pl(f) coin			
			print("coin chance: " + str(math.exp(new_pl - pl)) )
			if random.random() <= math.exp(new_pl - pl):
				# heads; accept f*
				#print("won the coinflip")
				won += 1
				pl = new_pl
				key = new_key
			else:
				# stay at f
				#print("lost the coinflip")
				lost += 1

			if i == 4000 and pl < -2700:
				# avoid local maxima by resetting
				return (False, msg)

			if key == "fucknqxbamhigelzwojtpvdrsy":
				print("TOOK " + str(i) + " ITERATIONS")
				break

	# end for

	print("won " + str(won) + " out of " + str(won + lost) + " coinflips.")
	print("final result: " + msg)
	print("key: " + key)

	return (True, msg)
# end func


# begin main

# associative array, k = char pair, v = frequency
freq = {}

# total number of pairs found in corpus
total = 0

# load up the corpus file
with open("war-and-peace.txt") as corpus:
	# grab first char before entering loop
	oldchar = corpus.read(1)

	while True:
		char = corpus.read(1)

		# if we don't get a character, break out of loop
		if not char:
			break

		# check if char is {a ... z} U ' '
		if not char.isalpha():
			if char != ' ':
				continue

		# else, increment frequency table
		tup = oldchar + char

		# check if tuple has been entered already
		if tup in freq:
			freq[tup] += 1
		else:
			freq[tup] = 1

		# done with this pair, move char over to oldchar
		oldchar = char
		total += 1

	# end while

# end file

# divide by total to get frequency, & take log
for pair in freq:
	freq[pair] = (math.log(freq[pair]) - math.log(total))

# list pairs from highest occurence to lowest
# for item in sorted(freq, key=freq.get, reverse=True):
# 	print(item + str(freq[item]))

# pl(f) = for i from 1 to n - 1, *= M[f[i],f[i+1]]
# log of both sides -> ln(pl(f)) = for i from 1 to n - 1, += ln(M[f[i],f[i+1]])

decoded_msg = ""
repeats = 0
while True:
	# returns a tuple.
	# first = bool - if true, dont repeat
	# second = the final decrypted message
	ans = attempt_solve(freq)
	decoded_msg = ans[1]
	if repeats > 5 or ans[0] == True:
		break

	print()
	repeats += 1
	# decodes.append(ans[1])
	

print("repeats: " + str(repeats))
print(decoded_msg)