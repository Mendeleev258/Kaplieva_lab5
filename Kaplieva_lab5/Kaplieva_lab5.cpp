﻿// LAB 5, var 30

#include <iostream>
#include <functional>
#include <fstream>


int task1(int* arr, int size);

int task_menu();
int source_menu();
void preamb(short choice, std::ifstream& file, int& size);
void print_array(int* arr, int size);

int* memory_allocation(int size); // выделение памяти под динам. массив
void free_memory(int*& arr); // возвращаем запрашиваемую память
void fill(int* arr, int size, std::istream& stream); // заполняем массив из файла/клавы
void fill(int* arr, int size, int a, int b); // заполняем массив рандомно
void ending(int n); // вывод фразы введите элементов с нужным окончанием

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message); // cin с нужной проверкой
//template<typename T, typename Predicat>
//void validation(T& x, T& y, Predicat condition, const char* message);
int check_file(std::ifstream& file); // проверка файла на существование/пустоту



int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int* arr = memory_allocation(10);
	fill(arr, 10, -200, 200);
	print_array(arr, 10);
	std::cout << task1(arr, 10);
}


int task1(int* arr, int size)
{
	int max{};
	for (int* ptr = arr; ptr != arr + size; ++ptr)
	{
		if (*ptr >= -99 && *ptr <= 99)
		{
			if (*ptr > max)
				max = *ptr;
		}
	}
	return max; // 0 обработать как отсутствие двузначных
}

int task_menu()
{
	std::cout << "-----------------------------------------------------\n";
	std::cout << "1. Найти максимум среди двузначных чисел.\n";
	std::cout << "2. Найти количество положительных элементов массива, расположенных\n   после первого элемента, оканчивающегося на заданную цифру.\n";
	std::cout << "3. Преобразовать массив таким образом, чтобы сначала располагались\n   все элементы кратные заданному числу А, а потом – все остальные.\n";
	std::cout << "Выход из программы.\n";
	std::cout << "-----------------------------------------------------\n";
	
	std::function<bool(int)> foo;
	foo = [](int x)->bool {return x >= 1 && x <= 4; };
	int choice;
	validation(choice, foo, "");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

int source_menu()
{
	std::cout << "-------------------------\n";
	std::cout << "1. Ввод с клавиатуры\n";
	std::cout << "2. Ввод из файла\n";
	std::cout << "3. Случайным образом\n";
	std::cout << "------------------------\n";

	std::function<bool(int)> foo;
	foo = [](int x)->bool {return x >= 1 && x <= 3; };
	int choice;
	validation(choice, foo, "Выберите способ ввода");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

void preamb(short choice, std::ifstream& file, int& size)
{
	switch (choice)
	{
	case 1:
	{
		std::cout << " \nВведите количество элементов: ";
		validation(size, [](int x) {return x > 0; }, "");
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		break;
	}
	case 2:
	{
		if (check_file(file) == 1)
			file >> size;
		break;
	}
	default:
	{
		std::cout << "\nВведите количество случайных слагаемых: ";
		validation(size, [](int x) {return x > 0; }, "\n-> ");
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	}
}

void print_array(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
		std::cout << arr[i] << ' ';
	std::cout << '\n';
}

int* memory_allocation(int size)
{
	return new int[size];
}

void free_memory(int*& arr)
{
	delete[]arr;
	arr = nullptr;
}

void fill(int* arr, int size, std::istream& stream)
{
	if (&stream == &std::cin)
	{
		std::cout << "Введите ";
		ending(size);
	}
	for (int i = 0; i < size; ++i)
		stream >> arr[i];
}

void fill(int* arr, int size, int a, int b)
{
	for (int i = 0; i < size; ++i)
		arr[i] = rand() % (b - a) + a;
}

void ending(int n)
{
	std::cout << n << " элемент";
	if (n % 100 >= 11 && n % 100 <= 14)
		std::cout << "ов\n";
	else
	{
		switch (n % 10)
		{
		case 1:
			std::cout << "\n";
			break;
		case 2:
		case 3:
		case 4:
			std::cout << "а\n";
			break;
		default:
			std::cout << "ов\n";
		}
	}
}

int check_file(std::ifstream& file)
{
	int res = 1;
	if (!file)
	{
		res = -1;
	}
	else
		if (file.peek() == EOF)
			res = 0;
	return res;
}

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message)
{
	std::cout << message << "\n>>> ";
	while (!(std::cin >> x && condition(x)))
	{
		std::cout << "Ошибка ввода!" << '\n';
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message << "\n>>> ";
	}
}

//template<typename T, typename Predicat>
//void validation(T& x, T& y, Predicat condition, const char* message)
//{
//	std::cout << message << '\n';
//	std::cout << ">>> ";
//	std::cin >> x;
//	std::cout << ">>> ";
//	std::cin >> y;
//	while (!(condition(x, y)))
//	{
//		std::cout << "Ошибка ввода!\n";
//		std::cout << message << '\n';
//		std::cout << ">>> ";
//		std::cin >> x;
//		std::cout << ">>> ";
//		std::cin >> y;
//		std::cout << '\n';
//		std::cin.clear();
//		std::cin.ignore(std::cin.rdbuf()->in_avail());
//	}
//}