#ifndef SICT_ITEM_H__
#define SICT_ITEM_H__
#include "POS.h"
#include "PosIO.h"
namespace sict{
    class Item : public PosIO {
    private:
        char _sku[MAX_SKU_LEN + 1];
        char* _name;
        double _price;
        bool _taxed;
        int _quantity;
    public:
        Item();
        Item(const char* sku, const char* name, double price, bool taxed = true);
        Item(const Item& I);
        Item& operator=(const Item& I);
        virtual ~Item();
        void sku(char sku[]);
        void price(double price);
        void name(char* name);
        void taxed(bool istaxed);
        void quantity(int quantity);
        const char* sku()const;
        double price() const;
        const char* name()const;
        bool taxed() const;
        int quantity() const;
        double cost() const;
        bool isEmpty() const;
        bool operator==(const char* N);
        int operator+=(int i);
        int operator-=(int i);
        std::ostream& write(std::ostream& ostr, bool linear)const;
        std::istream& read(std::istream& istr);
    };
    double operator+=(double& d, const Item& I);
    std::ostream& operator<<(std::ostream& os, const Item& out);
    std::istream& operator>>(std::istream& is, Item& in);
}
#endif