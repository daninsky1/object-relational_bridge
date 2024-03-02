#include <iostream>
#include <vector>
#include <type_traits>
#include <cstdint>
#include <sqlite3.h>

enum ColumnType {
    INTEGER,
    VARCHAR
};

template<typename T>
class Column {
public:
    Column(std::string n, ColumnType t)
        : name{n}
        , type{t} {
    }
    T get_value() {
        return T;
    }
    
    void set_value(T v) {
        value = v;
    }
private:
    std::string name;
    ColumnType type;
    int size;
    int precision;
    int scale;
    bool primary_key;
    bool not_null;
};

class ColumnInterface {
public:
    std::string name;
    ColumnType type;
    int size;
    int precision;
    int scale;
    bool primary_key;
    bool not_null;

    ColumnInterface(std::string n, ColumnType t)
        : name{n}
        , type{t} {
    }
};

class ColumnInteger : public ColumnInterface {
public:
    uint64_t default_value;
    uint64_t value;

    ColumnInteger(std::string name, ColumnType type)
        : ColumnInterface(name, type) {
    }
};

class ColumnString : public ColumnInterface {
public:
    std::string default_value;
    std::string value;

    ColumnString(std::string name, ColumnType type)
        : ColumnInterface(name, type) {
    }
};

class Entity {
public:
    virtual std::vector<ColumnInterface*> get_columns() = 0;
};

template<typename T>
class Repository {
public:
    Repository() {
    }
};

class CustumerEntity : public Entity {
    ColumnInteger custumer_id{"custumer_id", ColumnType::INTEGER};
    ColumnString first_name{"first_name", ColumnType::VARCHAR};
};

class Custumer {
    Column<int> custumer_id{"custumer_id", ColumnType::INTEGER};
    Column<std::string> first_name{"first_name", ColumnType::VARCHAR};
};

int main() {
    
}
