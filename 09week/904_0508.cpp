#include <iostream>
#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Entity 
{
public:
    virtual ~Entity() = default;

    virtual void test() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{ 
public: 
    void test() const override 
    { 
        std::cout << "Client::test\n";
    } 
};

////////////////////////////////////////////////////////////

class Server : public Entity 
{ 
public: 
    void test() const override 
    { 
        std::cout << "Server::test\n";
    } 
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Decorator : public Entity
{
public:
    // Используем std::unique_ptr для владения объектом m_entity
    Decorator(std::unique_ptr<Entity> entity): m_entity(std::move(entity)) {}

    void test() const override
    { 
        std::cout << "Decorator::test : ";
        m_entity->test();
    }

private:
    std::unique_ptr<Entity> m_entity;  // Умный указатель на Entity
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // Создаем объекты с использованием std::make_unique
    auto entity_1 = std::make_unique<Client>();

    auto entity_2 = std::make_unique<Decorator>(std::move(entity_1));

    entity_2->test();
}
