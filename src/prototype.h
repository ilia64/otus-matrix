#pragma once

#include <map>
#include <ostream>

template<typename T, T Default>
class Matrix
{
public:
	class Value
	{
	public:
		explicit Value(size_t x, size_t y, Matrix* matrix) : _x(x), _y(y), _matrix(matrix) {}

		const T& get()
		{
			return _matrix->get(_x, _y);
		}

		Value& operator=(T value)
		{
			if (value == get())
			{
				return *this;
			}

			if (value == _default)
			{
				_matrix->remove(_x, _y);
				return *this;
			}

			_matrix->insert(_x, _y, value);
			return *this;
		}

		bool operator==(const T& other) const
		{
			return _matrix->get(_x, _y) == other;
		}

		bool operator==(const Value& other) const
		{
			return other->equal(_x, _y);
		}

		bool equal(size_t x, size_t y) {return _x == x && _y == y;}

		friend std::ostream& operator<< (std::ostream& out, const Value& v);

	private:
		size_t _x;
		size_t _y;
		Matrix* _matrix;
		T _default = Default;
	};

public:
	using Column = std::map<size_t, T>;
	using Data = std::map<size_t, Column>;

	Value operator()(size_t x, size_t y)
	{
		return Value{x, y, this};
	}

	size_t size() const
	{
		size_t result = 0;
		for (const auto &xPair : data)
		{
			for (const auto &yPair : xPair.second)
			{
				++result;
			}
		}
		return result;
	}

	void insert(size_t x, size_t y, T value)
	{
		data[x][y] = value;
	}

	void remove(size_t x, size_t y)
	{
		auto iterX = data.find(x);
		if (iterX == data.end())
		{
			return;
		}

		Column& column = iterX->second;
		auto iterY = column.find(y);
		if (iterY == column.end())
		{
			return;
		}

		column.erase(iterY);
		if (column.empty())
		{
			data.erase(iterX);
		}
	}

private:
	const T& get(size_t x, size_t y) const
	{
		auto iterX = data.find(x);
		if (iterX == data.end())
		{
			return _default;
		}

		auto iterY = iterX->second.find(y);
		if (iterY == iterX->second.end())
		{
			return _default;
		}

		return iterY->second;
	}

private:
	Data data;
	T _default = Default;
};
