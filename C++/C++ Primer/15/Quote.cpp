#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
class Quote {
public:
    Quote() = default;
    Quote(const string &book, const double &sale_price) : BookNo(book), price(sale_price) {}
    virtual ~Quote() = default;
    string ISBN() const {
        return BookNo;
    }
    virtual double net_price(int n) const {
        return n * price;
    }

private:
    string BookNo;
protected:
    double price;
};

class Bulk_Quote : public Quote{
public:
    Bulk_Quote() = default;
    Bulk_Quote(const string &, double, int, double);
    double net_price(int) const override;
private:
    int min_qty = 0;
    double discount = 0.0;
};
int main() {
    Quote A("Hello", 1.0);
    cout << A.net_price(10) << '\n';
    return 0;
}