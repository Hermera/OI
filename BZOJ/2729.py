def A(n, m):
	ret = 1
	if(n < m): return 0
	for i in range(n-m+1, n+1): ret *= i
	return ret

n, m = map(int, raw_input().split())
print A(n, n)*(A(n+1, 2)*A(n+3, m) + A(m, 1)*A(2, 2)*A(n+1, 1)*A(n+2, m-1))

