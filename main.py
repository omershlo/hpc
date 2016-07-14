# main_script.py


import subprocess
import sys

def extract(data):
	print data
	return data.split()[7]


def main():
	phandles = []
	n_args = len(sys.argv)
	number_of_messages = 1 * 10**4 if n_args<3 else int(sys.argv[2])
	number_of_process = 4 if n_args<2 else int(sys.argv[1])

	for x in range(0, number_of_process):
		phandles.append (subprocess.Popen(['taskset', '-c', '%s' %(x,), './sha', '%d'  % (number_of_messages,) ], shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE))
	exit_codes = [p.communicate() for p in phandles]
	
	sum_ = 0
	max_ = 0
	for t in exit_codes:
		n_str = extract(t[0])[0:-2]
		n_sec = float(n_str)
		print n_sec
		sum_ += n_sec
		max_ = max(max_, n_sec)
	
	avg = sum_ / number_of_process
	time_per_message = max_ /  (number_of_messages * number_of_process)
	avg_per1M = 10**6 * time_per_message
	print "avarage time per process per %s for %s messages is %s s. time per 1M messages: %s" %(number_of_process, number_of_messages, avg, avg_per1M)

main()
