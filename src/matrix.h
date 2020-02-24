#pragma once

#include <array>
#include <map>
#include <cassert>

template<typename Matrix, typename T, size_t Depth = 2>
class Value
{
public:
	using Key = std::array<size_t, Depth>;

	Value() = delete;

	explicit Value(Matrix* matrix, Key key) : _matrix(matrix), _key(key), _index(Depth)
	{
		static_assert(Depth > 0, "Empty depth");
	}

	explicit Value(Matrix* matrix, size_t i) : _matrix(matrix), _key({i}), _index(1)
	{
		static_assert(Depth > 0, "Empty depth");
	}

	auto& operator[](size_t i)
	{
		assert(_index < Depth && "Out of depth");
		_key[_index] = i;
		++_index;
		return *this;
	}

	const auto& get() const
	{
		assert(_index == Depth && "Wrong depth");
		return _matrix->get(_key);
	}

	T operator=(T value)
	{
		assert(_index == Depth && "Wrong depth");
		_matrix->set(_key, value);
		return value;
	}

	bool operator==(const T& value) const
	{
		return get() == value;
	}

private :
	Matrix* _matrix;
	Key _key;
	size_t _index;
};

template<typename Matrix, typename T, size_t Depth = 2>
std::ostream &operator<<(std::ostream &out, const Value<Matrix, T, Depth>& value)
{
	return out << value.get();
}

template<typename T, T Default, size_t Depth = 2>
class Matrix
{
public:
	using Key = std::array<size_t, Depth>;
	using Map = std::map<Key, T>;

	auto operator[](size_t i)
	{
		return Value<Matrix, T, Depth>(this, i);
	}

	template<typename ...Args>
	auto operator()(Args... args)
	{
		return Value<Matrix, T, Depth>(this, {size_t(args)...});
	}

    const T& get(const Key& key) const
    {
        auto iter = _map.find(key);
        if (iter == _map.end())
        {
            return _default;
        }
        return iter->second;
    }

    void set(const Key& key, T value)
    {
        auto iter = _map.find(key);
        if (iter == _map.end())
        {
            if (value != Default)
            {
				_map.emplace(key, value);
            }
			return;
        }

        if (value == Default)
		{
			_map.erase(iter);
			return;
		}
		iter->second = value;
    }

    size_t size()
    {
	    return _map.size();
    }

    auto begin()
    {
        return _map.begin();
    }

    auto end()
    {
		return _map.end();
    }

private:
	Map _map;
	const T _default = Default;
};
