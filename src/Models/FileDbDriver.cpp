#include <Models/DatabaseDriver.hpp>
#include <Models/FileDbDriver.hpp>
#include <memory>

std::shared_ptr<DatabaseDriver> FileDbDriver::getInstance() {
    static std::shared_ptr<DatabaseDriver> instance = std::make_shared<FileDbDriver>();

    return instance;
}

void FileDbDriver::setBasePath(const std::filesystem::path &path) {
    m_base_path = path;
}

void FileDbDriver::setDatabase(const std::string &name) {
    m_database = name;
}

FileDbDriver::~FileDbDriver() {

}