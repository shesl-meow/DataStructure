import random

def gnr():
    rng = random.randint(0,10)
    lst = []
    for i in range(rng):
        lst.append( random.randint(-10,10) )
        lst.append( random.randint(-10,10) )
    return [rng] + lst

print( ' '.join([str(t) for t in gnr() + gnr()]) )