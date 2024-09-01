#include "BigInt.h"





int main()
{
	BigInt a(0xfu);
	BigInt b(0x10ull);

	//printf("%d", 0xF0F0F0F0E1E1E1E1ull >> 63);
	a.show();
	b.show();
	printf("------------\n");
	a.add(b);
	a.show();
	printf("------------\n");
	b.subtract(a);
	b.show();
	std::cout << b.getSign();
	
	return 0;
}