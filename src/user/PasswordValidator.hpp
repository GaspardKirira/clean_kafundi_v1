#ifndef PASSWORDVALIDATOR_HPP
#define PASSWORDVALIDATOR_HPP

#include <string>
#include <bcrypt.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>
#include <openssl/evp.h>
#include <cctype>
#include "exceptions/Exceptions.hpp"

namespace Softadastra
{
    class PasswordValidator
    {
    public:
        static std::string hashPassword(const std::string &password)
        {
            char salt[BCRYPT_HASHSIZE];
            if (bcrypt_gensalt(12, salt) != 0)
            {
                throw Softadastra::GenerateSaltException();
            }

            char hashed_password[BCRYPT_HASHSIZE];
            if (bcrypt_hashpw(password.c_str(), salt, hashed_password) != 0)
            {
                throw Softadastra::HashPasswordException();
            }

            return std::string(hashed_password);
        }

        static void validatePassword(const std::string &password, const std::string &stored_hash)
        {
            if (bcrypt_checkpw(password.c_str(), stored_hash.c_str()) != 0)
            {
                throw Softadastra::InvalidPasswordException();
            }
        }

        static bool validatePasswordComplexity(const std::string &password)
        {
            if (password.length() < 8)
                throw Softadastra::InvalidPasswordException();

            bool has_upper = false, has_lower = false, has_digit = false, has_special = false;

            for (char ch : password)
            {
                if (std::isupper(ch))
                    has_upper = true;
                if (std::islower(ch))
                    has_lower = true;
                if (std::isdigit(ch))
                    has_digit = true;
                if (std::ispunct(ch))
                    has_special = true;
            }
            if (!has_upper || !has_lower || !has_digit || !has_special)
            {
                throw Softadastra::InvalidPasswordException();
            }
            return true;
        }
    };
} // namespace Softadastra

#endif // PASSWORDVALIDATOR_HPP
