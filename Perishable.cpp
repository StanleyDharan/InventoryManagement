#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#include "Perishable.h"
#include "Item.h"
namespace sict{
    
    Perishable::Perishable(){
        _expiry.dateOnly(true);
    }

    const Date& Perishable::expiry()const{
        return this->_expiry;
    }

    void Perishable::expiry(const Date &value){
        _expiry = value;
    }

    std::fstream& Perishable::save(std::fstream& file)const{
        file << "P," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << ",";
        _expiry.write(file);
        file << endl;
        return file;
    }

    std::fstream& Perishable::load(std::fstream& file){
        char tempSku[MAX_SKU_LEN];
        char tempName[100];
        double tempPrice;
        int tempQty;
        int tempYear;
        int tempMon;
        int tempDay;
        int tax;

        file.getline(tempSku, MAX_SKU_LEN, ',');
        file.getline(tempName, 100, ',');
        file >> tempPrice;
        file.ignore();
        file >> tax;
        file.ignore();
        file >> tempQty;
        file.ignore();
        file >> tempYear;
        file.ignore();
        file >> tempMon;
        file.ignore();
        file >> tempDay;

        Date tempDate(tempYear, tempMon, tempDay);
        expiry(tempDate);
        taxed(tax == 1);
        sku(tempSku);
        name(tempName);
        price(tempPrice);
        quantity(tempQty);
        return file;
    }
   
    std::ostream& Perishable::write(std::ostream& ostr, bool linear)const{
        if (!_err.isClear()){
           return ostr << _err.message();
        }
        if (_err.isClear()){
            if (linear == true){
                ostr << setw(MAX_SKU_LEN) << left << sku() << "|";
                ostr << setw(20) << left << name() << "|";
                ostr << setw(7) << setprecision(2) << fixed << right << price() << "|";
                if (taxed()){
                    ostr << " tp|";
                }
                else {
                    ostr << "  p|";
                }
                ostr << setw(4) << right << quantity() << "|";
                ostr << setw(9) << right << setprecision(2) << fixed << (cost() * quantity()) << "|";
            }
            if (linear == false){
                if (taxed()){
                    ostr << "Name:" << endl;
                    ostr << name() << endl;//setw(80) << left << name() << endl;
                    ostr << "Sku: " << sku() << endl;
                    ostr << "Price: " << setprecision(2) << fixed << price() << endl;
                    ostr << "Price after tax: " << setprecision(2) << fixed << cost() << endl;
                    ostr << "Quantity: " << quantity() << endl;
                    ostr << "Total Cost: " << (cost() * quantity()) << endl;
                    ostr << "Expiry date: ";
                    _expiry.write(ostr);
                    ostr << endl;
                }
                if (!taxed()){
                    ostr << "Name:" << endl;
                    ostr << name() << endl;//setw(80) << left << name() << endl;
                    ostr << "Sku: " << sku() << endl;
                    ostr << "Price: " << setprecision(2) << fixed << price() << endl;
                    ostr << "Price after tax: " << "N/A" << endl;
                    ostr << "Quantity: " << quantity() << endl;
                    ostr << "Total Cost: " << (price() * quantity()) << endl;
                    ostr << "Expiry date: ";
                    _expiry.write(ostr);
                    ostr << endl;
                }
            }
        }
        return ostr;
    }

    std::istream& Perishable::read(std::istream& istr){
        _err.clear();
        char tempSku[MAX_SKU_LEN+1];
        char tempName[100];
        double tempPrice;
        int tempQty;
        char tempTax;
        //char tempDate[11];

        cout << "\nPerishable Item Entry: " << endl;
        cout << "Sku: ";
        istr >> tempSku;
        sku(tempSku);
        cout << "Name:" << endl;
        istr >> tempName;
        istr.ignore();
        name(tempName);
        cout << "Price: ";
        if (_err.isClear()){
            istr >> tempPrice;
            if (istr.fail()){
                _err.message("Invalid Price Entry");
                return istr;
            }
            else
                price(tempPrice);
        }
        cout << "Taxed: ";
        if (_err.isClear()){
            istr >> tempTax;
            if (tempTax == 'y'){
                taxed(true);
            }
            else if (tempTax == 'n'){
                taxed(false);
            }
            else{
                istr.setstate(ios::failbit);
                _err.message("Invalid Taxed Entry, (y)es or (n)o");
                return istr;
            }

        }
        cout << "Quantity: ";
        if (_err.isClear()){
            istr >> tempQty;
            if (istr.fail()){
                _err.message("Invalid Quantity Entry");
                return istr;
            }
            else
                quantity(tempQty);
        }
        cout << "Expiry date (YYYY/MM/DD): ";
        if (_err.isClear()){
            _expiry.read(istr);
            if (_expiry.errCode() == CIN_FAILED){
                istr.setstate(ios::failbit);
                _err.message("Invalid Date Entry");
                return istr;
            }
        }
            if (_expiry.errCode() == YEAR_ERROR){
                istr.setstate(ios::failbit);
                _err.message("Invalid Year in Date Entry");
                return istr;
            }
            else
                if (_expiry.errCode() == MON_ERROR){
                    istr.setstate(ios::failbit);
                    _err.message("Invalid Month in Date Entry");
                    return istr;
                }
            else
                if (_expiry.errCode() == DAY_ERROR){
                    istr.setstate(ios::failbit);
                    _err.message("Invalid Day in Date Entry");
                    return istr;
                }
        return istr;
    }
}