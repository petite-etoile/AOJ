#
# 　　  ⋀_⋀　 
#　　  (･ω･)  
# .／ Ｕ ∽ Ｕ＼
#  │＊　合　＊│
#  │＊　格　＊│ 
#  │＊　祈　＊│ 
#  │＊　願　＊│ 
#  │＊　　　＊│ 
#      ￣
#
import sys
sys.setrecursionlimit(10**6)
input=sys.stdin.readline
from math import floor,ceil,sqrt,factorial,log #log2ないｙｐ
from heapq import heappop, heappush, heappushpop
from collections import Counter,defaultdict,deque
from itertools import accumulate,permutations,combinations,product,combinations_with_replacement
from bisect import bisect_left,bisect_right
from copy import deepcopy
inf=float('inf')
mod = 10**9+7
def pprint(*A): 
    for a in A:     print(*a,sep='\n')
def INT_(n): return int(n)-1
def MI(): return map(int,input().split())
def MF(): return map(float, input().split())
def MI_(): return map(INT_,input().split())
def LI(): return list(MI())
def LI_(): return [int(x) - 1 for x in input().split()]
def LF(): return list(MF())
def LIN(n:int): return [I() for _ in range(n)]
def LLIN(n: int): return [LI() for _ in range(n)]
def LLIN_(n: int): return [LI_() for _ in range(n)]
def LLI(): return [list(map(int, l.split() )) for l in input()]
def I(): return int(input())
def F(): return float(input())
def ST(): return input().replace('\n', '')
def main():
    N,M = MI()
    edge = [[]for _ in range(N)]
    indegree = [0]*N #入次数
    for _ in range(M):
        a,b = MI()
        edge[a].append(b)
        indegree[b] += 1
    #print(indegree)
    #入次数が0の点からあれしていく
    queue = deque() 
    for i,x in enumerate(indegree):
        if not x:
            queue.append(i)

    pop = queue.popleft
    topological_index = [] #トポロジカルソート順
    while queue:
        v = pop()
        topological_index.append(v)

        for to in edge[v]:
            indegree[to] -= 1
            if not indegree[to]:
                queue.append(to)
    if tuple(1 for i in indegree if i!=0):
        print("loop")

    print(*topological_index,sep="\n")



if __name__ == '__main__':
    main()