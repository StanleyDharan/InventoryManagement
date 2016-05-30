#include <iostream>
#include <string.h>

using namespace std;
#include "Item.h"
namespace sict{

    Item::Item(){
        _price = 0;
        _quantity = 0;
        _name = nullptr;
       /*_name = new char[1];
        strcpy(_name, "");*/
        _sku[0] = '\0';
    }
    
    Item::Item(const char* sku, const char* name, double price, bool taxed){
        strncpy(_sku, sku, MAX_SKU_LEN);
        _name = nullptr;
        _name = new char[strlen(name)+1];
        strcpy(_name, name);
        _quantity = 0;
        _price = price;
        _taxed = taxed;
    }

    Item::Item(const Item& I){
        strncpy(_sku, I._sku, MAX_SKU_LEN);
        _name = nullptr;
        _name = new char[strlen(I._name)+ 1];
        strcpy(_name, I._name);
        _quantity = I._quantity;
        _price = I._price;
        _taxed = I._taxed;
    }

    Item& Item::operator=(const Item& I){
        if (this != &I){
            strncpy(_sku, I._sku, MAX_SKU_LEN);
            _name = new char[strlen(I._name)+1];
            strcpy(_name, I._name);
            _quantity = I._quantity;
            _price = I._price;
            _taxed = I._taxed;
        }
        return *this;
    }

    Item::~Item(){
         delete[] _name;
         _name = nullptr;
    }

    void Item::sku(char sku[]){
        strncpy(_sku, sku, MAX_SKU_LEN);
    }

    void Item::price(double price){
        _price = price;
    }

    void Item::name(char* name){
        delete[] _name;
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);
    }

    void Item::taxed(bool istaxed){
        _taxed = istaxed;
    }

    void Item::quantity(int quantity){
        _quantity = quantity;
    }

    const char* Item::sku()const{
        return _sku;
    }

    double Item::price() const{
        return _price;
    }

    const char* Item::name()const{
        return _name;
    }

    bool Item::taxed() const{
        return _taxed;
    }

    int Item::quantity() const{
        return _quantity;
    }

    double Item::cost() const{
        double taxedPriced = _price;
        if (_taxed){
            taxedPriced += (_price * TAX);
        }
        return taxedPriced;
    }

    bool Item::isEmpty() const{
        if (_price == 0 && _quantity == 0 && _name == nullptr && _sku[0] == '\0'){ /*strcmp(_name, "") == 0*/
            return true;
        }else return false;
    }

    bool Item::operator==(const char* N){
        if (strcmp(N, _sku) == 0){
            return true;
        }else
        return false;
    }

    int Item::operator+=(int i){
        return _quantity += i;
    }

    int Item::operator-=(int i){
        return _quantity -= i;
    }

    double operator+=(double& d, const Item& I){
        d += (I.cost() * I.quantity());
        return d;
    }

    std::ostream& operator<<(std::ostream& os, const Item& out){
        if (out.isEmpty()){
            return os;
        }
        else {
            return out.write(os, true);
        }
    }

    std::istream& operator>>(std::istream& istr, Item& in){
            return in.read(istr);
    }

    std::ostream& Item::write(std::ostream& ostr, bool linear)const{
            return ostr << sku() << name() << price();
    }

    std::istream& Item::read(std::istream& istr){
        return istr >> _sku >> _name >> _quantity >> _taxed >> _price;
    }
};