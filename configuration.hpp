#include <string>
#include <nlohmann/json.hpp>
#include <json-schema.hpp>
#include <vector>

class config {
private:
	std::string file_path;
	void validate_schema(const nlohmann::json& data);
	void save_to_file(const nlohmann::json& json_data, const std::string& file_p);
public:
	config(const std::string& file);
	std::string read_conf(const std::string& key);
	std::string create_file(const nlohmann::json& json_data, const std::string& file_p);
	nlohmann::json read_file(const std::string& file_p);
	void add_student(const std::string& file_p, int id, const std::string& name);
	void modify_student(const std::string& file_p, int id, const std::string& name);
	void delete_student(const std::string& file_p, int id);
	void list_students(const nlohmann::json& json_data);
};

class InvalidSchemaException : public std::runtime_error {
public:
    explicit InvalidSchemaException(const std::string& message);
};