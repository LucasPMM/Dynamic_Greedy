
import random
import sys

M = int(str(sys.argv[1]))

N = random.randrange(1000,10000)

print(N, M)

for i in range(0, M):
    print(random.randrange(50,700), random.randrange(100))