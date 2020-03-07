import hashlib
import os

import subprocess

def md5_test(text):
	org = hashlib.md5(text.encode('utf-8')).hexdigest()
	result = subprocess.run(['./ft_ssl', 'md5', '-s', text], stdout=subprocess.PIPE)
	my = result.stdout.decode('utf-8').rstrip()
	if org == my:
		print("OK")
	else:
		print("ERROR")


def hash_test(text):
	print("MD5 algorithm checker: ", end='')
	md5_test(text)

def copy_binary_for_test():
	subprocess.run(['cp', "../ft_ssl", "."], stdout=subprocess.PIPE)

copy_binary_for_test()
hash_test('')
hash_test('1')
hash_test('123r4rurjiro3r4tgh')
hash_test('yihurio0783903459884930495849034958thugjikjbfekdofijdskodskjofjkjfbhvjfljkfkjlfkjjgfjk')
hash_test('#pragma once\
#include <ft_ssl_md5.h>\
\
# define F(B, C, D) 			((B) & (C)) | (~(B) & (D))\
# define G(B, C, D) 			((B) & (D)) | ((C) & ~(D))\
# define H(B, C, D) 			(B) ^ (C) ^ (D)\
# define I(B, C, D) 			(C) ^ (B | ~(D))\
\
#define LEFT_ROTATE(x, c) ((x << c) | (x >> (32 - c)));\
\
#define NEEDED_MODULO_BYTES (448 / 8)\
#define DIV_BYTES (512 / 8)\
\
#define CHUNK_LEN_BYTES (512 / 8)\
\
#define A_INIT_VALUE 0x67452301; // 67452301h\
#define B_INIT_VALUE 0xefcdab89; // EFCDAB89h\
#define C_INIT_VALUE 0x98badcfe; // 98BADCFEh\
#define D_INIT_VALUE 0x10325476; // 10325476h\
')

with open('war_and_peace', 'r') as file:
	data = file.read().replace('\n', '')
	hash_test(data[:1024])
