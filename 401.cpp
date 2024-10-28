#include <cassert>
#include <string>

template <typename T, typename Key>
[[nodiscard]] const T* binary_search(const T* array, std::size_t size, const Key& key)
{
	if (size > 0)
	{
		std::size_t l = 0, r = size - 1, m{};

		while (l < r)
		{
			m = l + (r - l) / 2;
			array[m] < key ? l = m + 1 : r = m;
		}

		return (array[l] == key ? array + l : nullptr);
	}
	else
	{
		return nullptr;
	}
}

int main()
{
	const std::size_t size = 5;
	const int array[size] { 1, 2, 3, 4, 5 };

	assert(binary_search(array, size, 1) == array + 0);
	assert(binary_search(array, size, 2) == array + 1);
	assert(binary_search(array, size, 3) == array + 2);
	assert(binary_search(array, size, 4) == array + 3);
	assert(binary_search(array, size, 5) == array + 4);

	const char* str_array[] = { "a", "b", "c", "d", "e" };
	assert(binary_search(str_array, size, std::string("d")) == str_array + 3);

	return 0;
}

    
