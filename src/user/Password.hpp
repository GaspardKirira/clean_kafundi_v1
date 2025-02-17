#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <string>
#include "PasswordValidator.hpp"
#include <stdexcept>
#include <iostream>

namespace Softadastra
{
    class Password
    {
    public:
        Password() = default;

        explicit Password(const std::string &password)
        {
            !Softadastra::PasswordValidator::validatePasswordComplexity(password);
            m_password_hash = Softadastra::PasswordValidator::hashPassword(password);
        }

        ~Password() = default;
        const std::string &getPasswordHash() const { return m_password_hash; }
        void setPasswordHash(const std::string &password_hash) { m_password_hash = password_hash; }

        void validatePassword(const std::string &password) const
        {
            Softadastra::PasswordValidator::validatePassword(password, m_password_hash);
        }

    private:
        std::string m_password_hash{};
    };
} // namespace Softadastra

#endif // PASSWORD_HPP
