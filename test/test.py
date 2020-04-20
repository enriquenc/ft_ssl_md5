import unittest
import os
import subprocess
import hashlib

def test_preparation():
	if ('/' not in __file__):
		os.chdir("../")
	subprocess.run(["make", 're'], stdout=subprocess.PIPE)

def clean_after_test():
	subprocess.run(["make", "fclean"], stdout=subprocess.PIPE)


str_array = ["1", "1234n", "cxgdfgdfgdfgdfgdf", "0"]
hashed_str_array = []
for s in str_array:
	hashed_str_array.append(hashlib.md5(s.encode('utf-8')).hexdigest())

stdin_data = "155523"
s_flag_data = "fu55ck"
stdin_encoded = hashlib.md5(stdin_data.encode('utf-8')).hexdigest()
s_data_encoded = hashlib.md5(s_flag_data.encode('utf-8')).hexdigest()


files_array = ['test.py', 'test_file_1', 'test_file_2', 'war_and_peace']
hashed_files_array = []

for i in range(len(files_array)):
	files_array[i] = 'test/' + files_array[i]
	org = 'openssl md5 ' + files_array[i]
	hashed_files_array.append(subprocess.run(org.split(), stdout=subprocess.PIPE).stdout.decode('utf-8').split()[-1])

#Test string for hash algorithms testing
test_string = "test string"

class TestAll(unittest.TestCase):
	def test_flags_p(self):
		expected = stdin_data + "md5 (stdin) = " + stdin_encoded + '\n'
		actual = subprocess.Popen(['./ft_ssl', 'md5', '-p'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(stdin_data.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_psr(self):
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

	def test_flags_s(self):
		expected = "md5 (\"" + s_flag_data + "\") = " + s_data_encoded + "\n"
		actual = subprocess.run(['./ft_ssl', 'md5', '-s', s_flag_data], stdout=subprocess.PIPE)
		actual = actual.stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_sq(self):
		expected = s_data_encoded + "\n"
		actual = subprocess.run(['./ft_ssl', 'md5', '-s', s_flag_data, '-q'], stdout=subprocess.PIPE)
		actual = actual.stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_sr(self):
		expected = s_data_encoded + ' "' + s_flag_data + '"\n'
		actual = subprocess.run(['./ft_ssl', 'md5', '-s', s_flag_data, '-r'], stdout=subprocess.PIPE)
		actual = actual.stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_srq(self):
		expected = s_data_encoded + "\n"
		actual = subprocess.run(['./ft_ssl', 'md5', '-s', s_flag_data, '-r', '-q'], stdout=subprocess.PIPE)
		actual = actual.stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_ssss(self):
		expected = ""
		stdin = "./ft_ssl md5"
		for i in range(len(str_array)):
			expected = expected + "md5 (\"" + str_array[i] + "\") = " + hashed_str_array[i] + "\n"
			stdin = stdin + ' -s ' + str_array[i]
		actual = subprocess.run(stdin.split(), stdout=subprocess.PIPE)
		actual = actual.stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_ssssr(self):
		expected = ""
		stdin = "./ft_ssl md5 -r"
		for i in range(len(str_array)):
			expected = expected + hashed_str_array[i] + ' "' + str_array[i] + '"\n'
			stdin = stdin + ' -s ' + str_array[i]
		actual = subprocess.run(stdin.split(), stdout=subprocess.PIPE)
		actual = actual.stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_flags_ssssrq(self):
		expected = ""
		stdin = "./ft_ssl md5 -r -q"
		for i in range(len(str_array)):
			expected = expected + hashed_str_array[i] + "\n"
			stdin = stdin + ' -s ' + str_array[i]
		actual = subprocess.run(stdin.split(), stdout=subprocess.PIPE)
		actual = actual.stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_input_file(self):
		my = './ft_ssl md5 ' + files_array[0]
		expected = 'md5 (' + files_array[0] + ') = ' + hashed_files_array[0] + '\n'
		actual = subprocess.run(my.split(), stdout=subprocess.PIPE).stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_input_many_files(self):
		my = './ft_ssl md5'
		expected = ''
		for i in range(len(files_array)):
			my = my + ' ' + files_array[i]
			expected = expected + 'md5 (' + files_array[i] + ') = ' + hashed_files_array[i] + '\n'
		actual = subprocess.run(my.split(), stdout=subprocess.PIPE).stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_input_many_files_r(self):
		my = './ft_ssl md5 -r'
		expected = ''
		for i in range(len(files_array)):
			my = my + ' ' + files_array[i]
			expected = expected + hashed_files_array[i] + ' ' + files_array[i] + '\n'
		actual = subprocess.run(my.split(), stdout=subprocess.PIPE).stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_input_many_files_q(self):
		my = './ft_ssl md5 -q'
		expected = ''
		for i in range(len(files_array)):
			my = my + ' ' + files_array[i]
			expected = expected + hashed_files_array[i] + '\n'
		actual = subprocess.run(my.split(), stdout=subprocess.PIPE).stdout.decode('utf-8')
		self.assertEqual(expected, actual)

	def test_many_files_flags_rp_ssss(self):
		my = './ft_ssl md5 -r -p'
		expected = stdin_data + stdin_encoded + ' stdin\n'

		for i in range(len(str_array)):
			expected = expected + hashed_str_array[i] + ' "' + str_array[i] + '"\n'
			my = my + ' -s ' + str_array[i]

		for i in range(len(files_array)):
			my = my + ' ' + files_array[i]
			expected = expected + hashed_files_array[i] + ' ' + files_array[i] + '\n'

		actual = subprocess.Popen(my.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(stdin_data.encode('utf-8'))[0].decode('utf-8')

		self.assertEqual(expected, actual)

	def test_many_files_flags_rp_ssss_q(self):
		my = './ft_ssl md5 -r -p -q'
		expected = stdin_data + stdin_encoded + '\n'

		for i in range(len(str_array)):
			expected = expected + hashed_str_array[i] + '\n'
			my = my + ' -s ' + str_array[i]

		for i in range(len(files_array)):
			my = my + ' ' + files_array[i]
			expected = expected + hashed_files_array[i] + '\n'

		actual = subprocess.Popen(my.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(stdin_data.encode('utf-8'))[0].decode('utf-8')

		self.assertEqual(expected, actual)

	def test_md5(self):
		algorithm_name = 'md5'
		my = './ft_ssl ' + algorithm_name
		org = 'openssl ' + algorithm_name
		expected = algorithm_name + ' (stdin) = '
		actual = subprocess.Popen(org.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		expected = expected + actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8').split()[-1] + '\n'

		actual = subprocess.Popen(my.split(),  stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)

	def test_sha224(self):
		algorithm_name = 'sha512'
		my = './ft_ssl ' + algorithm_name
		org = 'openssl ' + algorithm_name
		expected = algorithm_name + ' (stdin) = '
		actual = subprocess.Popen(org.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		expected = expected + actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8').split()[-1] + '\n'

		actual = subprocess.Popen(my.split(),  stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)

	def test_sha256(self):
		algorithm_name = 'sha256'
		my = './ft_ssl ' + algorithm_name
		org = 'openssl ' + algorithm_name
		expected = algorithm_name + ' (stdin) = '
		actual = subprocess.Popen(org.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		expected = expected + actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8').split()[-1] + '\n'

		actual = subprocess.Popen(my.split(),  stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)

	def test_sha384(self):
		algorithm_name = 'sha384'
		my = './ft_ssl ' + algorithm_name
		org = 'openssl ' + algorithm_name
		expected = algorithm_name + ' (stdin) = '
		actual = subprocess.Popen(org.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		expected = expected + actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8').split()[-1] + '\n'

		actual = subprocess.Popen(my.split(),  stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)

	def test_sha512(self):
		algorithm_name = 'sha512'
		my = './ft_ssl ' + algorithm_name
		org = 'openssl ' + algorithm_name
		expected = algorithm_name + ' (stdin) = '
		actual = subprocess.Popen(org.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		expected = expected + actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8').split()[-1] + '\n'

		actual = subprocess.Popen(my.split(),  stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		actual = actual.communicate(test_string.encode('utf-8'))[0].decode('utf-8')
		self.assertEqual(expected, actual)



if __name__ == '__main__':
	test_preparation()
	unittest.main(exit=False)
	clean_after_test()

