#ifndef EMAILVALIDATOR_HPP
#define EMAILVALIDATOR_HPP

#include <string>
#include <regex>
#include <stdexcept>

namespace Softadastra
{
    class EmailValidator
    {
    public:
        static void validateEmail(const std::string &email)
        {
            // Regex pour valider un email similaire à Gmail
            std::regex email_regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

            if (!std::regex_match(email, email_regex))
            {
                throw std::invalid_argument("Invalid email format. It should be like example@gmail.com");
            }
        }
    };
} // namespace Softadastra

#endif
