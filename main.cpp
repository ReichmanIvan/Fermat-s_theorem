#include <iostream>
#include <random>

// Функция для быстрого возведения числа в степень по модулю
long long modularExponentiation(long long base, int exponent, int modulus) 
{
    long long result = 1;
    base %= modulus;
    while (exponent > 0) 
    {
        if (exponent & 1) 
        {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus; 
        exponent >>= 1;
    }
    return result;
}

// Тест простоты Ферма
bool fermatTest(int number) 
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> distribution(2, number - 2); 

    for (int i = 0; i < 5; ++i) 
    { 
        int base = distribution(generator);
        if (modularExponentiation(base, number - 1, number) != 1) 
        {
            return false; 
        }
    }
    return true;
}

// Функция для вычисления символа Якоби
int jacobiSymbol(int a, int n) 
{
    if (n <= 0 || (n & 1) == 0) return 0; 
    a %= n;
    if (a == 0) return (n == 1) ? 1 : 0;

    int symbol = 1;
    while (a != 0) 
    {
        while ((a & 1) == 0) 
        {
            a >>= 1; 
            if ((n & 7) == 3 || (n & 7) == 5) 
            { 
                symbol = -symbol;
            }
        }

        std::swap(a, n);
        if ((a & 3) == 3 && (n & 3) == 3) 
        { 
            symbol = -symbol;
        }
        a %= n; 
    }

    return (n == 1) ? symbol : 0;
}

// Тест Соловея-Штрассена
bool solovayStrassenTest(int number) 
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice()); 
    std::uniform_int_distribution<int> distribution(2, number - 2); 

    for (int i = 0; i < 5; ++i) 
    { 
        int base = distribution(generator); 
        int remainder = modularExponentiation(base, (number - 1) / 2, number); 

        if (remainder != 1 && remainder != number - 1) 
        {
            return false; 
        }

        int jacobi = jacobiSymbol(base, number); 
        if (jacobi == -1) 
        {
            jacobi = number - 1; 
        }

        if (remainder != jacobi) 
        {
            return false; 
        }
    }
    return true; 
}

// Тест Миллера-Рабина
bool millerRabinTest(int number) 
{
    const int bases[] = {3, 5, 7, 11};

    int s = 0;
    int d = number - 1;
    while ((d & 1) == 0) 
    {
        d >>= 1;
        ++s;
    }

    for (int base : bases) 
    { 
        int current = modularExponentiation(base, d, number);

        if (current != 1 && current != number - 1) 
        {
            bool isComposite = true; 

            for (int r = 1; r < s; ++r) 
            { 
                current = modularExponentiation(current, 2, number);

                if (current == number - 1) 
                {
                    isComposite = false; 
                    break;
                }
            }

            if (isComposite) 
            {
                return false; 
            }
        }
    }
    return true; 
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    int testNumber = 233;

    // Тест Ферма
    std::cout << "1.Тест Ферма\n" << "Число " << testNumber << " простое = "
        << std::boolalpha << fermatTest(testNumber) << "\n" << std::endl;

    // Тест Соловея-Штрассена
    std::cout << "2.Тест Соловея-Штрассена\n" << "Число " << testNumber << " простое = "
        << std::boolalpha << solovayStrassenTest(testNumber) << "\n" << std::endl;

    // Тест Миллера-Рабина
    std::cout << "3.Тест Миллера-Рабина\n" << "Число " << testNumber << " простое = "
        << std::boolalpha << millerRabinTest(testNumber) << std::endl;

    return 0;
}
