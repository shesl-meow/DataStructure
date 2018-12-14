from pwn import *
import random
import sys
# argv[1] ==> the row numbers of circuit board
# argv[2] ==> the column numbers of circuit board
# argv[3] ==> the laser size

if len(sys.argv) < 4:
    print("please provide row&column number and laser size as argument.")
    exit(1)

mp = [''.join([random.choice(['0', '1']) 
        for j in range(int(sys.argv[2]))])
        for i in range(int(sys.argv[1]))]

p = process('./main.out')
p.send('\n'.join(mp))
p.send('\n.\n')

p.send(sys.argv[3] + '\n')

msg = p.recvall()
print(msg)
p.close()
