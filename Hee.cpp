#include <iostream>
#include <fstream>
#include <string>
//nah id changed
using namespace std;

// Base class for menu items
class MenuItem {
protected:
    string name;
    double price;
public:
    MenuItem() {}
    MenuItem(string _name, double _price) : name(_name), price(_price) {}
    virtual void display() {
        cout << name << " - $" << price << endl;
    }
    virtual double getPrice() {
        return price;
    }
    virtual string getName() {
        return name;
    }
};

// Derived class for specific menu items, inheriting from MenuItem
class FoodItem : public MenuItem {
    string type;
public:
    FoodItem(string _name, double _price, string _type) : MenuItem(_name, _price), type(_type) {}
    void display() override {
        cout << type << " - " << name << " - $" << price << endl;
    }
};

// Derived class for specific menu items, inheriting from MenuItem
class DrinkItem : public MenuItem {
public:
    DrinkItem(string _name, double _price) : MenuItem(_name, _price) {}
};

// Class for managing the menu
class Menu {
private:
    MenuItem* items[100];
    int count;
public:
    Menu() : count(0) {}
    void AddMenuItem(MenuItem* item) {
        items[count++] = item;
    }
    void PrintMenu() {
        cout << "Menu:" << endl;
        for (int i = 0; i < count; ++i) {
            items[i]->display();
        }
    }
    MenuItem* GetMenuItemByName(string name) {
        for (int i = 0; i < count; ++i) {
            if (items[i]->getName() == name) {
                return items[i];
            }
        }
        return nullptr;
    }
};

// Class representing an order
class Order {
private:
    MenuItem* items[100];
    int count;
public:
    Order() : count(0) {}
    void PlaceOrder(MenuItem* item) {
        items[count++] = item;
    }
    double CalculateBill() {
        double total = 0;
        for (int i = 0; i < count; ++i) {
            total += items[i]->getPrice();
        }
        return total;
    }
};

// Class representing a restaurant manager
class RestaurantManager {
public:
    static void PrintReceipt(Order order) {
        cout << "Receipt:" << endl;
        double total = order.CalculateBill();
        cout << "Total: $" << total << endl;
    }
};

int main() {
    // Creating menu items
    FoodItem pizza("Pizza", 12.99, "Italian");
    FoodItem burger("Burger", 8.99, "American");
    DrinkItem coke("Coke", 1.99);
    DrinkItem coffee("Coffee", 2.49);

    // Creating the menu
    Menu menu;
    menu.AddMenuItem(&pizza);
    menu.AddMenuItem(&burger);
    menu.AddMenuItem(&coke);
    menu.AddMenuItem(&coffee);

    // Printing the menu
    menu.PrintMenu();

    // Creating an order
    Order order;
    order.PlaceOrder(&pizza);
    order.PlaceOrder(&coke);

    // Printing the receipt
    RestaurantManager::PrintReceipt(order);

    return 0;
}
