#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

const string Reset = "\033[0m";
const string Red = "\033[1;31m";
const string Green = "\033[1;32m";
const string Yellow = "\033[1;33m";
const string Blue = "\033[1;34m";
const string Magenta = "\033[1;35m";
const string Cyan = "\033[1;36m";
const string Purple = "\033[35m";
const string Light_Blue = "\033[1;36m";

void clearfile(const string& filename)
{
    ofstream outfile(filename, ios::out | ios::trunc);
    if (!outfile.is_open())
    {
        cout << "\t\t\t\t\tError opening file!" << endl;
    }
    else
    {
        cout << "\t\t\t\t\tFile cleared successfully." << endl;
    }
    outfile.close();
}

bool isfileempty(const string& filename)
{
    ifstream file(filename);
    return file.peek() == ifstream::traits_type::eof();
}

void additems()
{
    system("cls");
    ofstream outFile("items.txt", ios::app);
    if (!outFile)
    {
        cerr << Red << "\n\t\t\t\t\tError creating/opening the file." << endl;
        return;
    }
    string name;
    double price;
    char addanotheritem;
    do {
        cout << Cyan << "\t\t\t\tEnter the item you want to add (e.g., Croissant): ";
        cout << Reset;
        cin >> name;
        cout << Cyan << "\t\t\t\tEnter the price of the item : ";
        cout << Reset;
        cin >> price;
        outFile << name << " " << price << endl;
        cout << Yellow << "\t\t\t\tItem added to the menu!" << endl;
    addanotheritem:
        cout << Green << "\t\t\t\tDo you want to add another item? (Press y to add another, any other button to go to main menu):";

        cout << Reset;
        cin >> addanotheritem;
        if (addanotheritem == 'y' || addanotheritem == 'Y')
        {
            system("cls");

        }
    } while (addanotheritem == 'y' || addanotheritem == 'Y');
    outFile.close();
}
void viewmenu()
{
    string item;
    double price;
    ifstream file("items.txt");
    if (!file)
    {
        cout << "\n\t\t\t\t\tUnable to open file" << endl;
        return;
    }
    cout << Blue << "\t\t\t\t\tMenu:\n";
    cout << Yellow << left << setw(20) << "\t\t\t\t\tItem" << setw(10) << right << "\t\t\t\t\tPrice (PKR)" << endl;
    cout << "\t\t\t\t\t____________________" << endl;

    while (file >> item >> price)
    {
        cout << Yellow << "\t\t\t\t\t" << left << setw(30) << item << Reset << right << fixed << setprecision(2) << setw(30) << Green << price << Reset << endl;
    }
    file.close();
}

void deleteanitem()
{

    string nameofitem;
    cout << Cyan << "\t\t\t\t\tEnter the name of the item to delete: ";
    cout << Reset;
    cin >> nameofitem;

    ifstream infile("items.txt");
    ofstream temporaryfile("temp_items.txt");

    if (!infile || !temporaryfile)
    {
        cout << Red << "\t\t\t\t\tError opening files." << endl;
        return;
    }
    string item;
    double price;
    bool itemfound = false;

    while (infile >> item >> price)
    {
        if (item == nameofitem)
        {
            itemfound = true;
        }
        else
        {
            temporaryfile << item << " " << price << endl;
        }
    }
    infile.close();
    temporaryfile.close();

    if (!itemfound)
    {
        cout << Red << "\t\t\t\t\tItem not found." << endl;
        remove("temp_items.txt");
        return;
    }

    remove("items.txt");
    rename("temp_items.txt", "items.txt");
    cout << Yellow << "\t\t\t\t\tItem deleted successfully." << endl;
}
void itemspriceupdate()
{

    string nameofitems;
    double newpriceofitem;
    cout << Cyan << "\t\t\t\t\tEnter the name of the item to update: ";
    cin >> nameofitems;
    cout << Cyan << "\t\t\t\t\tEnter the new price: ";
    cin >> newpriceofitem;

    ifstream infile("items.txt");
    ofstream temporaryfileprice("temp_items.txt");

    if (!infile || !temporaryfileprice)
    {
        cout << Red << "\t\t\t\t\tError opening files." << endl;
        return;
    }
    string item;
    double price;
    bool itemfound = false;

    while (infile >> item >> price)
    {
        if (item == nameofitems)
        {
            temporaryfileprice << item << " " << newpriceofitem << endl;
            itemfound = true;
        }
        else
        {
            temporaryfileprice << item << " " << price << endl;
        }
    }
    infile.close();
    temporaryfileprice.close();
    if (!itemfound)
    {
        cout << Red << "\t\t\t\t\tItem not found." << endl;
        remove("temp_items.txt");
        return;
    }

    remove("items.txt");
    rename("temp_items.txt", "items.txt");
    cout << Yellow << "\t\t\t\t\tItem price updated successfully." << endl;
}
void returntologin();
int menuforowner()
{
    int h;
    while (true)
    {
        cout << Cyan << "\n\t\t\t\t\tPress 1 to view items in the menu" << endl;
        cout << Cyan << "\t\t\t\t\tPress 2 to add new items to the menu" << endl;
        cout << Cyan << "\t\t\t\t\tPress 3 to delete an item from the menu" << endl;
        cout << Cyan << "\t\t\t\t\tPress 4 to update an item price" << endl;
        cout << Cyan << "\t\t\t\t\tPress 5 to erase the previous menu" << endl;
        cout << Cyan << "\t\t\t\t\tPress 6 to return to login page" << endl;
        cout << Cyan << "\t\t\t\t\tYour choice : ";
        cout << Green;
        cin >> h;
        switch (h)
        {
        case 1:
            viewmenu();
            break;
        case 2:
            additems();
            break;
        case 3:
            deleteanitem();
            break;
        case 4:
            itemspriceupdate();
            break;
        case 5:
            clearfile("items.txt");
            break;
        case 6:
            returntologin();
            break;
        default:
            cout << Red << "\t\t\t\t\tInvalid choice" << endl;
        }
    }
}
void billgenerator(const string items[], const double prices[], int itemCount)
{
    double total = 0;
    cout << Blue << "\n\t\t\t\t\tYour Bill:\n";
    cout << Yellow << left << setw(30) << "\t\t\t\t\tItem" << setw(30) << right << "Price (PKR)" << endl;
    cout << "\t\t\t\t\t____________________" << endl;

    for (int i = 0; i < itemCount; ++i)
    {
        cout << Yellow << "\t\t\t\t\t" << left << setw(30) << items[i] << Reset << right << fixed << setprecision(2) << setw(30) << Green << prices[i] << Reset << endl;
        total += prices[i];
    }
    cout << "\t\t\t\t\t____________________" << endl;
    cout << Yellow << "\t\t\t\t\tTotal" << setw(58) << Green << total << " PKR" << Reset << endl;
}
void menuforcustomer()
{
    viewmenu();
    string item;
    double price;
    char c;
    double total = 0;
    string purchasedItems[100];
    double purchasedPrices[100];
    int itemCount = 0;

    cout << Blue << "\n\t\t\t\t\tWhat do you want to buy today?" << endl;
    do {
        string choice;
        cout << "\n\t\t\t\t\tEnter the name of the item : ";
        cout << Yellow;
        cin >> choice;

        ifstream itemfile("items.txt");
        if (!itemfile)
        {
            cout << "\t\t\t\t\tUnable to open file" << endl;
            return;
        }
        bool itemfound = false;
        do
        {
            itemfile.clear();
            itemfile.seekg(0, ios::beg);
            while (itemfile >> item >> price)
            {
                if (item == choice)
                {
                    purchasedItems[itemCount] = item;
                    purchasedPrices[itemCount] = price;
                    itemCount++;
                    total += price;
                    itemfound = true;
                    break;
                }
            }
            if (!itemfound)
            {
                cout << "\t\t\t\t\tItem not found." << endl;
                cout << "\t\t\t\t\tEnter the name again: ";
                cin >> choice;
            }
        } while (!itemfound);
        itemfile.close();
        cout << endl;
        cout << "\t\t\t\t\tYour total price is  " << Green << total << " PKR" << endl;
        cout << Blue << "\n\t\t\t\t\tDo you want to buy any other goods ? (Press any button to buy more or press n to exit): ";
        cout << Yellow;
        cin >> c;
        if (c == 'n' || c == 'N')
        {
            system("cls");
            cout << Reset;
            cout << Yellow <<
                "\t\t\t\t\t *******************************************\n"
                "\t\t\t\t\t*                                         *\n"
                "\t\t\t\t\t*                                         *\n"
                "\t\t\t\t\t*  Thank you for visiting our bakery !!   *\n"
                "\t\t\t\t\t*    -------------------------------      *\n"
                "\t\t\t\t\t*                                         *\n"
                "\t\t\t\t\t*******************************************\n";
            billgenerator(purchasedItems, purchasedPrices, itemCount);
            // returntologin();
        }
    } while (c != 'n' && c != 'N');
}
struct owner {
    string name;
    string pass;
};
int main()
{
    cout << Cyan << endl;
    cout << "  ____     ___     _____     __  __        _              -----\\       _         _  __      _____      -----    __      __      " << endl;
    cout << " / ___|    | |    / ___|    | |\\/| |      / \\\\           | |_) |      / \\\\      | |/ /     | ____|    | |_) |   \\ \\    / /       " << endl;
    cout << "| |___     | |   | |  _     | |\\/| |     /   \\\\          |_____/     /   \\\\     | ' /      | |__      |_____/    \\ \\  / /        " << endl;
    cout << " \\___ \\    | |   | | | |    | |\\/| |    /  _  \\\\         |  __ \\    /  _  \\\\    |  <       | |__|     | |   \\ \\   \\ \\/ /          " << endl;
    cout << "  ___) |   | |   | |_| |    | |  | |   /  ___  \\\\        | |_) |   /  ___  \\\\   | . \\      | |___     | |  \\ \\     |  |           " << endl;
    cout << " |____/    |_|    \\____|    |_|  |_|  /__/   \\__\\\\       |_____/  /__/   \\__\\\\  |_|\\_\\     |_____|    | |   \\ \\    |__|            " << endl;


    cout << endl << endl;
    cout << Light_Blue <<
        "\t\t\t\t\t*******************************************\n"
        "\t\t\t\t\t*                                         *\n"
        "\t\t\t\t\t*          Welcome to Our Bakery!         *\n"
        "\t\t\t\t\t*                                         *\n"
        "\t\t\t\t\t*     --------------------------------    *\n"
        "\t\t\t\t\t*                                         *\n"
        "\t\t\t\t\t*       Enjoy our freshly made goods!     *\n"
        "\t\t\t\t\t*                                         *\n"
        "\t\t\t\t\t*******************************************\n";
    cout << endl;
    cout << endl;
    cout << Yellow << "\t\t\t\t\tPlease choose an option:\n" << endl;
    cout << endl;
    cout << Reset;
    int p;
    cout << Green << "\t\t\t\t\tTo log in as a Customer, press 1  " << endl;
    cout << Green << "\t\t\t\t\tTo log in as an Owner, press 2 " << endl;
    cout << Green << "\t\t\t\t\tTo end the Program , press 3 " << endl;
    cout << Red;
    cout << "\t\t\t\t\t";
    cin >> p;

    if (p == 3)
    {
        cout << Yellow <<
            "\t\t\t\t\t *******************************************\n"
            "\t\t\t\t\t*                                         *\n"
            "\t\t\t\t\t*                                         *\n"
            "\t\t\t\t\t*  Thank you for visiting our bakery !!   *\n"
            "\t\t\t\t\t*    -------------------------------      *\n"
            "\t\t\t\t\t*                                         *\n"
            "\t\t\t\t\t*******************************************\n";
        cout << Reset;
        exit(0);
    }
    if (p != 1 && p != 2)
    {
        cout << Red << "\t\t\t\t\tInvalid choice";
        return 1;
    }
    if (p == 1)
    {
        system("cls");
        if (isfileempty("items.txt"))
        {
            cout << Magenta << "\n\t\t\t\t\tThe menu is empty, please ask the owner to add items to the menu." << endl;
            main();
        }
        menuforcustomer();
    }
    if (p == 2)
    {
        system("cls");
    start:
        owner saved;
        owner entered;
        ifstream passwordfile("password.txt");
        if (!passwordfile)
        {
            owner newowner;
            cout << Light_Blue << "\n\t\t\t\t\tEnter new username: ";
            cin >> newowner.name;
            cout << Light_Blue << "\n\t\t\t\t\tCreate new password: ";
            cin >> newowner.pass;
            ofstream n("password.txt");
            n << newowner.name << "  " << newowner.pass;
            cout << "\n\t\t\t\t\tNew username and password created";
            goto start;
        }
    username:
        cout << Yellow <<
            "\t\t\t\t\t*******************************************\n"
            "\t\t\t\t\t*                                         *\n"
            "\t\t\t\t\t*                                         *\n"
            "\t\t\t\t\t*            Enter username               *\n"
            "\t\t\t\t\t*    -------------------------------      *\n"
            "\t\t\t\t\t*                                         *\n"
            "\t\t\t\t\t*******************************************\n";
        cout << Cyan;
        cout << "\t\t\t\t\t";
        cin >> entered.name;
    password:
        cout << Yellow <<
            "\t\t\t\t\t*******************************************\n"
            "\t\t\t\t\t*                                         *\n"
            "\t\t\t\t\t*                                         *\n"
            "\t\t\t\t\t*            Enter password               *\n"
            "\t\t\t\t\t*    -------------------------------      *\n"
            "\t\t\t\t\t*                                         *\n"
            "\t\t\t\t\t*******************************************\n";
        cout << Cyan;
        cout << "\t\t\t\t\t";
        cin >> entered.pass;
        passwordfile >> saved.name >> saved.pass;
        if (entered.name == saved.name && saved.pass == entered.pass)
        {
            menuforowner();
        }
        if (entered.name != saved.name)
        {
            cout << Red << "\t\t\t\t\tEntered username is wrong , please enter the correct username." << endl;
            goto username;
        }
        if (entered.pass != saved.pass)
        {
            cout << Red << "\t\t\t\t\tEntered password is wrong , please enter the correct password." << endl;
            goto password;
        }
    }
    cout << Reset;
    return 0;
}
void returntologin()
{
    cout << Red << "\t\t\t\t\tReturning to login page..." << endl;
    cout << endl;
    system("cls");
    main();
}