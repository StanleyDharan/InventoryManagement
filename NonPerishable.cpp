#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "NonPerishable.h"
#include "Item.h"

namespace sict{
    std::fstream& NonPerishable::save(std::fstream& file)const{
        file << "N," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << endl;
        return file;
    }

    std::fstream& NonPerishable::load(std::fstream& file){
        char tempSku[MAX_SKU_LEN];
        char tempName[100];
        double tempPrice;
        int tempQty;
        int tax;

        file.getline(tempSku, MAX_SKU_LEN, ',');
        file.getline(tempName, 100, ',');
        file >> tempPrice;
        file.ignore();
        file >> tax;
        file.ignore(1);
        file >> tempQty;

        taxed(tax == 1);

        sku(tempSku);
        name(tempName);
        price(tempPrice);
        quantity(tempQty);
        return file;
    }

    std::ostream& NonPerishable::write(std::ostream& ostr, bool linear)const{
        if (!_err.isClear()){
           return ostr << _err.message();
        }
        if (_err.isClear()){
            if (linear == true){
                ostr << setw(MAX_SKU_LEN) << left << sku() << "|";
                ostr << setw(20) << left << name() << "|";
                ostr << setw(7) << setprecision(2) << fixed << right << price() << "|";
                if (taxed()){
                    ostr <<" t |";
                }
                else {
                    ostr << "   |";
                }
                ostr << setw(4) << right << quantity() << "|";
                ostr << setw(9) << right << setprecision(2) << fixed << (cost() * quantity()) << "|";
            }
            else if (linear == false){
                if (taxed()){
                    ostr << "Name:" << endl; 
                    ostr << name() << endl;//setw(80) << left << name() << endl;
                    ostr << "Sku: " << sku() << endl;
                    ostr << "Price: " << setprecision(2) << fixed << price() << endl;
                    ostr << "Price after tax: " << setprecision(2) << fixed << cost() << endl;
                    ostr << "Quantity: " << quantity() << endl;
                    ostr << "Total Cost: " << (cost() * quantity()) << endl;
                }
                else if (!taxed()){
                    ostr << "Name:" << endl;
                    ostr << setw(80) << left << name() << endl;
                    ostr << "Sku: " << sku() << endl;
                    ostr << "Price: " << setprecision(2) << fixed << price() << endl;
                    ostr << "Price after tax: " << "N/A" << endl;
                    ostr << "Quantity: " << quantity() << endl;
                    ostr << "Total Cost: " << (price() * quantity()) << endl;
                }
            }
        }
        return ostr;
    }

    std::istream& NonPerishable::read(std::istream& istr){
        _err.clear();
        char tempSku[MAX_SKU_LEN];
        char tempName[100];
        double tempPrice;
        int tempQty;
        char tempTax;
        
        cout << "\nNonPerishable Item Entry:" << endl;
        cout << "Sku: ";
        istr >> tempSku;
        sku(tempSku);
        cout << "Name:" << endl;
        istr >> tempName;
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
        return istr;
    }
};