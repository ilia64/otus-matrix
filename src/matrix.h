#pragma once

#include <map>

template<typename T, T Default>
class IteratorRow
{
public:
	explicit IteratorRow() = delete;
	explicit IteratorRow(size_t position = 0) : _position(position) {}

	bool operator== (const IteratorRow& rhs)
	{
		return _position == rhs._position;
	}
	bool operator!= (const IteratorRow& rhs)
	{
		return _position != rhs._position;
	}

private:
	size_t _position;
};

template<typename T, T Default>
class Rows
{
public:
	using Data = std::map<size_t, T>;

	auto get(size_t i) const
	{
		auto iter = data.find(i);
		if (iter == data.end())
		{
			return _default;
		}
		return iter->second;
	}

	void set(size_t i, T value)
	{
		auto iter = data.find(i);
		if (iter == data.end())
		{
			if (!isDefault(value))
			{
				data.emplace(i, value);
			}
			return;
		}
		if (isDefault(value))
		{
			data.erase(iter);
			return;
		}
		iter->second = value;
	}

	size_t size() const
	{
		if (data.begin() == data.end())
		{
			return 0;
		}
		return data.rbegin()->first + 1;
	}

	bool isDefault(T value)
	{
		return value == _default;
	}

	auto begin()
	{
		return IteratorRow<T, Default>{};
	}

	auto end(size_t maxSize = -1)
	{
		maxSize = maxSize == -1 ? size() : maxSize;
		return IteratorRow<T, Default>{maxSize};
	}

private:
	Data data;
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
