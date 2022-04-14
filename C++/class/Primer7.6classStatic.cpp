#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
class Account {
public:
    Account(string account_) {
        account = account_;                
    }
    static int baseRate;
    static int getBaseRate();
    string getAccount();
private:
    string account;
};
int Account::baseRate = 1; //初始化static成员变量
int Account::getBaseRate() {
    return baseRate;
}
string Account::getAccount() {
    return account;
}
int main() {
    Account *a = new Account("attack204");
    cout << (*a).getBaseRate() << '\n';
    cout << (*a).getAccount();
    return 0;
}