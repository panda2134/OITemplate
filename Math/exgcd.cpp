void exgcd(int a, int b, int &d, int &x, int &y) {
	if(b == 0) { d = a, x = 1, y = 0; }
	else {
		exgcd(b, a % b, d, y, x); y -= x * (a / b);
	}
}