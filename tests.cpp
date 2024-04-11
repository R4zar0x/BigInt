#include <string>

#include "BigInt.h"

int naivePower(int base, int exponent)
{
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

void toStringTest()
{
    std::cout <<
        "The class supports conversion to a string in 3 options:\n\
1 - \"bin\" - binary output\n\
2 - \"hex\" - output in hexadecimal\n\
3 - \"dec\" - output in decimal version\n";

    BigInt t(123456);

    std::cout << "example, displaying the number 123456:\n";
    std::cout << "bin - " << t.toString("bin");
    std::cout << "hex - " << t.toString("hex");
    std::cout << "dec - " << t.toString("dec") << std::endl;

    std::cout <<
        "converting to a decimal number takes a lot of time\n\
due to the large number of operations,\n\
so hexadecimal output will be used\n";
}
void testLengthComparison()
{
    std::cout << "Testing length comparison methods...\n";

    std::string str1 = "0xF0F0 F0F0 F0F0";
    std::string str2 = "0x1000 0000 0000";
    std::string str3 = "0x1234 ABCD 1234 ABCD 1234 ABCD";

    BigInt a(str1);
    BigInt b(str2);
    BigInt c(str3);

    std::cout << "a:\n" << a.toString("hex");
    std::cout << "b:\n" << b.toString("hex");
    std::cout << "c:\n" << c.toString("hex") << "\n";

    std::cout << "a.lengthEqualTo(b): ";
    if (a.lengthEqualTo(b))
        std::cout << "test passed\n";
    else
        std::cout << "test failed\n";

    std::cout << "c.lengthLongerTo(b): ";
    if (c.lengthLongerTo(b))
        std::cout << "test passed\n";
    else
        std::cout << "test failed\n";

    std::cout << "b.lengthLessTo(c): ";
    if (b.lengthLessTo(c))
        std::cout << "test passed\n";
    else
        std::cout << "test failed\n";
}
void testConstructors()
{
    std::cout << "Testing constructors...\n";

    BigInt a;
    std::cout << "Default constructor:\n" << a.toString("hex") << "\n";

    BigInt b(12345);
    std::cout << "Constructor from int:\n" << b.toString("hex") << "\n";

    BigInt c(54321U);
    std::cout << "Constructor from unsigned int:\n" << c.toString("hex") << "\n";

    BigInt d(987654321LL);
    std::cout << "Constructor from long long:\n" << d.toString("hex") << "\n";

    BigInt e(12345678901ULL);
    std::cout << "Constructor from unsigned long long:\n" << e.toString("hex") << "\n";

    std::string f_str = "0x1234567890ABCDEF";
    BigInt f(f_str);
    std::cout << "Constructor from string:\n" << f.toString("hex") << "\n";

    BigInt g(b);
    std::cout << "Copy constructor:\n" << g.toString("hex") << "\n";

    BigInt h(std::move(g));
    std::cout << "Move constructor:\n" << h.toString("hex") << "\n";
}
void testShiftLeftRight()
{
    std::cout << "Testing shift left and right...\n";
    std::string str = "0x1234 5678 90AB CDEF";
    BigInt a(str);
    std::cout << "a:\n" << a.toString("hex") << "\n";

    std::cout << "Shifting left by 4 bits:\n";
    a <<= BigInt(4);
    std::cout << a.toString("hex") << "\n";

    std::cout << "Shifting right by 4 bits:\n";
    a >>= BigInt(4);
    std::cout << a.toString("hex") << "\n";
}
void testUnaryOperators()
{
    std::cout << "Testing unary operators...\n";
    std::string str = "-12345";
    BigInt a(str);
    std::cout << "a: " << a.toString("dec") << "\n";

    BigInt b = +a;
    std::cout << "+a: " << b.toString("dec") << "\n";

    BigInt c = -a;
    std::cout << "-a: " << c.toString("dec") << "\n";
}
void randomAdditionTest(int tests)
{
    for (int i = 0; i < tests; i++)
    {
        int m1 = rand();
        int m2 = rand();

        BigInt t1(m1);
        BigInt t2(m2);

        std::cout << "testAddition " << i;
        std::cout << "\nt1:" << t1.toString("hex");
        std::cout << "t2:" << t2.toString("hex");

        BigInt t = t1 + t2;

        std::cout << "t1 + t2:\n   " << t.toString("hex");

        if (t == BigInt(m1 + m2))
            std::cout << "passed\n";
        else
            std::cout << "failed:\n";
    }
}
void randomSubtractionTest(int tests)
{
    for (int i = 0; i < tests; i++)
    {
        int m1 = rand();
        int m2 = rand();

        BigInt t1(m1);
        BigInt t2(m2);

        std::cout << "testSubtraction " << i;
        std::cout << "\nt1:" << t1.toString("hex");
        std::cout << "t2:" << t2.toString("hex");

        BigInt t = t1 - t2;

        std::cout << "t1 - t2:\n   " << t.toString("hex");

        if (t == BigInt(m1 - m2))
            std::cout << "passed\n";
        else
            std::cout << "failed:\n";
    }
}
void randomMultiplicationTest(int tests)
{
    for (int i = 0; i < tests; i++)
    {
        int m1 = rand();
        int m2 = rand();

        BigInt t1(m1);
        BigInt t2(m2);

        std::cout << "testMultiplication " << i;
        std::cout << "\nt1:" << t1.toString("hex");
        std::cout << "t2:" << t2.toString("hex");

        BigInt t = t1 * t2;

        std::cout << "t1 * t2:\n   " << t.toString("hex");

        if (t == BigInt(m1 * m2))
            std::cout << "passed\n";
        else
            std::cout << "failed\n";
    }
}
void randomDivisionTest(int tests)
{
    for (int i = 0; i < tests; i++)
    {
        int m1 = rand();
        int m2 = rand();

        BigInt t1(m1);
        BigInt t2(m2);

        std::cout << "testDivision " << i;
        std::cout << "\nt1:" << t1.toString("hex");
        std::cout << "t2:" << t2.toString("hex");

        BigInt t = t1 / t2;

        std::cout << "t1 / t2:\n   " << t.toString("hex");

        if (t == BigInt(m1 / m2))
            std::cout << "passed\n";
        else
            std::cout << "failed\n";
    }
}
void randomModuloTest(int tests)
{
    for (int i = 0; i < tests; i++)
    {
        int m1 = rand();
        int m2 = rand();

        BigInt t1(m1);
        BigInt t2(m2);

        std::cout << "testModulo " << i;
        std::cout << "\nt1:" << t1.toString("hex");
        std::cout << "t2:" << t2.toString("hex");

        BigInt t = t1 % t2;

        std::cout << "t1 % t2:\n   " << t.toString("hex");

        if (t == BigInt(m1 % m2))
            std::cout << "passed\n";
        else
            std::cout << "failed\n";
    }
}
void randomPowerTest(int tests)
{
    for (int i = 0; i < tests; i++)
    {
        int m1 = rand() & 10;
        int m2 = rand() & 6;

        BigInt t1(m1);
        BigInt t2(m2);

        std::cout << "testPower " << i;
        std::cout << "\nt1:" << t1.toString("hex");
        std::cout << "t2:" << t2.toString("hex");

        t1.pow(t2);

        std::cout << "t1 ** t2:\n   " << t1.toString("hex");

        if (t1 == BigInt(naivePower(m1, m2)))
            std::cout << "passed\n";
        else
            std::cout << "failed\n";
    }
}


int main()
{
    srand(time(0));


    toStringTest();
    system("pause");
    system("cls");

    testConstructors();
    system("pause");
    system("cls");

    testLengthComparison();
    system("pause");
    system("cls");

    testShiftLeftRight();
    system("pause");
    system("cls");

    testUnaryOperators();
    system("pause");
    system("cls");

    std::cout << "A set of tests with random numbers to test the operation of addition:\n";
    randomAdditionTest(5);
    system("pause");
    system("cls");

    std::cout << "A set of tests with random numbers to test the subtraction operation:\n";
    randomSubtractionTest(5);
    system("pause");
    system("cls");

    std::cout << "A set of tests with random numbers to test the operation of multiplication:\n";
    randomMultiplicationTest(5);
    system("pause");
    system("cls");

    std::cout << "A set of tests with random numbers to test the division operation:\n";
    randomDivisionTest(5);
    system("pause");
    system("cls");

    std::cout << "A set of tests with random numbers to test the operation of modulo:\n";
    randomModuloTest(5);
    system("pause");
    system("cls");

    std::cout << "A set of tests with random numbers to test the division operation:\n";
    randomPowerTest(5);
    system("pause");

}