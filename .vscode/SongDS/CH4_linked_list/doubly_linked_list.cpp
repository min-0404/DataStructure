#include <iostream>
using namespace std;

class DbList;

class DbListNode
{
private:
    int data;
    DbListNode* left, *right;
public:
    DbListNode(int element = 0, DbListNode* l = NULL, DbListNode* r = NULL):data(element), left(l), right(r)
    {}
    friend class DbList;
    friend ostream& operator<<(ostream& os, DbList& d);
};

class DbList
{
private:;
    DbListNode* first;
public:
    
};

