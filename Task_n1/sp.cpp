#include "sp.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <fstream>
#include "../../Hat.h"
#include <cmath>

int c = 0;

void wr_file(const char *filename, Sportsman *sp, int count)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char *>(sp), count * sizeof(Sportsman));
    file.close();
}

void input(Sportsman *sp, int i)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n"
              << i + 1 << " участник.\n"
              << "Введите название страны: ";
    std::cin.getline(sp[i].country, 50);
    std::cout << "Введите название команды: ";
    std::cin.getline(sp[i].team, 50);
    std::cout << "Введите ФИО: ";
    std::cin.getline(sp[i].name, 50);
    std::cout << "Введите игровой номер: ";
    sp[i].number = cinll();
    std::cout << "Введите возраст: ";
    sp[i].age = cinll();

    std::cout << "\nВведите рост или вес (введите 1 для роста, 2 для веса): ";
    int choice;
    choice = cinll();
    if (choice == 1)
    {
        std::cout << "Введите рост: ";
        sp[i].measurements.height = cinll();
    }
    else if (choice == 2)
    {
        std::cout << "Введите вес: ";
        sp[i].measurements.weight = cinll();
    }
    else
    {
        std::cerr << "Неверный ввод. Попробуйте снова.\n";
        input(sp, i);
    }
}

void qt(Sportsman *sp)
{
    std::cout << "Введите количество спортсменов: ";
    int n;
    n = cinll();
    c = n;

    for (int i = 0; i < c; i++)
    {
        input(sp, i);
    }
    wr_file("sportsmen.dat", sp, c);
}

void sign(Sportsman *sp)
{
    std::cout << "Введите название страны, название команды, ФИО, игровой номер, возраст, рост, вес (через enter): ";

    std::string country, team, name;
    int number, age, height, weight;

    std::cin >> country >> team >> name;
    number = cinll();
    age = cinll();
    height = cinll();
    weight = cinll();

    for (int i = 0;; i++)
    {
        c++;
        input(sp, i);
        if (sp[i].country == country && sp[i].team == team && sp[i].name == name && sp[i].number == number && sp[i].age == age &&
            (sp[i].measurements.height == height || sp[i].measurements.weight == weight))
        {
            break;
        }
    }
    wr_file("sportsmen.dat", sp, c);
}

void dia(Sportsman *sp)
{
    for (int i = 0;; i++)
    {
        int x;
        c++;
        std::cout << "Введите 1, если хотите продолжить ввод, 2, если завершить:  ";
        x = cinll();
        if (x == 1)
        {
            input(sp, i);
        }
        else if (x == 2)
        {
            break;
        }
        else
        {
            std::cout << "Неверный ввод\n";
        }
    }
    wr_file("sportsmen.dat", sp, c);
}

void print(Sportsman *sp)
{
    for (int i = 0; i < c; ++i)
    {
        std::cout << "\nСпортсмен " << i + 1 << ":\n";
        std::cout << "Страна: " << sp[i].country << "\n";
        std::cout << "Команда: " << sp[i].team << "\n";
        std::cout << "ФИО: " << sp[i].name << "\n";
        std::cout << "Игровой номер: " << sp[i].number << "\n";
        std::cout << "Возраст: " << sp[i].age << "\n";
        if (sp[i].measurements.height != 0)
        {
            std::cout << "Рост: " << sp[i].measurements.height << "\n";
        }
        else
        {
            std::cout << "Вес: " << sp[i].measurements.weight << "\n";
        }
    }
}

void dop(Sportsman *sp)
{
    int add;
    std::cout << "Введите количество спортсменов для добавления: ";
    add = cinll();
    sp = (Sportsman *)realloc(sp, (c + add) * sizeof(Sportsman));
    if (sp == NULL)
    {
        std::cerr << "Memory allocation failed\n";
        exit(1);
    }
    for (int i = c; i < c + add; ++i)
    {
        input(sp, i);
    }
    c += add;
    wr_file("sportsmen.dat", sp, c);
}

void poisk(Sportsman *sp)
{
    std::cout << "Спортсмены, которым больше 20 лет: ";
    bool found = false;
    for (int i = 0; i < c; ++i)
    {
        if (sp[i].age > 20)
        {
            std::cout << "\nНайден спортсмен:\n";
            std::cout << "Страна: " << sp[i].country << "\n";
            std::cout << "Команда: " << sp[i].team << "\n";
            std::cout << "ФИО: " << sp[i].name << "\n";
            std::cout << "Игровой номер: " << sp[i].number << "\n";
            std::cout << "Возраст: " << sp[i].age << "\n";
            if (sp[i].measurements.height != 0)
            {
                std::cout << "Рост: " << sp[i].measurements.height << "\n";
            }
            else
            {
                std::cout << "Вес: " << sp[i].measurements.weight << "\n";
            }
            found = true;
        }
    }
    if (!found)
    {
        std::cout << "Спортсмены с такой страной не найдены.\n";
    }
}

void del(Sportsman *&sp)
{
    int dell;
    std::cout << "Введите возраст спортсмена для удаления: ";
    dell = cinll();
    bool found = false;
    for (int i = 0; i < c; ++i)
    {
        if (sp[i].age == dell)
        {
            for (int j = i; j < c - 1; ++j)
            {
                sp[j] = sp[j + 1];
            }
            c--;
            sp = (Sportsman *)realloc(sp, c * sizeof(Sportsman));
            std::cout << "Спортсмен удален.\n";
            found = true;
            break;
        }
    }
    if (!found)
    {
        std::cout << "Спортсмен с таким возрастом не найден.\n";
    }
    wr_file("sportsmen.dat", sp, c);
}

void update(Sportsman *&sp, int c)
{
    int ageUp;
    std::cout << "Введите возраст спортсмена для изменения: ";
    ageUp = cinll();
    bool found = false;

    for (int i = 0; i < c; ++i)
    {
        if (sp[i].age == ageUp)
        {
            std::cout << "Введите новые данные для спортсмена:\n";
            std::cout << "Название страны: ";
            std::cin >> sp[i].country;
            std::cout << "Название команды: ";
            std::cin >> sp[i].team;
            std::cout << "ФИО игрока: ";
            std::cin >> sp[i].name;
            std::cout << "Игровой номер: ";
            sp[i].number  = cinll();
            std::cout << "Возраст: ";
            sp[i].age = cinll();

            std::cout << "Введите рост или вес (введите 1 для роста, 2 для веса): ";
            int choice;
            choice = cinll();
            if (choice == 1)
            {
                std::cout << "\nВведите рост: ";
                std::cin >> sp[i].measurements.height;
            }
            else if (choice == 2)
            {
                std::cout << "\nВведите вес: ";
                std::cin >> sp[i].measurements.weight;
            }
            else
            {
                std::cerr << "Неверный ввод. Попробуйте снова.\n";
                continue;
            }

            std::cout << "Данные спортсмена изменены.\n";
            found = true;
            break;
        }
    }

    if (!found)
    {
        std::cout << "Спортсмен с таким возрастом не найден.\n";
    }
    wr_file("sportsmen.dat", sp, c);
}

void sort(Sportsman *sp, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            Sportsman temp = sp[i];
            int j;
            for (j = i; j >= gap && sp[j - gap].age < temp.age; j -= gap)
            {
                sp[j] = sp[j - gap];
            }
            sp[j] = temp;
        }
    }
    std::cout << "Массив структур упорядочен по возрасту (по убыванию).\n";
    wr_file("sportsmen.dat", sp, c);
}

void up_f(const char *filename, int n, Sportsman up_rec)
{
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return;
    }

    file.seekp((n + 1) * sizeof(Sportsman), std::ios::beg);
    file.write(reinterpret_cast<const char *>(&up_rec), sizeof(Sportsman));
    file.close();
}

void print_file(const char *filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
        return;
    }

    file.seekg(0, std::ios::end);
    int count = file.tellg() / sizeof(Sportsman);
    file.seekg(0, std::ios::beg);

    Sportsman *sp = (Sportsman *)malloc(count * sizeof(Sportsman));
    if (sp == NULL)
    {
        std::cerr << "Memory allocation failed\n";
        exit(1);
    }

    file.read(reinterpret_cast<char *>(sp), count * sizeof(Sportsman));
    file.close();

    for (int i = 0; i < count; ++i)
    {
        std::cout << "Спортсмен " << i + 1 << ":\n\n";
        std::cout << "Страна: " << sp[i].country << "\n";
        std::cout << "Команда: " << sp[i].team << "\n";
        std::cout << "ФИО: " << sp[i].name << "\n";
        std::cout << "Игровой номер: " << sp[i].number << "\n";
        std::cout << "Возраст: " << sp[i].age << "\n";
        if (sp[i].measurements.height != 0)
        {
            std::cout << "Рост: " << sp[i].measurements.height << "\n\n";
        }
        else
        {
            std::cout << "Вес: " << sp[i].measurements.weight << "\n\n";
        }
    }

    free(sp);
}

void menu()
{
    Sportsman *sp = (Sportsman *)malloc(100 * sizeof(Sportsman));
    if (sp == NULL)
    {
        std::cout << "Memory allocation failed\n";
        exit(1);
    }

    std::cout << "Выберите тип ввода:\n1-ввод заранее заданного количества структур;\n2-ввод до появления структуры с заданным признаком;\n3-диалог с пользователем о необходимости продолжать ввод.\n";
    int n;
    n = cinll();

    if (n == 1)
    {
        qt(sp);
    }
    else if (n == 2)
    {
        sign(sp);
    }
    else if (n == 3)
    {
        dia(sp);
    }
    else
    {
        std::cout << "Неверный ввод\n";
        free(sp);
        return;
    }

    while (true)
    {
        std::cout << "\nВыберите функцию:\n1 - просмотр содержимого динамического массива структур\n2 - дополнение уже существующего массива структур новыми структурами\n3 - поиск и вывод на экран структур с заданным значением элемента\n4 - удаление элемента массива структур с заданным значением элемента\n5 - изменение элемента массива структур с заданным значением элемента\n6 - упорядочение массива структур по одному из полей\n7 - обновление записи в файле\n8 - вывод содержимого файла\n9 - выход\n";
        int ft;
        ft = cinll();
        if (ft == 1)
        {
            print(sp);
        }
        else if (ft == 2)
        {
            dop(sp);
        }
        else if (ft == 3)
        {
            poisk(sp);
        }
        else if (ft == 4)
        {
            del(sp);
        }
        else if (ft == 5)
        {
            update(sp, c);
        }
        else if (ft == 6)
        {
            sort(sp, c);
        }
        else if (ft == 7)
        {
            int n;
            std::cout << "Введите номер записи для обновления: ";
            n = cinll();
            n = fabs(n);

            Sportsman up_rec;
            input(&up_rec, n);

            up_f("sportsmen.dat", n, up_rec);
        }
        else if (ft == 8)
        {
            print_file("sportsmen.dat");
        }
        else if (ft == 9)
        {
            break;
        }
        else
        {
            std::cout << "Неверный ввод\n";
        }
    }
    free(sp);
}