
void FWT(int *a,int len){
	for(int h = 2 ; h <= len ; h <<= 1)
			for(int i = 0 ; i < len ; i += h)
				for(int j = i ; j < i + h/2 ; ++j){
					int u = a[j],v = a[j + h/2];
					a[j] = (u+v)%mod; a[j+h/2] = (u-v+mod)%mod;
					//xor:a[j] = u + v; a[j+h/2] = u - v
					//and:a[j] = u + v; a[j+h/2] = v;
					//or:a[j] = u; a[j+h/2] = u + v;
				}
}

void UFWT(int *a,int len){
	for(int h = 2 ; h <= len ; h <<= 1)
		for(int i = 0 ; i < len ; i += h)
			for(int j = i ; j < i + h/2 ; ++j){
				int u = a[j],v = a[j + h/2];
				a[j] = 1LL*(u+v)*inv%mod; a[j+h/2] = (1LL*(u-v)*inv%mod + mod) % mod;
				//xor:a[j] = (u + v)/2; a[j+h/2] = (u - v)/2
				//and:a[j] = u - v; a[j+h/2] = v;
				//or:a[j] = u; a[j+h/2] = v - u;
			}
}
