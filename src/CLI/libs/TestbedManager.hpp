class TestbedManager {
public:
    TestbedManager() {}

    std::unordered_map<std::string, std::unique_ptr<Testbed>> testbeds;
    std::string active_testbed;

    bool CheckActiveTestbed() {
        if(active_testbed.empty()){
            std::cout << "No active testbed, please select a testbed first\n";
            return false;
        }
        return true;
    }

    void ListTestbeds() {
        if(testbeds.empty()){
            std::cout << "No testbeds created yet\n";
        } else {
            std::cout << "List of available testbeds:\n";
            for(const auto& testbed : testbeds){
                std::cout << "- " << testbed.first << "\n";
            }
        }
    }

    void CreateTestbed(const std::string& testbed_name) {
        if(testbeds.find(testbed_name) != testbeds.end()){
            std::cout << "A testbed with the name " << testbed_name << " already exists.\n";
            return;
        }
        testbeds[testbed_name] = std::make_unique<Testbed>();
        std::cout << "Testbed " << testbed_name << " created successfully!\n";
    }

    void RemoveTestbed(const std::string& testbed_name) {
        if(testbeds.find(testbed_name) == testbeds.end()){
            std::cout << "Testbed with the name " << testbed_name << " does not exist.\n";
            return;
        }
        testbeds.erase(testbed_name);
        std::cout << "Testbed " << testbed_name << " removed successfully!\n";
    }

    void SelectTestbed(const std::string& testbed_name) {
        if(testbeds.find(testbed_name) == testbeds.end()){
            std::cout << "Testbed with the name " << testbed_name << " does not exist.\n";
            return;
        }
        active_testbed = testbed_name;
        std::cout << "Selected testbed: " << testbed_name << "\n";
    }
};
