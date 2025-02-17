#include <chrono>
#include "User.hpp"
#include "Validator.hpp"

namespace Softadastra
{
    User::User()
        : m_email(),
          m_password(),
          m_created_at(std::time(nullptr)),
          m_update_at(std::time(nullptr)) {}

    User::User(const std::string &firstname,
               const std::string &lastname,
               const std::string &username,
               const std::shared_ptr<Email> &email,
               const std::shared_ptr<Password> &password,
               const std::shared_ptr<Phone> &phone)
        : m_firstname(firstname), m_lastname(lastname), m_username(username),
          m_email(email), m_password(password), m_phone(phone), m_created_at(std::time(nullptr)), m_update_at(std::time(nullptr))
    {
        Softadastra::Validator::validateFirstname(firstname);
        Softadastra::Validator::validateLastName(lastname);
        Softadastra::Validator::validateUserName(username);
    }

    User::User(const User &rhs)
        : m_id(rhs.m_id), m_firstname(rhs.m_firstname), m_lastname(rhs.m_lastname),
          m_username(rhs.m_username), m_email(rhs.m_email), m_password(rhs.m_password), m_phone(rhs.m_phone),
          m_is_active(rhs.m_is_active), m_otp(rhs.m_otp), m_created_at(rhs.m_created_at),
          m_update_at(rhs.m_update_at) {}

    User &User::operator=(const User &rhs)
    {
        if (this != &rhs)
        {
            m_id = rhs.m_id;
            m_firstname = rhs.m_firstname;
            m_lastname = rhs.m_lastname;
            m_username = rhs.m_username;
            m_email = rhs.m_email;
            m_password = rhs.m_password;
            m_phone = rhs.m_phone;
            m_is_active = rhs.m_is_active;
            m_otp = rhs.m_otp;
            m_created_at = rhs.m_created_at;
            m_update_at = rhs.m_update_at;
        }
        return *this;
    }

    User::User(User &&rhs) noexcept
        : m_id(rhs.m_id), m_firstname(std::move(rhs.m_firstname)), m_lastname(std::move(rhs.m_lastname)),
          m_username(std::move(rhs.m_username)), m_email(std::move(rhs.m_email)),
          m_password(std::move(rhs.m_password)), m_phone(std::move(rhs.m_phone)), m_is_active(rhs.m_is_active), m_otp(rhs.m_otp),
          m_created_at(rhs.m_created_at), m_update_at(rhs.m_update_at)
    {
        rhs.m_id = 0;
        rhs.m_is_active = false;
        rhs.m_otp = 0;
        rhs.m_created_at = 0;
        rhs.m_update_at = 0;
    }

    User &User::operator=(User &&rhs) noexcept
    {
        if (this != &rhs)
        {
            m_id = rhs.m_id;
            m_firstname = std::move(rhs.m_firstname);
            m_lastname = std::move(rhs.m_lastname);
            m_username = std::move(rhs.m_username);
            m_email = std::move(rhs.m_email);
            m_password = std::move(rhs.m_password);
            m_phone = std::move(rhs.m_phone);
            m_is_active = rhs.m_is_active;
            m_otp = rhs.m_otp;
            m_created_at = rhs.m_created_at;
            m_update_at = rhs.m_update_at;

            rhs.m_id = 0;
            rhs.m_is_active = false;
            rhs.m_otp = 0;
            rhs.m_created_at = 0;
            rhs.m_update_at = 0;
        }
        return *this;
    }

    void User::displayInfo() const
    {
        std::cout << "ID: " << m_id << "\n"
                  << "Name: " << m_firstname << " " << m_lastname << "\n"
                  << "Username: " << m_username << "\n"
                  << "Email: " << m_email->getEmail() << "\n"
                  << "Password: " << m_password->getPasswordHash() << "\n"
                  << "Phone: " << m_phone->getPhone() << "\n"
                  << "Active: " << (m_is_active ? "Yes" : "No") << "\n"
                  << "OTP: " << m_otp << std::endl;
    }

    json User::to_json() const
    {
        return json{
            {"firstname", m_firstname},
            {"lastname", m_lastname},
            {"username", m_username},
            {"email", m_email->getEmail()},
            {"password_hash", m_password->getPasswordHash()},
            {"phone", m_phone->getPhone()},
            {"create_at", std::to_string(m_created_at)}};
    }

    void User::form_json(const json &j)
    {
        m_firstname = j.at("firstname").get<std::string>();
        m_lastname = j.at("lastname").get<std::string>();
        m_username = j.at("username").get<std::string>();
        m_email = std::make_shared<Email>(j.at("email").get<std::string>());
        m_password = std::make_shared<Password>(j.at("password_hash").get<std::string>());
        m_phone = std::make_shared<Phone>(j.at("phone").get<std::string>());

        std::string created_at_str = j.at("create_at").get<std::string>();
        m_created_at = std::stoll(created_at_str);
    }

    void User::displayCreatedAt() const
    {
        std::cout << "Account created at: " << std::ctime(&m_created_at);
    }

    void User::warning(const std::string &message) const
    {
        std::cout << "Warning: " << message << std::endl;
    }
}
