#ifndef __DINGDING_H
#define __DINGDING_H

#include <string>
#include <nlohmann/json.hpp>

class DingDing {
    using string = std::string;
    using json = nlohmann::json;
public:
    DingDing(string APIKey, string SecretKey);
    virtual ~DingDing();
    int init_access_token();
    int get_department_listsub(int dept_id, json &rs);
    int get_department_listsubid(int dept_id, json &rs);

private:
    string APIKey;
    string SecretKey;
    string accessToken;
};

#endif
