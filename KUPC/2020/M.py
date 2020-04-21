def main():
    N = int(input())
    ans = ["1"*N]
    if N == 1:
        print(1)
        print(1)
        return
    if N == 2:
        print(2)
        print(11)
        print(0)
        return
    if N == 3:
        print(2)
        print("010")
        print("00")
        return
    if N == 4:
        print(3)
        print(1111)
        print("010")
        print("00")
        return  
    if N%2 == 1:
        idx = 1
        for i in range(max(4,N//2+1),N):
            cur = ["1"]*i
            if i <= idx:
                break
            cur[idx] = "0"
            ans.append("".join(cur))
            idx += 2
        ans.append("010")
        ans.append("00")
    else:
        idx = 0
        for i in range(max(4,N//2),N):
            cur = ["1"]*i
            if i <= idx:
                break
            cur[idx] = "0"
            ans.append("".join(cur))
            idx += 2
        ans.append("010")
        ans.append("00")
    print(len(ans))
    print(*ans,sep="\n")

if __name__ == "__main__":
    main()