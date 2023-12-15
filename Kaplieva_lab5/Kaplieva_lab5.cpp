// LAB 5, var 30

#include <iostream>
#include <functional>
#include <fstream>

int task_menu();
int source_menu();
void preamb(short choice, std::ifstream& file, int& size);
void print_array(double* arr, int size);

double* memory_allocation(int size); // выделение памяти под динам. массив
void free_memory(double*& arr); // возвращаем запрашиваемую память
void fill(double* arr, int size, std::istream& stream = std::cin); // заполняем массив из файла/клавы
void fill(double* arr, int size, double a, double b); // заполняем массив рандомно
void ending(int n); // вывод фразы введите элементов с нужным окончанием

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message); // cin с нужной проверкой
int check_file(std::ifstream& file); // проверка файла на существование/пустоту



int main()
{
	setlocale(LC_ALL, "Russian");
	task_menu();
}



int task_menu()
{
	std::cout << "-----------------------------------------------------\n";
	std::cout << "1. Найти максимум среди двузначных чисел.\n";
	std::cout << "2. Найти количество положительных элементов массива, расположенных\n   после первого элемента, оканчивающегося на заданную цифру.\n";
	std::cout << "3. Преобразовать массив таким образом, чтобы сначала располагались\n   все элементы кратные заданному числу А, а потом – все остальные.\n";
	std::cout << "-----------------------------------------------------\n";
	
	/*std::function<bool(int)> foo;
	foo = [](int x)->bool {return x >= 1 && x <= 4; };
	int choice;
	validation(choice, foo, "");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;*/
	return 0;
}

int source_menu()
{
	return 0;
}

void preamb(short choice, std::ifstream& file, int& size)
{

}

void print_array(double* arr, int size)
{

}

double* memory_allocation(int size)
{
	return nullptr;
}

void free_memory(double*& arr)
{

}

void fill(double* arr, int size, std::istream& stream)
{

}

void fill(double* arr, int size, double a, double b)
{

}

void ending(int n)
{

}

int check_file(std::ifstream& file)
{
	return 0;
}

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message)
{

}
