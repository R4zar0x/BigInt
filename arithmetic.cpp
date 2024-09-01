#include "BigInt.h"

struct result
{
	UINT val;
	bool CF;
};

static void printBinary(int n)
{
	for (int i = sizeof(int) * 8 - 1; i >= 0; --i) 
	{
		std::cout << ((n >> i) & 1);
	}
}

static result addAsm(UINT left, UINT right)
{
	UINT val = 0;
	bool CF = 0;

	__asm
	{
		mov eax, left
		mov ebx, right
		add eax, ebx

		pushfd
		pop ebx
		and ebx, 0x1

		mov CF, bl
		mov val, eax
	}

	return {val, CF};
}

static result fullAdd(UINT left, UINT right, bool previousCF)
{
	result temp = addAsm(left, right);
	bool CF = temp.CF;
	
	temp = addAsm(temp.val, previousCF);
	temp.CF += CF;

	return temp;
}

void BigInt::add(BigInt& other)
{
	result temp = {0, 0};
	size_t maxLength = this->equalize(other);

	for (size_t i = 0; i < maxLength; i++)
	{
		temp = fullAdd(this->_number[i], other._number[i], temp.CF);
		this->_number[i] = temp.val;
	}

	this->shorten();
}

void BigInt::subtract(BigInt& other)
{
	other.negate();
	
	this->add(other);

	if (this->_number[this->getLength() - 1] == 0x1u)
	{
		this->_number.resize(this->getLength() - 1);
	}
	else
	{
		this->_sign = true;
	}
}
