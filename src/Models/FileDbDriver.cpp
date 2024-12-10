#include <Models/DatabaseDriver.hpp>
#include <Models/FileDbDriver.hpp>
#include <memory>

std::shared_ptr<DatabaseDriver> FileDbDriver::getInstance() {
    static std::shared_ptr<DatabaseDriver> instance = std::make_shared<FileDbDriver>();

    return instance;
}

FileDbDriver::FileDbDriver(const std::string &database, const std::filesystem::path &base_path) : 
    DatabaseDriver(database), m_base_path(base_path) {}

FileDbDriver::~FileDbDriver() {

}