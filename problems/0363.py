# give up
H, N = map(int, input().split())
ng = [0] * H
for i in range(N):
    x, y = map(int, input().split())
    ng[y] += 1 << (x)
*bits, = map(int, [0b1111, 0b1100, 0b0011, 0b0110])
dp = [[0, 0]for i in range(H)]
for i in range(1, H):
    new = 0
    for bit in bits:
        block = 0
        if bit & ng[i] or bit & ng[i - 1]:
            continue
        else:
            block = bit - (bit & dp[i - 1][1])
            if block in (int(0b1100), int(0b0011), int(0b0110)):
                new = 1
            elif block == int(0b1111):
                new = 2
            elif block == int(0b1001):
                new = 1
                block = int(0b1111)
            else:
                new = 0
                block = 0
            break
    if i == 1:
        dp[i][0] = new
        dp[i][1] = block
    else:
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][0] + new)
        dp[i][1] = block
        # dp[i]=max(dp[i-1],dp[i-2]+なにか)
print(dp[-1][0])
