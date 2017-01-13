#include <iostream>
#include "list.h"
#include "list_test.h"

using namespace std;

static void print_list(const MyLinkedList& list)
{
    cout << "  Linked list has " << list.size() << " items:" << endl;
    for (int i = 0; i < list.size(); i++)
    {
        cout << "    \"" << list.get(i) << "\"" << endl;
    }
}

static void test1()
{
    MyLinkedList list;
    list.append("hello");
    list.append("world");
    print_list(list);
}

static void test2()
{
    MyLinkedList list;
    list.append("hello");
    list.append("world");
    list.insert("hi", 0);
    print_list(list);
}

static void test3()
{
    MyLinkedList list;
    list.append("hello");
    list.append("world");
    list.insert("hi", 2);
    print_list(list);
}

void test_my_linked_list()
{
    cout << "Running test #1..." << endl;
    test1();
    cout << "Running test #2..." << endl;
    test2();
    cout << "Running test #3..." << endl;
    test3();
}
