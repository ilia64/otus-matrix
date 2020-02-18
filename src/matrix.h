#pragma once

#include <map>

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
		if (iter == _map.end())
		{
			return _default;
		}
		return iter->second;
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
		if (_map.begin() == _map.end())
		{
			return 0;
		}
		return _map.rbegin()->first + 1;
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

template<typename T, T Default, bool Columns = true>
class matrix
{
public:
	using DataValue = matrix<T, Default, Columns>;
	using Data = std::map<size_t, DataValue>;

	auto& operator[](size_t i)
	{
		auto iter = data.find(i);
		if (iter == data.end())
		{
			data.emplace(i, DataValue{});
			return data[i];
		}
		return iter->second;
	}

	size_t size() const
	{
		size_t result = 0;
		for(const auto& p : data)
		{
			result += p.second.size();
		}
		return result;
	}

private:
	 Data data;
};
