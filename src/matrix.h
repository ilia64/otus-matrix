#pragma once

#include <map>

template<typename T, T Default, size_t Depth = 2>
class matrix
{
public:
	using DataValue = matrix<T, Default, Depth - 1>;
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

template<typename T, T Default>
class matrix<T, Default, 1>
{
public:
	using DataValue = T;
	using Data = std::map<size_t, DataValue>;

	auto& operator[](size_t i)
	{
		auto iter = data.find(i);
		if (iter == data.end())
		{
			data.emplace(i, _default);
			return data[i];
		}
		return iter->second;
	}

	size_t size() const
	{
		size_t result = 0;
		for(const auto& p : data)
		{
			if (p.second != _default)
			{
				++result;
			}
		}
		return result;
	}

private:
	Data data;
	T _default = Default;
};
