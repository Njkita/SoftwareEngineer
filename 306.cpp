#include <algorithm>
#include <iostream>
#include <utility>

class Container
{
public:
	Container() : m_data(nullptr), m_size(0), m_capacity(0) {
		std::cout << "Container::Container (main)" << std::endl;
	}

	Container(std::size_t size) : m_size(size), m_capacity(size) {
		std::cout << "Container::Container (user)" << std::endl;
		m_data = new int[m_capacity]{};
	}

	Container(const Container & other) : m_size(other.m_size), m_capacity(other.m_capacity)  {
		std::cout << "Container::Container (copy)" << std::endl;
		m_data = new int[m_capacity]{};
		std::copy(other.m_data, other.m_data + m_size, m_data);
	}

	Container(Container && other) : Container() {
		std::cout << "Container::Container (move)" << std::endl;
		swap(other);
	}
	Container & operator=(Container other) {
		std::cout << "Container::operator= (swap)" << std::endl;
		swap(other);
		return *this;
	}
   ~Container() {
		std::cout << "Container::~Container" << std::endl;
		if (m_data) delete[] m_data;
	}

public:
	void swap(Container & other) {
		using std::swap; 
		swap(m_data, other.m_data);
		swap(m_size, other.m_size);
		swap(m_capacity, other.m_capacity);
	}

    int& front() {
        return m_data[0];
    }

    const int& front() const {
        return m_data[0];
    }

    int& back() {
        return m_data[m_size - 1];
    }

    const int& back() const {
        return m_data[m_size - 1];
    }

    int& operator[](std::size_t index) {
        return m_data[index];
    }

    const int& operator[](std::size_t index) const {
        return m_data[index];
    }

    std::size_t size() const {
        return m_size;
    }

    std::size_t capacity() const {
        return m_capacity;
    }

    bool empty() const {
        return m_size == 0;
    }

    void clear() {
        m_size = 0;
    }

	void capacity_increase(std::size_t new_capacity) {
		int* new_data = new int[new_capacity]{};
		std::copy(m_data, m_data + m_size, new_data);
		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
    }

	void push_back(int value) {
        if (m_size == m_capacity) {
			if (m_size == 0) m_capacity = 1;
			else m_capacity*=2;
            capacity_increase(m_capacity);
        }
        m_data[m_size] = value;
		m_size++;
    }

private:
	int* m_data; 
	std::size_t m_size;
	std::size_t m_capacity;
};

inline void swap(Container & x, Container & y) { x.swap(y); }

int main()
{
	const std::size_t size = 5;
	Container container_1;
	Container container_2(size);
	Container container_3(container_2);
	Container container_4(std::move(container_3));
	container_1 = container_2;
	container_3 = std::move(container_4);
	swap(container_1, container_3);
	
	Container container_5;
	container_5.push_back(0);
	container_5.push_back(1);
    container_5.push_back(2);
    container_5.push_back(3);
    std::cout << "First element: " << container_5.front() << std::endl;
    std::cout << "Last element: " << container_5.back() << std::endl;
    std::cout << "Element at index 2: " << container_5[2] << std::endl;
    std::cout << "Container size: " << container_5.size() << std::endl;
    std::cout << "Container capacity: " << container_5.capacity() << std::endl;
	container_5.push_back(4);
	container_5.push_back(5);
	std::cout << "Container size: " << container_5.size() << std::endl;
    std::cout << "Container capacity: " << container_5.capacity() << std::endl;
    container_5.clear();
    std::cout << "Container size after clear: " << container_5.size() << std::endl;
	std::cout << "Container capacity after clear: " << container_5.capacity() << std::endl;
	return 0;
}