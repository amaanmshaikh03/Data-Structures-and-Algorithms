/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name: Mohammedamaan Shaikh                    */
/*  Student number: 157304197                     */
/*                                                */
/**************************************************/

/* remember to code these in a RECURSIVE only manner*/

unsigned long long factorial (unsigned int n){
	unsigned long long fac = 1;
	if (n > 1) {
		fac = n * factorial(n - 1);
	}
	return fac;
}

unsigned long long power (unsigned int base, unsigned int n){
	unsigned long long pow = 1;
	if (n != 0) {
		pow = base * power(base, n - 1);
	}
	return pow;
}
unsigned long long fibonacci (unsigned int n){
	unsigned long long fib = n;
	if (n > 1) {
		fib = fibonacci(n - 1) + fibonacci(n - 2);
	}
}