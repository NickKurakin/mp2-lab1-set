// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
//#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

int main()
{
    try {
        /*TBitField bits1(5);
        TBitField bits2(5);
        TBitField bits3(1);
        std::cout << "bits1(5): ";
        std::cin >> bits1;
        std::cout << "bits2(5): ";
        std::cin >> bits2;
        std::cout << "bits1: " << bits1 << endl;
        std::cout << "bits2: " << bits2 << endl;
        std::cout << "~bits1: " << ~bits1 << endl;
        std::cout << "bits1 & bits2: " << (bits1 & bits2) << endl;
        std::cout << "bits1 | bits2: " << (bits1 | bits2) << endl;
        bits3 = bits2;
        std::cout << "bits3 (copy bits2): " << bits3 << endl;
        std::cout << "bits3 == bits1: " << (bits3 == bits1) << endl;
        std::cout << "bits3 != bits1: " << (bits3 != bits1) << endl;
        TBitField bits4(bits1);
        std::cout << "bits4 (copy bits1): " << bits4 << endl;
        TBitField bits5(6);
        std::cout << "bits5(6): ";
        std::cin >> bits5;
        std::cout << "bits5: " << bits5 << endl;
        std::cout << "bits1 & bits5: " << (bits1 & bits5) << endl;
        std::cout << "bits1 | bits5: " << (bits1 | bits5) << endl;*/
        TSet set1(5);
        TSet set2(5);
        int tmp;
        std::cout << "set1(5): ";
        std::cin >> set1;
        std::cout << "set2(5): ";
        std::cin >> set2;
        std::cout << "int: ";
        std::cin >> tmp;
        std::cout << "set1: " << set1 << endl;
        std::cout << "set2: " << set2 << endl;
        TSet set3(set1);
        std::cout << "set3(set1): " << set3 << endl;
        set3 = set2;
        std::cout << "set3(set3 = set2): " << set3 << endl;
        std::cout << "set1 + set2: " << set1 + set2 << endl;
        std::cout << "set1 * set2: " << set1 * set2 << endl;
        std::cout << "set1 + int: " << set1 + tmp << endl;
        std::cout << "set1 - int: " << set1 - tmp << endl;
        std::cout << "set1 == set2: " << (set1 == set2) << endl;
        std::cout << "set1 != set2: " << (set1 != set2) << endl;
        std::cout << "~set1: " << ~set1 << endl;
        TBitField bits(5);
        std::cout << "TBitField(5): ";
        std::cin >> bits;
        std::cout << "TBitField: " << bits << endl;
        TSet set4(bits);
        std::cout << "set4(bits): " << set4 << endl;
    }
    catch (...)
    {
        std::cout << "error" << endl;
    }
    system("pause");
    return 1;
}

TSet::TSet(int mp) try : MaxPower(mp), BitField(mp)
{} catch(...) { std::cout << "error" << endl; }

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField()
{
    TBitField tmp(this->BitField);
    return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this == &s) return *this;
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
}

bool TSet::operator==(const TSet &s) const // сравнение
{
    return ((this->MaxPower == s.MaxPower) && (this->BitField == s.BitField));
}

bool TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet tmp(*this);
    tmp.BitField = tmp.BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tmp(*this);
    tmp.BitField.SetBit(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tmp(*this);
    tmp.BitField.ClrBit(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tmp(*this);
    tmp.BitField = tmp.BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp(*this);
    tmp.BitField = ~tmp.BitField;
    return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    char ch = ' '; int tmp;
    while (ch != '{') istr >> ch;
    do
    {
        istr >> tmp;
        s.InsElem(tmp);
        do { istr >> ch;} while (ch != ',' && ch != '}');
    } while (ch != '}');
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    bool first = true;
    ostr << "{";
    for (int i = 0; i < s.GetMaxPower(); i++)
    {
        if (s.IsMember(i))
        {
            if (first)
            {
                ostr << ' ' << i;
                first = false;
            }
            else ostr << ", " << i;
        }
    }
    ostr << " }";
    return ostr;
}