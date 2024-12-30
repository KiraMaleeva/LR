#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
#include "../../Hat.h"

struct Date
{
    int day;
    int month;
    int year;
};

union Position
{
    char title[50];
    char code[10];
};

struct Employee
{
    char name[100];
    int number;
    Position position;
    Date date;
};

void input(Employee *emp, int i)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите Ф.И.О. сотрудника: ";
    std::cin.getline(emp[i].name, 100);
    std::cout << "Введите номер отдела: ";
    emp[i].number = cinll();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите должность: ";
    std::cin.getline(emp[i].position.title, 50);
    std::cout << "Введите дату начала работы (день месяц год): ";
    emp[i].date.day = cinll();
    emp[i].date.month = cinll();
    emp[i].date.year = cinll();
}

void print(const Employee &emp)
{
    std::cout << "Ф.И.О.: " << emp.name << "\n";
    std::cout << "Номер отдела: " << emp.number << "\n";
    std::cout << "Должность: " << emp.position.title << "\n";
    std::cout << "Дата начала работы: " << emp.date.day << "." << emp.date.month << "." << emp.date.year << "\n";
}

void add(Employee *&emp, int &c)
{
    emp = (Employee *)realloc(emp, (c + 1) * sizeof(Employee));
    if (emp == NULL)
    {
        std::cerr << "Не удалось выделить память\n";
        exit(1);
    }
    input(emp, c);
    c++;
}

void del(Employee *&emp, int &c, int ind)
{
    if (ind < 0 || ind >= c)
    {
        std::cout << "Неверный индекс\n";
        return;
    }

    for (int i = ind; i < c - 1; i++)
    {
        emp[i] = emp[i + 1];
    }
    c--;
    emp = (Employee *)realloc(emp, c * sizeof(Employee));
}

void edit(Employee *emp, int c, int ind)
{
    if (ind < 0 || ind >= c)
    {
        std::cout << "Неверный индекс\n";
        return;
    }
    input(emp, ind);
}

void sort(Employee *emp, int c)
{
    auto seniority = [](const Employee &a, const Employee &b)
    {
        if (a.number == b.number)
        {
            if (a.date.year != b.date.year)
                return a.date.year > b.date.year;
            if (a.date.month != b.date.month)
                return a.date.month > b.date.month;
            return a.date.day > b.date.day;
        }
        return a.number < b.number;
    };

    std::sort(emp, emp + c, seniority);
}

void save(const char *filename, Employee *emp, int c)
{
    std::ofstream file(filename);
    if (!file)
    {
        std::cerr << "Не удалось открыть файл для записи\n";
        return;
    }

    for (int i = 0; i < c; ++i)
    {
        file << emp[i].name << "\n";
        file << emp[i].number << "\n";
        file << emp[i].position.title << "\n";
        file << emp[i].date.day << " " << emp[i].date.month << " " << emp[i].date.year << "\n";
    }

    file.close();
}

void printF(const char *filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Не удалось открыть файл для чтения\n";
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << "Ф.И.О.: " << line << "\n";
        std::getline(file, line);
        std::cout << "Номер отдела: " << line << "\n";
        std::getline(file, line);
        std::cout << "Должность: " << line << "\n";
        std::getline(file, line);
        std::cout << "Дата начала работы: " << line << "\n";
        std::cout << "\n";
    }

    file.close();
}

void menu(Employee *emp, int &c)
{
    while (true)
    {
        std::cout << "Выберите действие:\n1 - Добавить сотрудника\n2 - Удалить сотрудника\n3 - Корректировать данные сотрудника\n4 - Показать всех сотрудников\n5 - Сортировать сотрудников по отделам и стажу работы\n6 - Вывести данные из текстового файла\n7 - Выход\n";

        int ch;
        ch = cinll();

        if (ch == 1)
        {
            add(emp, c);
            save("employees.txt", emp, c);
        }
        else if (ch == 2)
        {
            int ind;
            std::cout << "Введите индекс сотрудника для удаления: ";
            ind = cinll();
            del(emp, c, ind - 1);
            save("employees.txt", emp, c);
        }
        else if (ch == 3)
        {
            int ind;
            std::cout << "Введите индекс сотрудника для корректировки: ";
            ind = cinll();
            edit(emp, c, ind - 1);
            save("employees.txt", emp, c);
        }
        else if (ch == 4)
        {
            for (int i = 0; i < c; ++i)
            {
                print(emp[i]);
                std::cout << "\n";
            }
        }
        else if (ch == 5)
        {
            sort(emp, c);
            save("employees.txt", emp, c);
        }
        else if (ch == 6)
        {
            printF("employees.txt");
        }
        else if (ch == 7)
        {
            break;
        }
        else
        {
            std::cout << "Неверный выбор\n";
        }
    }
}

int main()
{
    Employee *emp = (Employee *)malloc(0);
    int c = 0;

    menu(emp, c);

    free(emp);
    return 0;
}