// Phonebook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;
const string FILENAME = "contacts.csv";
const int MAX_CONTACTS = 100;



class Contact
{
    public:
        string firstName;
        string lastName;
        string phoneNumber;
        string address;

        Contact()
        {
            firstName = "";
            lastName = "";
            phoneNumber = "";
            address = "";
        };

        bool exists(string search)
        {
            return ((firstName , " ", lastName).find(search) != string::npos);
        };

        void empty()
        {
            firstName = "";
            lastName = "";
            phoneNumber = "";
            address = "";
        }
};


void addContact();
void deleteContact(Contact contacts[MAX_CONTACTS]);
void editContact(Contact contacts[MAX_CONTACTS]);
void getContacts(Contact contacts[MAX_CONTACTS]);
void parseCSV();


int main()
{
    while (true)
    {
        int selection = -1;
        ifstream in;
        string contact;
        int contactNo = 1;
        Contact contacts[MAX_CONTACTS];

        cout << "---------\nPHONEBOOK\n---------\n";

        getContacts(contacts);

        cout
            << "0. Exit\n"
            << "1. Add contact\n"
            << "2. Delete contact\n"
            << "3. Edit contact\n> ";
        cin >> selection;

        switch (selection)
        {
            case(0):
                cout << "Exiting...\n";
                exit(0);
                break;
        case 1:
            addContact();
            break;
        case 2:
            deleteContact(contacts);
            break;
        case 3:
            editContact(contacts);
            break;
        default:
            cout << "Wrong selection.\n";
            break;
        };
    };
};


void getContacts(Contact contacts[MAX_CONTACTS])
{
    /**
     * Gets contacts from file and prints them.
    */
    ifstream data(FILENAME);
    string line;
    int contact_num = 0;

    // Get contacts
    while(getline(data,line))
    {
        stringstream lineStream(line);
        string cell;
        std::vector<std::string> parsedRow;

        while(getline(lineStream,cell,','))
        {
            parsedRow.push_back(cell);
        }

        contacts[contact_num].firstName = parsedRow[0];
        contacts[contact_num].lastName = parsedRow[1];
        contacts[contact_num].phoneNumber = parsedRow[2];
        contacts[contact_num].address = parsedRow[3];
        contact_num++;
    };

    // Print contacts
    for (int i = 0; i < MAX_CONTACTS; i++)
    {
        if (contacts[i].firstName != "")
        {
            cout << contacts[i].firstName << " " << contacts[i].lastName<< " " << contacts[i].phoneNumber<< " " << contacts[i].address << "\n";
        }
    }
};


void setContacts(Contact contacts[MAX_CONTACTS])
{
    /**
     * Overwrites old contacts file with updated contacts.
    */
    ofstream out;

    out.open(FILENAME, ios::trunc);

    for (int i = 0; i < MAX_CONTACTS; i++)
    {   
        if (contacts[i].firstName != "")
        {
            out << contacts[i].firstName << "," << contacts[i].lastName << "," << contacts[i].phoneNumber << "," << contacts[i].address << "\n";
        }
    }
    cout << "contacts set \n";
}


void addContact()
{
    /**
     * Adds a new contact.
    */
    string firstName{};
    string lastName{};
    string phoneNumber{};
    string address{};
    ofstream fileOut;

    cout << "Please input the required information.\n";
    cout << "Input first name.\n> ";
    cin >> firstName;
    cout << "Input last name.\n> ";
    cin >> lastName;
    cout << "Input phone number.\n> ";
    cin >> phoneNumber;
    cout << "Input address.\n> ";
    cin >> address;

    fileOut.open(FILENAME, ios::app);
    fileOut << firstName << "," << lastName << "," << phoneNumber << "," << address << "\n";
    fileOut.close();
    cout << "Contact added!\n";
};


void deleteContact(Contact contacts[MAX_CONTACTS])
{
    /**
     * Deletes the selected contact.
    */
    string input;
    int deleteLine;

    cout << "Which contact would you like to delete?\n> ";
    cin >> input;

    try
    {
        deleteLine = stoi(input);
    }
    catch(const std::exception& e)
    {
        cout << "Invalid input!\n";
        deleteContact(contacts);
    }

    for (int i = 0; i < MAX_CONTACTS; i++)
    {
        if (i = deleteLine)
        {
            contacts[i-1].empty();
            break;
        }
    }

    setContacts(contacts);
}

void editContact(Contact contacts[MAX_CONTACTS])
{
    /**
     * Edits the selected contact.
    */
    int selection;
    int editLine;
    string input;

    cout << "Which contact would you like to edit?\n";
    cin >> selection;

    for (int i = 0; i < MAX_CONTACTS; i++)
    {
        if (i = selection)
        {
            cout << "What would you like to do?\n"
                << "0. Nothing\n"
                << "1. Edit first name\n"
                << "2. Edit last name\n"
                << "3. Edit phone number\n"
                << "4. Edit address\n";
            cin >> selection;

            switch (selection)
            {
                case 0:
                    main();
                    break;
                case 1:
                    cout << "Enter new first name\n";
                    cin >> input;
                    contacts[i-1].firstName = input;
                    break;
                case 2:
                    cout << "Enter new last name\n";
                    cin >> input;
                    contacts[i-1].lastName = input;
                    break;
                case 3:
                    cout << "Enter new phone number\n";
                    cin >> input;
                    contacts[i-1].phoneNumber = input;
                    break;
                case 4:
                    cout << "Enter new address\n";
                    cin >> input;
                    contacts[i-1].address = input;
                    break;
                default:
                    cout << "Wrong selection.\n";
                    deleteContact(contacts);
                    break;
            };
            break;
        }
    }
    setContacts(contacts);
}
