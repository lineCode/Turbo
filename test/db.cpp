#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TCH = TURBO::CHART;
namespace TV = TURBO::VIDEO;
namespace TI = TURBO::INPUT;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TN = TURBO::NET;
namespace TS = TURBO::SYSTEM;
namespace TC = TURBO::SCRIPT;

void database()
{
    TU::DB_SQLITE sqlite{"resources/db.sqlite"};

    TU::DB_MYSQL mysql{"localhost", "root", "root"};
    mysql.dropDatabase("Turbo");
    mysql.createDatabase("Turbo");
    mysql.useDatabase("Turbo");

    mysql.createTable("Cars",
                      std::vector<std::string>{"Id", "Name", "Price"},
                      std::vector<std::string>{"INT", "TEXT", "INT"},
                      std::vector<std::string>{},
                      std::vector<std::string>{},
                      std::vector<std::string>{},
                      std::vector<std::string>{},
                      std::vector<std::string>{"PRIMARY KEY"});

    mysql.insertEntry("Cars", std::vector<std::string>{"Id", "Name", "Price"},
                      std::vector<std::string>{"0", "Test", "100"});

    for(auto &query : mysql.getQueryCache())
    {
        LOG(query);
    }
}