#ifndef __DINGDING_H
#define __DINGDING_H

#include <cstdint>
#include <string>
#include <list>
#include <nlohmann/json.hpp>

class DingDing {
    using string = std::string;
    using json = nlohmann::json;
public:
    DingDing(string APIKey, string SecretKey);
    virtual ~DingDing();
    int update_access_token();
    int get_department_listsub(int dept_id, json &rs);
    int get_department_listsubid(int dept_id, json &rs);
    int get_user_listsimple(int dept_id, int cursor, int size, json &rs);
    int get_user_listid(int dept_id, json &rs);
    int get_attendance_list(
        string date_from, string date_to,
        std::list<string> userid_list,
        int offset, int limit, json &rs);
    int get_attendance_updatedata(string userid, string date, json &rs);
    int get_checkin_record(
        std::list<string> userid_list,
        long start_time, long end_time,
        int cursor, int size, json &rs);

private:
    string APIKey;
    string SecretKey;
public:
    string accessToken;
    time_t expireTs;
};

#endif
