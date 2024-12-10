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
    static std::shared_ptr<DatabaseDriver> getInstance();

    void setBasePath(const std::filesystem::path &path);
    void setDatabase(const std::string &name);

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