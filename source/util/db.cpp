#include "util/db.h"

namespace TURBO
{
    namespace UTIL
    {
        template<typename T>
        T* IDB<T>::getHandle()
        {
            return handle;
        }

        template<typename T>
        std::vector<std::string> IDB<T>::getQueryCache()
        {
            return query_cache;
        }

        template<typename T>
        void IDB<T>::cacheQuery(std::string query)
        {
            if(query_cache.size() == QUERY_CACHE_SIZE)
            {
                query_cache.erase(query_cache.begin());
            }
            query_cache.push_back(query);
        }

        template<typename T>
        bool IDB<T>::createDatabase(std::string name)
        {
            return query("CREATE DATABASE " + name);
        }

        template<typename T>
        bool IDB<T>::selectDatabase(std::string name)
        {
            return query("SELECT DATABASE " + name);
        }

        template<typename T>
        bool IDB<T>::dropDatabase(std::string name)
        {
            return query("DROP DATABASE " + name);
        }

        template<typename T>
        bool IDB<T>::existTable(std::string name)
        {
            return false;
        }

        template<typename T>
        bool IDB<T>::dropTable(std::string name)
        {
            return false;
        }

        DB_MYSQL::DB_MYSQL(std::string host, std::string user, std::string pw, std::string db, Uint32 port, std::string socket, Uint32 flags)
        {
            handle = mysql_init(nullptr);
            mysql_real_connect(handle, host.c_str(), user.c_str(), pw.c_str(), nullptr, port, nullptr, flags);
        }

        DB_MYSQL::~DB_MYSQL()
        {
            mysql_close(handle);
        }

        bool DB_MYSQL::query(std::string query)
        {
            cacheQuery(query);
            return (!mysql_query(handle, query.c_str()));
        }

        bool DB_MYSQL::useDatabase(std::string name)
        {
            return (query("USE " + name));
        }

        bool DB_MYSQL::existDatabase(std::string name)
        {
            query("SHOW DATABASES LIKE " + name);

            MYSQL_RES *result = mysql_store_result(handle);

            return (mysql_num_fields(result) > 0);
        }

        DB_SQLITE::DB_SQLITE(std::string filename)
        {
            if(!sqlite3_open(filename.c_str(), &handle))
            {
                db = filename;
            }
        }

        DB_SQLITE::~DB_SQLITE()
        {
            if(!db.empty())
            {
                sqlite3_close(handle);
                db = "";
            }
        }

        bool DB_SQLITE::query(std::string query)
        {
            cacheQuery(query);
            return (!sqlite3_exec(handle, query.c_str(), nullptr, nullptr, nullptr));
        }

        bool DB_SQLITE::existDatabase(std::string name)
        {
            return false;
        }
    }
}