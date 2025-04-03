#include <fstream>
#include <iostream>
#include "configuration.hpp"

using json = nlohmann::json;

InvalidSchemaException::InvalidSchemaException(const std::string& message)
    : std::runtime_error(message) {}

void Config::validate_schema(const nlohmann::json& data) {
    nlohmann::json schema = {
        { "type", "object" },
        { "properties", {
            { "students", {
                { "type", "array" },
                { "items", {
                    { "type", "object" },
                    { "properties", {
                        { "id", { { "type", "integer" } } },
                        { "name", { { "type", "string" } } }
                    }},
                    { "required", { "id", "name" } }
                }}
            }}
        }},
        { "required", { "students" } }
    };

    json_schema::Validator validator;
    validator.set_schema(schema);
    auto result = validator.validate(data);
    if (!result.is_valid()) {
        throw InvalidSchemaException("JSON schema validation failed: " + result.get_error_message());
    }
}

void Config::save_to_file(const nlohmann::json& json_data, const std::string& file_p) {
    std::ofstream json_file(file_p);
    if (!json_file.is_open()) {
        throw std::runtime_error("Could not open file for writing.");
    }
    json_file << json_data.dump(4); // Pretty print with 4 spaces
    json_file.close();
}

std::string Config::create_file(const nlohmann::json& json_data, const std::string& file_p) {
    validate_schema(json_data);
    save_to_file(json_data, file_p);
    return "File saved successfully at " + file_p;
}

nlohmann::json Config::read_file(const std::string& file_p) {
    std::ifstream json_file(file_p);
    if (!json_file.is_open()) {
        throw std::runtime_error("Could not open file for reading.");
    }

    nlohmann::json json_data;
    json_file >> json_data; // Read the JSON data
    json_file.close();

    validate_schema(json_data);
    return json_data; // Return the validated JSON object
}

void Config::add_student(const std::string& file_p, int id, const std::string& name) {
    nlohmann::json json_data = read_file(file_p);
    nlohmann::json new_student = { {"id", id}, {"name", name} };
    json_data["students"].push_back(new_student);
    save_to_file(json_data, file_p);
}

void Config::modify_student(const std::string& file_p, int id, const std::string& name) {
    nlohmann::json json_data = read_file(file_p);
    for (auto& student : json_data["students"]) {
        if (student["id"] == id) {
            student["name"] = name;
            save_to_file(json_data, file_p);
            return;
        }
    }
    throw std::runtime_error("Student with ID " + std::to_string(id) + " not found.");
}

void Config::delete_student(const std::string& file_p, int id) {
    nlohmann::json json_data = read_file(file_p);
    auto& students = json_data["students"];
    for (auto it = students.begin(); it !=
    	students.end(); ++it) {
        if ((*it)["id"] == id) {
            students.erase(it);
            save_to_file(json_data, file_p);
            return;
        }
    }
    throw std::runtime_error("Student with ID " + std::to_string(id) + " not found.");
}

void Config::list_students(const nlohmann::json& json_data) {
	if (json_data.contains("students")) {
	    for (const auto& student : json_data["students"]) {
	        std::cout << "ID: " << student["id"] << ", Name: " << student["name"] << std::endl;
	    }
	} else {
	    std::cout << "No students found." << std::endl;
	}
}