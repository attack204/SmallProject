#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
class Sale_data {
public:
    Sale_data() = default;
    Sale_data(double revenue_, string isbn_): revenue(revenue_), isbn(isbn_) {}
    double revenue;
    friend ostream &operator << (ostream &os, const Sale_data &item);
    friend istream &operator >> (istream &is, Sale_data &item);
    Sale_data operator += (const Sale_data &rhs) {
        revenue += rhs.revenue;
        return *this;
    }
    string getIsbn() const{
        return isbn;
    }
private:
    string isbn;
};  
ostream &operator << (ostream &os, const Sale_data &item) {
    os << item.isbn << ' ' <<  item.revenue;
    return os;
}
istream &operator >> (istream &is, Sale_data &item) {
    is >> item.revenue >> item.isbn;
    if(!is) item = Sale_data();
    return is;
}
Sale_data operator + (const Sale_data  &lhs, const Sale_data &rhs) {
    Sale_data tmp = lhs;
    tmp += rhs;
    return tmp;
}
bool operator == (const Sale_data &lhs, const Sale_data &rhs) {
    return lhs.getIsbn() == rhs.getIsbn();
}
bool operator != (const Sale_data &lhs, const Sale_data &rhs) {
    return !(lhs == rhs);
}
int main() {
    Sale_data a(1.0, "attack204");
    cout << a << '\n';
    Sale_data b;
    cin >> b;
    cout << (a == b) << '\n';
    cout << (a != b) <<  '\n';
    return 0;
}