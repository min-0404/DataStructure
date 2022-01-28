#include "AVL.h"
int main()
{
	int a, choice, findele, delele;
	bstree bst;
	bool flag = true;
	bst.insert(19); bst.insert(10); bst.insert(46);
	bst.insert(4); bst.insert(14);
	bst.insert(37); bst.insert(55); bst.insert(7);
	bst.insert(12); bst.insert(18);
	bst.insert(28); bst.insert(40); bst.insert(51);
	bst.insert(61); bst.insert(21);
	bst.insert(32); bst.insert(49); bst.insert(58);
	while (flag == true)
	{
		cout << "Enter the choice: (1 : search, 2 : add, 3 : delete, 4 : show, 0 : exit) ";
			cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter node to search: ";
			cin >> findele;
			if (bst.getRoot() != NULL)
				bst.Search(findele);
			break;
		case 2:
			cout << "Enter a new value: ";
			cin >> a;
			bst.insert(a);
			bst.Showresult();
			break;
		case 3:
			cout << "Enter node to delete: ";
			cin >> delele;
			bst.del(delele);
			bst.Showresult();
			break;
		case 4:
			if (bst.getRoot() != NULL)
				bst.Showresult();
			break;
		case 0:
			cout << "\n\tThank your for using AVL tree program\n" <<
				endl;
			flag = false;
			break;
		default:
			cout << "Sorry! wrong input\n" << endl;
			break;
		}
	}
	return 0;
}


