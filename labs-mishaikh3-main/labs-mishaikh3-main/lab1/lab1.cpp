/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name:    Mohammedamaan Iqbal Shaikh           */
/*  Student number:  157304197                    */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

unsigned long long factorial (unsigned int n){
	unsigned long long fac = 1;
	for (int i = 2; i <= n; i++) {
		fac *= i;
	}
	return fac;
}

unsigned long long power (unsigned int base, unsigned int n){
	unsigned long long pow = 1;
	for (int i = 0; i < n; i++) {
		pow *= base;
	}
	return pow;
}
unsigned long long fibonacci (unsigned int n){
	unsigned long long fibpt = 1, fibmain = 0, fibdemo = 0;
	for (int i = 1; i <= n; i++)
	{
		fibdemo = fibpt + fibmain;
		fibpt = fibmain;
		fibmain = fibdemo;
	}
	return fibmain;
}
