#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <cctype>
#include <regex>
#include <string>

namespace Softadastra
{
    class LengthExecption : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Erreur: la chaine depase la longeur maximale autoriser";
        }
    };

    class AlphaNumericException : std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Erreur: La chaine contient des caracteres non alphanumeriques";
        }
    };

    class InavlidEmailException : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Erreur: Email invalide";
        }
    };

    class InvalidPasswordException : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Erreur: Le mot de passe doit contenir au moins 8 caracteres dont une majucule, une minuscule et un caractere special.";
        }
    };

    class GenerateSaltException : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Erreur: lors de la génération du salt.";
        }
    };

    class HashPasswordException : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Erreur: lors du hachage du mot de passe.";
        }
    };

    class InvalidPhoneNumberException : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Erreur: numero de telephone invalide.";
        }
    };

    class ValidationException : public std::exception
    {
    public:
        explicit ValidationException(const std::string &message) : m_error_message(message) {}

        const char *what() const noexcept override
        {
            return m_error_message.c_str();
        }

    private:
        std::string m_error_message;
    };
} // namespace Softadastra

#endif