from pwn import *
from sys import argv
# argv[1] ==> stand for the origin text for building huffman tree
# argv[2] ==> stand for the 01-sequence for decoding


huff = process('./main.out')
huff.recv()

# assign origin text. build huffman tree and flush buffer
huff.send('assign\no\n' + argv[1] + '\n')
huff.recv()
huff.send('build\n')
huff.recv()

# check tree view and table view
huff.send('tree\n')
tree = huff.recvuntil('\n\n')
huff.recv()
huff.send('table\n')
table = huff.recvuntil('\n\n')
huff.recv()

# assign 01-sequence and decode
huff.send('assign\no\n' + argv[2] + '\n')
huff.recv()
huff.send('decode\n')
plain = huff.recvuntil('\n\n')
huff.recv()

# exit the process
huff.send('exit\n')
huff.close()


print('\n===================\n' + tree)
print('\n===================\n' + table)
print('\n===================\n' + plain)

