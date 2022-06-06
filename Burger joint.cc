#include <iostream>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

vector<string> v;
time_t now = time(0);
tm *ltm = localtime(&now);

void calculating(){

}

void finding(string elem, int qty){
    vector<string>::iterator itr = find(v.begin(), v.end(), elem);
    if (itr != v.end()){
        v[distance(v.begin(), itr) + 1] = to_string(stoi(v[distance(v.begin(), itr) + 1]) + qty);
    }
    else {
        v.push_back(elem);
        v.push_back(to_string(qty));
    }
}

void ordering(int ord, int qty){
    string elem;

    if (ord == 0 || qty == 0){
        return;
    }
    else if (ord == 1){
        elem = "Chicken burger";
        finding(elem, qty);
    }
    else if (ord == 2)
    {
        elem = "Beef burger";
        finding(elem, qty);
    }
    else if (ord == 3)
    {
        elem = "Coca cola";
        finding(elem, qty);
    }
    else if (ord == 4)
    {
        elem = "Pepsi";
        finding(elem, qty);
    }
    else
    {
        cout <<"\nYou have entered an invalid number please try again";
        cout << "\nFood/Drinks: ";
        cin >> ord;
        cout << "\nQuantity: ";
        cin >> qty;
        ordering(ord, qty);
    }
}

int main() {
    int choice, order, qty, function, payment;

	cout << "=== Welcome to the burger joint drive thru application! ===\n\n";

    cout << "\t\t\t Menu\n";
    cout << "1. Order\n" << "2. Payment\n" << "3. Exit\n";
    cout << "Enter your choice in numbers: ";
    cin >> choice;

    switch (choice){
        case 1:
            cout << "1. New Order\n" << "2. View Orders\n";
            cout << "Enter your choice in numbers: ";
            cin >> choice;
            if (choice == 1){
                cout << "Enter the order details (Chicken burger id = 1, Beef burger id = 2, Coca cola id = 3, Pepsi id = 4):\n";
                
                while (order != 0){
                    cout << "\nFood/Drinks: ";
                    cin >> order;
                    cout << "\nQuantity: ";
                    cin >> qty;
                    cout << "Enter 0 to complete your order";
                    
                    ordering(order, qty);
                }

                fstream file;
                file.open("Order.txt",ios_base::out);
                
                vector<string>::iterator itr;
                    
                file << 1900 + ltm->tm_year << '/' << 1 + ltm->tm_mon << '/' << ltm->tm_mday << ", ";
                file << ltm->tm_hour << ":" << setfill('0') << setw(2) <<ltm->tm_min << ", ";

                for(itr=v.begin();itr!=v.end();itr++)
                {
                    file << *itr << ", ";
                }
            
                file.close();
                cout << "You have successfully completed your order.\n";
            }
            else if (choice == 2)
            {
                cout << "\n\nOrder ID,\tDate,\tTime,\tAmount\n";
                
                ifstream file("Order.txt");
                string data = "";
                int id = 1;
                while (getline(file, data))
                {
                    cout << setfill('0') << setw(4) << id << "\t";
                    cout << data;
                    id++;
                }
                file.close();

                cout << "\nFunctions:\n" << "1. Search Order\n" << "2. Sort Orders\n" << "3. Cancel Order\n";
                cout << "Enter the function in numbers: ";
                cin >> function;

                switch (function){
                    case 1:

                        //insert search algorithm
                    
                        break;
                    case 2:

                        //insert sort algorithm

                        break;
                    case 3:

                        //insert cancel algorithm

                        break;
                }

            }
            else
                cout << "You entered an invalid number. Please try again";
            break;
        case 2:
            cout << "Order ID, Time, Date, Amount";
                
                //Need to include a function to call the stored data

                cout << "Select order for payment in numbers: ";
                cin >> payment;

                //include function to search order 
                //and then another function to delete order
                //then a function to display order details in the form of a receipt

            break;
        case 3:
            exit(3);
        default:
            cout << "You have entered an invalid number. Please try again.";
            main();
            break;
    }
}
