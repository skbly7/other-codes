import commands
import signal
import sys
import os
import shutil
from os.path import expanduser
from os import popen
with popen('clear') as f:
    clear = f.read()
user=os.getenv('USER')
pc_name=os.uname()[1]



def main():
	while(1):
		try:
			raise_parameter_error=0
			command=take_input()
			command=command.split()
			i=0
			while i<len(command):
				if(command[i][-1:]=='\\' and (i+1<len(command))):
					command[i]=command[i][:-1]+" "+command[i+1]
					command.remove(command[i+1])
				i+=1
			parameters=[]
			other=[]
			for x in command[1:]:
				if x[0]=='-':
					parameters+=list(x[1:])
					if x[1]=='-':
						raise_parameter_error=1
				else:
					other+=[x]
			if raise_parameter_error==1:
				print "Ambiguous parameters passed."
				continue
			if(len(command)<1):
				command=['']
			if command[0]=='rm':
				rm_call(parameters,other)
			elif command[0]=='ls':
				ls_call(parameters)
			elif command[0]=='cp':
				cp_call(other)
			elif command[0]=='help':
				help_display(other)
			elif command[0]=='exit':
				break
			elif command[0]=='clear':
				print clear
			elif command[0]=='mkdir':
				mkdir_self(other)
			elif command[0]=='mv':
				move_call(other)
			elif command[0]=='cd':
				cd_self(other)
			elif command[0]=='dir':
				ls_call(parameters,1)
			elif command[0]=='dirstr':
				dirstr()
			elif command[0]=='':
				continue
			else:
				print command[0]+": command not found"
		except Exception as inst:
			print "Error processing your request, use 'help' to get list of supported commands"

#####################################################
#### PROGRAM RELATED FUNCTIONS
#####################################################

def cd_self(other):
	if len(other)>0 and (os.path.isfile(other[0])==False) and (os.path.exists(other[0])==True):
		os.chdir(other[0])
	elif len(other)==0:
		os.chdir(os.environ['HOME'])
	elif os.path.isfile(other[0]):
		print "bash: cd: "+other[0]+": Not a directory"
	else:
		print "bash: cd: "+other[0]+": No such file or directory"
def mkdir_self(other):
	for x in other:
		os.mkdir(x)

def move_call_old(other):
#	os.rename(other[0],other[1])
	all_files=[]
	temp=[]
	di=(os.path.isfile(other[-1])==False) and (os.path.exists(other[-1])==True)
	for x in other[:-1]:
#		print str(os.path.exists(x[:-1]))+" for "+x[:-1]
		if(x[-1]=="*" and x[-2]=="/" and os.path.exists(x[:-1])):
			temp+=os.listdir(x[:-1])
			for files in temp:
				all_files+=[x[:-1]+files]
		elif os.path.exists(x):
			all_files+=[x]
		else:
			print "mv: cannot stat '"+x+"': No such file or directory"
	#all_files=os.listdir((other[0])[:-1])
	#print all_files
	for x in all_files:
#		print x
		if os.path.isfile(x) and (di or len(other)<3):
			shutil.move(x,other[-1])
		elif di==False and len(other)>2:
			print "cp: "+other[-1]+" is not a directory"
			break
		else:
			print "cp: omitting directory '"+x+"'"

def move_call(other):
	if(len(other)<2):
		print "mv : Please pass arguments properly"
		return
	di=(os.path.isfile(other[-1])==False) and (os.path.exists(other[-1])==True)
	for x in other[:-1]:
		if os.path.exists(x)==True:
			shutil.move(x,other[-1])
		elif x[-1]=="*" and x[-2]=="/":
			all_files=os.listdir(x[:-1])
			for y in all_files:
				shutil.move(x[:-1]+y,other[-1])
		else:
			print "mv : "+x+" doen't exist"

def cp_call_old(files):
	length=len(files)
	if(length<2):
		print "Atleast pass one source and one destination file name !"
		return
	di=(os.path.isfile(files[length-1])==False) and (os.path.exists(files[length-1])==True)
	if di and length>2:
		shutil.copytree ((files[0])[:-1],files[length-1])
	elif length>2:
		print "cp: target '"+files[length-1]+"' is not a directory"
	elif os.path.isfile(files[0]):
		shutil.copy(files[0],files[1])
	elif os.path.exists((files[0])[:-1]) and (files[0])[-1]=='*' and di:
	#	shutil.copytree ((files[0])[:-1],files[length-1])
		all_files=os.listdir((files[0])[:-1])
		for x in all_files:
			if os.path.isfile((files[0])[:-1]+x):
				shutil.copy((files[0])[:-1]+x,files[length-1])
			else:
				print "cp: omitting directory '"+(files[0])[:-1]+x+"'"
	elif os.path.exists((files[length-1])[:-1]) and (files[length-1])[-1]=='*':
		print "cp: target '"+files[length-1]+"' is not a directory"
	else:
		print "Source path doesn't exist"

def cp_call(files):
	length=len(files)
	if(length<2):
		print "Atleast pass one source and one destination file name !"
		return
	di=(os.path.isfile(files[length-1])==False) and (os.path.exists(files[length-1])==True)
	for x in files[:-1]:
		if os.path.exists(x)==True:
			if os.path.isfile(x):
				shutil.copy(x,files[-1])
			else:
				shutil.copytree(x,files[-1])
		elif x[-1]=="*" and x[-2]=="/":
			all_files=os.listdir(x[:-1])
			for y in all_files:
				if os.path.isfile(x[:-1]+y):
					shutil.copy(x[:-1]+y,files[-1])
				else:
					shutil.copytree(x[:-1]+y,files[-1]+"/"+y)
		else:
			print "cp : "+x+" doen't exist"	
def ls_call(parameters,dirr=0):
	error=0
	a=0
	A=0
	p=0
	l=0
	for x in parameters:
		if(x=='a'):
			a=1
		elif(x=='A'):
			A=1
		elif(x=='p'):
			p=1
		elif(x=='l'):
			l=1
		elif(x=='a'):
			a=1
		else:
			error=1
			print "Sorry parameter '"+x+"' can't be understood. Use help for more info."
			break
	if error==0:
		if l==1:
			ls_advanced(a,A,p)
		else:
			ls_simple(a,A,p,dirr)

def rm_call(parameters,path):
	error=0
	r=0
	R=0
	for x in parameters:
		if(x=='R'):
			R=1
		elif(x=='r'):
			r=1
		else:
			error=1
			print "Sorry parameter '"+x+"' can't be understand. Use help for more info."
			break
	if(len(path)<1):
		error=1
		print "rm: missing operand"
	if error==0:
		for j in path:
				rm_work(r,R,j)

def rm_work(r=0,R=0,x='/never/to/be/empty/'):
	rec=0
	if r==1 or R==1:
		rec=1
	if os.path.exists(x):
		if rec==0 and os.path.isfile(x):
			os.remove(x)
		elif rec==0:
			print "rm: cannot remove '"+x+"': Is a directory"
		elif rec==1 and os.path.isfile(x):
			os.remove(x)
		else:
			shutil.rmtree(x)
	elif x[-1]!='*':
		print "rm: cannot remove '"+x+"' : No such file or directory"
	elif os.path.exists(x[:-1]) or (x[0]=='*' and len(x)==1):
		if len(x)!=1:
			all_files=os.listdir(x[:-1])
		else:
			all_files=os.listdir(os.getcwd())
		for x1 in all_files:
			if os.path.isfile(x[:-1]+x1):
				os.remove(x[:-1]+x1)
			else:
				if(rec==1 and os.path.exists(x[:-1]+x1)):
					shutil.rmtree(x[:-1]+x1)
#					os.remove(x[:-1]+x1)
				else:
					print "rm: cannot remove '"+x[:-1]+x1+"': Is a directory"
	else:
		print "rm: cannot remove '"+x+"' : No such file or directory"

def ls_simple(a=0,A=0,p=0,dirr=0):
	if(a==1):
		if p==1:
			print bcolors.OKBLUE+"./  ../ ",
		else:
			print bcolors.OKBLUE+".  .. ",
	all_files=os.listdir(os.curdir)
	for x in sorted(all_files,key=str.lower):
		if x[0]!='.' or a==1 or A==1 and dirr==0:
			if os.path.isfile(x) and x[0]!='.':
				print bcolors.ENDC+x+" ",
			elif p==1 and not(os.path.isfile(x)):
				print bcolors.OKBLUE+x+"/ ",
			else:
				print bcolors.OKBLUE+x+" ",					
		elif x[0]!='.' or a==1 or A==1 and dirr==1:
			print x+" ",
	print bcolors.ENDC

def ls_advanced(a=0,A=0,p=0):
	if(a==1):
		if p==1:
			print bcolors.ENDC+(commands.getstatus('.')).rsplit(' ', 1)[0]+bcolors.OKBLUE+" ."+"/ "
			print bcolors.ENDC+(commands.getstatus('..')).rsplit(' ', 1)[0]+bcolors.OKBLUE+" .."+"/ "
		else:
			print bcolors.ENDC+(commands.getstatus('.')).rsplit(' ', 1)[0]+bcolors.OKBLUE+" ."+" "
			print bcolors.ENDC+(commands.getstatus('..')).rsplit(' ', 1)[0]+bcolors.OKBLUE+" .."+" "
	all_files=os.listdir(os.curdir)
	for x in sorted(all_files,key=str.lower):
		if x[0]!='.' or a==1 or A==1:
			if os.path.isfile(x) and x[0]!='.':
				print bcolors.ENDC+(commands.getstatus(x)).rsplit(' ', 1)[0]+" "+x+" "
			elif p==1 and not(os.path.isfile(x)):
				print bcolors.ENDC+(commands.getstatus(x)).rsplit(' ', 1)[0]+bcolors.OKBLUE+" "+x+"/ "
			else:
				print bcolors.ENDC+(commands.getstatus(x)).rsplit(' ', 1)[0]+bcolors.OKBLUE+" "+x+" "					
	print bcolors.ENDC
def dirstr():
	special_function(os.getcwd(),0)
def special_function(path,space):
	temp=-1
	while temp<space:
			print '|'.ljust(3),
			temp+=1
	print "#------------------ Folder : "+path.split('/')[-1]+" -----------#"
	dirs=[]
	files=[]
	temp=-1
	all_files=os.listdir(path)
	for x in all_files:
		if os.path.isdir(path+"/"+x):
			dirs+=[path+"/"+x]
		else:
			files+=[path+"/"+x]
	for x in dirs:
		special_function(x,space+1)
	if(len(files)>0):
		for x in files:
			temp=0
			while temp<space:
				print '|'.ljust(3),
				temp+=1
			print '|'.ljust(3),
			print "#- "+x.split('/')[-1]
			temp=-1
			if files[-1]!=x:
				while temp<space:
					print '|'.ljust(3),
					temp+=1
				print '|'.ljust(3)
			else:
				temp=0
				while temp<space:
					print '|'.ljust(3),
					temp+=1
				print '|'.ljust(3)
	else:
		temp=0
		while temp<space:
			print '|'.ljust(3),
			temp+=1
		print '|'.ljust(3),

		print "		(EMPTY DIRECTORY)"
#####################################################
#### LETS GIVE IT SOME TERMINAL TOUCH
#####################################################
# FROM http://stackoverflow.com/questions/287871/print-in-terminal-with-colors-using-python
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

def take_input():
	return raw_input(user+'@'+pc_name+':'+see_directory()+'$ ')

def signal_handler(signal, frame):
        print('')
        sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)

def see_directory(x=0):
	path=os.getcwd()
	if x==0:
		return path.replace(os.environ['HOME'],'~',1)
	else:
		return path

def help_display(command):
	if len(command)<1:
		print "We support the following commands : \nmv, cp, rm, ls, mkdir, cd, help, exit, clear, dir and special 'dirstr'\n\nType help <command> to know more about it."
	if command[0]=='rm':
		print "rm\nRemove file(s)/directory(s)\nSyntax :\nrm <file_1> <file_2> <file_3> <file_4>\n\nArguments : \n-r,R : use to remove directories (directories are omitted by default)\ndirectory/* also works"
	elif command[0]=='ls':
		print "ls\nList the current directory\n\nSyntax :\nls -[parameters]\n\nParameters available :\n-a : Shows all the hidden files too along with other general files.\n-A : Almost shows all files (actually it just hide . and .. from you)\n-p : Shows a \"\\\" after your folder names\n-l : List all information related to file too\n-apl, -Al, etc.. etc.. are also allowed to be used. "
	elif command[0]=='cp':
		print "cp\nCopy file(s)/directory(s)\nSyntax :\ncp <file_1> <file_2> <file_3> <destination>\n\ndirectory/* also works"
	elif command[0]=='help':
		print "I guess you are already using it..! :P"
	elif command[0]=='exit':
		print "Brutefully kill my shell, you can use it as soon as you feel boarded in this limited edition shell."
	elif command[0]=='clear':
		print "clear\nClears the screen\n\nSyntax :\nclear"
	elif command[0]=='mkdir':
				print "mkdir\nCreate directory(s)\nSyntax :\nmkdir <dir_1> <dir_2> .... <dir_x>\n"
	elif command[0]=='mv':
		print "mv\nMove file(s)/directory(s)\nSyntax :\nmv <file_1> <file_2> <file_3> <destination>\n\nYou can move as many files you wish, but remember to give destination as a 'folder' if you are working with many files to be moved.\ndirectory/* also works"
	elif command[0]=='cd':
		print "cd\nMoves around in a virtual world\n\nSyntax :\ncp <relative_path>\n\nSimply give relative path of where you wish to go and you will reach there, as simple as that... :)"
	elif command[0]=='dir':
		print "dir\nList the current directory\n\nSyntax :\ndir"
	elif command[0]=='dirstr':
		print "dirstr\nSpecial function\n\nSyntax :\ndirstr\n\nSample output :\nHmmm sorry, I guess it is really special, why don't you just try right now ?\nPROMISE : Any damage to any file wouldn't be caused..! :)"

if __name__=="__main__":
	main()
