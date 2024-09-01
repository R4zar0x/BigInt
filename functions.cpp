#include "BigInt.h"


void BigInt::show()
{
    std::vector<std::string> str = {};

    for (auto val : this->_number)
    {
        char buff[10];
        sprintf(buff, "%.8X\n", val);
        str.insert(str.begin(), buff);
    }

    for (auto& val : str)
    {
        printf(val.c_str());
    }
}

void BigInt::resize(size_t length)
{   
    if (this->_number.size() == length)
    {
        return;
    }

    this->_number.resize(length, 0u);
}

void BigInt::shorten()
{
    size_t iterator = this->_number.size();

    do
    {
        iterator--;
    } while (this->_number[iterator] == 0);

    this->resize(iterator + 1);
}

size_t BigInt::equalize(BigInt& other) // выбирает максимальную длину и добавляет 1
{
    size_t maxLength = std::max(this->getLength(), other.getLength()) + 1;

    this->resize(maxLength);
    other.resize(maxLength);

    return maxLength;

}

void BigInt::invert()
{
    for (size_t i = 0; i < this->getLength(); i++)
    {
        this->_number[i] = ~this->_number[i];
    }
}

void BigInt::negate()
{
    BigInt a(1);

    this->_sign = !this->_sign;

    this->invert();

    this->add(a);

    if (this->_number[this->getLength() - 1] == 0x1u)
    {
        this->_number.resize(this->getLength() - 1);
    }
}
