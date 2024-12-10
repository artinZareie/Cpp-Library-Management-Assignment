#pragma once
#include "Utils/ArrayList.hpp"
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

class DatabaseDriver {
protected:
    virtual ~DatabaseDriver() = 0;
    std::string m_database;

public:
    using ValueTypes = std::variant<std::string, int, bool, double, std::size_t, float>;
    enum class FieldType {
        STRING,
        INT,
        BOOL,
        DOUBLE,
        SIZE_T,
        FLOAT
    };

    struct Field {
        FieldType type;
        bool is_primary_key;
        bool is_nullable;
        bool is_unique;

        Field(FieldType type, bool is_primary_key = false, bool is_nullable = true, bool is_unique = false) : 
        type(type), is_primary_key(is_primary_key), is_nullable(is_nullable), is_unique(is_unique) {}
    };

    using Record = std::unordered_map<std::string, ValueTypes>;
    using Schema = std::unordered_map<std::string, Field>;

    static std::shared_ptr<DatabaseDriver> getInstance();

    virtual bool createDatabase(const std::string &name) = 0;
    virtual bool createTable(const std::string &name, const std::unordered_map<std::string, Field> &fields) = 0;
    virtual bool dropTable(const std::string &name) = 0;
    virtual bool dropDatabase(const std::string &name) = 0;

    virtual bool insert(const std::string &table, const Record &record) = 0;
    virtual std::optional<Record> find(const std::string &table, const Record &constraints) = 0;
    virtual ArrayList<Record> findAll(const std::string &table, const Record &constraints) = 0;
    virtual bool remove(const std::string &table, const Record &constraints) = 0;
    virtual bool update(const std::string &table, const Record &constraints, const Record &updated) = 0;
};