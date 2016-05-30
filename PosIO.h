#ifndef SICT_POSIO_H__
#define SICT_POSIO_H__
#include <fstream>
#include <iostream>

namespace sict{
    class PosIO
    {
    public:
        virtual std::fstream& save(std::fstream& file)const = 0;
        virtual std::fstream& load(std::fstream& file) = 0;
        virtual std::ostream& write(std::ostream& ostr, bool linear)const = 0;
        virtual std::istream& read(std::istream& istr) = 0;
    };
}
#endif
