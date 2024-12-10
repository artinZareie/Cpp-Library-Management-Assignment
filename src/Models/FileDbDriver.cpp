#include <Models/DatabaseDriver.hpp>
#include <Models/FileDbDriver.hpp>
#include <fstream>
#include <memory>

std::shared_ptr<DatabaseDriver> FileDbDriver::getInstance() {
    static std::shared_ptr<DatabaseDriver> instance = std::make_shared<FileDbDriver>();

    return instance;
}

std::filesystem::path FileDbDriver::getDatabasePath() const {
    return getDatabasePath(m_database);
}

std::filesystem::path FileDbDriver::getDatabasePath(const std::string &name) const {
    return m_base_path / name;
}

std::filesystem::path FileDbDriver::getTablePath(const std::string &table) const {
    return getDatabasePath(m_database) / table;
}

void FileDbDriver::setBasePath(const std::filesystem::path &path) {
    m_base_path = path;
}

void FileDbDriver::setDatabase(const std::string &name) {
    m_database = name;
}

std::string FileDbDriver::getDatabase() const {
    return m_database;
}

std::filesystem::path FileDbDriver::getBasePath() const {
    return m_base_path;
}

bool FileDbDriver::createDatabase(const std::string &name) {
    auto path = getDatabasePath(name);

    if (std::filesystem::exists(path)) {
        return false;
    }

    std::filesystem::create_directory(path);
    return true;
}

bool FileDbDriver::createTable(const std::string &name, const std::unordered_map<std::string, Field> &fields) {
    auto path = getTablePath(name);

    if (std::filesystem::exists(path)) {
        return false;
    }

    std::ofstream table_file(path);

    for (const auto &[name, field] : fields) {
        table_file << name << ": " << static_cast<size_t>(field.type) << ", " << 
        field.is_primary_key << ", " << field.is_nullable << ", " << field.is_unique << "\n";
    }

    return true;
}

FileDbDriver::~FileDbDriver() {

}