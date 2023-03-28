#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

using namespace std;

void test_read_valid_yaml_file() {
    // create a valid YAML file with some sample parameters
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "param1" << YAML::Value << 10;
    emitter << YAML::Key << "param2" << YAML::Value << "hello";
    emitter << YAML::EndMap;
    ofstream fout("test.yaml");
    fout << emitter.c_str();
    fout.close();
    
    // call the parser function with the filename as input
    ifstream fin("test.yaml");
    YAML::Node node = YAML::Load(fin);
    int param1 = node["param1"].as<int>();
    string param2 = node["param2"].as<string>();
    
    // check that the parser returns the expected parameters and their values
    if (param1 != 10 || param2 != "hello") {
        cout << "test_read_valid_yaml_file failed" << endl;
    } else {
        cout << "test_read_valid_yaml_file passed" << endl;
    }
}

void test_handle_invalid_yaml_file() {
    // create an invalid YAML file with syntax errors
    ofstream fout("test.yaml");
    fout << "param1: 10\nparam2: hello\n";
    fout.close();
    
    // call the parser function with the filename as input
    try {
        ifstream fin("test.yaml");
        YAML::Node node = YAML::Load(fin);
    } catch (YAML::Exception& e) {
        // check that the parser raises an exception or returns an error message
        cout << "test_handle_invalid_yaml_file passed" << endl;
        return;
    }
    cout << "test_handle_invalid_yaml_file failed" << endl;
}

void test_handle_missing_parameters() {
    // create a valid YAML file with some parameters missing
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "param1" << YAML::Value << 10;
    emitter << YAML::EndMap;
    ofstream fout("test.yaml");
    fout << emitter.c_str();
    fout.close();
    
    // call the parser function with the filename as input
    ifstream fin("test.yaml");
    YAML::Node node = YAML::Load(fin);
    int param1 = node["param1"].as<int>();
    string param2 = node["param2"].as<string>("default");
    
    // check that the parser returns the expected parameters with default values
    if (param1 != 10 || param2 != "default") {
        cout << "test_handle_missing_parameters failed" << endl;
    } else {
        cout << "test_handle_missing_parameters passed" << endl;
    }
}

void test_handle_incorrect_types() {
    // create a valid YAML file with some parameters having incorrect types
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "param1" << YAML::Value << "not a number";
    emitter << YAML::Key << "param2" << YAML::Value << "hello";
    emitter << YAML::EndMap;
    ofstream fout("test.yaml");
    fout << emitter.c_str();
    fout.close();
    
    // call the parser function with the filename as input
    try {
        ifstream fin("test.yaml");
        YAML::Node node = YAML::Load(fin);
        int param1 = node["param1"].as<int>();
    } catch (YAML::Exception& e) {
        // check that the parser raises an exception or returns an error message
        cout << "test_handle_incorrect_types passed" << endl;
        return;
    }
    cout << "test_handle_incorrect_types failed" << endl;
}

int main() {
    test_read_valid_yaml_file();
    test_handle_invalid_yaml_file();
    test_handle_missing_parameters();
    test_handle_incorrect_types();
    return 0;
}
