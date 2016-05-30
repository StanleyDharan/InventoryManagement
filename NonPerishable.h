#ifndef _SICT_NONPERISHABLE_H_
#define _SICT_NONPERISHABLE_H_

#include "Item.h"
#include "ErrorMessage.h"
#include "PosIO.h"
namespace sict{
    class NonPerishable : public Item{
    private:
        ErrorMessage _err;
    public:
        std::fstream& save(std::fstream& file)const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& ostr, bool linear)const;
        std::istream& read(std::istream& istr);
    };
}

#endif