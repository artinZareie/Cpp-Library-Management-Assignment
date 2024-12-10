#pragma once
#include "Utils/ArrayList.hpp"
#include <Models/DatabaseDriver.hpp>
#include <any>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>

template<class Resource>
class Model {
private:
    static std::string m_table;
    static std::shared_ptr<DatabaseDriver> m_db;
    static std::unordered_map<std::string, std::any> m_fields;
    static std::unordered_set<std::string> m_immutable;
    std::unordered_map<std::string, std::any> m_data;

public:
    static std::optional<Model> findOrFail(const std::unordered_map<std::string, std::any> &constraints);
    static ArrayList<Resource> findAll(const std::unordered_map<std::string, std::any> &constraints);
    static bool findAndRemove(const std::unordered_map<std::string, std::any> &constraints);
    static ArrayList<Resource> all();
    static bool remove(const std::unordered_map<std::string, std::any> &constraints);

    virtual bool remove();
    virtual bool save();

    virtual ~Model() {
        m_db = nullptr;
    }
};