#include <iterator>
#include <memory>

///////////////////////////////////////////////////////////////////////////////////

template <typename T>
class List {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;

        Node(T value) : data(value) {}
    };

public:
    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator(std::shared_ptr<Node> node = nullptr) : m_node(node) {}

        Iterator& operator++() {
            if (m_node) {
                m_node = m_node->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy = *this;
            ++(*this);
            return copy;
        }

        Iterator& operator--() {
            if (m_node) {
                m_node = m_node->prev.lock();
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator copy = *this;
            --(*this);
            return copy;
        }

        T& operator*() const { return m_node->data; }
        T* operator->() const { return &m_node->data; }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.m_node == rhs.m_node;
        }

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return !(lhs == rhs);
        }

    private:
        std::shared_ptr<Node> m_node;
    };

    // Итераторы
    Iterator begin() const { return Iterator(m_head); }
    Iterator end() const { return Iterator(); }
    Iterator rbegin() const { return Iterator(m_tail); }
    Iterator rend() const { return Iterator(); }

    void push_back(T x) {
        auto node = std::make_shared<Node>(x);

        if (m_tail) {
            m_tail->next = node;
            node->prev = m_tail;
        } else {
            m_head = node;
        }

        m_tail = node;
    }

    void push_front(T x) {
        auto node = std::make_shared<Node>(x);
        
        if (m_head) {
            m_head->prev = node;
            node->next = m_head;
        } else {
            m_tail = node;
        }

        m_head = node;
    }

private:
    std::shared_ptr<Node> m_head;
    std::shared_ptr<Node> m_tail;
};

///////////////////////////////////////////////////////////////////////////////////

#include <iostream>

int main() {
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);

    std::cout << "Прямой обход списка: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\nОбратный обход списка: ";
    for (auto it = list.rbegin(); it != list.rend(); --it) {
        std::cout << *it << " ";
    }

    return 0;
}
