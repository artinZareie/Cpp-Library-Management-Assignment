#pragma once
#include <Models/DatabaseDriver.hpp>
#include <filesystem>
#include <memory>

class FileDbDriver final : public DatabaseDriver {
private:
    std::filesystem::path m_base_path;

private:
    std::filesystem::path getDatabasePath() const;
    std::filesystem::path getTablePath(const std::string &table) const;

public:
    FileDbDriver(const std::string &database = "default", const std::filesystem::path &base_path = ".");

    static std::shared_ptr<DatabaseDriver> getInstance();

    bool createDatabase(const std::string &name) final;
    bool createTable(const std::unordered_map<std::string, Field> &fields) final;
    bool dropTable(const std::string &name) final;
    bool dropDatabase(const std::string &name) final;

    bool insert(const std::string &table, const Record &record) final;
    std::optional<Record> find(const std::string &table, const Record &constraints) final;
    ArrayList<Record> findAll(const std::string &table, const Record &constraints) final;
    bool remove(const std::string &table, const Record &constraints) final;
    bool update(const std::string &table, const Record &constraints, const Record &updated) final;

    ~FileDbDriver() final;
};