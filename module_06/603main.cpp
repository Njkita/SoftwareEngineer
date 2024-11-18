import Entity;
#include <cassert>

int main() {
    using namespace MyNamespace;

    Entity entity_1;
    entity_1.set_data_3(1);
    assert(entity_1.data_3() == 1);
    assert(entity_1.data_as_string() == "0/0/1");

    const Entity entity_2;
    assert(entity_2.data_3() == 0);
    assert(entity_2.data_as_string() == "0/0/0");

    Entity entity_3;
    Entity entity_4(1, 2, 3);
    Entity entity_5(1, 2);

    entity_1.test();
    Entity::test();

    return 0;
}