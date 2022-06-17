#include <iostream>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <limits>
#include <cstring>

using namespace std;

vector<string> v;
time_t now = time(0);
tm *ltm = localtime(&now);
fstream file;
fstream temp;
vector<string>::iterator itr;

void writing(string elem, int qty){
    vector<string>::iterator itr = find(v.begin(), v.end(), elem);
    if (itr != v.end()){
        v[distance(v.begin(), itr) + 1] = to_string(stoi(v[distance(v.begin(), itr) + 1]) + qty);
    }
    else {
        v.push_back(elem);
        v.push_back(to_string(qty));
    }
}

void writing1(string filename){
    file.open("Order.txt",ios_base::in);
    string data = "";
    int line = 1;
    while (getline(file, data,',')){
        if (data.find('\n') != string::npos){
            line++;
        }
    }
    file.close();

    file.open(filename,ios_base::app);
    file << setfill('0') << setw(4) << line;
    file << "\t," << 1900 + ltm->tm_year << '/' << 1 + ltm->tm_mon << '/' << ltm->tm_mday << ',';
    file << setfill('0') << setw(2) << ltm->tm_hour << setfill('0') << setw(2) << ltm->tm_min << ',';

    for(itr=v.begin();itr!=v.end();itr++){
        file << *itr << ',';
    }
    file << endl;
    file.close();
}

void cal_total(string elem, int qty, double price){
    vector<string>::iterator itr = find(v.begin(), v.end(), elem);
    if (itr == v.end()){
        v.push_back("total");
        v.push_back("0");
    }
    itr = find(v.begin(), v.end(), elem);
    v[distance(v.begin(), itr) + 1] = to_string(stoi(v[distance(v.begin(), itr) + 1]) + (qty * price));
    
}

void ordering(int ord, int qty){
    string elem;
    double price;

    if (ord == 0 || qty == 0){
        return;
    }
    else if (ord == 1){
        price = 5.00;
        elem = "Chicken burger";
        cal_total("total", qty, price);
        writing(elem, qty);
    }
    else if (ord == 2)
    {
        price = 5.00;
        elem = "Beef burger";
        cal_total("total", qty, price);
        writing(elem, qty);
    }
    else if (ord == 3)
    {
        price = 2.50;
        elem = "Coca cola";
        cal_total("total", qty, price);
        writing(elem, qty);
    }
    else if (ord == 4)
    {
        price = 2.50;
        elem = "Pepsi";
        cal_total("total", qty, price);
        writing(elem, qty);
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

void delete_record(const char *a)
{
    file.open("Order.txt",ios::app);
    temp.open("temp.txt",ios::out);
    char data[25];
    char id[25];
    cin.ignore();
    while(!file.eof())
    {
        file.getline(id,25,',');
        file.getline(data,25,',');
        if(strcmp(id,a)==0){
            continue;
        }
        else{
            temp<< id<<' '<<data<<' ';
        }
    }
    temp.close();
    file.close();

    file.open("Order.txt",ios::out);
    temp.open("temp.txt",ios::in);
    while(!temp.eof())
    {
        temp.getline(id,25,',');
        temp.getline(data,25,',');
        //file<< id <<' '<<data<<' ';
    }
    temp.close();
    file.close();
    remove("temp.txt");
    cout<<"\n done !!! \n";
}

fstream& GotoLine(fstream& file, unsigned int num){
    file.seekg(ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(numeric_limits < streamsize > ::max(), '\n');
    }
    return file;
}



int main() {
    int choice, order, qty, function, payment, ID, line, num;
    string data, elem;

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
                    cout << "Enter 0 to complete the order";
                    
                    ordering(order, qty);
                }

                writing1("Pending.txt");
                writing1("Order.txt");
                
                cout << "\nYou have successfully completed your order.\n";
                main();
            }
            else if (choice == 2)
            {
                cout << "\n\nOrder ID,\tDate,\t\tTime,\t\tAmount\n";
                file.open("Order.txt");
                data = "";

                while (getline(file, data, ','))
                {
                    v.push_back(data);
                }
                

                for(itr=v.begin();itr!=v.end();itr++)
                {
                    if (*itr == "Chicken burger" || *itr == "Beef burger" || *itr == "Coca cola" || *itr == "Pepsi"){
                        advance(itr, 1);
                    }
                    else if (*itr == "total"){
                        ++itr;
                        cout << '\t' << fixed << setprecision(2) << stod(*itr) << '\t';
                    }
                    else if (*itr == "\n"){
                        break;   
                    }
                    else if (!isnan(stoi(*itr)))
                    {
                        cout << setfill('0') << setw(4) << *itr << '\t';
                    }
                } 
                file.close();

                cout << "\nFunctions:\n" << "1. Search Order\n" << "2. Sort Orders\n" << "3. Cancel Order\n";
                cout << "Enter the function in numbers: ";
                cin >> function;
                
                
                switch (function){
                    case 1:{
                        cout << "Enter the order ID: ";
                        cin >> ID;
                        cout << "\n\nOrder ID,\t\tDate,\t\t\tTime,\t\tAmount,\t\tOrder/Quantity";
                        data = "", line = 1, elem = "\n", num = 0;

                        v.clear();

                        file.open("Order.txt");
                        while (getline(file, data, ',')){
                            if (data.find('\n') != string::npos){
                                ++line;
                                if (line == ID){
                                    v.push_back(data);
                                }
                            }
                            else if (line == ID){
                                if (line == 1 || num == 0){
                                    v.push_back("\n");
                                    v.push_back(data);
                                    num++;
                                }
                                else{
                                    v.push_back(data);
                                }
                            }
                        }
                        
                        for(itr=v.begin();itr!=v.end();itr++)
                        {
                            if (*itr == "Chicken burger" || *itr == "Beef burger" || *itr == "Coca cola" || *itr == "Pepsi"){
                                cout << *itr << '/';
                                ++itr;
                                cout << *itr << ", ";
                            }
                            else if (*itr == "total"){
                                ++itr;
                                cout << fixed << setprecision(2) << stod(*itr) << "\t\t";
                            }
                            else if (*itr == "\n"){}
                            else if (!isnan(stod(*itr))){
                                cout << *itr << "\t\t";
                            }
                        }                        
                        file.close();
                        cout << endl << endl;
                        main();
                    }
                        
                    case 2:
                    {
                        ostream_iterator< string > output ( cout, "\n" );
                        while (getline(file,elem,'\n'))
                        {
                            v.push_back(elem);
                        }
                        file.close();
                        sort(v.begin(),v.end());

                        for ( unsigned int i = 0; i < v.size(); i++ )
                        {
                        cout << v[i] << endl;
                        }

                        cin.get();
                        break;
                    }
                        
                    case 3:
                        string id;
                        cout << "\nEnter the id to delete record : ";
                        cin >> id;
                        delete_record(id.c_str());
                        main();
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