#pragma once

#include <istream>
#include <ostream>
#include <cmath>
#include <stdexcept>

/*
    Klasa sama w sobie spe³nia³aby "Rule of Zero" (nie zarz¹dza zasobami - ma tylko dwa pola typu double),
    ale... jawny konstruktor kopiuj¹cy, który zosta³ zaimplementowany ze wzglêdu na wymagania zadania,
    od strony formalnej zaburza Rule of Zero. Dlatego, pomimo ¿e operator przypisania kopiuj¹cy oraz
    destruktor zosta³yby wygenerowane automatycznie (i wszystko by dzia³a³o poprawnie),
    zadeklarowa³em je jawnie jako "default", celowo wskazaæ w projekcie klasy zgodnoœæ z "Rule of Three".
*/

class CComplex
{
private:
    double m_real{0.0};
    double m_imaginary{0.0};

public:
    CComplex() = default;
    CComplex(double real, double imaginary = 0.0);
    CComplex(const CComplex& other);
    CComplex& operator=(const CComplex& other) = default;
    ~CComplex() = default;

    void SetReal(double real);
    double GetReal() const;

    void SetImaginary(double imaginary);
    double GetImaginary() const;

    bool operator==(const CComplex& other) const;
    bool operator!=(const CComplex& other) const;

    CComplex& operator+=(const CComplex& other);
    CComplex& operator-=(const CComplex& other);
    CComplex& operator*=(const CComplex& other);
    CComplex& operator/=(const CComplex& other);

    CComplex operator-() const;

    friend std::ostream& operator<<(std::ostream& outStream, const CComplex& value);
    friend std::istream& operator>>(std::istream& inStream, CComplex& value);
};

// Operatory globalne
inline CComplex operator+(CComplex left, const CComplex& right) { return left += right; }
inline CComplex operator-(CComplex left, const CComplex& right) { return left -= right; }
inline CComplex operator*(CComplex left, const CComplex& right) { return left *= right; }
inline CComplex operator/(CComplex left, const CComplex& right) { return left /= right; }
