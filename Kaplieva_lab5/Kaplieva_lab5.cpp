// LAB 5, var 30

#include <iostream>
#include <functional>
#include <fstream>


int task1(int* arr, int size);
bool task2range(int* arr, int size, int& k);
bool task2value(int* arr, int size, int& k);
void shift_to_right(int* pos, int* i);
void task3(int* arr, int size);

int task_menu();
int source_menu();
short preamb(short choice, std::ifstream& file, int& size);
void print_array(int* arr, int size);
void ending(int n);

int* memory_allocation(int size); // выделение памяти под динам. массив
void free_memory(int*& arr); // возвращаем запрашиваемую память
void fill(int* arr, int size, std::istream& stream = std::cin); // заполняем массив из файла/клавы (по умолчанию - клава)
void fill(int* arr, int size, int a, int b); // заполняем массив рандомно

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
int check_file(std::ifstream& file); // проверка файла на существование/пустоту



int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	short task = 0, source = 0;
	int size = 0;
	do
	{
		task = task_menu();
		if (task != 4)
		{
			source = source_menu();
			std::ifstream file("data.txt");
			int size = 0;
			short fileTest = preamb(source, file, size); // получаем size и ключ проверки файла
			if (fileTest == 1)
			{
				int* arr = memory_allocation(size);
				switch (source)
				{
				case 1:
				{
					fill(arr, size);
					break;
				}
				case 2:
				{
					fill(arr, size, file);
					break;
				}
				default:
				{
					int a{}, b{};
					validation(a, [](int x) {return true; }, "Нижняя граница");
					validation(b, [a](int x) {return x > a; }, "Нижняя граница");
					fill(arr, size, a, b);
					print_array(arr, size);
				}
				}

				switch (task)
				{
				case 1:
				{
					if (task1(arr, size))
						std::cout << "Ответ: " << task1(arr, size) << '\n';
					else
						std::cout << "Отсутствуют двузначные\n";
					break;
				}
				case 2:
				{
					int k = 0;
					if (task2range(arr, size, k))
					{
						if (task2value(arr, size, k))
							std::cout << "Ответ " << k << '\n';
						else
							std::cout << "Пустой диапазон\n";
					}
					else std::cout << "Отсутствует элемент входа\n";
					break;
				}
				default:
				{
					task3(arr, size);
					print_array(arr, size);
				}
				}
				free_memory(arr);
			}
			else if (fileTest == 0)
				std::cout << "Файл пустой!\n";
			else std::cout << "Файл не найден!\n";
		}
	} while (task != 4);
}


int task1(int* arr, int size)
{
	int max{};
	for (int* ptr = arr; ptr != arr + size; ++ptr)
	{
		if (*ptr >= -99 && *ptr <= 99 && !(*ptr > -10 && *ptr < 10))
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

void shift_to_right(int* pos, int* i)
{
	int tmp = *i;
	for (int* j = i; j >= pos + 1; --j)
		*j = *(j - 1);
	*pos = tmp;
}

void task3(int* arr, int size)
{
	int* pos = arr;
	int a{};
	validation(a, [](int x) {return true; }, "Введите А");
	for (int* i = arr; i != arr + size; ++i)
	{
		if (*i % a == 0)
		{
			if (i != pos)
			{
				shift_to_right(pos, i);
			}
			++pos;
		}
	}
}

int task_menu()
{
	std::cout << "\n-----------------------------------------------------\n";
	std::cout << "1. Найти максимум среди двузначных чисел.\n";
	std::cout << "2. Найти количество положительных элементов массива, расположенных\n   после первого элемента, оканчивающегося на заданную цифру.\n";
	std::cout << "3. Преобразовать массив таким образом, чтобы сначала располагались\n   все элементы кратные заданному числу А, а потом – все остальные.\n";
	std::cout << "4. Выход из программы.\n";
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

short preamb(short choice, std::ifstream& file, int& size)
{
	short res{ 1 };
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
		{
			file >> size;
		}
		else if (check_file(file) == 0)
			res = 0;
		else res = -1;
		break;
	}
	default:
	{
		std::cout << "\nВведите количество случайных слагаемых: ";
		validation(size, [](int x) {return x > 0; }, "");
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	}
	return res;
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
		res = -1; // Файл не найден!
	}
	else
		if (file.peek() == EOF) 
			res = 0; // Файл пустой!
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