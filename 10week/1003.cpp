/*
Можно использовать метод двух указателей fast и slow:
Один указатель ("быстрый") перемещается на два узла за шаг, а другой
("медленный") — на один узел за шаг. Когда быстрый указатель достигает конца
списка, медленный указатель будет находиться на среднем узле.
Алгоритм работает примерно одинаково как для односвязных, так и для двусвязных
списков, так как он не использует обратные ссылки.
*/

#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *findMiddle(ListNode *head) {
  if (!head)
    return nullptr;

  ListNode *slow = head;
  ListNode *fast = head;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  return slow;
}
