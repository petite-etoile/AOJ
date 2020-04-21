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
import matplotlib.pyplot as plt
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
class P:
    def __init__(self,x,y):
        self.x = x
        self.y = y
    
    def __str__(self):
        return str(self.x) + " " + str(self.y)
    __repr__ = __str__
    

    def __add__(self,p):
        return P(self.x+p.x, self.y+p.y)
    
    __radd__ = __add__
        
    def __sub__(self, p):
        return P(self.x-p.x, self.y-p.y)

    def __mul__(self,other):
        return P(self.x*other, self.y*other)

    def __truediv__(self, other):
        return P(self.x/other, self.y/other)

    # def __rsub__(self, other):
    #     if isinstance(other, ModInt):
    #         return ModInt(other.x - self.x)
    #     else:
    #         return ModInt(other - self.x)

ansx = []
ansy = []

def koch(n,left,right):
    if n==0:
        return 
    w = ((right-left)/3)
    s = left + w
    t = left + w*2
    center = (s+t)/2 #sとtの中点
    vec1 = (t-s)*sqrt(3)/2 #sからtへのベクトルの√3/2倍
    vec2 = P(-vec1.y, vec1.x) 
    u = center + vec2

    koch(n-1,left, s)

    print(s)
    ansx.append(s.x)
    ansy.append(s.y)

    koch(n-1, s, u)

    print(u)
    ansx.append(u.x)
    ansy.append(u.y)

    koch(n-1,u,t)

    print(t)
    ansx.append(t.x)
    ansy.append(t.y)

    koch(n-1,t,right)

def main():
    n = int(input())
    left = P(0,0)
    right = P(100,0)
    print(left)
    ansx.append(0)
    ansy.append(0)
    koch(n,P(0,0),P(100,0))
    print(right)
    ansx.append(100)
    ansy.append(0)
    plt.plot(ansx,ansy)
    plt.show() 
if __name__ == '__main__':
    main()


""" AOJ提出
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
ans = []
class P:
    def __init__(self,x,y):
        self.x = x
        self.y = y
    
    def __str__(self):
        return str(self.x) + " " + str(self.y)
    __repr__ = __str__
    

    def __add__(self,p):
        return P(self.x+p.x, self.y+p.y)
    
    __radd__ = __add__
        
    def __sub__(self, p):
        return P(self.x-p.x, self.y-p.y)

    def __mul__(self,other):
        return P(self.x*other, self.y*other)

    def __truediv__(self, other):
        return P(self.x/other, self.y/other)

    # def __rsub__(self, other):
    #     if isinstance(other, ModInt):
    #         return ModInt(other.x - self.x)
    #     else:
    #         return ModInt(other - self.x)


def koch(n,left,right):
    if n==0:
        return 
    w = ((right-left)/3)
    s = left + w
    t = left + w*2
    center = (s+t)/2 #sとtの中点
    vec1 = (t-s)*sqrt(3)/2 #sからtへのベクトルの√3/2倍
    vec2 = P(-vec1.y, vec1.x) 
    u = center + vec2

    #print(left)
    koch(n-1,left, s)
    print(s)
    koch(n-1, s, u)
    print(u)
    koch(n-1,u,t)
    print(t)
    koch(n-1,t,right)
    #print(right)
    


    # print(*left)
    # koch(n-1,left,s)
    # print(*s)
def main():
    n = int(input())
    left = P(0,0)
    right = P(100,0)
    print(left)
    koch(n,P(0,0),P(100,0))
    print(right)
    #print(ans)
if __name__ == '__main__':
    main()
"""