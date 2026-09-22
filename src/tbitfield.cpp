// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 1)
    {
        throw len;
    }
    else
    {
        BitLen = len;
        MemLen = ((len - 1) >> pBit) + 1;
        pMem = new TELEM[MemLen];
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[this->MemLen];
    for (int i = 0; i < this->MemLen;i++)
    {
        this->pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete pMem;
}

int TBitField::GetMemIndex(const int pos) const // индекс Мем для бита n
{
    return pos >> pBit;
}

TELEM TBitField::GetMemMask(const int pos) const // битовая маска для бита n
{
    return 1<<(pos&(nBit-1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int pos) // установить бит
{
    if ((pos < 0) || (pos >= BitLen))
    {
        throw pos;
    }
    else
    {
        pMem[GetMemIndex(pos)] |= GetMemMask(pos);
    }
}

void TBitField::ClrBit(const int pos) // очистить бит
{
    if ((pos < 0) || (pos >= BitLen))
    {
        throw pos;
    }
    else
    {
        pMem[GetMemIndex(pos)] &= ~GetMemMask(pos);
    }
}

int TBitField::GetBit(const int pos) const // получить значение бита
{
    if ((pos < 0) || (pos >= BitLen))
    {
        throw pos;
    }
    else
    {
        return pMem[GetMemIndex(pos)] & GetMemMask(pos);
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    delete pMem;
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[this->MemLen];
    for (int i = 0; i < this->MemLen;i++)
    {
        this->pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (this->BitLen == bf.BitLen)
    {
        for (int i = 0; i < this->BitLen; i++)
        {
            if (this->GetBit(i) != bf.GetBit(i))
            {
                return 0;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (this->BitLen == bf.BitLen)
    {
        for (int i = 0; i < this->BitLen; i++)
        {
            if (this->GetBit(i) != bf.GetBit(i))
            {
                return 1;
            }
        }
        return 0;
    }
    else
    {
        return 1;
    }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (this->BitLen != bf.BitLen)
    {
        throw this->BitLen;
    }
    else
    {
        TBitField newTBitField(*this);
        for (int i = 0; i < newTBitField.MemLen;i++)
        {
            newTBitField.pMem[i] |= bf.pMem[i];
        }
        return newTBitField;
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (this->BitLen != bf.BitLen)
    {
        throw this->BitLen;
    }
    else
    {
        TBitField newTBitField(*this);
        for (int i = 0; i < newTBitField.MemLen;i++)
        {
            newTBitField.pMem[i] &= bf.pMem[i];
        }
        return newTBitField;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField newTBitField(*this);
    for (int i = 0; i < newTBitField.MemLen;i++)
    {
        newTBitField.pMem[i] = ~newTBitField.pMem[i];
    }
    return newTBitField;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = bf.BitLen - 1;i >= 0; i--)
    {
        //ostr << bf.GetBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = bf.BitLen - 1;i >= 0; i--)
    {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
