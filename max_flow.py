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
class Dinitz:
    #edge := (to, capa, rev_index)

    def __init__(self, N):
        self.__N = N
        self.__Graph = [[] for _ in range(N)] #to, capa, rev_index
        self.__level = [0] * N
        self.__iter = [0]*N

    def add_edge(self, from_, to, capa):
        self.__Graph[from_].append([to, capa, len(self.__Graph[to])])
        self.__Graph[to].append([from_, 0, len(self.__Graph[from_])-1 ])
    
    def solve(self, source:int, target:int):
        self.__target = target
        flow = 0
        while self.leveling_bfs(source):
            self.__iter = [0] * self.__N
            while True:
                delta = self.dfs(source, inf)
                if not delta:
                    break
                flow += delta
        return flow


    def leveling_bfs(self, source: int) -> bool:
        self.__level = [-1] * self.__N
        self.__level[source] = 0
        queue = deque([source])

        pop = queue.popleft
        append = queue.append
        while queue:
            from_ = pop()
            for to, capa, _ in self.__Graph[from_]:
                if capa > 0 > self.__level[to]:
                    self.__level[to] = self.__level[from_] + 1
                    append(to)
        return self.__level[self.__target] != -1 #到達可能ならTrue

    def dfs(self, from_:int,  flow:int) ->int:
        if from_ == self.__target:
            return flow
        for i in range(self.__iter[from_], len(self.__Graph[from_])):
            self.__iter[from_] = i
            to, capa, rev = edge = self.__Graph[from_][i]
            if capa and self.__level[from_] < self.__level[to]:
                delta = self.dfs(to, min(flow,capa))
                if delta: #増加パス
                    edge[1] -= delta #capaをへらす
                    self.__Graph[to][rev][1] += delta #逆辺のcapaを増やす
                    return delta
        return 0

def main():
    N,M = MI()
    dinic = Dinitz(N)
    for _ in range(M):
        a,b,c = MI()
        dinic.add_edge(a,b,c)
    ans = dinic.solve(0,N-1)
    print(ans)

if __name__ == '__main__':
    main()