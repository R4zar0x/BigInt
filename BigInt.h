#pragma once
#include <iostream>

std::string to_bit(unsigned int numb);

class BigInt
{
protected:
    unsigned int* _buffer;
    size_t _length;

    friend static BigInt _addRaw(const BigInt& lhs, const BigInt& rhs);
    friend static BigInt _subRaw(const BigInt& lhs, const BigInt& rhs); 
    friend static BigInt _mulRaw(const BigInt& lhs, const BigInt& rhs); // TODO
    friend static BigInt _divRaw(const BigInt& lhs, const BigInt& rhs);
    friend static BigInt _modRaw(const BigInt& lhs, const BigInt& rhs); // TODO
    friend static BigInt _powRaw(const BigInt& lhs, const BigInt& rhs); // TODO

    static bool _equalLength(const BigInt& lhs, const BigInt& rhs);
    static bool _moreThenLength(const BigInt& lhs, const BigInt& rhs);
    static bool _lessThenLength(const BigInt& lhs, const BigInt& rhs);

    static void _removeSpaces(std::string& str);

    std::string _BigIntToDecString() const; // TODO
    std::string _BigIntToHexString() const;
    std::string _BigIntToBinString() const;

    void _DecStringToBigInt(std::string expression); // TODO
    void _HexStringToBigInt(std::string expression);
    void _BinStringToBigInt(std::string expression);
    
    void _resize(size_t sz);
    void _pushBack(unsigned int temp);
    void _removeFrontZeros();
    void _makeAddiction();

    bool _isZero() const;
    unsigned int _getSign() const;

    unsigned int _hexToInt(char ch) const;
    char _intToHex(unsigned int numb) const;
    
    BigInt _slice(size_t start, size_t end) const;


    void _ping(int numb) // delete
    {
        std::cout<< numb << ":\n" << *this << std::endl;
    }

public:
    BigInt();
    BigInt(int other);
    BigInt(unsigned int other);
    BigInt(long long other);
    BigInt(unsigned long long other);
    BigInt(std::string& other);
    BigInt(const BigInt& other); // ����������� �����������
    BigInt(BigInt&& other) noexcept; // ����������� �����������

    ~BigInt();

    std::string toString(const char com[4]);

    bool lengthEqualTo(BigInt& other);
    bool lengthLongerTo(BigInt& other);
    bool lengthLessTo(BigInt& other);

    BigInt& pow(BigInt pow);

    //��������������
    operator std::string(); //TODO
    operator int(); //TODO
    operator unsigned int(); //TODO
    operator long long(); //TODO
    operator unsigned long long(); //TODO

    // ������������
    BigInt& operator= (const BigInt& expression);

    // ��������� i/o
    friend std::ostream& operator<< (std::ostream& out, const BigInt& numb);
    friend std::istream& operator>> (std::istream& in, BigInt& numb);

    // ��������� ���������
    friend bool operator<   (const BigInt& lhs, const BigInt& rhs);
    friend bool operator<=  (const BigInt& lhs, const BigInt& rhs);
    friend bool operator>   (const BigInt& lhs, const BigInt& rhs);
    friend bool operator>=  (const BigInt& lhs, const BigInt& rhs);
    friend bool operator==  (const BigInt& lhs, const BigInt& rhs);

    // ��������� �������������� ��������
    friend BigInt operator+ (const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator- (const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator* (const BigInt& lhs, const BigInt& rhs); 
    friend BigInt operator/ (const BigInt& lhs, const BigInt& rhs); 
    friend BigInt operator% (const BigInt& lhs, const BigInt& rhs); 

    // ��������� ���������� � ����������
    BigInt& operator++ ();
    BigInt operator++ (int);
    BigInt& operator-- ();
    BigInt operator-- (int); 
    
    // ������� ���������
    BigInt operator+ ();
    BigInt operator- ();

    // ��������� ������������ � ��������������� ����������
    BigInt& operator+= (const BigInt& rhs);
    BigInt& operator-= (const BigInt& rhs);
    BigInt& operator*= (const BigInt& rhs);
    BigInt& operator/= (const BigInt& rhs);
    BigInt& operator%= (const BigInt& rhs);
};