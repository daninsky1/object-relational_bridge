#include <iostream>
#include <vector>
#include <type_traits>
#include <cstdint>
#include <string.h>
#include <sqlite3.h>

struct ResultSet {
    char** result;
    int n_row;
    int n_col;
    char *errmgs;
};

class Database {
    // TODO: Detalhes de implementação do banco de dados
public:
    Database() {
        int err = sqlite3_open_v2(filename, &db_handle, SQLITE_OPEN_READWRITE, NULL);
        if (err != SQLITE_OK) {
            std::cout << sqlite3_errmsg(db_handle) << '\n';
            exit(1);
        } else {
            std::cout << "Successufully opened database.\n";
        }
    }
    
    ResultSet execute(const char* sql_stmt) {
        std::cout << sql_stmt << '\n';
        sqlite3_stmt**  stmt;
        const char** tail;
        //sqlite3_prepare(*db_handle, sql_stmt, strlen(sql_stmt), stmt, tail);
        //sqlite3_step(*stmt);
        char** result_set;
        char *errmgs;
        int n_row;
        int n_col;
        int err = sqlite3_get_table(db_handle, sql_stmt, &result_set, &n_row, &n_col, &errmgs);
        std::cout << sqlite3_errstr(err) << '\n';
        //for (int i = 0; i < n_row * n_col; i++) {
        //    std::cout << result_set[i] << '\n';
        //}
        return ResultSet{result_set, n_row, n_col, errmgs};
    }
    sqlite3* db_handle;
    const char* filename = "../car_company_database/Car_Database.db";
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
    Column(ColumnInterface col)
        : ColumnInterface{col} {
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
    : Entity{"Customers"} { }
    Column<int> custumer_id{ColumnInterface{.name = "custumer_id", .type = ColumnType::INTEGER}};
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
    Repository() {
        
    }
    std::string findById() {
        std::string stmt = "SELECT * FROM " + entity.table_name + ';';
        ResultSet rs = database.execute(stmt.c_str());
        for (int i = 0; i < rs.n_row * rs.n_col; i++) {
            std::cout << rs.result[i] << '\n';
        }
        return stmt;
    }
    std::string findBy(ColumnInterface column) {
        std::string stmt = "SELECT " + column.name + " FROM " + entity.table_name +
            ';';
        return stmt;
    }
    T entity;
    Database database{};
};

int main() {
    Custumer custumer;
    Repository<Custumer> custumer_dao;
    custumer_dao.findById();
}
