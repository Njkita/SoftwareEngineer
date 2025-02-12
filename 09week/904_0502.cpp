#include <iostream>
#include <memory>

///////////////////////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default;

    virtual void test() const = 0;
};

///////////////////////////////////////////////////////////

class Client : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Client::test\n";
    } 
};

///////////////////////////////////////////////////////////

class Server : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Server::test\n";
    } 
};

///////////////////////////////////////////////////////////

template < typename E > auto make_entity() -> std::unique_ptr<Entity>
{ 
    return std::make_unique<E>();
}

///////////////////////////////////////////////////////////

class Router : public Entity
{
public:

    class Factory
    {
    public:
        // Создание через статический метод Factory
        static auto make_v1() -> std::unique_ptr<Entity> { return std::unique_ptr<Entity>(new Router(1)); }
        static auto make_v2() -> std::unique_ptr<Entity> { return std::unique_ptr<Entity>(new Router(2)); }
    };

    void test() const override 
    { 
        std::cout << "Router::test\n";
    }

private:

    // Приватный конструктор
    Router(int x) : m_data(x) {}

    int m_data = 0;
};

///////////////////////////////////////////////////////////

class Factory
{
public:

    virtual ~Factory() = default;

    virtual std::unique_ptr<Entity> make() const = 0;
};

///////////////////////////////////////////////////////////

class Factory_Client : public Factory 
{ 
public: 
    
    std::unique_ptr<Entity> make() const override 
    { 
        return std::make_unique<Client>();
    } 
};

///////////////////////////////////////////////////////////

class Factory_Server : public Factory 
{ 
public: 
    
    std::unique_ptr<Entity> make() const override 
    { 
        return std::make_unique<Server>();
    } 
};

///////////////////////////////////////////////////////////

int main()
{
    {
        auto entity = make_entity<Client>();
        entity->test();
    }
    
    {
        auto entity = Router::Factory::make_v1();
        entity->test();
    }

    {
        Factory_Client factory_client;
        auto entity = factory_client.make();
        entity->test();
    }

    return 0;
}
