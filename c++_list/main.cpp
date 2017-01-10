#include <iostream>

using namespace std;

struct node
{
	int data;
	node *next;
	node(int d)
	{
		data = d;
		next = NULL;
	}
};

struct list
{
	int count;
	node *head;
	list()
	{
		count = 0;
		head = NULL;
	}
};

int Count(list &l)
{
	return l.count;
}

void Add(list &l, node &n)
{
	l.count++;
	if (l.head == NULL)
	{		
		l.head = &n;
	}
	else
	{
		node node = *(l.head);
		while (node.next != NULL)
		{
			node = *(node.next);
		}
		node.next = &n;
	}
}

void show(list &l)
{
	node *n = l.head;
	do {
		cout << n->data << " ";
	} while ((n = n->next) && n != NULL);
		cout << endl;
}

int main()
{
	list l1;
	node n1(1);
	Add(l1,n1);
	Add(l1,n1);
	cout << Count(l1) << endl;
	show(l1);

	system("pause");
	return 0;
}