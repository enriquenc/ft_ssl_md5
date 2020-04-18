import unittest
import os
import subprocess
import hashlib

def test_preparation():
	if ('/' not in __file__):
		os.chdir("../")
	subprocess.run(["make"], stdout=subprocess.PIPE)

def clean_after_test():
	subprocess.run(["make", "fclean"], stdout=subprocess.PIPE)

class TestAll(unittest.TestCase):
	def test_test(self):
		stdin_data = "123"
		s_flag_data = "fuck"
		stdin_encoded = hashlib.md5(stdin_data.encode('utf-8')).hexdigest()
		s_data_encoded = hashlib.md5(s_flag_data.encode('utf-8')).hexdigest()
		expected = stdin_data + stdin_encoded + "\nmd5 (\"" + s_flag_data + "\") = " + s_data_encoded + "\n"
		actual = subprocess.Popen(['./ft_ssl', 'md5', '-s', s_flag_data, '-p'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(b'123')[0].decode('utf-8')
		self.assertEqual(expected, actual)

if __name__ == '__main__':
	test_preparation()
	unittest.main()
	clean_after_test()