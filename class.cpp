#include "Vector.h"
#include <cstdlib>
#include <cstring>

Vector::~Vector()
{
    delete[] _data;
}

Vector::Vector(const ValueType *rawArray, const size_t size, float coef) : _size(size), _capacity(size), _multiplicativeCoef(coef)
{
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < size; ++i)
    {
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector &other)
{
    *this = other;
}

Vector &Vector::operator=(const Vector &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] _data;
    ValueType *new_data = nullptr;
    if (other._size > 0)
    {
        new_data = new ValueType[other._size];
        for (size_t i = 0; i < other._size; ++i)
        {
            new_data[i] = other._data[i];
        }
    }
    _data = new_data;
    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    return *this;
}

Vector :: Vector(Vector&& other) noexcept
{
    *this = std::move(other);
}

Vector &Vector::operator=(Vector &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    delete[] _data;
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 0.f;
    return *this;
}

ValueType &Vector::operator[](size_t idx)
{
    if (idx >= _size)
    {
        throw std::out_of_range("Index " + std::to_string(idx) + " out of range");
    }
    return _data[idx];
}

const ValueType &Vector::operator[](size_t idx) const
{
    if (idx >= _size)
    {
        throw std::out_of_range("Index " + std::to_string(idx) + " out of range");
    }
    return _data[idx];
}

void Vector::reserve(size_t capacity)
{
    if (_capacity >= capacity)
    {
        return;
    }
    ValueType *new_data = new ValueType[capacity];
    for (size_t i = 0; i < _size; ++i)
    {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _capacity = capacity;
}

void Vector::pushBack(const ValueType &value)
{
    if ((_size + 1) > _capacity)
    {
        reserve(_capacity > 0 ? _capacity * _multiplicativeCoef : _multiplicativeCoef);
    }
    _data[_size++] = value;
}

void Vector::pushFront(const ValueType &value)
{
    if (_size + 1 > _capacity)
    {
        reserve(_capacity > 0 ? _capacity * _multiplicativeCoef : _multiplicativeCoef);
    }

    for (size_t i = _size; i > 0; --i)
    {
        _data[i] = _data[i - 1];
    }
    _data[0] = value;
    ++_size;
}

void Vector::insert(const ValueType &value, size_t pos)
{
    if (pos > _size)
    {
        throw std::out_of_range("Index " + std::to_string(pos) + " out of range");
    }

    if (_size + 1 > _capacity)
    {
        reserve(_capacity > 0 ? _capacity * _multiplicativeCoef : _multiplicativeCoef);
    }

    for (size_t i = _size; i > pos; --i)
    {
        _data[i] = _data[i - 1];
    }
    _data[pos] = value;
    ++_size;
}

void Vector::insert(const ValueType *values, size_t size, size_t pos)
{
    if (pos > _size)
    {
        throw std::out_of_range("Index " + std::to_string(pos) + " out of range");
    }

    if (_size + size > _capacity)
    {
        size_t new_capacity = _capacity;
        while (new_capacity < _size + size)
        {
            new_capacity = new_capacity > 0 ? new_capacity * _multiplicativeCoef : _multiplicativeCoef;
        }
        reserve(new_capacity);
    }

    for (size_t i = _size + size - 1; i >= pos + size; --i)
    {
        _data[i] = _data[i - size];
    }

    for (size_t i = 0; i < size; ++i)
    {
        _data[pos + i] = values[i];
    }
    _size += size;
}

void Vector::insert(const Vector &vector, size_t pos)
{
    insert(vector._data, vector._size, pos);
}

void Vector::popBack()
{
    if (_size == 0)
    {
        throw std::out_of_range("Vector is empty!");
    }
    --_size;
}

void Vector::popFront()
{
    if (_size == 0)
    {
        throw std::out_of_range("Vector is empty!");
    }

    for (size_t i = 0; i < _size - 1; ++i)
    {
        _data[i] = _data[i + 1];
    }
    --_size;
}

void Vector::erase(size_t pos, size_t count)
{
    if (pos >= _size)
    {
        throw std::out_of_range("Error: position out of range");
    }

    size_t end_pos = pos + count;
    if (end_pos > _size)
    {
        end_pos = _size;
    }

    for (size_t i = end_pos; i < _size; ++i)
    {
        _data[pos + i - end_pos] = _data[i];
    }

    _size -= (end_pos - pos);
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (beginPos >= endPos || beginPos >= _size)
    {
        throw std::out_of_range("Error: invalid range");
    }

    if (endPos > _size)
    {
        endPos = _size;
    }

    size_t count = endPos - beginPos;
    for (size_t i = endPos; i < _size; ++i)
    {
        _data[beginPos + i - endPos] = _data[i];
    }

    _size -= count;
}

size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

double Vector::loadFactor() const
{
    if (_capacity == 0)
    {
        throw std::out_of_range("делить на ноль низя");
    }
    return _size / _capacity;
}

long long Vector::find(const ValueType &value) const
{
    for (size_t i = 0; i < _size; ++i)
    {
        if (_data[i] == value)
        {
            return i;
        }
    }
    std::cout << "Элемента нет!" << std::endl;
    return -1;
}

void Vector::shrinkToFit()
{
    if (_size == _capacity)
    {
        return;
    }

    if (_size == 0)
    {
        delete[] _data;
        _data = nullptr;
        _capacity = 0;
        return;
    }

    ValueType *new_data = new ValueType[_size];
    for (size_t i = 0; i < _size; ++i)
    {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _capacity = _size;
}

Vector::Iterator Vector::begin()
{
    return Iterator(_data);
}

Vector::Iterator Vector::end()
{
    return Iterator(_data + _size);
}

Vector::Iterator::Iterator(ValueType *ptr) : _ptr(ptr) {}

ValueType &Vector::Iterator::operator*()
{
    return *_ptr;
}

const ValueType &Vector::Iterator::operator*() const
{
    return *_ptr;
}

ValueType *Vector::Iterator::operator->()
{
    return _ptr;
}

const ValueType *Vector::Iterator::operator->() const
{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++()
{
    ++_ptr;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++_ptr;
    return tmp;
}

bool Vector::Iterator::operator==(const Iterator &other) const
{
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator &other) const
{
    return _ptr != other._ptr;
}