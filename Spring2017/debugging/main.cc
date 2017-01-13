#include <iostream>
#include "list.h"
#include "list_test.h"

using namespace std;

int main()
{
    test_my_linked_list();

    /*
    MyLinkedList list;
    while (!cin.eof())
    {
        char buffer[1024];
        cin.getline(buffer, sizeof(buffer));
        string line {buffer};
        if (line != "")
        {
            list.append(line);
        }
    }
    cout << list.size() << " items in the list in reverse order:" << endl;
    list.print_reverse();
    */
    return 0;
}
