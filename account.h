#ifndef account_H
#define account_H

using json = nlohmann::json;

class account {
protected:
    int balance{};
    std::string id;
    std::string name;
    std::string surname;

public:
    int getBalance() {
        return balance;
    }
    std::string getID() {
        return id;
    }
    std::string getName() {
        return name;
    }
    std::string getSurname() {
        return surname;
    }

    void CreateAccount(account& a);
    void UpdateAccount(account& a, const int& id_pos);
    account(std::string i, std::string n, std::string s, int b);
};

account::account(std::string i, std::string n, std::string s, int b)
{
    id = i;
    balance = b;
    name = n;
    surname = s;
}

void account::CreateAccount(account& a)
{
    json j_new;

    std::ifstream old_file("CustomerList.json");
    if (old_file.is_open())
    {
        try {
            old_file >> j_new;
        }
        catch (...) {
            std::cout << "Customer list initialized.\n";
            j_new["CustomerList"] = json::array({});
        }
    }
    else {
        std::cout << "Cannot open the file\n";
    }

    json j = json::object({ { "CustID","#" + a.getID() }, {"CustInfo", json::object({{"CustName",a.getName()},{"CustSurname",a.getSurname()},{"CustBalance",a.getBalance()}}) } });
    j_new["CustomerList"].push_back(j);

    std::ofstream new_file;
    new_file.open("CustomerList.json");
    if (new_file.is_open())
    {
        new_file << std::setw(4) << j_new << "\n";
        new_file.close();
    }
    else {
        std::cout << "Cannot open the file\n";
    }
}

void account::UpdateAccount(account& a, const int& id_pos)
{
    std::ifstream my_file("CustomerList.json");
    if (my_file.is_open())
    {
        json j;
        my_file >> j;
        my_file.close();

        std::string name_path = "/CustomerList/" + std::to_string(id_pos) + "/CustInfo/CustName";
        std::string surname_path = "/CustomerList/" + std::to_string(id_pos) + "/CustInfo/CustSurname";
        std::string balance_path = "/CustomerList/" + std::to_string(id_pos) + "/CustInfo/CustBalance";

        j.at(json::json_pointer(name_path)) = a.getName();
        j.at(json::json_pointer(surname_path)) = a.getSurname();
        j.at(json::json_pointer(balance_path)) = a.getBalance();

        std::ofstream updated_file;
        updated_file.open("CustomerList.json");
        if (updated_file.is_open())
        {
            updated_file << std::setw(4) << j << "\n";
            updated_file.close();
        }
        else {
            std::cout << "Cannot open the file\n";
        }

    }
    else {
        std::cout << "Cannot open the file\n";
    }
}

#endif
