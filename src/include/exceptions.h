# ifndef EXCEPTIONS_H
# define EXCEPTIONS_H

# include <exception>
# include <string>

using std::string;
using std::exception;

namespace opt {
    class LengthNoMatch : public exception {
        string message;
    public:
        LengthNoMatch() : message("The Length of two element does not match!") {}
        LengthNoMatch(string& msg) : message(msg) {}
        ~LengthNoMatch() throw() {}
        const char* what() const throw() override {
            return message.c_str();
        }
    };
}

using namespace opt;

# endif