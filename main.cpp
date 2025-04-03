#include "configuration.hpp"
#include <iostream>

int main() {
    Config config;
    std::string input_file_path, output_file_path;

    std::cout << "Enter the path to the input JSON file: ";
    std::getline(std::cin, input_file_path);

    try {
         nlohmann::json json_input = config.read_file(input_file_path);

        while (true) {
            std::cout << "\nMenu:\n";
            std::cout << "1. List all students\n";
            std::cout << "2. Add a student\n";
            std::cout << "3. Modify a student\n";
            std::cout << "4. Delete a student\n";
            std::cout << "5. Save and exit\n";
            std::cout << "Choose an option (1-5): ";
            int choice;
            std::cin >> choice;

            if (choice == 1) {
                config.list_students(json_input);
            } else if (choice == 2) {
                int id;
                std::string name;
                std::cout << "Enter student ID: ";
                std::cin >> id;
                std::cout << "Enter student name: ";
                std::cin.ignore(); // Clear the newline character from the input buffer
                std::getline(std::cin, name);
                config.add_student(input_file_path, id, name);
                json_input = config.read_file(input_file_path); // Refresh the json_input
            } else if (choice == 3) {
                int id;
                std::string name;
                std::cout << "Enter student ID to modify: ";
                std::cin >> id;
                std::cout << "Enter new student name: ";
                std::cin.ignore(); // Clear the newline character from the input buffer
                std::getline(std::cin, name);
                config.modify_student(input_file_path, id, name);
                json_input = config.read_file(input_file_path); // Refresh the json_input
            } else if (choice == 4) {
                int id;
                std::cout << "Enter student ID to delete: ";
                std::cin >> id;
                config.delete_student(input_file_path, id);
                json_input = config.read_file(input_file_path); // Refresh the json_input
            } else if (choice == 5) {
                std::cout << "Exiting and saving changes." << std::endl;
                break;
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}