#include <iostream>
#include <vector>
#include <type_traits>
#include <cstdint>
#include <sqlite3.h>

enum ColumnType {
    INTEGER,
    VARCHAR
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

template<typename T>
class Column : public ColumnInterface {
public:
    Column(std::string n, ColumnType t)
        : ColumnInterface(n, t) {
    }
    T get_value() {
        return value;
    }
    
    void set_value(T v) {
        value = v;
    }
private:
    T value;
    T default_value;
};

class Entity {
public:
    virtual std::vector<ColumnInterface*> get_columns() = 0;
};

class Custumer : public Entity {
    Column<int> custumer_id{"custumer_id", ColumnType::INTEGER};
    Column<std::string> first_name{"first_name", ColumnType::VARCHAR};
    
    std::vector<ColumnInterface*> get_columns() override {
        std::vector<ColumnInterface*> r;
        r.push_back(&custumer_id);
        r.push_back(&first_name);
        return r;
    }
};

template<typename T>
class Repository {
public:
    Repository() { }
    
};

template<uint32_t N>
struct binary {
    static uint32_t const value = binary<N/10>::value << 1 | N%10;
};

template<>
struct binary<0> {
    static uint32_t const value = 0;
};

int main() {
    std::cout << binary<10>::value;
}
