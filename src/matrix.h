#pragma once

#include <map>
#include <ostream>

template<typename DataIterator, typename T, T Default>
class Iterator
{
public:
	explicit Iterator() = default;
	explicit Iterator(DataIterator iterator, size_t position, size_t end)
	: _iterator(iterator)
	, _position(position)
	, _end(end)
	{}

	bool operator== (const Iterator& rhs)
	{
		return _position == rhs._position;
	}

	bool operator!= (const Iterator& rhs)
	{
		return _position != rhs._position;
	}

	T& operator*()
	{
		return (_position == _iterator->first) ? _iterator->second : _default;
	}

	Iterator& operator++() //++a
	{
		incPosition();
		return *this;
	}

	Iterator operator++(int) //a++
	{
		Iterator temp{_iterator, _position, _end};
		incPosition();
		return temp;
	}

    std::ostream &operator<<(std::ostream &os)
    {
        return os << *(*this);
    }

private:
	void incPosition()
	{
		++_position;
		if (_position < _end && _position > _iterator->first)
		{
			++_iterator;
		}
	}

private:
	DataIterator _iterator;
	size_t _position;
	size_t _end;
	T _default = Default;
};

template<typename T, T Default>
class List
{
public:
	using Map = std::map<size_t, T>;
	using MapIterator = typename Map::iterator;
	using IteratorType = Iterator<MapIterator, T, Default>;

	auto get(size_t i) const
	{
		auto iter = _map.find(i);
        return iter == _map.end() ? _default : iter->second;
	}

	void set(size_t i, T value)
	{
		auto iter = _map.find(i);
		if (iter == _map.end())
		{
			if (!isDefault(value))
			{
				_map.emplace(i, value);
			}
			return;
		}
		if (isDefault(value))
		{
			_map.erase(iter);
			return;
		}
		iter->second = value;
	}

	size_t size() const
	{
        return _map.begin() == _map.end() ? 0 : _map.rbegin()->first + 1;
	}

	bool isDefault(T value)
	{
		return value == _default;
	}

	IteratorType begin()
	{
		return IteratorType{_map.begin(), 0, size()};
	}

	IteratorType end()
	{
		auto iterEnd = size();
		return IteratorType{_map.end(), iterEnd, iterEnd};
	}

	IteratorType end(size_t maxSize)
	{
		return IteratorType{_map.end(), maxSize, size()};
	}



private:
	Map _map;
	T _default = Default;
};

template <typename Matrix, typename T>
class ValueProxy
{
public:
    explicit ValueProxy(Matrix& matrix, size_t x): _matrix(matrix), _x(x) {}

    auto& operator[](size_t y)
    {
        _y = y;
        return *this;
    }

    const auto& get()
    {
        return _matrix->get(_x, _y);
    }

    bool operator==(const T& other) const
    {
        return get() == other;
    }

    bool operator==(const ValueProxy& other) const
    {
        return _x == other._x && _y == other._y;
    }

    ValueProxy& operator=(T value)
    {
        _matrix->set(_x, _y, value);
    }

private:
    Matrix& _matrix;
    size_t _x;
    size_t _y;
};

template<typename T, T Default>
class matrix
{
public:
	using MapValueType = List<T, Default>;
	using Map = std::map<size_t, MapValueType>;

	auto operator[](size_t x)
	{
		return ValueProxy{*this, x};
	}

    T& get(size_t x, size_t y) const
    {
        auto iter = data.find(x);
        if (iter == data.end())
        {
            return Default;
        }
        return iter->second.get(y);
    }

    void set(size_t x, size_t y, T value)
    {
        auto iter = data.find(x);
        if (iter == data.end())
        {
            if (value != Default)
            {
                auto& list = data[x];
                list.set(y, value);
            }
            return;
        }
        iter->second.set(y, value);
        if (iter.second.size() == 0)
        {
            data.erase(iter);
        }
    }

    size_t width() const
    {
        return data.begin() == data.end() ? 0 : data.rbegin()->first + 1;
    }

    size_t height() const
    {
        size_t result = 0;
        for(const auto& p : data)
        {
            result += p.second.size();
        }
        return result;
    }

private:
	 Map data;
};
