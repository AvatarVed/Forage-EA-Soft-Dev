#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

class Item {
private:
    std::string name;
    int quantity;
    float price;

public:
    Item(std::string name, int quantity, float price)
        : name(std::move(name)), quantity(quantity), price(price) {}

    std::string get_name() const { return name; }
    int get_quantity() const { return quantity; }
    void set_quantity(int new_quantity) { quantity = new_quantity; }
    float get_price() const { return price; }
};

class Inventory {
private:
    std::unordered_map<std::string, std::unique_ptr<Item>> items;
    float total_money;

    static void display_data(const Item &item) {
        std::cout << "Item name: " << item.get_name()
                  << "\nQuantity: " << item.get_quantity()
                  << "\nPrice: " << item.get_price() << "\n";
    }

public:
    Inventory() : total_money(0) {}

    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cin.ignore();
        std::cout << "Enter item name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;

        if (items.find(name) != items.end()) {
            items[name]->set_quantity(items[name]->get_quantity() + quantity);
        } else {
            items[name] = std::make_unique<Item>(name, quantity, price);
        }
    }

    void sell_item() {
        std::string item_to_check;
        std::cin.ignore();
        std::cout << "Enter item name: ";
        std::cin >> item_to_check;

        auto it = items.find(item_to_check);
        if (it != items.end()) {
            remove_item(it->second);
        } else {
            std::cout << "This item is not in your inventory.\n";
        }
    }

    void remove_item(std::unique_ptr<Item> &item) {
        int input_quantity;
        std::cout << "Enter number of items to sell: ";
        std::cin >> input_quantity;

        int quantity = item->get_quantity();
        if (input_quantity <= quantity) {
            float price = item->get_price();
            float money_earned = price * input_quantity;
            total_money += money_earned;

            item->set_quantity(quantity - input_quantity);
            std::cout << "Items sold\nMoney received: " << money_earned << "\n";

            // Remove item if quantity reaches zero
            if (item->get_quantity() == 0) {
                items.erase(item->get_name());
                std::cout << "Item " << item->get_name() << " removed from inventory.\n";
            }
        } else {
            std::cout << "Cannot sell more items than available.\n";
        }
    }

    void list_items() const {
        if (items.empty()) {
            std::cout << "Inventory empty.\n";
            return;
        }

        for (const auto &pair : items) {
            display_data(*pair.second);
            std::cout << "\n";
        }
    }
};

int main() {
    int choice;
    Inventory inventory;

    do {
        std::cout << "\n1. Add Item\n2. Sell Item\n3. List Items\n4. Exit\nChoose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1: inventory.add_item(); break;
            case 2: inventory.sell_item(); break;
            case 3: inventory.list_items(); break;
            case 4: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid option. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
