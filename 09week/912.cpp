#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <memory>

class Node {
public:
    virtual ~Node() = default;
    virtual std::string getTitle() const = 0;
    virtual bool isFolder() const = 0;
};

class File : public Node {
    std::string title;
public:
    File(std::string t) : title(std::move(t)) {}
    std::string getTitle() const override { return title; }
    bool isFolder() const override { return false; }
};

class Folder : public Node {
    std::string title;
    std::vector<std::shared_ptr<Node>> items;
public:
    Folder(std::string t) : title(std::move(t)) {}
    
    void insert(std::shared_ptr<Node> item) {
        items.push_back(std::move(item));
    }

    const std::vector<std::shared_ptr<Node>>& getItems() const {
        return items;
    }

    std::string getTitle() const override { return title; }
    bool isFolder() const override { return true; }
};

class Iter {
public:
    virtual ~Iter() = default;
    virtual bool hasNext() const = 0;
    virtual std::shared_ptr<Node> getNext() = 0;
};

class DFS : public Iter {
    std::stack<std::shared_ptr<Node>> nodes;
public:
    explicit DFS(std::shared_ptr<Node> root) {
        nodes.push(root);
    }

    bool hasNext() const override {
        return !nodes.empty();
    }

    std::shared_ptr<Node> getNext() override {
        if (nodes.empty()) return nullptr;
        auto node = nodes.top();
        nodes.pop();
        
        if (node->isFolder()) {
            auto folder = std::static_pointer_cast<Folder>(node);
            auto& items = folder->getItems();
            for (auto it = items.rbegin(); it != items.rend(); ++it) {
                nodes.push(*it);
            }
        }
        return node;
    }
};

int main() {
    auto mainFolder = std::make_shared<Folder>("Main");
    auto subFolder1 = std::make_shared<Folder>("Sub1");
    auto subFolder2 = std::make_shared<Folder>("Sub2");
    auto doc1 = std::make_shared<File>("Doc1.txt");
    auto doc2 = std::make_shared<File>("Doc2.txt");
    auto doc3 = std::make_shared<File>("Doc3.txt");

    mainFolder->insert(subFolder1);
    mainFolder->insert(doc1);
    subFolder1->insert(subFolder2);
    subFolder1->insert(doc2);
    subFolder2->insert(doc3);

    std::cout << "DFS Order:\n";
    DFS dfs(mainFolder);
    while (dfs.hasNext()) {
        std::cout << dfs.getNext()->getTitle() << "\n";
    }
}
