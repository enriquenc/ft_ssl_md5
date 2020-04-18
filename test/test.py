import unittest
import os
import subprocess
import hashlib

def test_preparation():
	if ('/' not in __file__):
		os.chdir("../")
	subprocess.run(["make", "re"], stdout=subprocess.PIPE)

def clean_after_test():
	subprocess.run(["make", "fclean"], stdout=subprocess.PIPE)


stdin_data = "155523"
s_flag_data = "fu55ck"
stdin_encoded = hashlib.md5(stdin_data.encode('utf-8')).hexdigest()
s_data_encoded = hashlib.md5(s_flag_data.encode('utf-8')).hexdigest()

class TestAll(unittest.TestCase):
	def test_flags_p(self):
		expected = stdin_data + "md5 (stdin) = " + stdin_encoded + '\n'
		actual = subprocess.Popen(['./ft_ssl', 'md5', '-p'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(stdin_data.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_pr(self):
		expected = stdin_data + stdin_encoded + " stdin\n" + s_data_encoded + " \"" + s_flag_data + "\"\n"
		actual = subprocess.Popen(['./ft_ssl', 'md5', '-s', s_flag_data, '-p', '-r'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(stdin_data.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_ps(self):
		expected = stdin_data + "md5 (stdin) = " + stdin_encoded + "\nmd5 (\"" + s_flag_data + "\") = " + s_data_encoded + "\n"
		actual = subprocess.Popen(['./ft_ssl', 'md5', '-s', s_flag_data, '-p'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(stdin_data.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_pq(self):
		expected = stdin_data + stdin_encoded + '\n'
		actual = subprocess.Popen(['./ft_ssl', 'md5', '-p', '-q'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(stdin_data.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)


if __name__ == '__main__':
	test_preparation()
	unittest.main(exit=False)
	clean_after_test()

