import sys
input=sys.stdin.readline
from copy import deepcopy
inf=float('inf')
def main():
    N = int(input())
    *A, = map(int,input().split())
    Q = int(input())
    *B, = map(int,input().split())

    bit_max = 1<<N
    S = set()
    for bit in range(bit_max):
        sum_ = 0
        for i in range(N):
            if(bit & (1<<i)):
                sum_ += A[i]
        S.add(sum_)
    

    for q in B:
        if q in S:
            print("yes")
        else:
            print("no")

    
if __name__ == '__main__':
    main()
