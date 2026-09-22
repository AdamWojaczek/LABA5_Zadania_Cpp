#include "CComplex.h"

CComplex::CComplex(double real, double imaginary)
    : m_real(real),
      m_imaginary(imaginary)
{
}

CComplex::CComplex(const CComplex& other)
    : m_real(other.m_real),
      m_imaginary(other.m_imaginary)
{
}

void CComplex::SetReal(double real)
{
    m_real = real;
}

double CComplex::GetReal() const
{
    return m_real;
}

void CComplex::SetImaginary(double imaginary)
{
    m_imaginary = imaginary;
}

double CComplex::GetImaginary() const
{
    return m_imaginary;
}

bool CComplex::operator==(const CComplex& other) const
{
    return (m_real == other.m_real) && (m_imaginary == other.m_imaginary);
}

bool CComplex::operator!=(const CComplex& other) const
{
    return !(*this == other);
}

CComplex& CComplex::operator+=(const CComplex& other)
{
    // (a + bi) + (c + di) = (a + c) + (b + d)i

    m_real += other.m_real;
    m_imaginary += other.m_imaginary;

    return *this;
}

CComplex& CComplex::operator-=(const CComplex& other)
{
    // (a + bi) - (c + di) = (a - c) + (b - d)i

    m_real -= other.m_real;
    m_imaginary -= other.m_imaginary;

    return *this;
}

CComplex& CComplex::operator*=(const CComplex& other)
{
    // (a + bi) * (c + di) = (ac - bd) + (bc + ad)i

    double re = m_real * other.m_real - m_imaginary * other.m_imaginary;
    double im = m_imaginary * other.m_real + m_real * other.m_imaginary;
    m_real = re;
    m_imaginary = im;

    return *this;
}

CComplex& CComplex::operator/=(const CComplex& other)
{
    // (a + bi) / (c + di) --> Div = c^2 + d^2; Re = (ac + bd) / Div; Im = (bc - ad) / Div

    double divisor = (other.m_real * other.m_real) + (other.m_imaginary * other.m_imaginary);
    if (divisor == 0.0)
        throw std::invalid_argument("Division by zero (c + di).");

    double re = (m_real * other.m_real + m_imaginary * other.m_imaginary) / divisor;
    double im = (m_imaginary * other.m_real - m_real * other.m_imaginary) / divisor;
    m_real = re;
    m_imaginary = im;

    return *this;
}

CComplex CComplex::operator-() const
{
    return CComplex(-m_real, -m_imaginary);
}

std::ostream& operator<<(std::ostream& outStream, const CComplex& value)
{
    outStream << value.m_real;

    if (value.m_imaginary >= 0.0)
        outStream << " + " << value.m_imaginary;
    else
        outStream << " - " << std::abs(value.m_imaginary);

    outStream << "i";

    return outStream;
}

std::istream& operator>>(std::istream& inStream, CComplex& value)
{
/*
    Uwaga: Operator >> jest uproszczony (format wsadowy) i nie obs³uguje sprawdzania znaków,
    notacji, poprawnoœci danych itp. Doda³em go roboczo, tylko dla zachowania
    symetrii wzglêdem operatorem <<.
*/

    inStream >> value.m_real >> value.m_imaginary;
    return inStream;
}
