#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>
#include "exceptions/Exceptions.hpp"

namespace Softadastra
{
    class Validator
    {
    public:
        Validator() = default;
        ~Validator() = default;
        Validator(const Validator &) = delete;
        Validator &operator=(const Validator &) = delete;
        Validator(Validator &&) = delete;
        Validator &operator=(Validator &&) = delete;

        static bool validateLength(const std::string &input, size_t maxlength)
        {
            if (input.size() > maxlength)
            {
                throw Softadastra::LengthExecption();
            }
            return true;
        }

        static bool validateAlphaNumeric(const std::string &input)
        {
            for (char c : input)
            {
                if (!std::isalnum(c))
                {
                    throw Softadastra::AlphaNumericException();
                }
            }
            return true;
        }

        static bool validateEmail(const std::string &input)
        {
            std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
            if (!std::regex_match(input, pattern))
            {
                throw Softadastra::InavlidEmailException();
            }
            return true;
        }

        static bool validatePassword(const std::string &input)
        {
            if (input.size() < 8)
            {
                throw Softadastra::InvalidPasswordException();
            }

            bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
            for (char c : input)
            {
                if (std::isupper(c))
                    hasUpper = true;
                if (std::islower(c))
                    hasLower = true;
                if (std::isdigit(c))
                    hasDigit = true;
                if (std::ispunct(c))
                    hasSpecial = true;
            }

            if (!hasUpper || !hasLower || !hasDigit || !hasSpecial)
            {
                throw Softadastra::InvalidPasswordException();
            }
            return true;
        }

        static bool validateFirstname(const std::string &input)
        {
            std::regex inputPattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)*$");
            if (input.length() < 2 || input.length() > 50)
            {
                throw Softadastra::ValidationException("Le prenom doit etre entre 2 et 50 caracteres");
            }

            if (!std::regex_match(input, inputPattern))
            {
                throw Softadastra::ValidationException("Le prenom ne peut contenir que des lettres, des espaces ou des tirets");
            }
            return true;
        }

        static bool validateLastName(const std::string &input)
        {
            return validateFirstname(input);
        }

        static bool validateUserName(const std::string &input)
        {
            std::regex usernamePattern("^[A-Za-z0-9_-]{3,20}$");
            if (!std::regex_match(input, usernamePattern))
            {
                throw Softadastra::ValidationException("Le username doit etre entre 3 et 20 caracteres et ne peut contenir que des lettres, chiffres, tirets ou underscores.");
            }
            return true;
        }

    private:
        std::string m_str;
    };

} // namespace Softadastra

#endif