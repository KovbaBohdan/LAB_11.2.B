#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

enum Spec { КН, ІНФ, МТЕ, ФТІ, ТН };
string specStr[] = { "КН", "ІНФ", "МТЕ", "ФТІ", "ТН" };

struct Student
{
    char Surname[99];
    unsigned course;
    Spec spec;
    unsigned physics;
    unsigned mathematics;
    union
    {
        unsigned prog;
        unsigned chuslo;
        unsigned ped;
    };
};

void EnterSave(char* fname);
void LoadPrint(char* fname);
void CountMarks(char* fname, int& countPhysics, int& countMath, int& countProg, int& countChuslo, int& countPed);
void MinAverage(char* fname, int& Procent);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char fname[61];
    char ch;
    int r = 0;
    
    int countPhysics = 0;
    int countMath = 0;
    int countProg = 0;
    int countChuslo = 0;
    int countPed = 0;

    do
    {
        cout << "1. Заповнити дані\n"
            << "2. Вивести на екран дані\n"
            << "3. Кількість студентів з оцінками 5 з фізики та математики\n"
            << "4. Кількість оцінок відмінно з кожного предмету:\n"
            << "0. Завершити роботу програми\n\n";
        cout << "Виберіть дію:\n"; cin >> ch; cout << "\n";
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "Введіть ім'я файлу: "; cin.getline(fname, 100);
            EnterSave(fname);
            cout << "\n\n";
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу для зчитування даних: "; cin.getline(fname, 100);
            LoadPrint(fname);
            cout << "\n\n";
            break;
        case '3':
            MinAverage(fname, r);
            cout << "5 з фізики та математики: " << r << "\n";
            cout << "\n\n";
            break;
        case '4':
            CountMarks(fname, countPhysics, countMath, countProg, countChuslo, countPed);
            cout << "Кількість оцінок 5 з фізики: " << countPhysics << "\n";
            cout << "Кількість оцінок 5 з математики: " << countMath << "\n";
            cout << "Кількість оцінок 5 з програмування: " << countProg << "\n";
            cout << "Кількість оцінок 5 з чисельних методів: " << countChuslo << "\n";
            cout << "Кількість оцінок 5 з педагогіки: " << countPed << "\n";
            cout << "\n\n";
            break;
        default:
            cout << "Нерозпізнана команда!\n\n";
        }
    } while (ch != '0');

    system("pause");
    return 0;
}

void EnterSave(char* fname)
{
    ofstream f(fname, ios::binary);
    if (!f)
    {
        cout << "Не вдалося відкрити файл \'" << fname << "\'\n";
        return;
    }

    Student student;

    int spec;
    char ch;
    int i = 0;
    do
    {
        cout << "Студент №" << i + 1 << ":\n";
        i++;
        cin.sync();
        cout << "Прізвище: "; cin >> student.Surname;
        cout << "Курс: "; cin >> student.course;
        cout << "Спеціальність (КомпНауки - 0, Інформатика - 1, Математика та економіка - 2, Фізика та інформатика - 3, Трудове навчання - 4): ";
        cin >> spec;
        student.spec = (Spec)spec;
        cout << "Оцінка з фізики: "; cin >> student.physics;
        cout << "Оцінка з математики: "; cin >> student.mathematics;
        switch (student.spec)
        {
        case КН:
            cout << " оцінка з програмування: "; cin >> student.prog;
            break;
        case ІНФ:
            cout << " оцінка з чисельних методів: "; cin >> student.chuslo;
            break;
        case МТЕ:
        case ФТІ:
        case ТН:
            cout << " оцінка з педагогіки: "; cin >> student.ped;
            break;
        }
        cout << "\n";

        if (!f.write((char*)&student, sizeof(Student)))
        {
            cerr << "Помилка відкриття файлу" << endl;
        }
        cout << "Введіть \'y\', щоб продовжити введення:\n\n "; cin >> ch;
    } while (ch == 'Y' || ch == 'y');
}

void LoadPrint(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "Не вдалося відкрити файл \'" << fname << "'" << endl;
        return;
    }

    Student student;
    int i = 0;

    cout << "==============================================================================================================="
        << endl;
    cout << "|  № |   прізвище   |  курс |  спец. |  фіз. |  мат. |  прог. | числ. |  педг. |"
        << endl;
    cout << "---------------------------------------------------------------------------------------------------------------"
        << endl;


    while (f.read((char*)&student, sizeof(Student)))
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(13) << right << student.Surname
            << "| " << setw(4) << right << student.course << " "
            << "| " << setw(6) << right << specStr[student.spec] << " " << setw(6)
            << "| " << setw(4) << right << student.physics << " "
            << "| " << setw(4) << right << student.mathematics << " ";
            switch (student.spec)
            {
            case КН:
                cout << "| " << setw(6) << right << student.prog << " " << "| " << setw(8) << "| " << setw(8);
                break;
            case ІНФ:
                cout << "| " << setw(9) << "| " << setw(5) << right << student.chuslo << " " << "| " << setw(8);
                break;
            case МТЕ:
            case ФТІ:
            case ТН:
                cout << "| " << setw(9) << "| " << setw(8) << "| " << setw(6) << right << student.ped << " ";
                break;
            }
        cout << "|"
            << endl;


        cout << "+-----------------------------------------------------------------------------------------------------------+"
            << "\n";
        ++i;
    }
}

void CountMarks(char* fname, int& countPhysics, int& countMath, int& countProg, int& countChuslo, int& countPed)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cout << "Не вдалося відкрити файл \'" << fname << "\'\n";
        return;
    }

    Student student;

    while (f.read((char*)&student, sizeof(Student)))
    {
        if (student.physics == 5)
            countPhysics++;
        if (student.mathematics == 5)
            countMath++;
        switch (student.spec) {
        case КН:
            if (student.prog == 5)
                countProg++;
            break;
        case ІНФ:
            if (student.chuslo == 5)
                countChuslo++;
            break;
        case МТЕ:
        case ФТІ:
        case ТН:
            if (student.ped == 5)
                countPed++;
            break;
        }
    }
}

void MinAverage(char* fname, int& r)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cout << "Не вдалося відкрити файл \'" << fname << "\'\n";
        return;
    }

    Student student;
    int NumberOfStudents = 0;
    int kilkist = 0;
    while (f.read((char*)&student, sizeof(Student)))
    {
        if ((student.physics == 5 && student.mathematics == 5))
            r++;
    }
}
