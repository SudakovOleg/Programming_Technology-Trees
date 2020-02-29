#include <iostream>

using namespace std;

//Глобальная переменная для присвоения id к сыну дерева
static int Sid = 0;
//Глобальная переменая для хранения самого нижнего уровня
static int Task = 0;

//Структура дерева
struct Tree
{
	//Данные
	int val, id, lvl, numSons, N;
	//Массив сылок на сыновей
	Tree **Sons;
};

//Функция Инициализация корня
//Принимает Указатель на начало дерева его значение икол-во сыновей
void Init(Tree **tree, int val, int N)
{
	//Создаем ячейку
	Tree *son = new Tree;
	//Присваиваем id попутно увеличивая его
	son->id = Sid++;
	//Прописываем уровень
	son->lvl = 0;
	//Задаем значение
	son->val = val;
	//Вводим число нынешних сыновей
	son->numSons = 0;
	//Вводим макс кол-во сыновей
	son->N = N;
	//Выделяем память под массив сылок
	son->Sons = new Tree*[N];
	for (int i(0); i < N; i++)
	{
		son->Sons[i] = NULL;
	}
	//Устанавливаем указатель на корень
	*tree = son;
}

//Функция добавления сына
//Принимает указатель на корень дерева, id элемента и его значение
//Возвращает булево значение
bool AddSon(Tree **tree, int id, int val)
{
	//Создаем временный указатель
	Tree *temp = *tree;
	//Если нужный нам id и еще можно добавить сыновей
	if (id == temp->id && temp->numSons < temp->N)
	{
		//Создаем ячейку
		Tree *son = new Tree;
		//Присваиваем id попутно увеличивая его
		son->id = Sid++;
		//Прописываем уровень
		son->lvl = temp->lvl + 1;
		//Задаем значение
		son->val = val;
		//Вводим макс кол-во сыновей
		son->N = temp->N;
		//Вводим число нынешних сыновей
		son->numSons = 0;
		//Выделяем память под массив сылок
		son->Sons = new Tree*[temp->N];
		for (int i(0); i < temp->N; i++)
		{
			son->Sons[i] = nullptr;
		}
		//Привязываем к отцу нового сына
		temp->Sons[temp->numSons++] = son;
		return true;
	}
	else //Иначе продолжаем поиск
	{
		for (int i = 0; i < temp->numSons; i++)
		{
			if (AddSon(&temp->Sons[i], id, val))
			{
				return true;
			}
		}
		//Если не нашли
		return false;
	}
}

//Функция печати
//Принимает указатель на корень дерева
void Print(Tree *tree)
{
	//Если дерево есть
	if (tree != nullptr)
	{
		//Создаем временный указатель
		Tree *temp = tree;
		//Выводим дерево
		cout << " [Id-" << temp->id << "|lvl-" << temp->lvl << "] Val: " << temp->val << endl;
		for (int i = 0; i < temp->numSons; i++)
		{
			for (int j = -1; j < temp->lvl; j++)
				cout << "      ";
			Print(temp->Sons[i]);
		}
	}
	else    //Если дерева нету
	{
		cout << "Not tree ^-^";
	}
}

//Функция ввода целочисленого значения в определенном интервале
//Принимает указатель на значение и интервал
void Get(int *temp, int min, int max)
{
	//Если мин больше меняем местами
	if (min > max)
	{
		max += min;
		min = max - min;
		max = max - min;
	}
	//Вводи значение пока не будет верно
	do {
		//Вводим значение
		cin >> *temp;
		//Если не верно
		if (!(cin))
		{
			//Подготавливаем поток к повторному вводу
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

//Функция меню
//Возвращает ответ пользователя
int Choose()
{
	//-------Меню-------//
	int tempForChoose = 'n';
	cout << "1) Add element" << endl;
	cout << "2) Print tree" << endl;
	cout << "3) Searh" << endl;
	cout << "0) Exit" << endl;
	cout << "__________________" << endl;
	cout << "Your choose: ";
	//Принимаем выбор
	Get(&tempForChoose, 0, 3);
	//Возвращаем выбор
	return tempForChoose;
	//-------------------//
}

//Функциясчитает кол-во листьев в дереве
//Принимает указатель на корень дерева
//Возвращает число листьев
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

//Функция ищет сына который находится глубже всех
//Принимает указатель на корень дерева и число листьев
int Search(Tree *tree, int N)
{
	//Если дерево есть
	if (tree != nullptr)
	{
		//Создаем временный указатель
		Tree *temp = tree;
		//Если сыновей нету
		if (Counter(temp) == N)
		{
			//Если уровень глубже чем был записан ранее
			if (temp->lvl > Task && temp->Sons[0] != nullptr)
			{
				//Записываем уровень
				Task = temp->lvl;
			}
		}
		//Пробегаемся по остальным сыновьям ища место ниже
		for (int i = 0; temp->Sons[i] != nullptr; i++)
			Search(temp->Sons[i], N);
	}
	else    //Если дерева нету
	{
		cout << "Not tree ^-^";
	}
	return Task;
}

//Функция очищает память
//Принимает указатель на корень дерева
void Delete(Tree **tree)
{
	//Если дерево есть
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
	else    //Если дерева нету
	{
		cout << "Not tree ^-^";
	}
}

int main()
{
	//Создаем указатель на корень дерева
	Tree *tree = nullptr;
	//Временные параметры для инициализации дерева
	int id, val;
	id = 0;
	val = 0;
	//Инициализируем дерево
	Init(&tree, val, 5);
	//Меню
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

