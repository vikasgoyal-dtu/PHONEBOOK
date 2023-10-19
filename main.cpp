#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

void EnterData();
void DisplayRecords();
void SearchBySerialNo();
void deleteRecord();
void modifyRecord();
void SearchByPhoneNo();
void RemoveAll();
void menu();
void administrator();
void menuUser();
void loading();
bool phoneValidator(long long int ph);
bool serialValidator(int sn);

class record
{
public:
    int serialNo;
    string name;
    char email[30];
    long long int phno;
    int SerialNumberReturn() { return serialNo; }
    long long int PhonenumberReturn() { return phno; }
    string NameReturn() { return name; }

    void enterdetails()
    {
        int sNo;
        string nm;
        char em[30];
        long long int ph;
    START:
        cout << "\n\t\t\t\t\t\t\t\t\tENTER SERIAL NUMBER:";
        cin >> sNo;
        if (serialValidator(sNo) == false)
        { 
            cout << "\n\t\t\t\t\t\t\t\t\tINVALID SERIAL NUMBER ENTERED!";
            goto START;
        }
        cout << "\n\t\t\t\t\t\t\t\t\tENTER NAME:";
        cin.ignore();
        getline(cin, nm);
    RETRY:
        cout << "\n\t\t\t\t\t\t\t\t\tENTER PHONE NUMBER: ";
        cin >> ph;
        cin.ignore();
        if (phoneValidator(ph) == false)
        {
            cout << "\n\t\t\t\t\t\t\t\t\tINVALID PHONE NUMBER ENTERED!";
            // cin.ignore();
            goto RETRY;
        }

        cout << "\n\t\t\t\t\t\t\t\t\tENTER EMAIL: ";
        cin.getline(em, 30);
        feedDetails(sNo, nm, em, ph);
    }

    void enterdetails2(int sNo)
    {
        string nm;
        char em[30];
        long long int ph;
        cout << "\n\t\t\t\t\t\t\t\t\tSERIAL NUMBER:" << sNo;

        cout << "\n\t\t\t\t\t\t\t\t\tENTER NAME:";
        cin.ignore();
        getline(cin, nm);
    RETRY:
        cout << "\n\t\t\t\t\t\t\t\t\tENTER PHONE NUMBER: ";
        cin >> ph;
        cin.ignore();
        if (phoneValidator(ph) == false)
        {
            cout << "\n\t\t\t\t\t\t\t\t\tINVALID PHONE NUMBER ENTERED!";
            // cin.ignore();
            goto RETRY;
        }

        cout << "\n\t\t\t\t\t\t\t\t\tENTER EMAIL: ";
        cin.getline(em, 30);
        feedDetails(sNo, nm, em, ph);
    }

    void feedDetails(int sn, string nm, char em[], long long int ph)
    {
        serialNo = sn;
        phno = ph;
        name = nm;
        strcpy(email, em);
    }

    void display()
    {
        cout << "\n\t\t\t\t\t\t\t\t\tSERIAL NUMBER:" << serialNo;
        cout << "\n\t\t\t\t\t\t\t\t\tNAME:" << name;
        cout << "\n\t\t\t\t\t\t\t\t\tPHONE NUMBER:" << phno;
        cout << "\n\t\t\t\t\t\t\t\t\tEMAIL:" << email;
        cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
    }

} r;

int phlen(long long int ph)
{
    int ans = 0;
    while (ph > 0)
    {
        ans++;
        ph /= 10;
    }
    return ans;
}

bool phoneValidator(long long int ph)
{
    if (ph < 0 || phlen(ph) != 10)
    {
        return false;
    }
    ifstream fin;

    fin.open("Record3.txt", ios::out | ios::binary | ios::app);

    while (fin.read((char *)&r, sizeof(r)))
    {
        if (ph == r.PhonenumberReturn())
        {
            cout << "\n\t\t\t\t\t\t\t\t\tTHIS PHONE NUMBER ALREADY EXISTS!";
            return false;
        }
    }
    fin.close();
    return true;
}

bool serialValidator(int sn)
{
    if (sn < 0 || sn > 200)
    {
        return false;
    }
    ifstream fin;

    fin.open("Record3.txt", ios::out | ios::binary | ios::app);

    while (fin.read((char *)&r, sizeof(r)))
    {
        if (sn == r.SerialNumberReturn())
        {
            cout << "\n\t\t\t\t\t\t\t\t\tTHIS SERIAL NUMBER ALREADY EXISTS!";
            return false;
        }
    }
    fin.close();
    return true;
}

void EnterData()
{
    ofstream fout;
    fout.open("Record3.txt", ios::out | ios::binary | ios::app);
    r.enterdetails();
    fout.write((char *)&r, sizeof(r));
    fout.close();
    cout << "\n\t\t\t\t\t\t\t\t\tRecord Saved to File......\n";
}

void DisplayRecords()
{
    ifstream fin;
    fin.open("Record3.txt", ios::out | ios::binary | ios::app);
    while (fin.read((char *)&r, sizeof(r)))
    {
        r.display();
    }
    fin.close();
    cout << "\n\t\t\t\t\t\t\t\t\tReading of Data File Completed......\n";
}

void deleteRecordSerialNumber()
{
    ifstream fin;
    ofstream fout;
    int n, flag = 0;
    fin.open("Record3.txt", ios::out | ios::binary | ios::app);
    fout.open("temp.txt", ios::out | ios::binary);
    cout << "\n\t\t\t\t\t\t\t\t\tEnter Serial Number : ";
    cin >> n;

    while (fin.read((char *)&r, sizeof(r)))
    {
        if (n == r.SerialNumberReturn())
        {
            cout << "\n\t\t\t\t\t\t\t\t\tThe Following record is deleted....\n";
            r.display();
            flag++;
        }
        else
        {
            fout.write((char *)&r, sizeof(r));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\n\t\t\t\t\t\t\t\t\tThe Record of Serial Number " << n << " is not in file....\n";
    cout << "\n\t\t\t\t\t\t\t\t\tReading of Data File Completed......\n";
    remove("Record3.txt");
    rename("temp.txt", "Record3.txt");
}

void deleteRecordPhoneNumber()
{
    ifstream fin;
    ofstream fout;
    long long int n;
    int flag = 0;
    fin.open("Record3.txt", ios::out | ios::binary | ios::app);
    fout.open("temp.txt", ios::out | ios::binary);
    cout << "\n\t\t\t\t\t\t\t\t\tEnter Phone Number To Search Record To Delete : ";
    cin >> n;

    while (fin.read((char *)&r, sizeof(r)))
    {
        if (n == r.PhonenumberReturn())
        {
            cout << "\n\t\t\t\t\t\t\t\t\tThe Following record is deleted....\n";
            r.display();
            flag++;
        }
        else
        {
            fout.write((char *)&r, sizeof(r));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\n\t\t\t\t\t\t\t\t\tThe Record of Serial Number " << n << " is not in file....\n";
    cout << "\n\t\t\t\t\t\t\t\t\tReading of Data File Completed......\n";
    remove("Record3.txt");
    rename("temp.txt", "Record3.txt");
}

void deleteRecordName()
{
    ifstream fin;
    ofstream fout;
    int flag = 0;
    string nm;
    fin.open("Record3.txt", ios::out | ios::binary | ios::app);
    fout.open("temp.txt", ios::out | ios::binary);
    cout << "\n\t\t\t\t\t\t\t\t\tEnter Name To Search Record To Delete : ";
    cin.ignore();
    getline(cin, nm);

    while (fin.read((char *)&r, sizeof(r)))
    {
        if (nm == r.NameReturn())
        {
            cout << "\n\t\t\t\t\t\t\t\t\tThe Following record is deleted....\n";
            r.display();
            flag++;
        }
        else
        {
            fout.write((char *)&r, sizeof(r));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\n\t\t\t\t\t\t\t\t\tThe Record of Serial Number " << nm << " is not in file....\n";
    cout << "\n\t\t\t\t\t\t\t\t\tReading of Data File Completed......\n";
    remove("Record3.txt");
    rename("temp.txt", "Record3.txt");
}

void deleteRecord()
{
    int n;
    cout << "\n\t\t\t\t\t\t\t\t\t1.)Search By Phone Number ";
    cout << "\n\t\t\t\t\t\t\t\t\t2.)Search By Serial Number ";
    cout << "\n\t\t\t\t\t\t\t\t\t3.)Search By Name \n\t\t\t\t\t\t\t\t\t";

    cin >> n;

    switch (n)
    {
    case 1:
        deleteRecordPhoneNumber();
        break;
    case 2:
        deleteRecordSerialNumber();
        break;
    case 3:
        deleteRecordName();
        break;
    default:
        cout << "Invalid Choice Entered";
        break;
    }
}

void modifyRecord()
{
    fstream fio;
    int n, flag = 0, pos;
    fio.open("Record3.txt", ios::out | ios::binary | ios::in);

    cout << "Enter Serial Number of Record To Modify : ";
    cin >> n;

    while (fio.read((char *)&r, sizeof(r)))
    {
        pos = fio.tellg();
        if (n == r.SerialNumberReturn())
        {
            cout << "\n\t\t\t\t\t\t\t\t\tThe Following record will be modified....\n";
            r.display();
            flag++;
            cout << "\n\t\t\t\t\t\t\t\t\tRe-Enter the New Details----\n";
            r.enterdetails2(n);
            fio.seekg(pos - sizeof(r));
            fio.write((char *)&r, sizeof(r));
            cout << "\n\t\t\t\t\t\t\t\t\t----Data Modified Successfully----\n";
        }
    }
    fio.close();
    if (flag == 0)
        cout << "\n\t\t\t\t\t\t\t\t\tThe Record of Serial Number " << n << " is not in file....\n";
    cout << "\n\t\t\t\t\t\t\t\t\tReading of Data File Completed......\n";
}

void SearchByPhoneNo()
{
    ifstream fin;
    long long int n;
    int flag = 0;
    fin.open("Record3.txt", ios::out | ios::binary | ios::app);
    cout << "\n\t\t\t\t\t\t\t\t\tEnter Phone Number of Record To Display: ";
    cin >> n;

    while (fin.read((char *)&r, sizeof(r)))
    {
        if (n == r.PhonenumberReturn())
        {
            r.display();
            flag++;
            cout << "\n\n\t\t\t\t\t\t\t\t\t-----Record Found and Displayed-----\n";
        }
    }
    fin.close();
    if (flag == 0)
        cout << "\n\t\t\t\t\t\t\t\t\tThe Record of Serial Number " << n << " is not in file....\n";
    cout << "\n\t\t\t\t\t\t\t\t\tReading of Data File Completed-----\n";
}

void SearchBySerialNo()
{
    ifstream fin;
    int n, flag = 0;
    fin.open("Record3.txt", ios::out | ios::binary | ios::app);
    cout << "\n\t\t\t\t\t\t\t\t\tEnter Serial Number of Record To Display: ";
    cin >> n;

    while (fin.read((char *)&r, sizeof(r)))
    {
        if (n == r.SerialNumberReturn())
        {
            r.display();
            flag++;
            cout << "\n\n\t\t\t\t\t\t\t\t\t-----Record Found and Displayed-----\n";
        }
    }
    fin.close();
    if (flag == 0)
        cout << "\n\t\t\t\t\t\t\t\t\tThe Record of Serial Number " << n << " is not in file....\n";
    cout << "\n\t\t\t\t\t\t\t\t\tReading of Data File Completed-----\n";
}

void RemoveAll()
{
    string ans;
    cout << "\n\t\t\t\t\t\t\t\t\tDO YOU REALLY WANT TO DELETE ALL THE RECORDS?(Y/N)";
    cin >> ans;
    if (ans == "y" || ans == "Y")
        remove("Record3.txt");

    cout << "\n\t\t\t\t\t\t\t\t\tDELETED ALL RECORDS!!!!";
}

int main()
{

    int ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|           PHONEBOOK APPLICATION SYSTEM              |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                [1]User                              |\n";
        cout << "\t\t\t\t\t\t\t\t|                [2]Administrator Login               |\n";
        cout << "\t\t\t\t\t\t\t\t|                [3]Exit                              |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                OOPS PROJECT                          |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            loading();
            menuUser();
            break;
        case 2:
            administrator();
            break;
        }
        getch();
    } while (ch != 3);

    return 0;
}

void menu()
{
    int ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|           PHONEBOOK APPLICATION SYSTEM              |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                [1]ADD CONTACTS                      |\n";
        cout << "\t\t\t\t\t\t\t\t|                [2]DISPLAY CONTACTS                  |\n";
        cout << "\t\t\t\t\t\t\t\t|                [3]UPDATE CONTACTS                   |\n";
        cout << "\t\t\t\t\t\t\t\t|                [4]DELETE CONTACTS                   |\n";
        cout << "\t\t\t\t\t\t\t\t|                [5]SEARCH BY SERIAL NUMBER           |\n";
        cout << "\t\t\t\t\t\t\t\t|                [6]SEARCH BY PHONE NUMBER            |\n";
        cout << "\t\t\t\t\t\t\t\t|                [7]DELETE ALL CONTACTS               |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                   [8]LOGOUT                         |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            EnterData();
            break;
        case 2:
            DisplayRecords();
            break;
        case 3:
            modifyRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            SearchBySerialNo();
            break;
        case 6:
            SearchByPhoneNo();
            break;
        case 7:
            RemoveAll();
            break;
        case 8:
            return;
        }
        getch();
    } while (ch != 8);
}

void menuUser()
{
    int ch; 
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|           PHONEBOOK APPLICATION SYSTEM              |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                [1]DISPLAY CONTACTS                  |\n";
        cout << "\t\t\t\t\t\t\t\t|                [2]SEARCH BY SERIAL NUMBER           |\n";
        cout << "\t\t\t\t\t\t\t\t|                [3]SEARCH BY PHONE NUMBER            |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t|                   [4]EXIT                           |\n";
        cout << "\t\t\t\t\t\t\t\t-------------------------------------------------------\n";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            DisplayRecords();
            break;
        case 2:
            SearchBySerialNo();
            break;
        case 3:
            SearchByPhoneNo();
            break;
        case 4:
            return;
        }
        getch();
    } while (ch != 4);
}

void loading()
{
    // char x=219;
    char x = 254;
    cout << "\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\tPHONEBOOK MANAGEMENT SYSTEM\n ";
    cout << "\t\t\t\t\t\t\t\tLoading: ";
    for (int i = 0; i < 35; i++)
    {
        cout << x;
        Sleep(100);
        if (i > 10 && i <= 20)
            Sleep(50);
        if (i > 20)
            Sleep(25);
    }
    system("cls");
}

void administrator()
{
ADMIN:
    string username;
    string pass = "";
    char ch;
    cout << "\t\t\t\t\t\t\t\tEnter username\n\t\t\t\t\t\t\t\t";
    cin >> username;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\tEnter password\n\t\t\t\t\t\t\t\t";
    ch = _getch();
    while (ch != 13)
    { //character 13 is enter
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if ((pass == "qwerty" && username == "vaibhav") || (pass == "qwerty" && username == "vikas"))
    {
        loading();
        menu();
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\t\tAccess aborted...\n";
        cout << "\n\t\t\t\t\t\t\t\tdo you want to try again?(y/n)  ";
        char c;
        cin >> c;
        if (c == 'y' || c == 'Y')
        {
            goto ADMIN;
        }
        else
        {
            return;
        }
    }
}
