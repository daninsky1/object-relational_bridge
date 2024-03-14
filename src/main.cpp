#include <iostream>
#include <vector>
#include <type_traits>
#include <cstdint>
#include <string.h>
#include <sqlite3.h>

class Database {
    // TODO: Detalhes de implementação do banco de dados
public:
    Database() {
        int err = sqlite3_open(filename, db_handle);
        if (err) {
            exit(1);
        }
    }
    
    void execute(const char* sql_stmt) {
        sqlite3_stmt**  stmt;
        const char** tail;
        sqlite3_prepare(*db_handle, sql_stmt, strlen(sql_stmt), stmt, tail);
        if (!SQLITE_OK) {
            std::cerr << "Erro ao executar SQL.\n";
            return;
        }
        sqlite3_prepare(*db_handle);
    }
    
    static sqlite3** db_hanle
    constexpr static const char* filename = "Car_Database.db";
};

enum ColumnType {
    INTEGER,
    VARCHAR
};

struct ColumnInterface {
    std::string name;
    ColumnType type;
    int size;
    int precision;
    int scale;
    bool primary_key;
    bool not_null;
};

template<typename T>
struct Column : ColumnInterface {
public:
    Column(std::string n, ColumnType t)
        : ColumnInterface{.name = n, .type = t} {
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
    Entity(std::string name) : table_name{name} {}
    std::string table_name;
};

// TODO: Adicionar validação de colunas repetidas
class Custumer : public Entity {
public:
    Custumer()
    : Entity{"Custumer"} { }
    Column<int> custumer_id{"custumer_id", ColumnType::INTEGER};
    Column<std::string> first_name{"first_name", ColumnType::VARCHAR};
    Column<std::string> last_name{"last_name", ColumnType::VARCHAR};
    Column<std::string> gender{"gender", ColumnType::VARCHAR};
    Column<int> house_income{"house_income", ColumnType::INTEGER};
    Column<std::string> email{"email", ColumnType::INTEGER};
    std::vector<ColumnInterface*> columns{
        &custumer_id,
        &first_name
    };
};

template<typename T>
class Repository {
    static_assert(std::is_base_of<Entity, T>::value, "Repository require an Entity type");
public:
    std::string findById() {
        std::string stmt = "SELECT * FROM " + entity.table_name + ';';
        return stmt;
    }
    std::string findBy(ColumnInterface column) {
        std::string stmt = "SELECT " + column.name + " FROM " + entity.table_name +
            ';';
        return stmt;
    }
    T entity;
    static Database database;
};

int main() {
    Custumer custumer;
    Repository<Custumer> custumer_dao;
    std::cout << custumer_dao.findById() << '\n';
    std::cout << custumer_dao.findBy(custumer.first_name) << '\n';
    std::cout << custumer_dao.findBy(custumer.last_name) << '\n';
    for (auto column : custumer.columns) {
        std::cout << column->name << '\n';
    }
}
