T = int(raw_input())
for _ in range(T):
    n,m = [int(i) for i in raw_input().split()]
    print (str(2**(n+1)-2**(m+1))+(".00"))
