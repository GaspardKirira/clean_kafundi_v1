#ifndef PHONEVALIDATOR_HPP
#define PHONEVALIDATOR_HPP

#include <stdexcept>
#include <string>
#include <regex>
#include "exceptions/Exceptions.hpp"

namespace Softadastra
{
    class PhoneValidator
    {
    public:
        static bool validatePhoneNumber(const std::string &input)
        {
            std::regex phonePattern("^\\+?\\d{1,3}[\\s\\-\\.\\(]?[\\d\\s\\-\\.\\)]{5,20}$");
            if (!std::regex_match(input, phonePattern))
            {
                throw Softadastra::InvalidPhoneNumberException();
            }
            return true;
        }
    };
} // namespace Softadastra

#endif