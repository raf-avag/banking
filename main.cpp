#include <iostream>
#include <istream>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <limits>
#include <iomanip>
#include "json.hpp"
#include "account.h"
#include "functions.h"

int main()
{
    std::cout << "*******CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM*******\n";
    std::cout << "****************Welcome to the Main Menu****************\n" << "\n";

    bool exit = true;
    std::string answer{};
    int balance{};
    std::string id, name, surname;

    std::ofstream my_file("CustomerList.json", std::ios_base::app);
    my_file.open("CustomerList.json");
    my_file.close();

    while (exit) {
        bool end_command{};
        std::string command_input{};
        std::cout << "1. Create a new account\n";
        std::cout << "2. Update information of an account\n";
        std::cout << "3. Record a transaction\n";
        std::cout << "4. Check details of an account\n";
        std::cout << "5. Remove an account\n";
        std::cout << "6. View customer's list\n";
        std::cout << "7. Exit the system\n \n";
        std::cin >> command_input;

        if (command_input == "1") {
            do {
                std::cout << "Input the Customer ID. Input \"b\" to go back to menu. \n";
                std::cin >> id;
                if (id == "b")
                    end_command = true;
                else if (account_exists(id))
                {
                    std::cout << "Account already exists!";
                    end_command = true;
                }
                else {
                    std::cout << "Input Customer Name & Surname\n";
                    std::cin >> name >> surname;
                    std::cout << "Customer Balance (ONLY IN '000 FORMAT!)\n";
                    input_int(balance);
                    std::cout << "Customer ID: #" << id << ";\n Name: " << name << ";\n Surname: " << surname << ";\n Balance: " << balance << "\n";
                    std::cout << "Is everything correct? Y/N\n";
                    answer.clear();
                    while (!(answer == "Y" || answer == "N")) {
                        std::cin >> answer;
                        if (answer == "Y") {
                            account a(id, name, surname, balance);
                            a.CreateAccount(a);
                            end_command = true;
                        }
                        else if (answer == "N") {
                            end_command = false;
                        }
                        else
                            std::cout << "Invalid Input. Try again.\n";
                    };
                }
                
            } while (!end_command);
        }
        else if (command_input == "2") {
            try {
                do {
                    std::cout << "Input the Customer ID to update. Input \"b\" to go back to menu. \n";
                    std::cin >> id;
                    int id_pos{};

                    if (id == "b")
                        end_command = true;
                    else {
                        if (account_exists(id, &id_pos))
                        {
                            std::cout << "Update Customer New Name & Surname\n";
                            std::cin >> name >> surname;
                            std::cout << "Update Current Balance (ONLY IN '000 FORMAT!)\n";
                            input_int(balance);
                            std::cout << "Customer ID: #" << id << ";\n Name: " << name << ";\n Surname: " << surname << ";\nBalance: " << balance << "\n";
                            std::cout << "Is everything correct? Y/N\n";
                            answer.clear();
                            while (!(answer == "Y" || answer == "N")) {
                                std::cin >> answer;
                                if (answer == "Y") {
                                    account a(id, name, surname, balance);
                                    a.UpdateAccount(a, id_pos);
                                    end_command = true;
                                }
                                else if (answer == "N") {
                                    end_command = false;
                                }
                                else
                                    std::cout << "Invalid Input. Try again.\n";
                            };

                        }
                        else
                            end_command = false;
                    }

                } while (!end_command);

            }
            catch (...)
            {
                std::cout << "Account list is empty.\n";
            }

        }
        else if (command_input == "3") {
            try {
                do {
                    std::string id_1{};
                    std::cout << "Input the Sender Customer ID. Input \"b\" to go back to menu. \n";
                    std::cin >> id_1;
                    int id1_pos{};

                    if (id == "b")
                        end_command = true;
                    else {
                        if (account_exists(id_1, &id1_pos))
                        {
                            std::cout << "Sending ";
                            print_account(id_1, id1_pos);
                            do {
                                std::string id_2{};
                                std::cout << "Input the Receiver Customer ID\n";
                                std::cin >> id_2;
                                int id2_pos{};

                                if (account_exists(id_2, &id2_pos))
                                {
                                    std::cout << "Receiving ";
                                    print_account(id_2, id2_pos);

                                    do {
                                        int money{};
                                        std::cout << "Input the amount to be sent (ONLY IN '000 FORMAT!)\n";
                                        input_int(money);
                                        std::cout << "Amount to be sent is " << money << "\n";
                                        std::cout << "Is everything correct? Y/N\n";
                                        answer.clear();
                                        while (!(answer == "Y" || answer == "N")) {
                                            std::cin >> answer;
                                            if (answer == "Y") {
                                                make_transaction(id1_pos, id2_pos, money);
                                                end_command = true;
                                            }
                                            else if (answer == "N") {
                                                end_command = false;
                                            }
                                            else
                                                std::cout << "Invalid Input. Try again.\n";
                                        };

                                    } while (!end_command);

                                }
                                else
                                    end_command = false;

                            } while (!end_command);

                        }
                        else
                            end_command = false;
                    }

                } while (!end_command);
            }
            catch (...) {
                std::cout << "Account list is empty.\n";
            }
        }
        else if (command_input == "4") {
            try {
                do {
                    std::cout << "Input the Customer ID. Input \"b\" to go back to menu. \n";
                    std::cin >> id;
                    int id_pos{};

                    if (id == "b")
                        end_command = true;
                    else {
                        if (account_exists(id, &id_pos))
                        {
                            print_account(id, id_pos);
                            end_command = true;
                        }
                        else
                            end_command = false;
                    }

                } while (!end_command);

            }
            catch (...) {
                std::cout << "Account list is empty.\n";
            }
        }
        else if (command_input == "5") {
            try {
                do {
                    std::cout << "Input the Customer ID. Input \"b\" to go back to menu. \n";
                    std::cin >> id;

                    if (id == "b")
                    {
                        end_command = true;
                    }
                    else if (account_exists(id))
                    {
                        std::cout << "Customer ID to be deleted is #" << id << "\nAre you sure? Y/N\n";
                        answer.clear();
                        while (!(answer == "Y" || answer == "N")) {
                            std::cin >> answer;
                            if (answer == "Y") {
                                delete_account(id);
                                end_command = true;
                            }
                            else if (answer == "N") {
                                end_command = false;
                            }
                            else
                                std::cout << "Invalid Input. Try again.\n";
                        };
                    }
                    else
                        end_command = false;

                } while (!end_command);
            }
            catch (...) {
                std::cout << "Account list is empty.\n";
            }
        }
        else if (command_input == "6") {
            try {
                print_account_list();
            }
            catch (...) {
                std::cout << "Account list is empty.\n";
            }
        }
        else if (command_input == "7") {
            do {
                std::cout << "Are you sure? Y/N\n";
                answer.clear();
                while (!(answer == "Y" || answer == "N")) {
                    std::cin >> answer;
                    if (answer == "Y") {
                        std::cout << "Finished. Goodbye!";
                        end_command = true;
                        exit = false;
                    }
                    else if (answer == "N") {
                        end_command = true;
                    }
                    else
                        std::cout << "Invalid Input. Try again.\n";
                };
            } while (!end_command);
        }
        else
            std::cout << "Input Error, Please try again!\n";
    };    
}
