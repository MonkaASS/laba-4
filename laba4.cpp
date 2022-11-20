/*
Описать функции toUpperCase и toLowerCase (или функцию) соответственно преобразовывающие входную строку в верхний или нижний регистр.

Тема: Работа с памятью. Динамическая память и косвенная адресация

Вопросы:
1. Архитектура Фон-Неймана. Принципы архитектуры Фон-Неймана
2. Линейная память
3. Указатель
4. Ссылка
5. Косвенная адресация
6. Арифметика указателей
7. Указатели и ссылки в C++, операции разыменования и взятия адреса
8. Представление массивов в памяти
9. N-мерные массивы, тензоры
10.	Стековая память
11.	Статическая память
12.	Динамическая память, куча
13.	Средства работы с памятью в языке C++
14.	Способы передачи аргументов в функцию
15.	Утечка памяти
16.	Виртуальная память
17.	Процесс и программа в ОС
*/

#include <iostream>

using namespace std;

// Перевод всей строки в верхний регистр
void toUpperCase(char* line, unsigned int size) {
	for (int i = 0; i < size; i++) {
		char current_character = int(line[i]);
		// для латиницы
		if (current_character >= 97 && current_character <= 122 ) {
			line[i] = char(current_character - 32);
		}

		// Для кириллицы. Работает, если удаётся подключить win 1251
		else if (256 + current_character >= 224 && 256 + current_character <= 255) {
			line[i] = char(256 + current_character - 32);
		}

		// Буква ё отдельный кейс. Работает, если удаётся подключить win 1251
		else if (256 + current_character == 184) {
			line[i] = char(256 + current_character - 16);
		}
	}
}

// Перевод строки в верхний регистр от иднекса start до индекса finish не включая finish
void toUpperCase(char* line, unsigned int start, unsigned int finish) {
	for (int i = start - 1; i < finish - 1; i++) {
		char current_character = int(line[i]);
		if (current_character >= 97 && current_character <= 122) {
			line[i] = char(current_character - 32);
		}

		else if (256 + current_character >= 224 && 256 + current_character <= 255) {
			line[i] = char(256 + current_character - 32);
		}

		else if (256 + current_character == 184) {
			line[i] = char(256 + current_character - 16);
		}
	}
}

// Перевод всей строки в нижний регистр
void toLowerCase(char* line, unsigned int size) {
	for (int i = 0; i < size; i++) {
		char current_character = int(line[i]);
		if (current_character >= 65 && current_character <= 90) {
			line[i] = char(current_character + 32);
		}

		else if (256 + current_character >= 192 && 256 + current_character <= 223) {
			line[i] = char(256 + current_character + 32);
		}

		else if (256 + current_character == 168) {
			line[i] = char(256 + current_character + 16);
		}
	}
}

// Перевод строки в нижний регистр от иднекса start до индекса finish не включая finish
void toLowerCase(char* line, unsigned int start, unsigned int finish) {
	for (int i = start - 1; i < finish - 1; i++) {
		char current_character = int(line[i]);
		if (current_character >= 65 && current_character <= 90) {
			line[i] = char(current_character + 32);
		}

		else if (256 + current_character >= 192 && 256 + current_character <= 223) {
			line[i] = char(256 + current_character + 32);
		}

		else if (256 + current_character == 168) {
			line[i] = char(256 + current_character + 16);
		}
	}
}

int main()
{
	// Ставим кодировку win 1251 для русских символов и консольно для русских букв
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	char* line = new char[12];
	unsigned int length = 0;
	
	cout << "Enter your line" << endl;
	// цикл считывает строку пока не встретит перенос строки
	for (int i = 0; ; i++) {
		// считываем символ из консоли
		char ch = getchar();
		// если встречает перенос строки, цикл заканчивается
		if (ch == '\n') break;

		// довыделяем память если её не хватает
		if (i % 10 == 0 && i != 0) {
			// временный массив чтобы сохранить строку
			char* tmp = new char[i];
			for (int j = 0; j < i; j++) {
				tmp[j] = line[j];
			}
			// довыделяем память в основной массив и снова его заполняем
			delete[] line;
			line = new char[i + 12];
			for (int j = 0; j < i; j++) {
				line[j] = tmp[j];
			}
			// очищаем память выделнную под средний массив
			delete[] tmp;
		}

		// добавляем элемент к строке и считаем длину
		line[i] = ch;
		length++;
	}

	// WhatWouldYouPrefer переменная, через которую пользователь выбирает тип преобразования (верхний или нижний регистр)
	char wwyp;
	cout << "Would you like to convert line to uppercase or to lowercase? (u/l)" << endl;
	do {
		cin >> wwyp;
	} while (wwyp != 'l' && wwyp != 'u');
	char answer;
	cout << "Would you like to convert the whole line? (y/n)" << endl;
	do {
		cin >> answer;
	} while (answer != 'y' && answer != 'n');


	// функция преобразует строку
	if (wwyp == 'u') {
		if (answer == 'y') {
			toUpperCase(line, length);
		}
		if (answer == 'n') {
			unsigned int start, finish;
			cout << "Enter first and last index of line you want to convert. (Indexes should not be greater than the line's length + 1)" << endl;
			cin >> start >> finish;
			if (start > length) {
				start = length;
			}
			if (finish > length) {
				finish = length + 1;
			}
			toUpperCase(line, start, finish);
		}
	}
	else {
		if (answer == 'y') {
			toLowerCase(line, length);
		}
		if (answer == 'n') {
			unsigned int start, finish;
			cout << "Enter first and last index of line you want to convert. (Indexes should not be greater than the line's length + 1)" << endl;
			cin >> start >> finish;
			if (start > length) {
				start = length;
			}
			if (finish > length) {
				finish = length + 1;
			}
			toLowerCase(line, start, finish);
		}
	}

	// выводим строку
	for (int i = 0; i < length; i++) {
		cout << line[i];
	}

	// очищаем память
	delete[] line;

	return 0;
}
