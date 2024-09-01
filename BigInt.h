#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <stdio.h>

#define UINT unsigned int
#define ULONG unsigned long long
#define UIVEC std::vector<unsigned int>
#define MASK 0x80000000

class BigInt
{
private:
    UIVEC _number = { 0 };
    bool _sign = false;

    void resize(size_t length);
    void shorten();
    size_t equalize(BigInt& other); // выбирает максимальную длину и добавляет 1

    void invert();
    void negate();
public:

    BigInt() {}
    BigInt(int value);
    BigInt(UINT value);
    BigInt(long long value);
    BigInt(ULONG value);

    BigInt(BigInt& other);
    BigInt(BigInt&& other) noexcept;

    ~BigInt();

    bool lengthEqual(BigInt& other) { return this->getLength() == other.getLength(); }
    bool lengthMore(BigInt& other)  { return this->getLength() >  other.getLength(); }
    bool lengthLess(BigInt& other)  { return this->getLength() <  other.getLength(); }

    bool lengthNotEqual(BigInt& other)  { return this->getLength() != other.getLength(); }
    bool lengthMoreEqual(BigInt& other) { return this->getLength() == other.getLength(); }
    bool lengthMLessEqual(BigInt& other){ return this->getLength() == other.getLength(); }

    void show();

    void add(BigInt& other);
    void subtract(BigInt& other);
    void multiply(BigInt& other);
    void divide(BigInt& other);

    size_t getLength() { return this->_number.size(); }
    bool getSign() const { return this->_sign; }
};
