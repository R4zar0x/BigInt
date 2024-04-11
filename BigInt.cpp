#include "BigInt.h"

using namespace std;

BigInt _addRaw(const BigInt& lhs, const BigInt& rhs)
{
    BigInt result;

    size_t maxLength = std::max(lhs._length, rhs._length);
    bool differentSign = lhs._getSign() ^ rhs._getSign();
    bool twoNegative = lhs._getSign() && rhs._getSign();
    
    result._resize(maxLength + 1);

    unsigned int carry = 0;
    for (size_t i = 0; i < maxLength; ++i)
    {
        unsigned int sum = carry;

        if (i < lhs._length)
            sum += lhs._buffer[i];
        if (i < rhs._length)
            sum += rhs._buffer[i];
        
        result._buffer[i] = sum & (i == maxLength - 1 ? 0xFFFFFFFF : 0x7FFFFFFF);
        
        carry = sum >> 31;
    }
    
    if (differentSign)
        carry = 0;

    if (carry)
        result._buffer[maxLength] = carry;
    else
        result._resize(maxLength);

    return result;
}
BigInt _subRaw(const BigInt& lhs, const BigInt& rhs)
{
    if (rhs._isZero())
        return lhs;

    BigInt result(0);
    BigInt lhsCopy(lhs);
    BigInt rhsCopy(rhs);

    size_t maxLength = std::max(lhsCopy._length, rhsCopy._length);

    lhsCopy._resize(maxLength);
    rhsCopy._resize(maxLength);

    rhsCopy._makeAddiction();

    result = lhsCopy + rhsCopy;

    return result;
}
BigInt _mulRaw(const BigInt& lhs, const BigInt& rhs)
{
    if (lhs._isZero() || rhs._isZero())
        return BigInt(0);

    BigInt result(0);
    BigInt shift(0);
    BigInt lhsCopy(lhs);
    BigInt iterator(rhs);

    if (lhsCopy._getSign())
        lhsCopy._makeAddiction();

    if (iterator._getSign())
        iterator._makeAddiction();

    while (iterator > BigInt(0))
    {
        if (iterator._getBit(0))
            result += lhsCopy << shift;

        shift++;
        iterator >>= 1;
    }

    if (lhsCopy._getSign() ^ iterator._getSign())
        result._makeAddiction();

    return result;
}
BigInt _divRaw(const BigInt& lhs, const BigInt& rhs)
{
    if (rhs._isZero()) 
        throw std::invalid_argument("Division by zero");

    BigInt iterator(0);
    BigInt lhsCopy = lhs;
    BigInt rhsCopy = rhs;

    if (lhsCopy._getSign())
        lhsCopy._makeAddiction();

    if (rhsCopy._getSign())
        rhsCopy._makeAddiction();

    if (rhsCopy == lhsCopy)
        return BigInt(1);
    
    if (rhsCopy > lhsCopy)
        return BigInt(0);

    while (lhsCopy >= rhsCopy)
    {
        lhsCopy -= rhsCopy;
        
        iterator++;
    }

    if (lhsCopy._getSign() ^ iterator._getSign())
        iterator._makeAddiction();

    return iterator;
}
BigInt _modRaw(const BigInt& lhs, const BigInt& rhs)
{
    BigInt lhsCopy(lhs);
    BigInt rhsCopy(rhs);

    if (lhsCopy._getSign())
        lhsCopy._makeAddiction();

    if (rhsCopy._getSign())
        rhsCopy._makeAddiction();

    if (rhsCopy > lhsCopy)
        return BigInt(0);

    BigInt result(lhsCopy);

    lhsCopy /= rhsCopy;
    result -= lhsCopy * rhsCopy;

    if (lhs._getSign() ^ rhs._getSign())
        result._makeAddiction();

    return result;
}
BigInt _powRaw(const BigInt& lhs, const BigInt& rhs)
{
    if (rhs < BigInt(0))
        throw std::invalid_argument("power is less than zero");;
    
    if (rhs == BigInt(0))
        return BigInt(1u);
    
    BigInt result(lhs);
    BigInt iterator(rhs);

    iterator--;
    
    while (iterator > BigInt(0))
    {
        result *= lhs;
        
        iterator--;
    }

    return result;
}

bool BigInt::_equalLength(const BigInt& lhs, const BigInt& rhs)
{
    return lhs._length == rhs._length;
}
bool BigInt::_moreThenLength(const BigInt& lhs, const BigInt& rhs)
{
    return lhs._length > rhs._length;
}
bool BigInt::_lessThenLength(const BigInt& lhs, const BigInt& rhs)
{
    return lhs._length < rhs._length;
}

void BigInt::_removeSpaces(std::string& str)
{
    size_t newPos = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] != ' ')
        {
            str[newPos++] = str[i];
        }
    }
    str.resize(newPos);
}
void BigInt::_swap(std::string& str)
{
    if (str.length() == 0 || str.length() == 1)
        return;

    std::size_t left = 0;
    std::size_t right = str.length() - 1;

    while (left < right)
    {
        std::swap(str[left], str[right]);

        ++left;
        --right;
    }
}

std::string BigInt::_BigIntToDecString() const
{
    if ((*this)._isZero())
        return "0";

    std::string str = "";
    BigInt copy(*this);
    BigInt base(10);
    size_t triad = 0;
    
    if ((*this)._getSign())
        copy._makeAddiction();

    while (copy > BigInt(0))
    {
        BigInt test = copy % base;

        str += (unsigned int)(copy % base) + 0x30;
        copy /= base;

        if (triad >= 2)
        {
            triad = 0;
            str += ' ';
        }
        else
        {
            triad++;
        }
    }
    
    BigInt::_swap(str);

    if (str[0] == ' ')
        str = str.substr(1, std::string::npos);

    if ((*this)._getSign())
        str.insert(0, 1, '-');

    return str;
}
std::string BigInt::_BigIntToHexString() const
{
    std::string result;

    if (this->_length % 2 != 0 && this->_length != 1) result += "          ";

    for (long long cell = this->_length - 1; cell >= 0; cell--)
    {
        for (long long shift = 28; shift >= 0; shift -= 4)
        {
            unsigned int ch = (this->_buffer[cell] >> shift) & 0xFu;
            result += this->_intToHex(ch);
            if (shift == 16) result += ' ';
        }
        result += cell % 2 ? ' ' : '\n';
    }

    return result;
}
std::string BigInt::_BigIntToBinString() const
{
    std::string result;

    for (long long cell = this->_length - 1; cell >= 0; cell--)
    {
        for (long long shift = 31; shift >= 0; shift--)
        {
            result += (this->_buffer[cell] >> shift & 1u) + 0x30u;
            if (shift == 31) result += ' ';
        }
        result += '\n';
    }

    return result;
}

void BigInt::_DecStringToBigInt(std::string expression)
{
    BigInt temp(0);
    BigInt shift(1);

    BigInt::_swap(expression);

    for (unsigned int ch : expression)
    {
        BigInt numb(ch - 0x30u);

        temp += numb * shift;
        shift *= 10;
    }

    *this = temp;
}
void BigInt::_HexStringToBigInt(std::string expression)
{
    unsigned int temp = 0;

    if (expression.size() % 8 != 0)
    {
        for (size_t i = 0; i < expression.size() % 8; i++)
            expression.insert(0, "0");
    }

    for (int iterator = expression.size() - 1; iterator >= 0; iterator--)
    {
        unsigned int ch = this->_hexToInt(expression[iterator]);
        int shift = 4 * (7 - (iterator % 8));

        if (iterator % 8 != 0)
        {
            temp |= ch << shift;
        }
        else
        {
            temp |= ch << shift;
            this->_pushBack(temp);
            temp = 0;
        }
    }
}
void BigInt::_BinStringToBigInt(std::string expression)
{
    unsigned int temp = 0;

    if (expression.size() % 32 != 0)
    {
        for (size_t i = 0; i < expression.size() % 32; i++)
            expression.insert(0, "0");
    }

    for (int iterator = expression.size() - 1; iterator >= 0; iterator--)
    {
        unsigned int ch = expression[iterator] - 0x30;
        int shift = 63 - (iterator % 32);

        if (iterator % 32 != 0)
        {
            temp |= ch << shift;
        }
        else
        {
            temp |= ch << shift;
            this->_pushBack(temp);
            temp = 0;
        }
    }
}

void BigInt::_shiftLeft()
{
    unsigned int carry = 0u;

    for (size_t i = _length - 1; i > 0; --i)
    {
        unsigned int temp = this->_buffer[i];

        this->_buffer[i] = (this->_buffer[i] << 1) | carry;

        carry = temp >> 31;
    }
    this->_buffer[0] = (this->_buffer[0] << 1) | carry;

    if (this->_buffer[this->_length - 1] & 0x80000000u)
    {
        _pushBack(this->_buffer[this->_length - 1] >> 31);
        this->_buffer[this->_length - 2] &= 0x7FFFFFFFu;
    }
         
    this->_removeFrontZeros();
}
void BigInt::_shiftRight()
{
    unsigned int carry = 0u;

    for (size_t i = 0; i < this->_length - 1; i++)
    {
        carry = this->_buffer[i + 1] & 0x1u;

        this->_buffer[i] >>= 1;
        this->_buffer[i] &= 0x7FFFFFFFu;
        this->_buffer[i] |= carry << 30;
    }

    this->_buffer[this->_length - 1] >>= 1;

    _removeFrontZeros();
}

char BigInt::_intToHex(unsigned int value) const
{
    if (value < 10)
        return (char)(value + 0x30);
    else
        return (char)(value + 0x37);
}
unsigned int BigInt::_hexToInt(char value) const
{
    switch (value)
    {
    case '0':
        return 0x0u;
    case '1':
        return 0x1u;
    case '2':
        return 0x2u;
    case '3':
        return 0x3u;
    case '4':
        return 0x4u;
    case '5':
        return 0x5u;
    case '6':
        return 0x6u;
    case '7':
        return 0x7u;
    case '8':
        return 0x8u;
    case '9':
        return 0x9u;
    case 'a':
        return 0xAu;
    case 'A':
        return 0xAu;
    case 'b':
        return 0xBu;
    case 'B':
        return 0xBu;
    case 'c':
        return 0xCu;
    case 'C':
        return 0xCu;
    case 'd':
        return 0xDu;
    case 'D':
        return 0xDu;
    case 'e':
        return 0xEu;
    case 'E':
        return 0xEu;
    case 'f':
        return 0xFu;
    case 'F':
        return 0xFu;
    }
}

void BigInt::_pushBack(unsigned int value)
{
    size_t newLength = this->_length + 1;
    unsigned int* newBuffer = new unsigned int[newLength];

    if (this->_buffer != nullptr)
    {
        memcpy(newBuffer, this->_buffer, newLength * sizeof(unsigned int));
        delete[] _buffer;
    }
    
    newBuffer[newLength - 1] = value;
    
    this->_buffer = newBuffer;
    this->_length = newLength;
}
void BigInt::_pushFront(unsigned int value, size_t count)
{
    size_t newLength = _length + count;
    unsigned int* newBuffer = new unsigned int[newLength];

    for (size_t i = 0; i < count; ++i)
    {
        newBuffer[i] = value;
    }

    for (size_t i = 0; i < _length; ++i)
    {
        newBuffer[i + count] = _buffer[i];
    }

    delete[] _buffer;
    _buffer = newBuffer;
    _length = newLength;
}

void BigInt::_resize(size_t sz)
{
    if (sz == _length)
        return;

    unsigned int* newBuffer = new unsigned int[sz];
    unsigned int sign = this->_getSign();

    if (this->_buffer != nullptr)
    {
        size_t copySize = std::min(sz, _length); 
        memcpy(newBuffer, this->_buffer, copySize * sizeof(unsigned int));
        delete[] this->_buffer;
    }

    for (size_t i = 0; i < sz; i++)
        newBuffer[i] &= 0x7FFFFFFFu;

    for (size_t i = this->_length; i < sz; i++)
    {
        if (sign)
            newBuffer[i] = 0x7FFFFFFFu;
        else
            newBuffer[i] = 0u;
    }

    newBuffer[sz - 1] |= sign ? 0x80000000u : 0x0u;

    this->_buffer = newBuffer;
    this->_length = sz;
}
void BigInt::_removeFrontZeros()
{
    if (this->_getSign())
    {
        while (this->_length > 2 && this->_buffer[_length - 1] == 0x7FFFFFFF)
        {
            this->_length--;
        }
    }
    else
    {
        while (this->_length > 1 && this->_buffer[_length - 1] == 0) // or (this->_length > 1 && this->_buffer[_length - 1] == 0)
        {
            this->_length--;
        }
    }

    this->_resize(this->_length);

    if (this->_length == 1 && !(this->_buffer[0] & 0x80000000u))
        this->_buffer[this->_length - 1] &= 0x7FFFFFFFu;
}
void BigInt::_makeAddiction()
{
    unsigned int sign = this->_buffer[this->_length - 1] >> 31;

    this->_buffer[this->_length - 1] &= 0x7FFFFFFFu;

    for (size_t cell = 0; cell < this->_length; cell++)
        this->_buffer[cell] = ~this->_buffer[cell] & 0x7FFFFFFFu;

    (*this)++;

    this->_buffer[this->_length - 1] |= sign ? 0x0u : 0x80000000u;
}

bool BigInt::_isZero() const
{
    if (this->_length == 1 && this->_buffer[0] == 0x0u)
        return true;
    else
        return false;
}
unsigned int BigInt::_getBit(size_t bitIndex) const
{
    if (bitIndex >= this->_length * 31)
        return 0;

    size_t wordIndex = bitIndex / 31;
    size_t bitOffset = bitIndex % 31;

    return (this->_buffer[wordIndex] >> bitOffset) & 0x1u;
}
unsigned int BigInt::_getSign() const
{
    if (this->_length != 0)
        return this->_buffer[this->_length - 1] >> 31;
    else
        return 0x0;
}

BigInt::BigInt() :
    _buffer(nullptr), 
    _length(0)
{}
BigInt::BigInt(int other)
{
    this->_buffer = new unsigned int[1];
    this->_length = 1;

    this->_buffer[0] = other;
}
BigInt::BigInt(unsigned int other)
{
    this->_buffer = new unsigned int[2];
    this->_length = 2;
    
    this->_buffer[0] = other & 0x7FFFFFFFu;
    this->_buffer[1] = other >> 31;
}
BigInt::BigInt(long long other)
{
    this->_buffer = new unsigned int[3];
    this->_length = 3;

    this->_buffer[0] = (other & 0x7FFFFFFFu);
    other >>= 31;
    this->_buffer[1] = other & 0x7FFFFFFFu;
    other >>= 31;
    this->_buffer[2] = other & 0x7FFFFFFFu;

    this->_buffer[2] |= 0x80000000;
}
BigInt::BigInt(unsigned long long other)
{
    this->_buffer = new unsigned int[3];
    this->_length = 3;

    this->_buffer[0] = (other & 0x7FFFFFFFu);
    other >>= 31;
    this->_buffer[1] = other & 0x7FFFFFFFu;
    other >>= 31;
    this->_buffer[2] = other;
}
BigInt::BigInt(std::string& expression)
{
    this->_buffer = nullptr;
    this->_length = 0;

    this->_removeSpaces(expression);

    if (expression.find_first_not_of("0123456789") == std::string::npos)
    {
        this->_DecStringToBigInt(expression);
    }
    else if (expression.find_first_not_of("-0123456789") == std::string::npos)
    {
        this->_DecStringToBigInt(expression.substr(1, std::string::npos));
        this->_makeAddiction();
    }
    else if (expression.find_first_not_of("Hh0123456789ABCDEFabcdef") == std::string::npos)
    {
        this->_HexStringToBigInt(expression.substr(1, std::string::npos));
    }
    else if (expression.find_first_not_of("x0123456789ABCDEFabcdef") == std::string::npos)
    {
        this->_HexStringToBigInt(expression.substr(2, std::string::npos));
    }
    else if (expression.find_first_not_of("Bb01") == std::string::npos)
    {
        this->_BinStringToBigInt(expression.substr(1, std::string::npos));
    }
    else
    {
        throw std::invalid_argument("Invalid input format");
    }
}
BigInt::BigInt(const BigInt& other)
{
    if (this->_buffer ==nullptr)
        delete[] this->_buffer;

    this->_length = other._length;
    this->_buffer = new unsigned int[this->_length];
    memcpy(this->_buffer, other._buffer, this->_length * sizeof(unsigned int));
}
BigInt::BigInt(BigInt&& other) noexcept :
    _buffer(other._buffer),
    _length(other._length)
{
    other._buffer = nullptr;
    other._length = 0;
}

BigInt::~BigInt()
{
    delete[] _buffer;
}

void BigInt::pow(BigInt power)
{
   /* std::cout << "1" << std::endl << (*this) << std::endl;
    std::cout << "2" << std::endl << power << std::endl;
    std::cout << "3" << std::endl << _powRaw(*this, power) << std::endl;*/
    *this = _powRaw(*this, power);
}

BigInt::operator std::string() 
{
    return (*this)._BigIntToDecString();
}
BigInt::operator int()
{
    if (this->_length == 0)
        return 0;

    if (this->_length == 1)
        return static_cast<int>(this->_buffer[0]);

    if (this->_getSign())
        return -static_cast<int>(this->_buffer[0] | 0x80000000u);
    else
        return static_cast<int>(this->_buffer[0]);
}
BigInt::operator unsigned int()
{
    if (this->_length == 0)
        return 0;

    return this->_buffer[0];
}
BigInt::operator long long()
{
    if (_length == 0)
        return 0;

    long long result = 0;

    result |= static_cast<long long>(this->_buffer[0]);
    result |= static_cast<long long>(this->_buffer[1]) << 31;
    result |= static_cast<long long>(this->_buffer[2]) & 0x1ull << 62;

    if (this->_getSign())
        result |= 0x1ull << 63;

    return result;
}
BigInt::operator unsigned long long()
{
    if (_length == 0)
        return 0;

    unsigned long long result = 0;

    result |= static_cast<long long>(this->_buffer[0]);
    result |= static_cast<long long>(this->_buffer[1]) << 31;
    result |= static_cast<long long>(this->_buffer[2]) & 0x3ull << 62;

    return result;
}

bool BigInt::lengthEqualTo(BigInt& other)
{
    return BigInt::_equalLength(*this, other);
}
bool BigInt::lengthLongerTo(BigInt& other)
{
    return BigInt::_moreThenLength(*this, other);
}
bool BigInt::lengthLessTo(BigInt& other)
{
    return BigInt::_lessThenLength(*this, other);;
}

std::string BigInt::toString(const char com[4])
{
    /*arguments:
        "bin" converts BigInt to a string with a binary representation of the number (highest bit is the overflow flag) 
        "hex" converts BigInt to a string with a heximal representation of the number
        "hex" converts BigInt to a string with a decimal representation of the number*/
    if (com == "bin")
        return this->_BigIntToBinString();
    else if (com == "hex")
        return this->_BigIntToHexString();
    else if (com == "dec")
        return this->_BigIntToDecString();
    else
        return std::string("Bad command");
}

BigInt& BigInt::operator= (const BigInt& other)
{
    if (this != &other) 
    {
        delete[] _buffer; 

        this->_length = other._length;
        this->_buffer = new unsigned int[this->_length];
        memcpy(this->_buffer, other._buffer, this->_length * sizeof(unsigned int));
    }

    return *this;
}

std::ostream& operator<< (std::ostream& out, const BigInt& value)
{  
    out << value._BigIntToBinString();

    return out;
}
std::istream& operator>> (std::istream& in, BigInt& value)
{
    std::string expression;

    in >> expression;

    BigInt newNumb(expression);
    
    value.~BigInt();

    value = newNumb;

    return in;
}

BigInt operator<<(const BigInt& lhs, const BigInt& rhs)
{
    if (rhs._isZero())
        return lhs;

    BigInt result(lhs);
    BigInt rhsCopy(rhs);

    for (; rhsCopy > BigInt(0); rhsCopy--)
    {
        result._shiftLeft(); 
    }

    return result;
}
BigInt operator>>(const BigInt& lhs, const BigInt& rhs)
{
    if (rhs._isZero())
        return lhs;
    BigInt result(lhs);
    BigInt rhsCopy(rhs);

    for (; rhsCopy > BigInt(0); rhsCopy--)
    {
        result._shiftRight();
    }

    return result;
}

bool operator<(const BigInt& lhs, const BigInt& rhs)
{
    if (lhs._getSign() && rhs._isZero())
        return true;

    BigInt result = lhs - rhs;

    return result._getSign() && !result._isZero();
}
bool operator<=(const BigInt& lhs, const BigInt& rhs)
{
    BigInt result = lhs - rhs;

    return result._getSign() || result._isZero();
}
bool operator> (const BigInt& lhs, const BigInt& rhs)
{
    if (!lhs._getSign() && !lhs._isZero() && rhs._isZero())
        return true;

    BigInt result = lhs - rhs;

    /*std::cout << "1\n" << result.toString("hex") << std::endl;
    std::cout << "2 " << result._getSign() << std::endl;*/

    return !(result._getSign() || result._isZero()); // ~(a + b) = ~a * ~b
}
bool operator>=(const BigInt& lhs, const BigInt& rhs)
{
    BigInt result = lhs - rhs;

    return !result._getSign();
}
bool operator==(const BigInt& lhs, const BigInt& rhs)
{
    if (!BigInt::_equalLength(lhs, rhs))
        return false;

    BigInt result = lhs - rhs;

    return result._isZero();
}

BigInt operator+ (const BigInt& lhs, const BigInt& rhs)
{
    BigInt result = _addRaw(lhs, rhs);

    result._removeFrontZeros();

    return result;
}
BigInt operator- (const BigInt& lhs, const BigInt& rhs)
{
    BigInt result = _subRaw(lhs, rhs);

    return result;
}
BigInt operator* (const BigInt& lhs, const BigInt& rhs)
{
    BigInt result = _mulRaw(lhs, rhs);

    return result;
}
BigInt operator/ (const BigInt& lhs, const BigInt& rhs)
{
    BigInt result = _divRaw(lhs, rhs);

    return result;
}
BigInt operator% (const BigInt& lhs, const BigInt& rhs)
{
    BigInt result = _modRaw(lhs, rhs);

    return result;
}

BigInt& BigInt::operator++()
{
    *this += 1;
    return *this;
}
BigInt BigInt::operator++(int)
{
    *this += 1;
    return *this;
}
BigInt& BigInt::operator--()
{
    *this -= 1;
    return *this;
}
BigInt BigInt::operator--(int)
{
    *this -= 1;
    return *this;
}

BigInt BigInt::operator+()
{
    return BigInt(*this);
}
BigInt BigInt::operator-()
{
    this->_makeAddiction();
    return (*this);
}

BigInt& BigInt::operator+= (const BigInt& rhs)
{
    *this = *this + rhs;
    return *this;
}
BigInt& BigInt::operator-= (const BigInt& rhs)
{
    *this = *this - rhs;
    return *this;
}
BigInt& BigInt::operator*= (const BigInt& rhs)
{
    *this = *this * rhs;
    return *this;
}
BigInt& BigInt::operator/= (const BigInt& rhs)
{
    *this = *this / rhs;
    return *this;
}
BigInt& BigInt::operator%= (const BigInt& rhs)
{
    *this = *this % rhs;
    return *this;
}

BigInt& BigInt::operator<<=(const BigInt& rhs)
{
    *this = *this << rhs;
    return *this;
}
BigInt& BigInt::operator>>=(const BigInt& rhs)
{
    *this = *this >> rhs;
    return *this;
}