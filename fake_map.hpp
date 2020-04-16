#ifndef DUGI_FAKE_MAP
#define DUGI_FAKE_MAP

#include <vector>
#include <stdexcept>

template <typename KeyType, typename MappedType, typename = void, typename = void>
class FakeMap {
public:
	using key_type = KeyType;
	using mapped_type = MappedType;
	using size_type = int;
	using value_type = std::pair<const key_type, mapped_type>;
	using reference = mapped_type&;
	using const_reference = const mapped_type&;
private:
	using mutable_value_type = std::pair<key_type, mapped_type>;
public:
	using underlying_type = std::vector<mutable_value_type>;
private:
	underlying_type _data;
public:
	FakeMap() { }
	FakeMap(size_type initialCapacity) {
		_data.reserve(initialCapacity);
	}
	FakeMap(const FakeMap& other)
		: _data(other._data) { }
	FakeMap(FakeMap&& other)
		: _data(other._data) { }
	~FakeMap() { }
	FakeMap& operator=(const FakeMap& other) {
		_data = other._data;
		return *this;
	}
	FakeMap& operator=(FakeMap&& other) {
		_data = other._data;
		return *this;
	}

	size_type size() const {
		return _data.size();
	}

	size_type capacity() const {
		return _data.capacity();
	}

	bool empty() const {
		return _data.empty();
	}

	using iterator = typename underlying_type::iterator;
	using const_iterator = typename underlying_type::const_iterator;

	iterator begin() {
		return _data.begin();
	}

	iterator end() {
		return _data.end();
	}

	const_iterator cbegin() const {
		return _data.begin();
	}

	const_iterator cend() const {
		return _data.end();
	}

	const_iterator begin() const {
		return cbegin();
	}

	const_iterator end() const {
		return cend();
	}

	void insert(const value_type added) {
		_data.push_back(added);
	}

	void emplace() {
		return _data.push_back();
	}	

	template <typename Arg, typename... Args >
	void emplace(Arg arg, Args&&... args ) {
		return _data.emplace_back(arg, args...);
	}

	iterator erase(const_iterator erased) {
		return _data.erase(erased._value);
	}

	const_iterator find(const key_type& key) const {
		for (auto it = _data.begin(); it != _data.end(); ++it) {
			if (it->first == key)
				return it;
		}
		return _data.end();
	}

	iterator find(const key_type &key) { // Same as above, can't cast the result to reuse the code
		for (auto it = _data.begin(); it != _data.end(); ++it) if (it->first == key) return it;
		return _data.end();
	}

	size_type erase(const key_type& key) {
		if (empty()) return 0;
		for (auto it = _data.begin(); it != _data.end(); ++it)
			if (it->first == key) {
				_data.erase(it);
				return 1;
		}
		return 0;
	}

	mapped_type& operator[](const key_type& key) {
		for (auto& it : _data) {
			if (it.first == key)
				return it.second;
		}
		_data.push_back(std::make_pair(key, mapped_type()));
		return _data.back().second;
	}

	const mapped_type& at(const key_type& key) const {
		for (auto& it : _data) {
			if (it.first == key)
				return it.second;
		}
		throw std::out_of_range("Element does not exist");
	}

	mapped_type& at(const key_type& key) {
		return const_cast<mapped_type&>(const_cast<const FakeMap*>(this)->at(key));
	}

	int count(const key_type& key) {
		for (auto& it : _data) {
			if (it.first == key)
				return 1;
		}
		return 0;
	}

	void clear() {
		_data.clear();
	}
};
#endif
