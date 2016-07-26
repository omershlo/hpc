# main_script.py


import subprocess
import sys

def extract(data):
	print data
	return data.split()[7]


def main():
	phandles = []
	n_args = len(sys.argv)
	#eqToStat = 100 if n_args<3 else int(sys.argv[2])
	number_of_process = 1 if n_args<2 else int(sys.argv[1])
	print "running with %s process, eqtoBreak=142, eqToStat=%s" %(number_of_process, 106)
	for x in range(0, number_of_process):
		phandles.append (subprocess.Popen(['taskset', '-c', '%s' %(x,), './sha', ], shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE))
	exit_codes = [p.communicate() for p in phandles]
	

main()
