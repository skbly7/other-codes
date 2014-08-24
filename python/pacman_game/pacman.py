from random import randint
import os
#FUNCTION USED FROM : https://gist.github.com/jasonrdsouza/1901709
def getchar():
	if os.name == 'nt':
		ch = raw_input('Enter your turn (w,a,s,d) : ')
	else:
	    import tty, termios, sys
	    fd = sys.stdin.fileno()
	    old_settings = termios.tcgetattr(fd)
	    try:
	    	tty.setraw(sys.stdin.fileno())
	    	ch = sys.stdin.read(1)
	    finally:
			termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
	return ch
class bcolors:
    PACMAN = '\033[1;32m'
    WALL = '\033[0;36m'
    GHOST = '\033[1;31m'
    COINS = '\033[1;37m'
    EMPTY = '\033[1;37m'
    NEWEMP = '\033[0;30m'
def rem_dup(seq):
    seen = set()
    seen_add = seen.add
    return [ x for x in seq if not (x in seen or seen_add(x))]
class Board:
	def safe_play (self):
		for i in [-1,self.__x]:
			for j in range(-1,self.__y+2):
				self.set_wall(i,j)
		for j in [-1,self.__y]:
			for i in range(-1,self.__x+2):
				self.set_wall(i,j)
	def map_with_old_wall(self,ghost=0):
		for i in range(0,self.__x):
				for j in range(0,self.__y):
					if self.__pac.get_xy != [i,j] and self.check_wall(i,j)==False:
						rand=randint(0,30)
						if rand%9==0:
							self.set_coin(i,j)
						if rand==5 and ghost==1:
							self.add_ghost(i,j)
	def __init__(self, anything=''):
		self.__score=0
		self.__ghosts=[]
		self.__coins=[]
		self.__walls=[]
		self.__change_map=0
		self.__random=0
		if(anything=='random'):
			os.system("clear")
			x = int(raw_input('\n Dimenstions of the board is needed before procceding.\n x (>5) = '))
			y = int(raw_input(' y (>5) = '))
			self.__change_map = int(raw_input('Do you want map to change after every completion (1->Yes, 0->No) : '))
			self.__x = int(x) - 2
			self.__y = int(y) - 2
			self.__pac=Pacman(randint(0,x-3),randint(0,y-3))
			self.__random=1
			self.__random_board()
		elif(anything=='level'):
			os.system("clear")
			self.__x = 15 - 2
			self.__y = 35 - 2
			self.__pac=Pacman(10,20)
			self.__level_board()
			self.__change_map=0
		self.safe_play()
	def __level_board(self):
		for j in range(1,6):
			self.set_wall(j,3)
		for j in range(6,11):
			self.set_wall(j,8)
		for j in range(3,9):
			self.set_wall(1,j)
		for j in range(3,9):
			self.set_wall(6,j)
		for j in range(3,9):
			self.set_wall(11,j)
		self.set_wall(6,11)
		for j in range(1,12):
			self.set_wall(j,14)
		for j in range(2,6):
			self.set_wall(-j+6,j+14)
		for j in range(2,6):
			self.set_wall(j+6,j+14)
		self.set_wall(6,20)
		for j in range(1,12):
			self.set_wall(j,22)
		for j in range(1,12):
			self.set_wall(j,31)
		for j in range(1,5):
			self.set_wall(j,26)
		for j in range(1,7):
			self.set_wall(6,j+23)
		for j in range(8,12):
			self.set_wall(j,26)
		self.map_with_old_wall()
		self.add_ghost(5,8)
	def __random_board(self):
		for i in range(0,self.__x):
				for j in range(0,self.__y):
					if self.__pac.get_xy != [i,j]:
						rand=randint(0,20)
						if rand==1:
							self.set_wall(i,j)
						elif rand==2:
							self.set_coin(i,j)
						elif ((rand==3)and(randint(0,5)==0)):
							self.add_ghost(i,j)
						elif rand==4:
							self.set_coin(i,j)
						elif rand==5 or rand==6:
							self.set_wall(i,j)
	def add_ghost(self,x,y):
		if(self.check_wall(x,y)==False):
			self.__ghosts+=[Ghost(x,y)]
	def add_coin(self,x,y):
		if(self.check_wall(x,y)==False):
			self.__coins+=[[x,y]]
			self.set_coin(x,y)
	def set_wall(self,x,y):
		self.__walls+=[[x,y]]
	def set_coin(self,x,y):
		if [x,y] not in self.__walls and [x,y] != self.__pac.get_xy():
			self.__coins+=[[x,y]]
	def set_pac(self,x,y):
		self.__pac.set_position(x,y)
	def check_wall(self,x,y):
		if [x,y] in self.__walls:
			return True;
		else:
			return False;
	def check_ghost(self,x,y):
		temp=[]
		for i in range(0,len(self.__ghosts)):
			temp+=[self.__ghosts[i].get_xy()]
		if [x,y] in temp:
			return True;
		else:
			return False;
	def check_coin(self,x,y):
		if [x,y] in self.__coins:
			return True;
		else:
			return False;
	def display_char(self,x,y):
		temp=[]
		h=len(self.__ghosts)
		for i in range(0,h):
			temp+=[self.__ghosts[i].get_xy()]
		if [x,y] in temp:
			print bcolors.GHOST+"G",
		elif [x,y] == self.__pac.get_xy():
			print bcolors.PACMAN+"P",
		elif [x,y] in self.__walls:
			print bcolors.WALL+"X",
		elif [x,y] in self.__coins:
			print bcolors.COINS+"C",
		else:
			print bcolors.NEWEMP+".",
	def display(self):
		print ""
		for i in range(-1,self.__x+1):
			for  j in range(-1,self.__y+1):
				self.display_char(i,j)
			print ""
		print bcolors.EMPTY+""
	def __checkGhost():
		over=0
		loc=self.__pac.get_xy()
		for i in range(0,len(self.__ghosts)):
			if(self.__ghosts[i].get_xy()==loc):
				over=1
				break
		if over==1:
			return False
			#Don't over
		else:
			return True
			#Over the game
	def collectCoin(self,out):
		self.__coins.remove([out[0],out[1]])

	def player_turn(self):
		play=1
		over=0
		os.system("clear")
		self.display()
		while(play):
			out=self.__pac.move_packman_input('Enter your turn sir (w,a,s,d) : ')
			os.system("clear")
			if self.check_wall(out[0],out[1]) == False:
				self.__pac.set_position(out[0],out[1])
			if self.check_coin(out[0],out[1]) == True:
				self.__score+=10
				self.collectCoin(out)
			for i in range(0,len(self.__ghosts)):
				possible_moves=self.__ghosts[i].move_ghost_future_preference(self.__pac)
				for j in range(0,len(possible_moves)):
					if self.check_wall(possible_moves[j][0],possible_moves[j][1]) == False and self.check_ghost(possible_moves[j][0],possible_moves[j][1]) == False:
						self.__ghosts[i].set_position(possible_moves[j][0],possible_moves[j][1])
						break
				if possible_moves[j]==self.__pac.get_xy():
					over=1
			if (over==1):
				play=0
			if (out[2]=='q' or out[2]=='Q'):
				play=0
				print "Thank you for playing PACMAN ! :)"
			else:
				self.display()
				print "Score : "+self.get_score()+"  Coins left : "+str(len(self.__coins))
			if over==1:
				print "Game Over !"
			if len(self.__coins)==0 and self.__random==1:
				os.system("clear")
				self.__ghosts=[]
				self.__coins=[]
				if(self.__change_map==1):
					self.__walls=[]
					self.__random_board()
				else:
					self.map_with_old_wall(1)
				self.safe_play()
				self.display()
				print "Score : "+self.get_score()+"  Coins left : "+str(len(self.__coins))
			if self.__random==0 and len(self.__coins)==0:
				self.add_ghost(5,8)
				self.map_with_old_wall(0)
	def get_score(self):
		return str(self.__score)

class Person:
	def __init__(self,x=0,y=0):
		self.__x=x
		self.__y=y
	def set_position(self,x,y):
		self.__x=x
		self.__y=y
	def get_x(self):
		return self.__x
	def get_y(self):
		return self.__y
	def get_xy(self):
		return [self.__x,self.__y]

class Pacman(Person):
	def move_packman_input(self,msg=''):
		x_n=self.get_x()
		y_n=self.get_y()
		inp=getchar()
		#inp=raw_input(msg)
		if(inp=="a" or inp=="A"):
			x_n = self.get_x()
			y_n = self.get_y()-1
		if(inp=="d" or inp=="D"):
			x_n = self.get_x()
			y_n = self.get_y()+1
		if(inp=="s" or inp=="S"):
			x_n = self.get_x()+1
			y_n = self.get_y()
		if(inp=="w" or inp=="W"):
			x_n = self.get_x()-1
			y_n = self.get_y()
		return [x_n,y_n,inp]

class Ghost(Person):
	def move_ghost_future_preference(self,Packman):
		jaadu = []
		x = self.get_x()
		y = self.get_y()
		if x - Packman.get_x() >	0 :
			if y - Packman.get_y() > 0 :
				jaadu = [[x-1,y],[x,y-1],[x+1,y],[x,y+1],[x,y]]
			elif y - Packman.get_y() < 0 :
				jaadu = [[x-1,y],[x,y+1],[x+1,y],[x,y-1],[x,y]]
			else :
				jaadu = [[x-1,y],[x+1,y],[x,y]]				
		elif x - Packman.get_x() <	0 :
			if y - Packman.get_y() > 0 :
				jaadu = [[x+1,y],[x,y-1],[x-1,y],[x,y+1],[x,y]]
			elif y - Packman.get_y() < 0 :
				jaadu = [[x+1,y],[x,y+1],[x,y-1],[x-1,y],[x,y]]
			else:
				jaadu = [[x+1,y],[x-1,y],[x,y]]
		else :
			if y - Packman.get_y() > 0 :
				jaadu = [[x,y-1],[x,y+1],[x,y]]
			elif y - Packman.get_y() < 0 :
				jaadu = [[x,y+1],[x,y-1],[x,y]]
			else:
				jaadu = [[x,y]]

		return jaadu


os.system("clear")
print "Please select a option :\n \n1. Play level wise\n2. Play on a random map\n3. Quit\n\n"
inp=input('Enter your choice : ')
inp=int(inp)
if inp==1:
	t=Board('level')
	t.player_turn()
elif inp==2:
	t=Board('random')
	t.player_turn()
elif inp==3:
	print "Thank you for using the program.. :)"
else:
	print "Wrong input !! \nQuitting program...."
#os.system("clear")
#t.display()