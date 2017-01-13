#ifndef _LIST_H_
#define _LIST_H_

#include <string>

struct ListNode
{
    std::string data;
    ListNode* next;
    ListNode* prev;
};

class MyLinkedList
{
    public:
        MyLinkedList();
        ~MyLinkedList();
        int size() const;
        void append(std::string item);
        void insert(std::string item, int position);
        std::string get(int position) const;
        void print() const;
        void print_reverse() const;

    private:
        ListNode* head;
        ListNode* tail;
        int n;
};

#endif
