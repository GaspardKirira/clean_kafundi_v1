#include <iostream>
#include <fstream>
#include <string>

class User
{
public:
    std::string m_firstname;
    std::string m_lastname;
    int m_age;

    // Sérialisation binaire
    void serialize(std::ofstream &out) const
    {
        size_t firstname_len = m_firstname.size();
        size_t lastname_len = m_lastname.size();

        // Sérialiser les longueurs des chaînes
        out.write(reinterpret_cast<const char *>(&firstname_len), sizeof(firstname_len));
        out.write(m_firstname.c_str(), firstname_len);

        out.write(reinterpret_cast<const char *>(&lastname_len), sizeof(lastname_len));
        out.write(m_lastname.c_str(), lastname_len);

        // Sérialiser l'âge
        out.write(reinterpret_cast<const char *>(&m_age), sizeof(m_age));
    }

    // Désérialisation binaire
    void deserialize(std::ifstream &in)
    {
        size_t firstname_len, lastname_len;

        // Désérialiser les longueurs des chaînes
        in.read(reinterpret_cast<char *>(&firstname_len), sizeof(firstname_len));
        m_firstname.resize(firstname_len);
        in.read(&m_firstname[0], firstname_len);

        in.read(reinterpret_cast<char *>(&lastname_len), sizeof(lastname_len));
        m_lastname.resize(lastname_len);
        in.read(&m_lastname[0], lastname_len);

        // Désérialiser l'âge
        in.read(reinterpret_cast<char *>(&m_age), sizeof(m_age));
    }
};

int main()
{
    User user1;
    user1.m_firstname = "John";
    user1.m_lastname = "Doe";
    user1.m_age = 30;

    // Sérialisation dans un fichier binaire
    std::ofstream out("user.dat", std::ios::binary);
    user1.serialize(out);
    out.close();

    // Désérialisation depuis un fichier binaire
    User user2;
    std::ifstream in("user.dat", std::ios::binary);
    user2.deserialize(in);
    in.close();

    std::cout << "User2: " << user2.m_firstname << " " << user2.m_lastname << ", Age: " << user2.m_age << std::endl;

    return 0;
}
