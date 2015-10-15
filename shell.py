"""
Ben Spaeth
Python Shell Program
2/11/15
"""
import os
import subprocess
import sys

print("Welcome to the shell.\nEnter a command after the $.")
def parse(command):
	args = command.split()
	
	if args[0] == "HELP":
		help()
		main()
	elif args[0] == 'LIST':
		if len(args) == 1:
			elist()
		elif os.path.exists(args[1]):
			lists(args[1])
		else:
			print("invalid command")
			return
		main()
	elif args[0] == 'CHDIR':
		CHDIR(args[1])
		main()
	elif args[0] == 'RUN':
		run(args)
		main()
	elif args[0] == 'RMDIR':
		rmdir(args[1])
		main()
	elif args[0] == 'REMOVE':
		remove(args[1])
		main()
	elif args[0] == 'RENAME':
		rename(args[1], args[2])
		main()
	elif args[0] == 'QUIT':
		quit()
	else:
		print("invalid command")
		main()
def help():
	print("Valid commands are \nLIST\nCHDIR\nRUN\nREMOVE\nRENAME\nQUIT")
def run(args):
	pid = os.fork()
	if (pid ==0):
		subprocess.call(args[1])
	else:
		os.waitpid(pid,0)
	return
def elist():
	print(os.getcwd())
	return
def lists(path):
	print(os.listdir(path))
	return
def CHDIR(path):
	os.chdir(path)
	return
def rmdir(path):
	os.rmdir(path)
def remove(path):
	os.remove(path)
def rename(old,new):
	os.rename(old,new)
def main():
	command = raw_input("$")
	parse(command)
main()
	