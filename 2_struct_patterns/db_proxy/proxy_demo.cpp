#include <map>
#include <string>
#include <iostream>

#include "db_proxies.h"

int main() {
    auto real_db = VeryHeavyDatabase();
    auto cached_db = CacheProxyDB(std::addressof(real_db));
    auto test_db = TestDB(std::addressof(real_db));
    std::cout << cached_db.GetData("key") << std::endl;
    std::cout << cached_db.GetData("key") << std::endl;
    std::cout << test_db.GetData("key") << std::endl;

    auto short_life_db = OneShotDB(std::addressof(real_db), 2);
    std::cout << short_life_db.GetData("key") << std::endl;
    std::cout << short_life_db.GetData("key") << std::endl;
    std::cout << short_life_db.GetData("key") << std::endl;
    std::cout << short_life_db.GetData("key") << std::endl;

    return 0;
}