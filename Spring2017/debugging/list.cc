#include <iostream>
#include "list.h"

MyLinkedList::MyLinkedList()
{
    this->n = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

MyLinkedList::~MyLinkedList()
{
    ListNode* c = head;
    while (c != nullptr)
    {
        ListNode* next = c->next;
        delete c;
        c = next;
    }
}

int MyLinkedList::size() const
{
    return n;
}

void MyLinkedList::append(std::string item)
{
    ListNode* node = new ListNode { item, nullptr, nullptr };
    if (head == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    n++;
}

void MyLinkedList::insert(std::string item, int position)
{
    ListNode* node = new ListNode { item, nullptr, nullptr };
    ListNode* c = head;
    ListNode* p = nullptr;
    for (int i = 0; i < position; i++)
    {
        p = c;
        c = c->next;
    }
    if (p == nullptr)
    {
        if (head != nullptr)
        {
            head->prev = node;
            node->next = head;
            head = node;
        }
        else
        {
            head = node;
            tail = node;
        }
    }
    else
    {
        p->next = node;
        node->prev = p;
        c->prev = node;
        node->next = c;
    }
}

std::string MyLinkedList::get(int position) const
{
    ListNode* c = head;
    for (int i = 0; i < position; i++)
    {
        c = c->next;
    }
    return c->data;
}

void MyLinkedList::print() const
{
    ListNode* c = head;
    while (c != nullptr)
    {
        std::cout << c->data << std::endl;
        c = c->next;
    }
}

void MyLinkedList::print_reverse() const
{
    ListNode* c = tail;
    while (c != nullptr)
    {
        std::cout << c->data << std::endl;
        c = c->prev;
    }
}
