#ifndef SPORTSMAN_H
#define SPORTSMAN_H

typedef struct sportsman
{
    char country[50];
    char team[50];
    char name[50];
    int number;
    int age;
    union {
        int height;
        int weight;
    } measurements;
} Sportsman;

void input(Sportsman *sp, int i);
void qt(Sportsman *sp);
void sign(Sportsman *sp);
void dia(Sportsman *sp);
void print(Sportsman *sp);
void dop(Sportsman *sp);
void poisk(Sportsman *sp);
void del(Sportsman *&sp);
void update(Sportsman *&sp, int c);
void sort(Sportsman *sp, int n);
void write_to_file(const char *filename, Sportsman *sp, int count);
void read_from_file(const char *filename, Sportsman *&sp, int &count);
void update_record(const char *filename, int record_number, Sportsman updated_record);
void print_file_content(const char *filename);
void menu();

#endif // SPORTSMAN_H
