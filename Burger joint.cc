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
#include <bits/stdc++.h>
#include <filesystem>

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
        cout << "You have completed the order.\n\n";
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

int max_line(int num){
    fstream file;
    string data;
    int maxline = 0;

    v.clear();

    if (num == 0)
        file.open("Order.txt", ios_base::in);
    else if (num ==1)
        file.open("Pending.txt", ios_base::in);

    while (getline(file, data)){
        v.push_back(data);
        maxline++;
    }

    return maxline;
}


void delete_record(int n, int num)
{
    ifstream file;
    ofstream temp;
    if (num == 0)
        file.open("Order.txt", ios_base::in);
    else if (num ==1)
        file.open("Pending.txt", ios_base::in);
    temp.open("Temp.txt", ios_base::app);

    string data = "";
    int line = 1, max = max_line(num), no = 0;

    while (getline(file, data,',')){
        while (no != 1){
            if (stoi(data) == n)
                no = 1;
            else {
                line = 9999;
                no = 1;
            }
        }
        if (data == "\n")
            break;
        else if (data.find('\n') != string::npos){
            ++line;
            if (n == stoi(data))
                line = n;
            if (line != n){
                temp << data << ',';
            }
        }
        else if (line != n){
            temp << data << ',';
        }
        else if (n == max){
            temp << "\n";
            break;
        }
    }
  
    temp.close();
    file.close();
    if (num == 0){
        remove("Order.txt");
        rename("Temp.txt", "Order.txt");
        delete_record(n, 1);
    }
    else if (num ==1){
        remove("Pending.txt");
        rename("Temp.txt", "Pending.txt");
    }
}

fstream& GotoLine(fstream& file, unsigned int num){
    file.seekg(ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(numeric_limits < streamsize > ::max(), '\n');
    }
    return file;
}



int main() {
    int choice, order, qty, function, payment, ID, line, num, no;
    string data, elem, s[10]; 
    bool check;

	cout << "=== Welcome to the burger joint drive thru application! ===\n\n";

    cout << "\t\t\t Menu\n";
    cout << "1. Order\n" << "2. Payment\n" << "3. Exit\n";
    cout << "Enter your choice in numbers: ";
    cin >> choice;

    switch (choice){
        case 1:
            cout << "1. New Order\n" << "2. View Orders\n" << "3. Back\n";
            cout << "Enter your choice in numbers: ";
            cin >> choice;
            if (choice == 1){
                v.clear();
                cout << "Enter the order details (Chicken burger id = 1, Beef burger id = 2, Coca cola id = 3, Pepsi id = 4):\n";
                cout << "Enter 0 to complete the order";

                check = false;
                while (order != 0 || qty != 0){
                    cout << "\nFood/Drinks: ";
                    cin >> order;
                    if (order == 0 || order < 0 || order > 4){
                        ordering(order, 0);
                        break;
                    }
                    cout << "Quantity: ";
                    cin >> qty;
                    if (qty == 0){
                        ordering(0, qty);
                        break;
                    }
                    else if (qty > 0)
                        check = true;
                    ordering(order, qty);
                }
                if (check == true){
                    writing1("Pending.txt");
                    writing1("Order.txt");
                }
                main();
            }
            else if (choice == 2)
            {
                v.clear();
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

                cout << "\nFunctions:\n" << "1. Search Order\n" << "2. Sort Orders\n" << "3. Cancel Order\n" << "4. Back\n";
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
                        cout << "\n\nOrder ID,\tDate,\t\tTime,\t\tAmount\n";
                        file.open("Order.txt", ios_base::in);
                        data = "", num = 0, check = false;

                        while (getline(file, data, ','))
                        {
                            v.push_back(data);
                            if (data.find('\n') != string::npos){
                                num++;
                            }
                        }
                        file.close();

                        while (num != 0){
                            line = 1;
                            for(itr=v.begin();itr!=v.end();itr++){
                                try{
                                    data = *itr;
                                    if (*itr == "Chicken burger" || *itr == "Beef burger" || *itr == "Coca cola" || *itr == "Pepsi"){
                                        advance(itr, 1);
                                    }
                                    else if (*itr == "total" && line == num){
                                        ++itr;
                                        cout << '\t' << fixed << setprecision(2) << stod(*itr) << '\t';
                                    }
                                    else if (data.find('\n') != string::npos){
                                        ++line;
                                        if (line == num && check == true)
                                            cout << setfill('0') << setw(4) << *itr << '\t';
                                        else if (line > num && check == true){
                                            --num;
                                            break;
                                        }
                                        else if (line == num && check == false){
                                            cout << setfill('0') << setw(4) << line << "\t\t";
                                            check = true;
                                        }
                                        
                                    }
                                    else if (!isnan(stoi(*itr)) && line == num)
                                    {
                                        if (stoi(*itr) == 1 && stoi(*itr) == num)
                                            cout << endl;
                                        else if (stoi(*itr) == 1){
                                            num--;
                                            break;
                                        }
                                        cout << setfill('0') << setw(4) << *itr << '\t';
                                    }
                                }
                                catch (exception e){}
                            }   
                        }
                        cout << endl << endl << endl;
                        main();
                    }
                        
                    case 3:
                        cout << "Enter the order ID to delete: ";
                        cin >> ID;
                        delete_record(ID, 0);
                        main();

                    case 4:
                        main();
                }

            }
            else if (choice == 3){
                main();
            }
            
            else
                cout << "You entered an invalid number. Please try again";
            break;
        case 2:
            cout << "\n\nOrder ID,\tDate,\t\tTime,\t\tAmount\n";
            file.open("Pending.txt", ios_base::in);
            
            v.clear();

            while (getline(file, data, ',')){
                v.push_back(data);
            }
            for(itr=v.begin();itr!=v.end();itr++){
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
            
            cout << "\n\nSelect order for payment in numbers: ";
            cin >> payment;

            file.open("Pending.txt", ios_base::in);
            line = 1, no = 0, check = false;
            v.clear();
            
            while (getline(file, data, ',')){
                while (no != 1){
                    if (stoi(data) == payment)
                        no = 1;
                    else {
                        line = 9999;
                        no = 1;
                   }
                }
                if (data.find('\n') != string::npos){
                    line++;
                    if (payment == stoi(data))
                        line = payment;
                    if (line == payment){
                        v.push_back(data);
                    }
                }
                else if (line == payment){
                    v.push_back(data);
                }
            }
            file.close();

            for(itr=v.begin();itr!=v.end();itr++){
                if (*itr == "Chicken burger" || *itr == "Beef burger" || *itr == "Coca cola" || *itr == "Pepsi"){}
                else if (*itr == "total"){
                    ++itr;
                    s[distance(v.begin(), itr)] = *itr;
                }
                else if (*itr == "\n"){}
                else if (!isnan(stod(*itr))){
                    s[distance(v.begin(), itr)] = *itr;
                }
            }   

            try{
                stod(s[4]);
            }
            catch(const std::exception& e)
            {
                cout << "The order id you have entered does not exist!\n\n";
                check = true;
            }
            if (check == false){
                cout << "\n\t\t                       Burger Joint - Customer Invoice                  "<< endl;
                cout << "\t\t	///////////////////////////////////////////////////////////"<< endl;
                cout << "\t\t	| Date :" << "-------------------------|" << s[1] << endl;
                cout << "\t\t	| Time :" << "-------------------------|" << setfill('0') << setw(2) << ltm->tm_hour << setfill('0') << setw(2) << ltm->tm_min << endl;
                cout << "\t\t	| Invoice No. :" << "------------------|" << setfill('0') << setw(4) << payment << " |"<< endl;
                cout << "\t\t	 ________________________________________________________"<< endl;
                cout <<"\n";
                cout << "\t\t	| Total Payment Amount is :"<<"------|RM" << fixed << setprecision(2) << stod(s[4]) << " |" << endl;
                cout << "\t\t	 ________________________________________________________"<< endl;
                cout << "\t\t	 # This is a computer generated invoce and it does not"<< endl;
                cout << "\t\t	 require an authorised signture #"<< endl<< endl;         
                cout << endl << endl;
            }

            delete_record(payment, 1);
            main();
        case 3:
            exit(3);
        default:
            cout << "You have entered an invalid number. Please try again.";
            main();
            break;
    }
}