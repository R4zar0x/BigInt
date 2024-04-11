#pragma once
#include <iostream>

class BigInt 
{
protected:
    unsigned int* _buffer;
    size_t _length;

    friend static BigInt _addRaw(const BigInt& lhs, const BigInt& rhs);
    friend static BigInt _subRaw(const BigInt& lhs, const BigInt& rhs);
    friend static BigInt _mulRaw(const BigInt& lhs, const BigInt& rhs);
    friend static BigInt _divRaw(const BigInt& lhs, const BigInt& rhs);
    friend static BigInt _modRaw(const BigInt& lhs, const BigInt& rhs);
    friend static BigInt _powRaw(const BigInt& lhs, const BigInt& rhs);

    static bool _equalLength(const BigInt& lhs, const BigInt& rhs);
    static bool _moreThenLength(const BigInt& lhs, const BigInt& rhs);
    static bool _lessThenLength(const BigInt& lhs, const BigInt& rhs);

    static void _removeSpaces(std::string& str);
    static void _swap(std::string& str);

    std::string _BigIntToDecString() const; // TODO
    std::string _BigIntToHexString() const;
    std::string _BigIntToBinString() const;

    void _DecStringToBigInt(std::string expression); 
    void _HexStringToBigInt(std::string expression);
    void _BinStringToBigInt(std::string expression);

    void _shiftLeft();
    void _shiftRight();

    char _intToHex(unsigned int value) const;
    unsigned int _hexToInt(char value) const;

    void _pushBack(unsigned int value);
    void _pushFront(unsigned int value, size_t count);

    void _resize(size_t sz); // TODO
    void _removeFrontZeros();
    void _makeAddiction();

    bool _isZero() const;
    unsigned int _getBit(size_t bitIndex) const;
    unsigned int _getSign() const;
    void _setSign(bool negative);
   

public:
    BigInt();
    BigInt(int other);
    BigInt(unsigned int other);
    BigInt(long long other);
    BigInt(unsigned long long other);
    BigInt(std::string& other);
    BigInt(const BigInt& other);
    BigInt(BigInt&& other) noexcept;

    ~BigInt();

    std::string toString(const char com[4]);

    bool lengthEqualTo(BigInt& other);
    bool lengthLongerTo(BigInt& other);
    bool lengthLessTo(BigInt& other);

    void pow(BigInt pow);

    // Conversion
    operator std::string();
    operator int();
    operator unsigned int();
    operator long long();
    operator unsigned long long();

    // Assignment
    BigInt& operator=(const BigInt& expression); // TODO

    // Operators i/o
    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);
    friend std::istream& operator>>(std::istream& in, BigInt& value);

    // Bit shift
    friend BigInt operator<<(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator>>(const BigInt& lhs, const BigInt& rhs);

    // Comparison operators
    friend bool operator<(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<=(const BigInt& lhs, const BigInt& rhs);
    friend bool operator>(const BigInt& lhs, const BigInt& rhs);
    friend bool operator>=(const BigInt& lhs, const BigInt& rhs);
    friend bool operator==(const BigInt& lhs, const BigInt& rhs);

    // Arithmetic operators
    friend BigInt operator+(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator-(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator*(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator/(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator%(const BigInt& lhs, const BigInt& rhs);

    // Increment and decrement operators
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);

    // Unary operators
    BigInt operator+();
    BigInt operator-();

    // Assignment operators with arithmetic operations
    BigInt& operator+=(const BigInt& rhs);
    BigInt& operator-=(const BigInt& rhs);
    BigInt& operator*=(const BigInt& rhs);
    BigInt& operator/=(const BigInt& rhs);
    BigInt& operator%=(const BigInt& rhs);

    // Bit-shift assignment operators
    BigInt& operator<<=(const BigInt& rhs);
    BigInt& operator>>=(const BigInt& rhs);
};