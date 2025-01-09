#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

class User {
    string username, password;

public:
    User() {}
    User(string username, string password) {
        this->username = username;
        this->password = password;
    }

    string getusername() { return this->username; }
    string getpassword() { return this->password; }

    void setusername(string username) { this->username = username; }
    void setpassword(string password) { this->password = password; }
};

class UserManager: public User {
    void saveUser(User &user) {
        string filename = "users.txt";
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << user.getusername() << " " << user.getpassword() << endl;
            file.close();
        } else {
            cout << "Unable to open file for writing!" << endl;
        }
    }

    bool loadUser(string username, string password) {
        ifstream file("users.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (line == (username + " " + password)) {
                    return true;
                }
            }
            file.close();
        } else {
            cout << "Unable to open file for reading!" << endl;
        }
        return false;
    }

public:
    void SignUp(User u) { saveUser(u); }

    bool Login(User u) {
        return loadUser(u.getusername(), u.getpassword());
    }

    void DisplayUsers() {
        ifstream file("users.txt");
        if (file.is_open()) {
            string line;
            cout << "------------------------" << endl;
            cout << "       USERS" << endl;
            cout << "------------------------" << endl;

            while (getline(file, line)) {
                int spacePos = line.find(" ");
                cout << line.substr(0, spacePos) << endl;
            }
            cout << "------------------------" << endl;
            file.close();
        } else {
            cout << "Unable to open file for reading!" << endl;
        }
    }
};

class Product {
protected:
    string prod;
    double price, rentalPrice;
    int quantity;

public:
    Product() {}
    Product(string prod, double price, double rentalPrice, int quantity) {
        this->prod = prod;
        this->price = price;
        this->rentalPrice = rentalPrice;
        this->quantity = quantity;
    }

    string getProd() { return this->prod; }
    virtual string getCategory() const = 0; // Pure virtual function
    double getPrice() { return this->price; }
    double getRentalPrice() { return this->rentalPrice; }
    int getQuantity() { return this->quantity; }

    void setProd(string prod) { this->prod = prod; }
    void setPrice(double price) { this->price = price; }
    void setRentalPrice(double rentalPrice) { this->rentalPrice = rentalPrice; }
    void setQuantity(int quantity) { this->quantity = quantity; }
};

class Loader : public Product {
public:
    Loader(string prod, double price, double rentalPrice, int quantity)
        : Product(prod, price, rentalPrice, quantity) {}

    string getCategory() const override { return "LOADER"; }
};

class Hauler : public Product {
public:
    Hauler(string prod, double price, double rentalPrice, int quantity)
        : Product(prod, price, rentalPrice, quantity) {}

    string getCategory() const override { return "HAULER"; }
};

class Excavator : public Product {
public:
    Excavator(string prod, double price, double rentalPrice, int quantity)
        : Product(prod, price, rentalPrice, quantity) {}

    string getCategory() const override { return "EXCAVATOR"; }
};

class OHT : public Product {
public:
    OHT(string prod, double price, double rentalPrice, int quantity)
        : Product(prod, price, rentalPrice, quantity) {}

    string getCategory() const override { return "OHT"; }
};


class Dozer : public Product {
public:
    Dozer(string prod, double price, double rentalPrice, int quantity)
        : Product(prod, price, rentalPrice, quantity) {}

    string getCategory() const override { return "DOZER"; }
};

class ProductManager {
    void updateProductFile(vector<Product*> &products) {
        ofstream file("products.txt");
        if (file.is_open()) {
            for (auto &p : products) {
                file << p->getProd() << " " << p->getCategory() << " " << p->getPrice() << " "
                     << p->getRentalPrice() << " " << p->getQuantity() << endl;
            }
            file.close();
        } else {
            cout << "Unable to open file for updating!" << endl;
        }
    }

    vector<Product*> loadProducts() {
        vector<Product*> products;
        ifstream file("products.txt");
        if (file.is_open()) {
            string prod, category;
            double price, rentalPrice;
            int quantity;
            while (file >> prod >> category >> price >> rentalPrice >> quantity) {
                if (category == "LOADER") {
                    products.push_back(new Loader(prod, price, rentalPrice, quantity));
                } 
                else if (category == "HAULER") {
                    products.push_back(new Hauler(prod, price, rentalPrice, quantity));
                } 
                else if (category == "EXCAVATOR") {
                    products.push_back(new Excavator(prod, price, rentalPrice, quantity));
                }
                else if (category == "OHT") {
                    products.push_back(new OHT(prod, price, rentalPrice, quantity));
                }
                else if (category == "DOZER") {
                    products.push_back(new OHT(prod, price, rentalPrice, quantity));
                }
            }
            file.close();
        } else {
            cout << "Unable to open file for reading!" << endl;
        }
        return products;
    }

    void logTransaction(const string &transactionDetails, const string &filename) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << transactionDetails << endl;
            file.close();
        } else {
            cout << "Unable to log transaction!" << endl;
        }
    }

public:
    void saveProduct(Product *product) {
        ofstream file("products.txt", ios::app);
        if (file.is_open()) {
            file << product->getProd() << " " << product->getCategory() << " " << product->getPrice() << " "
                 << product->getRentalPrice() << " " << product->getQuantity() << endl;
            file.close();
        } else {
            cout << "Unable to open file for writing!" << endl;
        }
    }

    void ViewProducts() {
        auto products = loadProducts();
        cout << "------------------------------------------------------------------------" << endl;
        cout << "| Name           | Category       | Price   | Rental Price | Quantity |" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        for (auto &p : products) {
            cout << "| " << setw(15) << left << p->getProd()
                 << "| " << setw(15) << left << p->getCategory()
                 << "| " << setw(8) << right << p->getPrice()
                 << "| " << setw(13) << right << p->getRentalPrice()
                 << "| " << setw(8) << right << p->getQuantity() << " |" << endl;
        }
        cout << "-------------------------------------------------------------------------" << endl;
    }

    void SearchProduct(int ch, string query) {
        auto products = loadProducts();
        bool found = false;
        cout << "------------------------------------------------------------------------" << endl;
        cout << "| Name           | Category       | Price   | Rental Price | Quantity |" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        if (ch == 1) {
            for (auto &p : products) {
                if (p->getProd().find(query) != string::npos) {
                    found = true;
                    cout << "| " << setw(15) << left << p->getProd() << "| " << setw(15) << left << p->getCategory()
                         << "| " << setw(8) << right << p->getPrice()
                         << "| " << setw(13) << right << p->getRentalPrice()
                         << "| " << setw(8) << right << p->getQuantity() << " |" << endl;
                }
            }
            if (!found) {
                cout << "Product not found!" << endl;
            }
        } else if (ch == 2) {
            for (auto &p : products) {
                if (p->getCategory().find(query) != string::npos) {
                    found = true;
                    cout << "| " << setw(15) << left << p->getProd()
                         << "| " << setw(15) << left << p->getCategory()
                         << "| " << setw(8) << right << p->getPrice()
                         << "| " << setw(13) << right << p->getRentalPrice()
                         << "| " << setw(8) << right << p->getQuantity() << " |" << endl;
                }
            }
            if (!found) {
                cout << "Product not found!" << endl;
            }
        }
        cout << "------------------------------------------------------------------------" << endl;
    }

    void BuyProduct(string prodName, int quantity, string username) {
        auto products = loadProducts();
        bool updated = false;
        ViewProducts();
        for (auto &p : products) {
            if (p->getProd() == prodName && p->getQuantity() >= quantity) {
                p->setQuantity(p->getQuantity() - quantity);
                logTransaction(username + " - " + prodName + " - " + to_string(quantity), "buy.txt");
                cout << "Purchased " << quantity << " units of " << prodName << "." << endl;
                updated = true;
                break;
            }
        }
        if (!updated) {
            cout << "Insufficient stock or product not found!" << endl;
        }
        updateProductFile(products);
    }

    void RentProduct(string prodName, int days, int quantity, string username) {
        auto products = loadProducts();
        bool found = false;
        ViewProducts();
        for (auto &p : products) {
            if (p->getProd() == prodName && p->getQuantity() >= quantity) {
                p->setQuantity(p->getQuantity() - quantity);
                logTransaction(username + " - " + prodName + " - " + to_string(quantity) + " - " + to_string(days), "rent.txt");
                cout << "Rented " << prodName << " for " << days << " days at "
                     << (p->getRentalPrice() * days) << "." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Product not found for rent!" << endl;
        }
    }

    void ViewTransactions(const string &filename) {
        ifstream file(filename);
        if (file.is_open()) {
            cout << "Transaction History:\n";
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "No transactions recorded yet!" << endl;
        }
    }

    double getprice(string prodName, int quantity) {
        auto products = loadProducts();
        for (auto &p : products) {
            if (p->getProd() == prodName) {
                return p->getPrice() * quantity;
            }
        }
        return 0;
    }

    double getrentedprice(string prodName, int quantity) {
        auto products = loadProducts();
        for (auto &p : products) {
            if (p->getProd() == prodName) {
                return p->getRentalPrice() * quantity;
            }
        }
        return 0;
    }
};

int main() {
    int choice = 1;
    cout << "\n\nWelcome To Caterpillar Marketplace\n";
    cout << "1. User\n2. Admin\n3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        User u;
        UserManager um;
        ProductManager pm;
        bool flag = false;
        bool login = false;
        cout << "1. Login\n2. Signup\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            while (!login) {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                u = User(username, password);
                if (um.Login(u)) {
                    cout << "Logged in successfully\n";

                    login = true;
                    int userChoice;
                    double amount = 0;
                    do {
                        cout << "1. View Products\n2. Search Product\n3. Buy Product\n4. Rent Product\n5. Exit\n";
                        cout << "Enter your choice: ";
                        cin >> userChoice;
                        switch (userChoice) {
                        case 1:
                            pm.ViewProducts();
                            break;
                        case 2: {
                            string query;
                            int ch;
                            do {
                                cout << "1. Search By Product Name\n2. Search by Product Category\n3. Exit\n";
                                cout << "Enter your choice: ";
                                cin >> ch;
                                switch (ch) {
                                case 1:
                                    cout << "Enter product name to search: ";
                                    cin >> query;
                                    pm.SearchProduct(1, query);
                                    break;
                                case 2:
                                    cout << "Enter product name to search: ";
                                    cin >> query;
                                    pm.SearchProduct(2, query);
                                    break;
                                case 3:
                                    break;
                                }
                            } while (ch != 3);
                            break;
                        }
                        case 3: {
                            flag = true;
                            string prodName;
                            int quantity;
                            cout << "Enter product name to buy: ";
                            cin >> prodName;
                            cout << "Enter quantity: ";
                            cin >> quantity;
                            pm.BuyProduct(prodName, quantity, username);
                            amount += pm.getprice(prodName, quantity);
                            break;
                        }
                        case 4: {
                            flag = true;
                            string prodName;
                            int days, quantity;
                            cout << "Enter product name to rent: ";
                            cin >> prodName;
                            cout << "Enter quantity: ";
                            cin >> quantity;
                            cout << "Enter rental days: ";
                            cin >> days;
                            pm.RentProduct(prodName, days, quantity, username);
                            amount += pm.getrentedprice(prodName, quantity) * days;
                            break;
                        }
                        case 5:
                            if (flag) {
                                cout << "*************************************" << endl;
                                cout << "  Total amount to be paid: " << amount << endl;
                                cout << "*************************************" << endl;
                                cout << "Request Has Been Sent to Dealer..!!\n";
                                cout << "Thank You For Using CATERPILLAR SERVICES!!!\n";
                                cout << "Exiting user panel...\n";
                            } else {
                                cout << "Contact Your Nearest Dealer For Further Details\n";
                                cout << "Thank You For Using CATERPILLAR SERVICES!!!\n";
                                cout << "Exiting user panel...\n";
                            }
                            break;
                        default:
                            cout << "Invalid choice!\n";
                        }
                    } while (userChoice != 5);
                } else {
                    cout << "Invalid credentials. Try again.\n";
                }
            }
        } else if (choice == 2) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            u = User(username, password);
            um.SignUp(u);
            cout << "Account created successfully.\n";
        }
        break;
    }
    case 2: {
        string adminUsername, adminPassword;
        cout << "Enter User Name";
        cin >> adminUsername;
        cout << "Enter admin password: ";
        cin >> adminPassword;
        bool adminLogin = false;
        while (!adminLogin) {
            if (adminUsername == "admin" && adminPassword == "admin") {
                adminLogin = true;
            } else {
                cout << "Invalid Credentials\n";
                break;
            }
        }
        if (adminLogin) {
            ProductManager pm;
            UserManager um;
            int adminChoice;
            do {
                cout << "Admin Panel\n";
                cout << "1. Add Product\n2. View Products\n3. View Users\n4. View Buy Transactions\n5. View Rent Transactions\n6. Exit\n";
                cout << "Enter your choice: ";
                cin >> adminChoice;
                switch (adminChoice) {
                case 1: {
                    string prod, category;
                    double price, rentalPrice;
                    int quantity;
                    cout << "Enter product name: ";
                    cin >> prod;
                    cout << "Enter category: ";
                    cin >> category;
                    cout << "Enter price: ";
                    cin >> price;
                    cout << "Enter rental price: ";
                    cin >> rentalPrice;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    for (auto &c : category) {
                        c = toupper(c);
                    }
                    Product *product;
                    if (category == "LOADER") {
                        product = new Loader(prod, price, rentalPrice, quantity);
                    } 
                    else if (category == "HAULER") {
                        product = new Hauler(prod, price, rentalPrice, quantity);
                    } 
                    else if (category == "EXCAVATOR") {
                        product = new Excavator(prod, price, rentalPrice, quantity);
                    } 
                    else if (category == "OHT") {
                        product = new OHT(prod, price, rentalPrice, quantity);
                    } 
                    else if (category == "DOZER") {
                        product = new Dozer(prod, price, rentalPrice, quantity);
                    } 
                    else {
                        cout << "Invalid category!" << endl;
                        break;
                    }
                    pm.saveProduct(product);
                    cout << "Product added successfully.\n";
                    break;
                }
                case 2:
                    pm.ViewProducts();
                    break;
                case 3:
                    um.DisplayUsers();
                    break;
                case 4:
                    pm.ViewTransactions("buy.txt");
                    break;
                case 5:
                    pm.ViewTransactions("rent.txt");
                    break;
                case 6:
                    cout << "Exiting admin panel...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
            } while (adminChoice != 6);
        }
        break;
    }
    case 3:
        cout << "Exiting program.\n";
        break;
    default:
        cout << "Invalid choice!\n";
    }
    return 0;
}