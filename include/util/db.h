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
        const unsigned char QUERY_CACHE_SIZE = 32;

        template<typename T>
        class IDB
        {
        protected:
            T                        *handle;
            std::string              db;
            std::string              tb;
            std::vector<std::string> query_cache;

        public:
            virtual T *getHandle();

            virtual bool query(std::string query) = 0;

            virtual std::vector<std::string> getQueryCache();

            virtual void cacheQuery(std::string query);

            virtual bool createDatabase(std::string name);

            virtual bool selectDatabase(std::string name);

            virtual bool existDatabase(std::string name) = 0;

            virtual bool dropDatabase(std::string name);

            /**
             *
             * @note PRIMARY KEY can not be generically adjusted!
             * @param table
             * @param names
             * @param types
             * @param nulls
             * @param defaults
             * @param uniques
             * @param keys
             * @return
             */
            virtual bool createTable(std::string table, std::vector<std::string> names, std::vector<std::string> types,
                                     std::vector<std::string> nulls, std::vector<std::string> defaults,
                                     std::vector<std::string> extras, std::vector<std::string> uniques,
                                     std::vector<std::string> keys)
            {
                std::stringstream sql;

                sql << "CREATE TABLE " << table << " (";

                if(names.size() == types.size())
                {
                    for(int index = 0; index < names.size(); ++index)
                    {
                        sql << names[index] << " " << types[index];
                        if(index < nulls.size())
                        {
                            sql << " " << nulls[index];
                        }
                        else
                        {
                            sql << " NOT NULL";
                        }

                        if(index < defaults.size())
                        {
                            sql << " DEFAULT '" << defaults[index] << "'";
                        }

                        if(index < extras.size())
                        {
                            sql << " " << defaults[index];
                        }

                        if(index < uniques.size())
                        {
                            sql << " UNIQUE";
                        }

                        if(index < keys.size())
                        {
                            sql << " PRIMARY KEY";
                        }

                        std::string del = (index == names.size() - 1) ? "" : ", ";
                        sql << del;
                    }
                }

                sql << ")";
                return query(sql.str());
            }

            virtual bool existTable(std::string name);

            virtual bool dropTable(std::string name);

            virtual bool insertEntry(std::string table, std::vector<std::string> names, std::vector<std::string> values)
            {
                std::stringstream sql;

                sql << "INSERT INTO " << table;

                if(names.size() == values.size())
                {
                    sql << "(";

                    for(int index = 0; index < names.size(); ++index)
                    {
                        std::string del = (index == names.size() - 1) ? "" : ", ";
                        sql << names[index] << del;
                    }

                    sql << ") VALUES(";

                    for(int index = 0; index < values.size(); ++index)
                    {
                        std::string del = (index == names.size() - 1) ? "" : ", ";
                        sql << "'" << values[index] << "'" << del;
                    }

                    sql << ")";
                }
                return query(sql.str());
            }

            virtual bool insertEntries(std::string table, std::vector<std::string> names,
                                       std::vector<std::vector<std::string>> values)
            {
                std::stringstream sql;

                return query(sql.str());
            }
        };

        class DB_MYSQL
            : public IDB<MYSQL>
        {
        public:
            DB_MYSQL(std::string host, std::string user, std::string pw, std::string db = "", Uint32 port = 0,
                     std::string socket = "", Uint32 flags = 0x0);

            ~DB_MYSQL();

            bool query(std::string query) override;

            bool useDatabase(std::string name);

            bool existDatabase(std::string name) override;
        };

        class DB_SQLITE
            : public IDB<sqlite3>
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
