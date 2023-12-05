#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

enum Spec { ��, ���, ���, �Ҳ, �� };
string specStr[] = { "��", "���", "���", "�Ҳ", "��" };

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
        cout << "1. ��������� ���\n"
            << "2. ������� �� ����� ���\n"
            << "3. ʳ������ �������� � �������� 5 � ������ �� ����������\n"
            << "4. ʳ������ ������ ������ � ������� ��������:\n"
            << "0. ��������� ������ ��������\n\n";
        cout << "������� ��:\n"; cin >> ch; cout << "\n";
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "������ ��'� �����: "; cin.getline(fname, 100);
            EnterSave(fname);
            cout << "\n\n";
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "������ ����� ����� ��� ���������� �����: "; cin.getline(fname, 100);
            LoadPrint(fname);
            cout << "\n\n";
            break;
        case '3':
            MinAverage(fname, r);
            cout << "5 � ������ �� ����������: " << r << "\n";
            cout << "\n\n";
            break;
        case '4':
            CountMarks(fname, countPhysics, countMath, countProg, countChuslo, countPed);
            cout << "ʳ������ ������ 5 � ������: " << countPhysics << "\n";
            cout << "ʳ������ ������ 5 � ����������: " << countMath << "\n";
            cout << "ʳ������ ������ 5 � �������������: " << countProg << "\n";
            cout << "ʳ������ ������ 5 � ��������� ������: " << countChuslo << "\n";
            cout << "ʳ������ ������ 5 � ���������: " << countPed << "\n";
            cout << "\n\n";
            break;
        default:
            cout << "����������� �������!\n\n";
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
        cout << "�� ������� ������� ���� \'" << fname << "\'\n";
        return;
    }

    Student student;

    int spec;
    char ch;
    int i = 0;
    do
    {
        cout << "������� �" << i + 1 << ":\n";
        i++;
        cin.sync();
        cout << "�������: "; cin >> student.Surname;
        cout << "����: "; cin >> student.course;
        cout << "������������ (��������� - 0, ����������� - 1, ���������� �� �������� - 2, Գ���� �� ����������� - 3, ������� �������� - 4): ";
        cin >> spec;
        student.spec = (Spec)spec;
        cout << "������ � ������: "; cin >> student.physics;
        cout << "������ � ����������: "; cin >> student.mathematics;
        switch (student.spec)
        {
        case ��:
            cout << " ������ � �������������: "; cin >> student.prog;
            break;
        case ���:
            cout << " ������ � ��������� ������: "; cin >> student.chuslo;
            break;
        case ���:
        case �Ҳ:
        case ��:
            cout << " ������ � ���������: "; cin >> student.ped;
            break;
        }
        cout << "\n";

        if (!f.write((char*)&student, sizeof(Student)))
        {
            cerr << "������� �������� �����" << endl;
        }
        cout << "������ \'y\', ��� ���������� ��������:\n\n "; cin >> ch;
    } while (ch == 'Y' || ch == 'y');
}

void LoadPrint(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "�� ������� ������� ���� \'" << fname << "'" << endl;
        return;
    }

    Student student;
    int i = 0;

    cout << "==============================================================================================================="
        << endl;
    cout << "|  � |   �������   |  ���� |  ����. |  ���. |  ���. |  ����. | ����. |  ����. |"
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
            case ��:
                cout << "| " << setw(6) << right << student.prog << " " << "| " << setw(8) << "| " << setw(8);
                break;
            case ���:
                cout << "| " << setw(9) << "| " << setw(5) << right << student.chuslo << " " << "| " << setw(8);
                break;
            case ���:
            case �Ҳ:
            case ��:
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
        cout << "�� ������� ������� ���� \'" << fname << "\'\n";
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
        case ��:
            if (student.prog == 5)
                countProg++;
            break;
        case ���:
            if (student.chuslo == 5)
                countChuslo++;
            break;
        case ���:
        case �Ҳ:
        case ��:
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
        cout << "�� ������� ������� ���� \'" << fname << "\'\n";
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
