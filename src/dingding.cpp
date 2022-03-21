#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <restclient-cpp/restclient.h>
#include <restclient-cpp/connection.h>
#include <spdlog/spdlog.h>
#include "dingding.h"

using string = std::string;
using json = nlohmann::json;

static RestClient::Connection *get_conn(string url)
{
    RestClient::Connection *conn = new RestClient::Connection(url);
    conn->SetTimeout(5);
    RestClient::HeaderFields headers;
    headers["Accept"] = "application/json";
    conn->SetHeaders(headers);
    conn->AppendHeader("Content-Type", "application/json");
    return conn;
}

static void put_conn(RestClient::Connection *conn)
{
    delete conn;
}

static int rs_parse(RestClient::Response &r, json &rs)
{
    if (r.code != 200) {
        spdlog::error("code: %d, body: %s", r.code, r.body.c_str());
        return -1;
    }

    try {
        rs = json::parse(r.body);
    } catch (json::exception &ex) {
        std::cerr << __func__ << ":" << ex.what() << std::endl;
        return -1;
    }

    return 0;
}

DingDing::DingDing(string APIKey, string SecretKey)
{
    this->APIKey = APIKey;
    this->SecretKey = SecretKey;
}

DingDing::~DingDing()
{
}

int DingDing::init_access_token()
{
    string url = "https://api.dingtalk.com";
    string api = "/v1.0/oauth2/accessToken";
    json j;
    j["appKey"] = this->APIKey;
    j["appSecret"] = this->SecretKey;

    auto conn = get_conn(url);
    RestClient::Response r = conn->post(api, j.dump().c_str());
    put_conn(conn);
    json rs;
    int rc = rs_parse(r, rs);
    this->accessToken = rs["accessToken"];
    return rc;
}

int DingDing::get_department_listsub(int dept_id, json &rs)
{
    string url = "https://oapi.dingtalk.com";
    string api = "/topapi/v2/department/listsub?access_token=" + accessToken;
    json j;
    if (dept_id != 0) j["dept_id"] = dept_id;
    j["language"] = "zh_CN";

    auto conn = get_conn(url);
    RestClient::Response r = conn->post(api, j.dump().c_str());
    put_conn(conn);
    return rs_parse(r, rs);
}

int DingDing::get_department_listsubid(int dept_id, json &rs)
{
    string url = "https://oapi.dingtalk.com";
    string api = "/topapi/v2/department/listsubid?access_token=" + accessToken;
    json j;
    j["dept_id"] = dept_id;

    auto conn = get_conn(url);
    RestClient::Response r = conn->post(api, j.dump().c_str());
    put_conn(conn);
    return rs_parse(r, rs);
}

int DingDing::get_user_listsimple(int dept_id, int cursor, int size, json &rs)
{
    string url = "https://oapi.dingtalk.com";
    string api = "/topapi/user/listsimple?access_token=" + accessToken;
    json j;
    j["dept_id"] = dept_id;
    j["cursor"] = cursor;
    j["size"] = size;
    j["language"] = "zh_CN";

    auto conn = get_conn(url);
    RestClient::Response r = conn->post(api, j.dump().c_str());
    put_conn(conn);
    return rs_parse(r, rs);
}

int DingDing::get_user_listid(int dept_id, json &rs)
{
    string url = "https://oapi.dingtalk.com";
    string api = "/topapi/user/listid?access_token=" + accessToken;
    json j;
    j["dept_id"] = dept_id;

    auto conn = get_conn(url);
    RestClient::Response r = conn->post(api, j.dump().c_str());
    put_conn(conn);
    return rs_parse(r, rs);
}

int DingDing::get_attendance_list(
    string date_from, string date_to,
    std::list<string> userid_list,
    int offset, int limit, json &rs)
{
    string url = "https://oapi.dingtalk.com";
    string api = "/attendance/list?access_token=" + accessToken;
    json j;
    j["workDateFrom"] = date_from;
    j["workDateTo"] = date_to;
    j["userIdList"] = json::array();
    int i = 0;
    for (auto item : userid_list)
        j["userIdList"][i++] = item;
    j["offset"] = offset;
    j["limit"] = limit;

    auto conn = get_conn(url);
    RestClient::Response r = conn->post(api, j.dump().c_str());
    put_conn(conn);
    return rs_parse(r, rs);
}

int DingDing::get_checkin_record(
    std::list<string> userid_list,
    long start_time, long end_time,
    int cursor, int size, json &rs)
{
    string url = "https://oapi.dingtalk.com";
    string api = "/topapi/checkin/record/get?access_token=" + accessToken;
    json j;
    j["userid_list"] = "";
    for (auto item : userid_list)
        j["userid_list"] = j["userid_list"].get<string>() + "," + item;
    j["start_time"] = start_time;
    j["end_time"] = end_time;
    j["cursor"] = cursor;
    j["size"] = size;

    auto conn = get_conn(url);
    RestClient::Response r = conn->post(api, j.dump().c_str());
    put_conn(conn);
    return rs_parse(r, rs);
}
