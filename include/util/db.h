#ifndef TURBO_DB_H
#define TURBO_DB_H

#include <vector>
#include <sstream>

#include "util/util_def.h"

#include "mysql/mysql.h"
#include "sqlite3.h"

namespace TURBO
{
    namespace UTIL
    {
        template<typename T>
        class IDB<T>
        {
        protected:
            T *handle;
            std::string db;
            std::string tb;

        public:
            virtual bool query(std::string query) = 0;
            bool createDatabase(std::string name);
            bool selectDatabase(std::string name);
            virtual bool existDatabase(std::string name) = 0;
            bool dropDatabase(std::string name);
            /**
             *
             * @note PRIMARY KEY can not be generically adjusted!
             * @param name
             * @param names
             * @param types
             * @param nulls
             * @param defaults
             * @param uniques
             * @param keys
             * @return
             */
            bool createTable(std::string name,
                             std::vector<std::string> names, std::vector<std::string> types,
                             std::vector<std::string> nulls, std::vector<std::string> defaults,
                             std::vector<std::string> uniques, std::vector<std::string> keys);
            bool existTable(std::string name);
            bool dropTable(std::string name);
        };

        class DB_MYSQL : public IDB<MYSQL>
        {
        public:
            DB_MYSQL(std::string host, std::string user, std::string pw, std::string db = "", Uint32 port = 0,
               std::string socket = "", Uint32 flags);
            ~DB_MYSQL();
            bool query(std::string query) override;
            bool existDatabase(std::string name) override;
        };

        class DB_SQLITE : public IDB<sqlite3>
        {
        public:
            explicit DB_SQLITE(std::string filename);
            ~DB_SQLITE();
            bool query(std::string query) override;
            bool existDatabase(std::string name) override;
        };
    }
}

#endif //TURBO_DB_H
