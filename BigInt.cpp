#include "BigInt.h"

BigInt::BigInt(int value)
{
    this->_number.resize(1);
    this->_number[0] = ((UINT)(value)) & ~MASK;
    
    this->_sign = ((UINT)(value)) >> 31;
}

BigInt::BigInt(UINT value)
{
    this->_number.resize(1);
    this->_number[0] = value;

    printf("UINT constructor, size %d\n", this->_number.size());
}

BigInt::BigInt(long long value)
{
    this->_number.resize(2);
    this->_number[0] = ((ULONG)(value));
    this->_number[1] = (((ULONG)(value)) >> 32) & ~MASK;

    this->_sign = ((ULONG)(value)) >> 63;

    this->shorten();
}

BigInt::BigInt(ULONG value)
{
    this->_number.resize(2);
    this->_number[0] = value;
    this->_number[1] = value >> 32;

    this->shorten();
}

BigInt::BigInt(BigInt& other) :
    _number(other._number),
    _sign(other._sign)
{}

BigInt::BigInt(BigInt&& other) noexcept :
    _number(std::move(other._number)),
    _sign(other._sign)
{
    other._number = { 0 };
    other._sign = false;
}

BigInt::~BigInt()
{

}