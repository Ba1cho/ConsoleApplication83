#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <ctime>


using namespace std;

struct PersonalSalary {
	int number;
	string name;
	string surname;
	string patronymic;
	int salary;
	string moon;
};
void input(int& x, string s) {
	cout << s << endl;
	cin >> x;
	cout << endl;
}
void del_array(PersonalSalary* arr, int size) {
	delete[] arr;
	arr = nullptr;
}

void write_file(PersonalSalary* arr, int size) {
	fstream file;
	file.open("file.txt", ios::out | ios::binary);
	for (int i = 0; i < size; i++) {

		file.write((char*)(&arr), sizeof(PersonalSalary));
	}
	file.close();
}

void read_file(PersonalSalary* arr) {
	fstream file;
	file.open("file.txt", ios::in | ios::binary);
	while (!file.eof()) {
		file.read((char*)(&arr), sizeof(PersonalSalary));
	}
	file.close();
}

void vivod(PersonalSalary* arr, int size) {
	for (int i = 0; i < size; i++)
	{
		cout << arr[i].number << "\t";
		cout << arr[i].name;
		cout << arr[i].surname;
		cout << arr[i].patronymic;
		cout << arr[i].salary << "\t";
		cout << arr[i].moon << "\n";
	}

}

void zapolnenie_struct(PersonalSalary* arr, int size) {
	srand(time(NULL));

	string surnames[10] = {
	"Turner     ",
	"Evans      ",
	"Arnold     ",
	"Strickland ",
	"Ellis      ",
	"Rodriguez  ",
	"Johnson    ",
	"Allen      ",
	"Butler     ",
	"Sullivan   "
	};

	string names[10] = {
	"Jeremy      ",
	"Todd        ",
	"Timothy     ",
	"James       ",
	"Charles     ",
	"William     ",
	"Vincent     ",
	"Christopher ",
	"Edward      ",
	"Ralph       "
	};

	string patronymics[10] = {
	"Johnny      ",
	"Richard     ",
	"John        ",
	"Samuel      ",
	"Robert      ",
	"Ronald      ",
	"Alex        ",
	"Christopher ",
	"Frederick   ",
	"James       "
	};
	string moons[12] = {
	"January   ",
	"February  ",
	"March 	   ",
	"April 	   ",
	"May 	   ",
	"June 	   ",
	"July 	   ",
	"August    ",
	"September ",
	"October   ",
	"November  ",
	"December  "
	};
	for (int i = 0; i < size; i++)
	{
		arr[i].number = (i + 1);
		arr[i].surname = surnames[rand() % 10];
		arr[i].name = names[rand() % 10];
		arr[i].patronymic = patronymics[rand() % 10];
		arr[i].salary = rand() % 3000 + 30000;
		arr[i].moon = moons[rand() % 12];

	}
}



void delete_field(PersonalSalary*& arr, int& size) {
	int delete_number;
	bool flag;
	do {
		flag = false;
		input(delete_number, "Какую запись вы хотите удалить: ");
		for (int i = 0; i < size; i++)
		{
			if (arr[i].number == delete_number) {
				flag = true;
			}
		}
	} while (!flag);
	PersonalSalary* arr2 = new PersonalSalary[size - 1];
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i].number != delete_number) {
			arr2[j] = arr[i];
			j++;
		}
	}
	delete[] arr;
	arr = arr2;
	arr2 = nullptr;
	size = size - 1;
	write_file(arr, size);
	read_file(arr);
	vivod(arr, size);

}

void sorting(PersonalSalary* arr, int size) {
	cout << "сортировка по зарплате" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (arr[j].salary > arr[j + 1].salary) {
				int b = arr[j].salary; // создали дополнительную переменную
				arr[j].salary = arr[j + 1].salary; // меняем местами
				arr[j + 1].salary = b; // значения элементов
			}
		}
	}
	write_file(arr, size);
	read_file(arr);
	vivod(arr, size);
}
void search_out(PersonalSalary* arr, int i) {
	cout << arr[i].number << "\t";
	cout << arr[i].name;
	cout << arr[i].surname;
	cout << arr[i].patronymic;
	cout << arr[i].salary << "\t";
	cout << arr[i].moon << "\n";
}
void search(PersonalSalary* arr, int size) {
	int sortnumber = -1;
	string subject_of_search = "";

	char word;
	cout << "Введите символ: ";
	cin >> word;
	subject_of_search = word;
	bool flag = false;
	for (int i = 0; i < size; i++) {
		if (arr[i].surname[0] == word) {
			search_out(arr, i);
			flag = true;
		}

	}
	if (!flag)
		cout << "Таких Пользователей нет" << endl;
}
void interface(PersonalSalary* arr, int size) {
	int a;
	input(a, "выберите действие \n1 - удалить запись \n2 - найти определенную запись \n3 - сортировать по одному из полей \n4 - Любой другой символ завершит программу");
	switch (a)
	{
	case 1:
		delete_field(arr, size);
		interface(arr, size);
		break;
	case 2:
		search(arr, size);
		interface(arr, size);
		break;
	case 3:
		sorting(arr, size);
		interface(arr, size);
		break;
	default:
		break;
	}
}
void logic_programm() {
	setlocale(LC_ALL, "rus");
	int size;
	input(size, "Введите количество Записей: ");
	PersonalSalary* arr = new PersonalSalary[size];
	zapolnenie_struct(arr, size);
	write_file(arr, size);
	read_file(arr);
	vivod(arr, size);
	interface(arr, size);
	del_array(arr, size);
}

int main() {
	logic_programm();
	return 0;
}

