﻿// LAB 5, var 30

#include <iostream>
#include <functional>
#include <fstream>


int task1(int* arr, int size);
bool task2range(int* arr, int size, int& k);
bool task2value(int* arr, int size, int& k);


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
int check_file(std::ifstream& file); // проверка файла на существование/пустоту



int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int* arr = memory_allocation(10);
	int size = 10;
	fill(arr, size, -200, 200);
	print_array(arr, size);
	
	int k = 0;
	if (task2range(arr, size, k))
	{
		if (task2value(arr, size, k))
			std::cout << "Ответ " << k << '\n';
		else
			std::cout << "Пустой диапазон\n";
	}
	else std::cout << "Отсутствует элемент входа\n";
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

bool task2range(int* arr, int size, int& k)
{
	bool res = false;
	k = 0;
	int c{}, i{};
	validation(c, [](int x) {return x >= 0 && x < 10; }, "Введите C");
	int* ptr = arr;
	while ((ptr != arr + size) && !res)
	{
		if (std::abs(*ptr) % 10 == c)
		{
			k = i;
			res = true;
		}
		i++;
		ptr++;
	}
	return res; // 0 отсутствие чисел, оканчивающихся на С
				// 1 такое число есть
}

bool task2value(int* arr, int size, int& k)
{
	int res{};
	int cnt{};
	for (int* ptr = arr + k + 1; ptr != arr + size; ++ptr)
	{
		if (*ptr > 0)
			cnt++;
	}
	k = cnt;
	if (k != 0)
		res = 1; // Есть ответ
	else res = 0; // Пустой диапазон
	return res;
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