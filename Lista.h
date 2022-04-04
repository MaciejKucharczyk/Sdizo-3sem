#include <iostream>

using namespace std;

struct ElemList
{
	ElemList* next, *prev;   // nastêpnik i poprzednik                 DOSTOSUJ
	int data;
};

class List
{
	ElemList* head, * tail;
public:

	List();
	~List();

	void loadFromFile(ElemList*& head, string filename);

	ElemList* IsValueInList(ElemList* head, int val);

	void addValue(int index, int value);

	void deleteFromList(ElemList*& head, ElemList*& tail, int val);

	void display(ElemList* head);

	void displayBackwards(ElemList* tail);

	//	void generateList(int size);

	ElemList* findTail(ElemList* head); //funkcja zwracajaca ogon listy

	void push_front(ElemList*& head, int val);

	void push_back(ElemList*& tail, int val);

	void push_whereIndex(ElemList*& head, int val, int in);


};
