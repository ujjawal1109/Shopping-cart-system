#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ---------------- Product Class ----------------
class Product {
private:
    int id;
    string name;
    double price;

public:
    Product(int pid, string pname, double pprice) {
        id = pid;
        name = pname;
        price = pprice;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }

    void displayProduct() const {
        cout << "ID: " << id << " | " << name << " | Price: ₹" << price << endl;
    }
};

// ---------------- CartItem Class ----------------
class CartItem {
private:
    Product product;
    int quantity;

public:
    CartItem(Product p, int q) : product(p), quantity(q) {}

    double getTotalPrice() const {
        return product.getPrice() * quantity;
    }

    void displayCartItem() const {
        cout << product.getName() << " x" << quantity 
             << " = ₹" << getTotalPrice() << endl;
    }
};

// ---------------- ShoppingCart Class ----------------
class ShoppingCart {
private:
    vector<CartItem> items;

public:
    void addItem(Product product, int qty) {
        items.push_back(CartItem(product, qty));
        cout << product.getName() << " added to cart." << endl;
    }

    void viewCart() const {
        cout << "\n--- Your Cart ---" << endl;
        if (items.empty()) {
            cout << "Cart is empty!" << endl;
            return;
        }
        double total = 0;
        for (const auto &item : items) {
            item.displayCartItem();
            total += item.getTotalPrice();
        }
        cout << "-----------------\nTotal: ₹" << total << endl;
    }
};

// ---------------- User Class ----------------
class User {
private:
    string name;
    ShoppingCart cart;

public:
    User(string uname) {
        name = uname;
    }

    void shop(vector<Product> &products) {
        int choice, qty;
        while (true) {
            cout << "\n1. View Products\n2. Add to Cart\n3. View Cart\n4. Checkout & Exit\nChoose: ";
            cin >> choice;
            if (choice == 1) {
                cout << "\n--- Product List ---" << endl;
                for (auto &p : products) {
                    p.displayProduct();
                }
            } else if (choice == 2) {
                int pid;
                cout << "Enter Product ID: ";
                cin >> pid;
                cout << "Enter Quantity: ";
                cin >> qty;

                bool found = false;
                for (auto &p : products) {
                    if (p.getId() == pid) {
                        cart.addItem(p, qty);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Invalid Product ID!" << endl;
            } else if (choice == 3) {
                cart.viewCart();
            } else if (choice == 4) {
                cout << "\nThank you for shopping with us, " << name << "!" << endl;
                cart.viewCart();
                break;
            } else {
                cout << "Invalid choice!" << endl;
            }
        }
    }
};

// ---------------- Main Function ----------------
int main() {
    vector<Product> products = {
        Product(1, "Laptop", 55000),
        Product(2, "Smartphone", 25000),
        Product(3, "Headphones", 2000),
        Product(4, "Smartwatch", 5000)
    };

    string username;
    cout << "Enter your name: ";
    getline(cin, username);

    User user(username);
    user.shop(products);

    return 0;
}
