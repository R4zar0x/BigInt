#include "BigInt.h"

std::string to_bit(unsigned int numb)
{
    std::string result;
    for (size_t i = 0; i < 32; i++)
    {
        result += (numb >> i & 1u) + 0x30;
        if (i == 30) result += ' ';
    }

    return result;
}

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

    if (differentSign || twoNegative)
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

    BigInt result;
    



    result._removeFrontZeros();
    return result;
}



BigInt _divRaw(const BigInt& lhs, const BigInt& rhs)
{
    if (rhs._isZero()) 
        throw std::invalid_argument("Division by zero");

    if (rhs > lhs) 
        return BigInt(0);

    // Инициализируем переменные
    BigInt quotient;
    BigInt remainder = lhs; // Делитель в начале равен делимому

    // Если делитель больше делимого, возвращаем ноль

    // Устанавливаем длину частного как разницу длин делимого и делителя
    size_t quotientLength = lhs._length - rhs._length + 1;
    quotient._resize(quotientLength);

    // Выполняем деление
    for (size_t i = 0; i < quotientLength; ++i) {
        unsigned int div = 0;
        while (remainder >= rhs) {
            remainder -= rhs;
            div++;
        }
        quotient._buffer[i] = div;
        remainder._removeFrontZeros();
        remainder._makeAddiction(); // Нормализуем остаток
        if (remainder._isZero()) {
            break;
        }
        remainder._pushBack(lhs._buffer[i + rhs._length]); // Добавляем следующий разряд к остатку
    }

    // Удаляем лишние нули в частном
    quotient._removeFrontZeros();

    return quotient;
}
BigInt _modRaw(const BigInt& lhs, const BigInt& rhs)
{
    BigInt lhsCopy(lhs);
    BigInt result(lhs);

    lhsCopy /= rhs;
    result -= lhsCopy * rhs;

    return result;
}
BigInt _powRaw(const BigInt& lhs, const BigInt& rhs)
{
    BigInt temp(lhs);
    BigInt iterator(rhs);

    while (iterator > 0)
    {
        temp *= lhs;
        
        iterator--;
    }

    return temp;
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

char BigInt::_intToHex(unsigned int numb) const
{
    if (numb < 10)
        return (char)(numb + 0x30);
    else
        return (char)(numb + 0x37);
}
unsigned int BigInt::_hexToInt(char ch) const
{
    switch (ch)
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
BigInt BigInt::_slice(size_t start, size_t end) const
{
    //TODO
    return BigInt();
}

std::string BigInt::_BigIntToDecString() const
{
    //TODO
    
    return std::string();
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

bool BigInt::_isZero() const
{
    if (this->_length == 1 && this->_buffer[0] == 0x0u)
        return true;
    else
        return false;
}

void BigInt::_DecStringToBigInt(std::string expression)
{
    //TODO
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

void BigInt::_resize(size_t sz)
{
    if (sz == _length)
        return;

    unsigned int* newBuffer = new unsigned int[sz];

    if (_buffer != nullptr)
    {
        size_t copySize = std::min(sz, _length); 
        memcpy(newBuffer, _buffer, copySize * sizeof(unsigned int));
        delete[] _buffer;
    }

    bool sign = newBuffer[sz - 1] >> 31;
    for (size_t i = _length; i < sz; i++)
    {
        if (sign)
            newBuffer[i] = 0x7FFFFFFFu;
        else
            newBuffer[i] = 0u;
    }

    this->_buffer = newBuffer;
    this->_length = sz;
}
void BigInt::_pushBack(unsigned int temp)
{
    size_t newLength = this->_length + 1;
    unsigned int* newBuffer = new unsigned int[newLength];

    if (this->_buffer != nullptr)
    {
        memcpy(newBuffer, this->_buffer, newLength * sizeof(unsigned int));
        delete[] _buffer;
    }
    
    newBuffer[newLength - 1] = temp;
    
    this->_buffer = newBuffer;
    this->_length = newLength;
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

    if (expression.find_first_not_of("-0123456789") == std::string::npos)
        this->_BinStringToBigInt(expression);
    else if (expression.find_first_not_of("Hh0123456789ABCDEFabcdef") == std::string::npos)
        this->_HexStringToBigInt(expression.substr(1, std::string::npos));
    else if (expression.find_first_not_of("x0123456789ABCDEFabcdef") == std::string::npos)
        this->_HexStringToBigInt(expression.substr(2, std::string::npos));
    else if (expression.find_first_not_of("Bb01") == std::string::npos)
        this->_BinStringToBigInt(expression.substr(1, std::string::npos));
    else
        throw std::invalid_argument("Invalid input format");
}
BigInt::BigInt(const BigInt& other) :
    _buffer(new unsigned int[other._length]),
    _length(other._length)
{
    std::copy(other._buffer, other._buffer + _length, this->_buffer);
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

BigInt& BigInt::pow(BigInt power)
{
    *this = _powRaw(*this, power);

    return *this;
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

BigInt& BigInt::operator= (const BigInt& other)
{
    if (this != &other) 
    {
        delete[] _buffer; 

        _length = other._length;
        _buffer = new unsigned int[_length];
        std::copy(other._buffer, other._buffer + _length, _buffer);
    }

    return *this;
}

std::ostream& operator<< (std::ostream& out, const BigInt& numb)
{  
    out << numb._BigIntToBinString();

    return out;
}
std::istream& operator>> (std::istream& in, BigInt& numb)
{
    std::string expression;

    in >> expression;

    BigInt newNumb(expression);
    
    numb.~BigInt();

    numb = newNumb;

    return in;
}

bool operator<(const BigInt& lhs, const BigInt& rhs)
{
    if (!BigInt::_equalLength(lhs, rhs))
        return false;

    BigInt result = lhs - rhs;

    return result._getSign() && !result._isZero();
}
bool operator<=(const BigInt& lhs, const BigInt& rhs)
{
    if (!BigInt::_equalLength(lhs, rhs))
        return false;

    BigInt result = lhs - rhs;

    return result._getSign() || result._isZero();
}
bool operator> (const BigInt& lhs, const BigInt& rhs)
{
    if (!BigInt::_equalLength(lhs, rhs))
        return false;

    BigInt result = lhs - rhs;

    return !(result._getSign() || result._isZero()); // ~(a + b) = ~a * ~b
}
bool operator>=(const BigInt& lhs, const BigInt& rhs)
{
    if (!BigInt::_equalLength(lhs, rhs))
        return false;

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

