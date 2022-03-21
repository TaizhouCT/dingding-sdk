#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
extern "C" {
#include <cmocka.h>
}
#include <unistd.h>
#include "dingding.h"

#define CONFIG_FILE "config.json"

using string = std::string;
using json = nlohmann::json;

static DingDing *dd;

static __attribute__((constructor)) void ctor()
{
    std::ifstream ifs(CONFIG_FILE);
    json conf = json::parse(ifs);
    ifs.close();

    string APIKey = conf["dingding"]["APIKey"];
    string SecretKey = conf["dingding"]["SecretKey"];

    dd = new DingDing(APIKey, SecretKey);
    dd->init_access_token();
}

static __attribute__((destructor)) void dtor()
{
    delete dd;
}

static void test_dingding(void **status)
{
    json rs;

    dd->get_department_listsub(0, rs);
    printf("%s\n", rs.dump().c_str());
    dd->get_department_listsubid(1, rs);
    printf("%s\n", rs.dump().c_str());
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_dingding),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
