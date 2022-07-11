#include<iostream>
#include <memory>
#include <unordered_map>
class Calculator {
public:
    Calculator(int version_) : version(version_) {}
    int getVersion() {
        return version;
    }
private:
    int version;
};
int main() {
    auto calculator_ptr = std::make_unique<Calculator>(1);
    std::unordered_map<std::string, std::unique_ptr<Calculator> > mp;
    mp.emplace("index1", std::move(calculator_ptr));
    auto res = mp.find("index1");
    std::cout << res->first << '\n';
    std::cout << res->second->getVersion() << '\n';
    std::cout << mp.at("index1")->getVersion() << '\n';
}
