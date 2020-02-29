#include <iostream>

using namespace std;

//���������� ���������� ��� ���������� id � ���� ������
static int Sid = 0;
//���������� ��������� ��� �������� ������ ������� ������
static int Task = 0;

//��������� ������
struct Tree
{
	//������
	int val, id, lvl, numSons, N;
	//������ ����� �� �������
	Tree **Sons;
};

//������� ������������� �����
//��������� ��������� �� ������ ������ ��� �������� ����-�� �������
void Init(Tree **tree, int val, int N)
{
	//������� ������
	Tree *son = new Tree;
	//����������� id ������� ���������� ���
	son->id = Sid++;
	//����������� �������
	son->lvl = 0;
	//������ ��������
	son->val = val;
	//������ ����� �������� �������
	son->numSons = 0;
	//������ ���� ���-�� �������
	son->N = N;
	//�������� ������ ��� ������ �����
	son->Sons = new Tree*[N];
	for (int i(0); i < N; i++)
	{
		son->Sons[i] = NULL;
	}
	//������������� ��������� �� ������
	*tree = son;
}

//������� ���������� ����
//��������� ��������� �� ������ ������, id �������� � ��� ��������
//���������� ������ ��������
bool AddSon(Tree **tree, int id, int val)
{
	//������� ��������� ���������
	Tree *temp = *tree;
	//���� ������ ��� id � ��� ����� �������� �������
	if (id == temp->id && temp->numSons < temp->N)
	{
		//������� ������
		Tree *son = new Tree;
		//����������� id ������� ���������� ���
		son->id = Sid++;
		//����������� �������
		son->lvl = temp->lvl + 1;
		//������ ��������
		son->val = val;
		//������ ���� ���-�� �������
		son->N = temp->N;
		//������ ����� �������� �������
		son->numSons = 0;
		//�������� ������ ��� ������ �����
		son->Sons = new Tree*[temp->N];
		for (int i(0); i < temp->N; i++)
		{
			son->Sons[i] = nullptr;
		}
		//����������� � ���� ������ ����
		temp->Sons[temp->numSons++] = son;
		return true;
	}
	else //����� ���������� �����
	{
		for (int i = 0; i < temp->numSons; i++)
		{
			if (AddSon(&temp->Sons[i], id, val))
			{
				return true;
			}
		}
		//���� �� �����
		return false;
	}
}

//������� ������
//��������� ��������� �� ������ ������
void Print(Tree *tree)
{
	//���� ������ ����
	if (tree != nullptr)
	{
		//������� ��������� ���������
		Tree *temp = tree;
		//������� ������
		cout << " [Id-" << temp->id << "|lvl-" << temp->lvl << "] Val: " << temp->val << endl;
		for (int i = 0; i < temp->numSons; i++)
		{
			for (int j = -1; j < temp->lvl; j++)
				cout << "      ";
			Print(temp->Sons[i]);
		}
	}
	else    //���� ������ ����
	{
		cout << "Not tree ^-^";
	}
}

//������� ����� ������������� �������� � ������������ ���������
//��������� ��������� �� �������� � ��������
void Get(int *temp, int min, int max)
{
	//���� ��� ������ ������ �������
	if (min > max)
	{
		max += min;
		min = max - min;
		max = max - min;
	}
	//����� �������� ���� �� ����� �����
	do {
		//������ ��������
		cin >> *temp;
		//���� �� �����
		if (!(cin))
		{
			//�������������� ����� � ���������� �����
			cin.clear();
			cin.sync();
			cin.ignore();
			*temp = min - 1;
		}
		system("cls");
		cout << "Error, try again(" << min << "-" << max << "): " << endl;
	} while (*temp < min || *temp > max);
	system("cls");
}

//������� ����
//���������� ����� ������������
int Choose()
{
	//-------����-------//
	int tempForChoose = 'n';
	cout << "1) Add element" << endl;
	cout << "2) Print tree" << endl;
	cout << "3) Searh" << endl;
	cout << "0) Exit" << endl;
	cout << "__________________" << endl;
	cout << "Your choose: ";
	//��������� �����
	Get(&tempForChoose, 0, 3);
	//���������� �����
	return tempForChoose;
	//-------------------//
}

//�������������� ���-�� ������� � ������
//��������� ��������� �� ������ ������
//���������� ����� �������
int Counter(Tree *tree)
{
	int Count = 0;
	Tree *temp = tree;
	if (temp->Sons[0] == nullptr)
	{
		return 1;
	}
	else
	{
		for (int i(0); temp->Sons[i] != nullptr; i++)
		{
			Count += Counter(temp->Sons[i]);
		}
		return Count;
	}
}

//������� ���� ���� ������� ��������� ������ ����
//��������� ��������� �� ������ ������ � ����� �������
int Search(Tree *tree, int N)
{
	//���� ������ ����
	if (tree != nullptr)
	{
		//������� ��������� ���������
		Tree *temp = tree;
		//���� ������� ����
		if (Counter(temp) == N)
		{
			//���� ������� ������ ��� ��� ������� �����
			if (temp->lvl > Task && temp->Sons[0] != nullptr)
			{
				//���������� �������
				Task = temp->lvl;
			}
		}
		//����������� �� ��������� �������� ��� ����� ����
		for (int i = 0; temp->Sons[i] != nullptr; i++)
			Search(temp->Sons[i], N);
	}
	else    //���� ������ ����
	{
		cout << "Not tree ^-^";
	}
	return Task;
}

//������� ������� ������
//��������� ��������� �� ������ ������
void Delete(Tree **tree)
{
	//���� ������ ����
	if (tree != nullptr)
	{
		Tree *temp = *tree;
		for (int i = 0; i < temp->numSons; i++)
		{
			for (int j = -1; j < temp->lvl; j++)
				Delete(&temp->Sons[i]);
		}
		delete[] temp;
	}
	else    //���� ������ ����
	{
		cout << "Not tree ^-^";
	}
}

int main()
{
	//������� ��������� �� ������ ������
	Tree *tree = nullptr;
	//��������� ��������� ��� ������������� ������
	int id, val;
	id = 0;
	val = 0;
	//�������������� ������
	Init(&tree, val, 5);
	//����
	do
	{
		switch (Choose())
		{
		case 1:
		{
			cout << "--------Add Son-------" << endl;
			cout << "Enter id of father(0-" << Sid - 1 << "): ";
			Get(&id, 0, Sid);
			cout << "Enter value(0-10): ";
			Get(&val, 0, 10);
			AddSon(&tree, id, val);
			break;
		}
		case 2:
		{
			cout << "--------Print tree-------" << endl;
			Print(tree);
			break;
		}
		case 3:
		{
			cout << "--------Search-------" << endl;
			Task = 0;
			int N = 0;
			cout << "How many leaf's?: ";
			Get(&N, 0, tree->N);
			cout << "The lowest level with a specified number of sheets: " << Search(tree, N) << endl;
			break;
		}
		case 0:
		{
			Delete(&tree);
			return 0;
		}
		default:
		{
			return -1;
		}
		}
	} while (true);
}

