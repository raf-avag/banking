#ifndef functions_H
#define functions_H

using json = nlohmann::json;

void make_transaction(const int& id1, const int& id2, const int& money)
{
    std::ifstream my_file("CustomerList.json");
    if (my_file.is_open())
    {
        
	json j;
        my_file >> j;
        my_file.close();

        std::string sender_path = "/CustomerList/" + std::to_string(id1) + "/CustInfo/CustBalance";
        std::string receiver_path = "/CustomerList/" + std::to_string(id2) + "/CustInfo/CustBalance";

        int sender_new_balance = j.at(json::json_pointer(sender_path));
        int receiver_new_balance = j.at(json::json_pointer(receiver_path));

	sender_new_balance += money;
	receiver_new_balance -= money;

        j.at(json::json_pointer(sender_path)) = sender_new_balance;
        j.at(json::json_pointer(receiver_path)) = receiver_new_balance;

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

bool account_exists(const std::string& id, int* id_pos)
{
    std::ifstream my_file("CustomerList.json");
    if (my_file.is_open())
    {

        json j;
        my_file >> j;
        my_file.close();

        auto const list = j.find("CustomerList");
        if (list == j.end())
        {
            std::cerr << "No data in the Database. Create an account first!\n";
            return false;
        }

        for (unsigned int i{}; i < list->size(); ++i)
        {
            if (j["CustomerList"][i]["CustID"].get<std::string>() == "#" + id)
            {
                std::cout << "Account found!\n";
                *id_pos = i;
                return true;
            }
        }
        std::cout << "Account doesn't exist.\n";
        return false;

    }
    else {
        std::cout << "Cannot open the file\n";
        return false;
    }
}

bool account_exists(const std::string& id)
{

    std::ifstream my_file("CustomerList.json");
    if (my_file.is_open())
    {

        json j;
        my_file >> j;
        my_file.close();

        auto const list = j.find("CustomerList");
        if (list == j.end())
        {
            std::cerr << "No data in the Database. Create an account first!\n";
            return false;
        }

        for (unsigned int i{}; i < list->size(); ++i)
        {
            if (j["CustomerList"][i]["CustID"].get<std::string>() == "#" + id)
            {
                std::cout << "Account found!\n";
                return true;
            }
        }

        std::cout << "Account doesn't exist.\n";
        return false;

    }
    else {
        std::cout << "Cannot open the file\n";
        return false;
    }
}

void print_account_list()
{
    std::ifstream my_file("CustomerList.json");
    if (my_file.is_open())
    {
        json j;
        my_file >> j;
        my_file.close();
        std::cout << "\n" << j.dump(4) << "\n";
    }
    else {
        std::cout << "Cannot open the file\n";
    }
}

void print_account(const std::string& id, const int& id_pos)
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

        std::cout << "Customer ID: #" << id << ";\n Name: " << j.at(json::json_pointer(name_path)) << ";\n Surname: " << j.at(json::json_pointer(surname_path)) << ";\n Balance: " << j.at(json::json_pointer(balance_path)) << "\n";
    }
    else
        std::cout << "Cannot open the file\n";
}

void delete_account(const std::string& id) {
    std::ifstream my_file("CustomerList.json");
    if (my_file.is_open())
    {
        json j;
        my_file >> j;
        my_file.close();

        std::string cust_id = "#" + id;

        std::vector<int> to_remove;

        for (auto& it : j["CustomerList"].items()) {
            if (it.value().at("CustID").get<std::string>() == cust_id)
                to_remove.push_back(stoi(it.key()));
        }
        std::sort(to_remove.rbegin(), to_remove.rend());

        for (int& it : to_remove)
            j["CustomerList"].erase(j["CustomerList"].begin() + it);

        std::cout << j.dump(4) << "\n";

        std::ofstream updated_file;
        updated_file.open("CustomerList.json");
        if (updated_file.is_open())
        {
            updated_file << std::setw(4) << j << "\n";
            updated_file.close();
            std::cout << "Account removed\n";
        }
        else {
            std::cout << "Cannot open the file\n";
        }
    }
    else {
        std::cout << "Cannot open the file\n";
    }
}

void change_key(json& object, const std::string& old_key, const std::string& new_key)
{
    try {
        json::iterator it = object.find(old_key);
        std::swap(object[new_key], it.value());
        object.erase(it);
    }
    catch (...) {
        std::cout << "Requested info not found in the list!";
    }
}

void input_int(int& s)
{
    int is_num = 0;
    int decimal_count = 0;
    int user_converted_num{};
    bool is_num_bool = 0;
    bool contains_spaces = false;

    do
    {
        std::string user_string_num;
        std::cin.clear();
        do {
            std::getline(std::cin, user_string_num);
        } while (!(user_string_num.size() > 0 && user_string_num.size() < 20));

        for (unsigned int i = 0; i < user_string_num.size(); i++)
        {
            if (isspace(user_string_num[i])) {
                contains_spaces = true;
                break;
            }
        }
        if (!(contains_spaces)) {
            if (user_string_num[0] == '-')
            {
                is_num++;
                if (user_string_num[1] == '0') // -0999 invalid
                {
                    is_num = 0;
                }
            }
            else
            {
                if ((user_string_num[0] == '0' && isdigit(user_string_num[1]))) // 0934939
                {
                    is_num = 0;
                }
                else
                {
                    for (unsigned int i = 0; i < user_string_num.size(); i++)
                    {
                        if (isdigit(user_string_num[i]))
                            is_num++;
                        if (user_string_num[i] == '.')
                            decimal_count++;
                    }
                    if (decimal_count > 0) // 66.7 // 8..9.9.9..9.9
                    {
                        is_num = 0;
                    }
                }
            }
        }

        if (is_num == user_string_num.size() && contains_spaces == false)
        {
            std::stringstream str_stream_object(user_string_num);
            str_stream_object >> user_converted_num;

            is_num_bool = 1;
        }
        else
        {
            std::cout << std::endl
                << "Number must NOT contain spaces.\n"
                << "Number must NOT contain letters.\n"
                << "Number must NOT contain symbols.\n"
                << "Number must NOT be a decimal number.\n"
                << std::endl;

            is_num_bool = 0;
            is_num = 0;
            decimal_count = 0;
            contains_spaces = false;

        }

    } while (is_num_bool == 0);

    s = user_converted_num;
}

#endif

