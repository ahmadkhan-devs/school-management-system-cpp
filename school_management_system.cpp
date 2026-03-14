#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
using namespace std;

                                     //animation section
void typeEffect(const char *text)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        cout << text[i];
        Sleep(30);
    }
}

void loading()
{
    system("cls");
    typeEffect("Loading School Management System");
    for (int i = 0; i < 5; i++)
    {
        cout << ".";
        Sleep(400);
    }
}
void pass_load()
{
    typeEffect("Enter Admin Pasword : ");
}
void roll_No()
{
    typeEffect("Enter Roll Number : ");
}
void roll_search()
{
    typeEffect("Enter Roll Number to search : ");
}
void back()
{
    typeEffect("\nPress any key to return ");
    for (int i = 0; i < 5; i++)
    {
        cout << ".";
        Sleep(200);
    }
}
void pressAnyKey()
{
    cout << "\n\nPress any key to start...";
    getch();
}

struct Student
{
    string roll;
    string name;
    int classno;
    int section;
    int fee;
};
                             //menu display

void menu()
{
    cout << "\n=================================\n";
    cout << "   SCHOOL MANAGEMENT SYSTEM\n";
    cout << "=================================\n";
    cout << "1. Add Student\n";
    cout << "2. View All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Remove Student\n";
    cout << "5. Change Class\n";
    cout << "6. Update Fee Status\n";
    cout << "7. Fee Defaulters\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}
void addstudent()
{
    system("cls");

    cout << "==============================\n";
    cout << "       ENTER STUDENT DETAILS  \n";
    cout << "   (Type 0 at any step to cancel)\n";
    cout << "==============================\n\n";

    Student s;
    Student *p = &s;
       
    
    string newroll;
    roll_No();
    cin >> newroll;
    if (newroll == "0") { 
        back();
        getch();
         return;
         }
     
    ifstream checkfile("students.txt");
    Student temp;
    while (checkfile >> temp.roll >> temp.name >> temp.classno >> temp.section >> temp.fee)
    {
        if (temp.roll == newroll)
        {
            cout << "\nThis Roll number already exists!";
            checkfile.close();
            back();
            getch();
            return;
        }
    }
    checkfile.close();
    p->roll = newroll;
    cin.get();


    string inputname;
    cout << "Name: ";
    cin >> inputname;
    if (inputname == "0") { 
        back();
        getch();
        return; 
    }
    p->name = inputname;


    int inputclass;
    while (true)
    {
        cout << "Class (1-10): ";
        cin >> inputclass;
        if (inputclass == 0) {
            back();
            getch();
            return;
         }
        if (inputclass >= 1 && inputclass <= 10) { 
            p->classno = inputclass;
             break;
             }
        cout << "Invalid class! Only 1 to 10 allowed.\n";
    }

    //        sectionn input
    int inputsection;
    while (true)
    {
        cout << "Section (1-5): ";
        cin >> inputsection;
        if (inputsection == 0) { 
            back(); 
            getch(); 
            return;
         }
        if (inputsection >= 1 && inputsection <= 5) { 
            p->section = inputsection; 
            break; }
        cout << "Invalid section! Only 1 to 5 allowed.\n";
    }

    //  fees inputt
    int inputfee;
    while (true)
    {
        cout << "Fee Paid? (1 = Yes, 0 = No) [9 = Cancel]: ";
        cin >> inputfee;
        if (inputfee == 9) {
             back();
             getch(); 
             return; }
        if (inputfee == 0 || inputfee == 1) { 
            p->fee = inputfee; 
            break;
        }
        cout << "Invalid input! Only 0 or 1 allowed.\n";
    }

    //    save data
    ofstream file("students.txt", ios::app);
    file << p->roll << " " << p->name << " " << p->classno << " " << p->section << " " << p->fee << endl;
    file.close();

    cout << "\nSaving data ";
    for (int i = 0; i < 10; i++)
    {
        cout << char(219);
        Sleep(100);
    }

    cout << "\nStudent Added Successfully!";
    Sleep(1500);
}
void viewstudents()
{
    system("cls");

    ifstream file("students.txt");
    if (!file)
    {
        cout << "File not found!";
        getch();
        return;
    }

    cout << "=============================\n";
    cout << "       ALL STUDENTS LIST     \n";
    cout << "=============================\n\n";

    cout << "ROLL    NAME    CLASS   SEC   FEE\n";
    cout << "-----------------------------------\n";

    Student s;
    Student *p = &s;

    while (file >> p->roll >> p->name >> p->classno >> p->section >> p->fee)
    {
        cout << p->roll << "   "<< p->name << "       "<< p->classno << "       "<< p->section << "     "<< (p->fee ? "Paid" : "Unpaid") << endl;
    }

    file.close();
    back();
    getch();
}
void searchstudent()
{
    system("cls");
    ifstream file("students.txt");

    if (!file)
    {
        cout << "No student records found!";
        getch();
        return;
    }

    cout << "=============================\n";
    cout << "       SEARCH STUDENT        \n";
    cout << "=============================\n\n";

    Student s;
    Student *p = &s;

    string searchroll;
    roll_search();
    cin >> searchroll;
    if (searchroll == "0") { 
        back();
         getch();
          return;
         } 

    bool found = false;
    while (file >> p->roll >> p->name >> p->classno >> p->section >> p->fee)
    {
        if (p->roll == searchroll)
        {
            cout << "\nStudent Found!\n";cout << "Name: " << p->name << endl;
            cout << "Class: " << p->classno << endl;
            cout << "Section: " << p->section << endl;
            cout << "Fee Status: " << (p->fee ? "Paid" : "Unpaid") << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nStudent not found.";

    file.close();
    back();
    getch();
}
void removestudent()
{
    system("cls");

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file)
    {
        cout << "No student records found!";
        getch();
        return;
    }

    cout << "=============================\n";
    cout << "       REMOVE STUDENT        \n";
    cout << "=============================\n\n";

    Student s;
    Student *p = &s;
    string removeroll;

    roll_No();
    cin >> removeroll;
    if (removeroll == "0") { 
        back(); 
        getch(); 
        return;
     } 

    bool found = false;
    while (file >> p->roll >> p->name >> p->classno >> p->section >> p->fee)
    {
        if (p->roll == removeroll)
        {
            found = true; 
            continue;
        }

        temp << p->roll << " " << p->name << " "<< p->classno << " " << p->section << " " << p->fee << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent removed successfully!";
    else
        cout << "\nStudent not found!";

    back();
    getch();
}
void changeclass()
{
    system("cls");

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file)
    {
        cout << "No student records found!";
        getch();
        return;
    }

    cout << "=============================\n";
    cout << "        CHANGE CLASS         \n";
    cout << "=============================\n\n";

    Student s;
    Student *p = &s;

    string searchroll;
    roll_No();
    cin >> searchroll;
    if (searchroll == "0") { 
        back(); 
        getch(); 
        return; } 

    bool found = false;
    while (file >> p->roll >> p->name >> p->classno >> p->section >> p->fee)
    {
        if (p->roll == searchroll)
        {
            cout << "Current Class: " << p->classno << endl;
            cout << "Promote or Demote? (P/D): ";
            char choice;
            cin >> choice;

            bool valid = false;
            int newclass;

            if (choice == 'P' || choice == 'p')
            {
                while (!valid)
                {
                    cout << "Enter new class for promotion (1-10) [0 = Cancel]: ";
                    cin >> newclass;
                    if (newclass == 0) {
                         back(); 
                         getch(); 
                         return;
                        }

                    if (newclass > p->classno && newclass >= 1 && newclass <= 10)
                    {
                        p->classno = newclass;
                        valid = true;
                    }
                    else
                    {
                        cout << "Invalid! Promotion must be to higher class between 1-10.\n";
                    }
                }
            }
            else if (choice == 'D' || choice == 'd')
            {
                while (!valid)
                {
                    cout << "Enter new class for demotion (1-10) [0 = Cancel]: ";
                    cin >> newclass;
                    if (newclass == 0) { 
                        back(); 
                        getch(); 
                        return;
                     }

                    if (newclass < p->classno && newclass >= 1 && newclass <= 10)
                    {
                        p->classno = newclass;
                        valid = true;
                    }
                    else
                    {
                        cout << "Invalid! Demotion must be to lower class between 1-10.\n";
                    }
                }
            }
            else
            {
                cout << "Wrong choice! No change made.\n";
            }

            found = true;
        }
        temp << p->roll << " " << p->name << " "
             << p->classno << " " << p->section << " " << p->fee << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nClass updated successfully!";
    else
        cout << "\nStudent not found!";

    back();
    getch();
}
void updatefee()
{
    system("cls");

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file)
    {
        cout << "No student records found!";
        getch();
        return;
    }

    cout << "=============================\n";
    cout << "       UPDATE FEE STATUS     \n";
    cout << "=============================\n\n";

    Student s;
    Student *p = &s;
    string searchroll;

    roll_No();
    cin >> searchroll;
    if (searchroll == "0") { 
        back(); 
        getch(); 
        return; 
    }

    bool found = false;
    while (file >> p->roll >> p->name >> p->classno >> p->section >> p->fee)
    {
        if (p->roll == searchroll)
        {
            cout << "Current Fee Status: " << (p->fee ? "Paid" : "Unpaid") << endl;
        
            int newfee;
            while (true)
            {
                cout << "Enter new Fee Status (1 = Paid, 0 = Unpaid) [9 = Cancel]: ";
                cin >> newfee;

                if (newfee == 9) { 
                    back(); 
                    getch(); 
                    return; 
                }
                if (newfee == 0 || newfee == 1)
                {
                    p->fee = newfee;
                    break;
                }
                cout << "Invalid input! Only 0 or 1 allowed.\n";
            }

            found = true;
        }

        temp << p->roll << " " << p->name << " "
             << p->classno << " " << p->section << " " << p->fee << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nFee updated successfully!";
    else
        cout << "\nStudent not found!";

    back();
    getch();
}
void feedefaulters(){
    system("cls");

    ifstream file("students.txt");
    if (!file)
    {
        cout << "No student records found!";
        getch();
        return;
    }

    cout << "=============================\n";
    cout << "       FEE DEFAULTERS        \n";
    cout << "=============================\n\n";

    cout << "ROLL    NAME    CLASS   SEC\n";
    cout << "----------------------------\n";

    Student s;
    Student *p = &s;

    while (file >> p->roll >> p->name >> p->classno >> p->section >> p->fee)
    {
        if (p->fee == 0)
        {
            cout << p->roll << "    "
                 << p->name << "       "
                 << p->classno << "       "
                 << p->section << endl;
        }
    }

    file.close();
    back();
    getch();
}
                      //admin login
void adminpanel(){
    system("cls");
    string pass;
    pass_load();
    cin >> pass;
    if (pass == "*****")
    {
        cout << "\nAccess Granted!";
    }
    else
    {
        do{
            cout << "\nWrong Password!"<<endl;
            cout<<"Try Again : "<<endl;
            cin>>pass;
        }while(pass != "*****");
    }
    Sleep(1500);
}
                                                          //main section
int main()
{
    int choice;
    loading();
    pressAnyKey();
    adminpanel();

    do
    {
        system("cls");
         menu();

        
        while (!(cin >> choice))  
        {
            cin.clear();          
             cin.ignore(1000, '\n');
            cout << "Invalid input! Enter a number: ";
        }
        switch (choice)
        {
        case 1: addstudent(); 
        break;
        case 2: viewstudents();
        break;
        case 3: searchstudent(); 
        break;
        case 4: removestudent(); 
        break;
        case 5: changeclass(); 
        break;
        case 6: updatefee(); 
        break;
        case 7: feedefaulters(); 
        break;
        case 0:
            typeEffect("\nExiting Program...");
            Sleep(1000);
            break;
        default:
            cout << "Invalid Choice!";
            Sleep(1000);
        }
    } while (choice != 0);
    return 0;
}