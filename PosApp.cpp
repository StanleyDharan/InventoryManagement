#include <cstring>
#include <iomanip>
#include <ctime>
#include <string>
#include <limits.h>
#include "PosApp.h"
using namespace std;
namespace sict{

    PosApp::PosApp(const char* filename, const char* billfname){
        strcpy(_filename, filename);
        strcpy(_billfname, billfname);
        for (int i = 0; i < MAX_NO_ITEMS; i++)
        {
            _items[i] = NULL;
        }
        _noOfItems = 0;
        loadRecs();
    }

    int PosApp::menu(){
        int selection;
        cout << "The OOPs Store" << endl;
        cout << "1- List items" << endl;
        cout << "2- Add Perishable item" << endl;
        cout << "3- Add Non-Perishable item" << endl;
        cout << "4- Update item quantity" << endl;
        cout << "5- Show Item" << endl;
        cout << "6- POS" << endl;
        cout << "0- exit program" << endl;

        cout << "> ";
        cin >> selection;
        
        if (cin.fail()){
            return -1;
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return selection;
    }

    void PosApp::loadRecs(){
        int readIndex = 0;
        char id = '\0';

        fstream readFile;
        readFile.open(_filename, ios::in);

        if (readFile.fail()){
            readFile.clear();
            readFile.close();
            readFile.open(_filename, ios::out);
            readFile.close();
        }
        else if(!readFile.fail()){
            //cout << "in else if" << endl;
            while (!readFile.fail()){
              //  cout << "before" << endl;
                if (_items[readIndex] != NULL){
                    delete _items[readIndex];
                    _items[readIndex] = NULL;
                }
                //cout << "after" << endl;
                id = readFile.get();

                if (id == 'P'){
                    _items[readIndex] = new Perishable();
                    readFile.ignore(1);
                    _items[readIndex]->load(readFile);
                    readIndex++;

                }

                if (id == 'N'){
                    _items[readIndex] = new NonPerishable();
                    readFile.ignore(1);
                    _items[readIndex]->load(readFile);
                    readIndex++;
                }
            }
            _noOfItems = readIndex;
            readFile.close();
        }
    }

    void PosApp::saveRecs(){
        fstream readFile;
        readFile.open(_filename, ios::out);

        for (int i = 0; i < _noOfItems; i++){
            if (_items[i]->quantity() > 0){
                _items[i]->save(readFile);
            }
        }
        readFile.close();
        loadRecs();
    }

    int PosApp::searchItems(const char* sku)const{
        int returnval;
        for (int i = 0; i < _noOfItems; i++){
            if (*_items[i] == sku){
                returnval = i;
                i = _noOfItems;
            }
            else{
                returnval = -1;
            }
        }
        return returnval;
    }

        void PosApp::updateQty(){
        cout << "\nPlease enter the SKU: ";
        char sku[MAX_SKU_LEN];
        cin >> sku;
        int itemNo = searchItems(sku);
        if (itemNo == -1){
            cout << "Not found!" << endl;
        }
        else{
            int newQty;
            _items[itemNo]->write(cout, false);
            cout << "\nPlease enter the number of purchased items: ";
            cin >> newQty;
            if (cin.fail()){
                cout << "Invalid quantity entry!" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else{
                *_items[itemNo] += newQty;
                saveRecs();
                cout << "Updated!\n" << endl;
            }
        }
    }

    void PosApp::addItem(bool isPerishable){
        std::fstream readFile;
        if (isPerishable == true){
           
            Perishable p;
            cin >> p;
            if (cin.fail()){
                p.write(cout, true);
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else{
                readFile.open(_filename, ios::out);
                for (int i = 0; i < _noOfItems; i++){
                    _items[i]->save(readFile);
                }
                p.save(readFile);
                readFile.close();
                _noOfItems++;
                cout << "Item added." << endl << endl;
            }

        }
        if (isPerishable == false){
            NonPerishable np;
            cin >> np;
            if (cin.fail()){
                np.write(cout, true);
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else{
                readFile.open(_filename, ios::out);
                for (int i = 0; i < _noOfItems; i++){
                    _items[i]->save(readFile);
                }
                np.save(readFile);
                readFile.close();
                _noOfItems++;
                cout << "Item added." << endl << endl;
            }
        }
    }

    void PosApp::listItems()const{
        double totalAsset = 0.00;
        cout << setfill(' ') << setw(5) << right << "\n Row " << "|";
        cout << setfill(' ') << setw(8) << left << " SKU" << "|";
        cout << setfill(' ') << setw(20) << left << " Item Name" << "|";
        cout << setfill(' ') << setw(7) << left << " Price" << "|";
        cout << setfill(' ') << setw(3) << left << "TX" << "|";
        cout << setfill(' ') << setw(4) << left << "Qty" << "|";
        cout << setfill(' ') << setw(9) << right << " Total " << "|" << endl;
        cout << "-----|--------|--------------------|-------|---|----|---------|" << endl;
        int a = 1;
        for (int i = 0; i < _noOfItems; i++){
            cout << setfill(' ') << setw(4) << right << i + 1 << " | ";
            cout << setfill(' ');
            _items[i]->write(cout, true);
            cout << endl;
            totalAsset += *_items[i];
            a++;
        }
        cout << "-----^--------^--------------------^-------^---^----^---------^" << endl;
        cout << fixed << setprecision(2) << "Total Asset: $" << totalAsset << endl << endl;
    }
    /*void PosApp::dateTime(){
        time_t now = time(0);
        struct tm* dt = localtime(&now);
        cout << setfill(' ') << setw(37) << put_time(dt, "%Y/%m/%d, %H:%M") << "" << "|" << endl;
    }*/

    void PosApp::showBill(){
        int readIndex = 0;
        double total = 0.0;
        cout << "v--------------------------------------------------------v" << endl;
        cout << "| " << left; 
       // dateTime();
        time_t now = time(0);
        tm* dt = localtime(&now);
        char buffer[80];
        strftime(buffer, 80, "%Y/%m/%d, %H:%M", dt);
        cout << setfill(' ') << setw(54) << buffer << "" << "|" << endl;

        cout << "| " << setfill(' ') << setw(5) << left << "SKU" << " |";
        cout << setfill(' ') << setw(19) << left << " Item Name" << " |";
        cout << " Price " << "|";
        cout << "TX " << "|";
        cout << "QTY " << "|";
        cout << setfill(' ') << setw(9) << right << " Total " << "|" << endl;
        cout << "|-------|--------------------|-------|---|----|---------|" << endl;

        fstream bill;
        bill.open(_billfname, ios::in);

        if (bill.fail()){
            bill.clear();
            bill.close();
            bill.open(_filename, ios::out);
            bill.close();
        }
        else if (!bill.fail()){
            while (readIndex < _noOfItems){
                if (!bill.fail()){
                    cout << "|";
                    _items[readIndex]->write(cout, true);
                    cout << endl;
                    total += *_items[readIndex];
                    delete _items[readIndex];
                    _items[readIndex] = NULL;
                }
                readIndex++;
            }
            bill.close();
        }
        bill.open(_billfname, ios::out | ios::trunc);
        bill.close();
        
        cout << "^-------^--------------------^-------^---^----^---------^" << endl;
        cout << "Total $" << total << endl << endl;

    }

    void PosApp::addToBill(Item& I){
        int qty;
        qty = I.quantity();
        I.quantity(1);

        fstream bill;
        bill.open(_billfname, ios::out | ios::app);
        I.save(bill);
        if (qty > 0){
            qty--;
        }
        I.quantity(qty);
        saveRecs();
    }

    void PosApp::POS(){
        bool notDone = true;
        char sku[MAX_SKU_LEN];
        while (notDone){
            cout << "\nSku: ";

            cin.getline(sku, MAX_SKU_LEN);
            int itemNo = searchItems(sku);
            
            if (strlen(sku) == 0){
                showBill();
                notDone = false;
            }
            else if (itemNo == -1){
                cout << "Not found!";
            }
            else{
                cout << "v------------------->" << endl;
                cout  << "| " << _items[itemNo]->name() << endl;
                cout << "^------------------->";
                addToBill(*_items[itemNo]);
            }
        }
    }

    void PosApp::run(){
        fstream datafile;
        int uSelect = -1;
        int a;
        int option;
        while (uSelect != 0){
            option = menu();
            switch (option)
            {
            case 0:
                uSelect = 0;
                cout << "Goodbye!!" << endl;
                exit(0);
                break;

            case 1:
                /*listItems();
                for (int i = 0; i < _noOfItems; i++){
                    _items[i]->save(datafile);
                }*/
                loadRecs();
                listItems();
                break;

            case 2:
                addItem(true);
                loadRecs();
                break;

            case 3:
                addItem(false);
                loadRecs();
                break;

            case 4:
                updateQty();
                loadRecs();
                break;

            case 5:
                char sku[MAX_SKU_LEN];
                cout << "\nPlease enter the SKU: ";
                cin.getline(sku, MAX_SKU_LEN);
                a = searchItems(sku);
                if (a > -1){
                    cout << "v-----------------------------------v" << endl;
                    _items[a]->write(cout, false);
                    cout << "^-----------------------------------^" << endl << endl;
                }
                else{
                    cout << "Not found!" << endl << endl;
                }
                break;

            case 6:
                POS();
                loadRecs();
                break;

            default:
                cout << " == = Invalid Selection, try again. == = " << endl;
                uSelect = -1;
                break;
            }
        }
    }
}
