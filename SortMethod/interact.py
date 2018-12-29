from pwn import *
import random
import time

f = open('result.md', 'w')
f.write('# Test Result.\n\n')

s = process('./main.out')
s.recvuntil('$ ')

# TODO: generate 20 thousands random numbers
r = [random.uniform(0,1000) for i in range(20000)]
f.write('## Origin Text\n\n[origin data](./data/random.txt)\n\n')
with open('./data/random.txt', 'w') as ff:
    ff.write('\n'.join([str(fl) for fl in r]))

# TODO: assign 20 thousands to the process
s.send('assign\n')
s.send('\n'.join([str(fl) for fl in r]))
s.send('\n.\n')
s.recvuntil('$ ')

# TODO: analysis by different sort method
f.write('## Sort Method\n\n')
sort_method = ['Bubble', 'Insert', 'Select', 'Shell', 'Merge']
for method in sort_method:
    print('Test method:' + method)
    f.write('### ' + method + '\n\n')
    beg = time.time()
    s.send(method + '\n')
    s.recvuntil('$ ')
    end = time.time()

    s.send('detail\n')
    detail = s.recvuntil('$ ')[:-2]
    s.send('check\n')
    res = s.recvuntil('$ ')[:-2]
    
    f.write('*detail*:\n' + detail + '\n')
    with open('./data/' + method + '.txt', 'w') as ff:
        ff.write(res);
    f.write('*result*:\n' + '[' + method + '](./data/' + method + '.txt)\n\n')
    f.write('*time*:\n' + str(end-beg) + 's\n\n')

    s.send('reset\n')
    s.recvuntil('$ ')

s.close()
f.close()
