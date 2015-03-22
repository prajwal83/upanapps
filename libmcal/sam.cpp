#include <stdio.h>


class A
{
	private:
		int a ;
	public:
		A(int x) : a(x) { }
		void set(int x) { a = x ; }
		void dis() { printf("\n a = %d", a) ; }
} ;

int main()
{
	A a1(1) ;
	A a100(100) ;
	a1.dis() ;
	a100.dis() ;

	return 0 ;
}
