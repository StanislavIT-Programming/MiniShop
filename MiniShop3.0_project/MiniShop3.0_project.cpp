#include <limits>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include <fstream>
using namespace std;

class Product
{
private:
    string name;
    double price;
    int quantity;

public:
    Product(string newName, double newPrice, int newQuantity)
    {
        name = newName;
        price = newPrice;
        quantity = newQuantity;
    }

    void print() const
    {
        cout << name << " | " << price << " | " << quantity << " | " << endl;
    }

    bool buy(int amount)
    {
        if (quantity < amount || amount < 1)
        {
            return false;
        }
        quantity = quantity - amount;
        return true;
    }

    bool restock(int amount)
    {
        if (amount < 1)
        {
            return false;
        }
        else
        {
            quantity = quantity+  amount;
            return true;
        }
    }

    string getName() const
    {
        return name;
    }

    double getPrice() const
    {
        return price;
    }

    int getQuantity() const
    {
        return quantity;
    }

};


int readInteger()
{
    int n1;
    cin >> n1;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter another number: ";
        cin >> n1;
    }
    return n1;
}

double readDouble()
{
    double n1;
    cin >> n1;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter another number: ";
        cin >> n1;
    }
    return n1;
}

void outputAllProducts(const vector<Product>& products)
{
    for (int i = 0; i < products.size(); i++)
    {
        cout << i + 1 << " | ";
        products[i].print();
    }
}

double buyProduct(vector<Product>& products)
{
    cout << "Enter index of product which you want to buy: ";
    int productNumber = readInteger();
    while (productNumber < 1 || productNumber>products.size())
    {
        cout << "We dont have this item, enter another index: ";
        productNumber = readInteger();
    }
    Product& chosen = products[productNumber - 1];
    chosen.print();

    if (chosen.getQuantity() == 0)
    {
        cout << "This item is out of stock!" << endl;
        cout << endl;
        return 0;
    }
    cout << "Which amount of this product do you want: ";
    int amount = readInteger();
    while (chosen.buy(amount)!=true)
    {
        cout << "We don't have this amount of this position, try another amount: ";
        amount = readInteger();
    }
    double boughtPrice = amount * chosen.getPrice();
    cout << "You bought " << amount << " quantity of " << chosen.getName() << endl;
    return boughtPrice;
}

void addProduct(vector<Product>& products)
{
    string newName;
    cout << "Enter which product you want to add: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newName);

    cout << "Enter this products price: ";
    double newPrice = readDouble();
    while (newPrice <= 0)
    {
        cout << "Price cant be negative or zero, try another: ";
        newPrice = readDouble();
    }

    cout << "Enter this products quantity: ";
    int newQuantity = readInteger();
    while (newQuantity <= 0)
    {
        cout << "Quantity cant be negative or zero, try another: ";
        newQuantity = readInteger();
    }

    Product newProduct{ newName, newPrice, newQuantity };
    products.push_back(newProduct);

    cout << newName << " added!" << endl;
}

double totalStockValue(const vector<Product>& products)
{
    double totalValue = 0;
    for (int i = 0; i < products.size(); i++)
    {
        totalValue = totalValue + products[i].getQuantity() * products[i].getPrice();
    }
    return totalValue;
}

bool deleteProduct(vector<Product>& products, int index)
{
    if (products.size() <= index - 1 || index < 1)
    {
        return false;
    }
    else
    {
        cout << products[index - 1].getName() << " was deleted!" << endl;
        products.erase(products.begin() + (index - 1));
        return true;
    }
}

string toLowerCase(string name)
{
    for (int i = 0; i < name.size(); i++)
    {
        name[i] = tolower(name[i]);
    }
    return name;
}

int findProduct(const vector<Product>& products, string name)
{
    name = toLowerCase(name);
    int i = 0;
    while (i < products.size())
    {
        if (name == toLowerCase(products[i].getName()))
        {
            return i;
        }
        else
        {
            i++;
        }
    }
    return -1;
}

void saveProducts(const vector<Product>& products) //запись в файл
{
    ofstream file("products.txt");
    if (!file.is_open())
    {
        cout << "Can not open file!" << endl;
        return;
    }
    for (const Product& item : products)
    {
        file << item.getName() << endl;
        file << item.getPrice() << " " << item.getQuantity() << endl;
    }
    file.close();
}

bool loadProducts(vector<Product>& products) //читаем и выводим с файла
{
    ifstream file("products.txt");
    if (!file.is_open())
    {
        cout << "Can not open file!" << endl;
        return false;
    }
    string name;
    double price;
    int quantity;
    while (getline(file, name))
    {
        file >> price;
        file >> quantity;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        Product newProduct{ name, price, quantity };
        products.push_back(newProduct);
    }
    file.close();
    return true;
}

void printMenu()
{
    cout << "If you want to see shops assortment - input one" << endl;
    cout << "If you want to buy item - input two" << endl;
    cout << "If you want to add item - input three" << endl;
    cout << "If you want know total stock value - input four" << endl;
    cout << "If you want to see your total spent - input five" << endl;
    cout << "If you want to delete product by its number - input six" << endl; //six
    cout << "If you want to find product by its name - input seven" << endl; //seven :)
    cout << "If you want to change product amount - input eight" << endl; //seven :)
    cout << "If you want to see menu - input nine" << endl;
    cout << "If you want to exit - input zero" << endl;
}

int main()
{
    Product milk("Milk", 0.8, 12);
    Product bread("Bread", 0.5, 16);
    Product eggs("Eggs", 2, 30);
    Product chicken("Chicken", 12.5, 5);

    vector<Product> products;
    if (loadProducts(products) == false)
    {
        products.push_back(milk);
        products.push_back(bread);
        products.push_back(eggs);
        products.push_back(chicken);
    }

    printMenu();
    int forSwitch = readInteger();

    double totalPrice = 0;

    cout << fixed << setprecision(2);
    while (forSwitch != 0)
    {
        switch (forSwitch)
        {
        case 1:
        {
            outputAllProducts(products);
        }
        break;
        case 2:
        {
            double boughtPrice = buyProduct(products);
            cout << "Price for this product is: " << boughtPrice << "$" << endl;
            totalPrice = totalPrice + boughtPrice;

        }
        break;
        case 3:
        {
            addProduct(products);
        }
        break;
        case 4:
        {
            double totalValue = totalStockValue(products);
            cout << "Total stock value is " << totalValue << endl;
        }
        break;
        case 5:

            cout << "Your total spent is: " << totalPrice << "$" << endl;

            break;
        case 6:
        {
            cout << "Enter products number: ";
            int deletedProduct = readInteger();
            if (deleteProduct(products, deletedProduct) == false)
            {
                cout << "Number of product is incorrect!" << endl;
            }
        }
        break;
        case 7:
        {
            string productToFind;
            cout << "Enter products name to find it: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, productToFind);
            int indexOfProduct = findProduct(products, productToFind);
            if (indexOfProduct == -1)
            {
                cout << "Shop doesnt have this product" << endl;
            }
            else
            {
                cout << indexOfProduct + 1 << " | ";
                products[indexOfProduct].print();
            }
        }
        break;
        case 8:
        {
            cout << "Enter products number to restock it: ";
            int productNumber  = readInteger();
            while (productNumber < 1 || productNumber>products.size())
            {
                cout << "We dont have this product, try another number: ";
                productNumber = readInteger();
            }
            cout << "Enter new amount of product: ";
            int newAmount;
            newAmount = readInteger();
            if (products[productNumber - 1].restock(newAmount))
            {
                cout << "Product amount was changed!" << endl;
                products[productNumber - 1].print();
            }
            else
            {
                cout << "You cant add negative or zero amount!" << endl;
            }
        }
        break;
        case 9:
        {
            printMenu();
        }
        break;
        default:
        {
            cout << "Number is wrong, enter another: " << endl;
        }
        break;
        }
        cout << "Enter another number for menu: ";
        forSwitch = readInteger();
    }
    saveProducts(products);
}


