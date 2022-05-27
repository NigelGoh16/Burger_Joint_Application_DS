#include <iostream>
#include <stdlib.h>

using namespace std;

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
                
                //In the while function need to include a function to store the data
                
                while (order != 0){
                    cout << "Food/Drinks: ";
                    cin >> order;
                    cout << "\nQuantity: ";
                    cin >> qty;
                    cout << "Enter 0 to complete your order";
                }
                cout << "You have successfully completed your order.\n";
            }
            else if (choice == 2)
            {
                cout << "Order ID, Time, Date, Amount";
                
                //Need to include a function to call the stored data

                cout << "Functions:\n" << "1. Search Order\n" << "2. Sort Orders\n" << "3. Cancel Order\n";
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
