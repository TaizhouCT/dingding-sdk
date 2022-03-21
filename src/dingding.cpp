#include <string>
#include <sstream>
#include <iostream>
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
    auto conn = get_conn(url);

    json j;
    j["appKey"] = this->APIKey;
    j["appSecret"] = this->SecretKey;
    RestClient::Response r = conn->post(api, j.dump().c_str());

    if (r.code != 200) {
        spdlog::error("code: %d, body: %s", r.code, r.body.c_str());
        return -1;
    }

    try {
        json rs = json::parse(r.body);
        this->accessToken = rs["accessToken"];
    } catch (json::exception &ex) {
        std::cerr << __func__ << ":" << ex.what() << std::endl;
        return -1;
    }

    put_conn(conn);
    return 0;
}

int DingDing::get_department_listsub(int dept_id, json &rs)
{
    string url = "https://oapi.dingtalk.com";
    string api = "/topapi/v2/department/listsub?access_token=" + accessToken;
    auto conn = get_conn(url);

    json j;
    if (dept_id != 0) j["dept_id"] = dept_id;
    j["language"] = "zh_CN";
    RestClient::Response r = conn->post(api, j.dump().c_str());

    if (r.code != 200) {
        spdlog::error("code: %d, body: %s", r.code, r.body.c_str());
        return -1;
    }

    try {
        rs = json::parse(r.body);
    } catch (json::exception &ex) {
        std::cerr << __func__ << ":" << ex.what() << std::endl;
    }

    put_conn(conn);
    return 0;
}

int DingDing::get_department_listsubid(int dept_id, json &rs)
{
    string url = "https://oapi.dingtalk.com";
    string api = "/topapi/v2/department/listsubid?access_token=" + accessToken;
    auto conn = get_conn(url);

    json j;
    if (dept_id != 0) j["dept_id"] = dept_id;
    RestClient::Response r = conn->post(api, j.dump().c_str());

    if (r.code != 200) {
        spdlog::error("code: %d, body: %s", r.code, r.body.c_str());
        return -1;
    }

    try {
        rs = json::parse(r.body);
    } catch (json::exception &ex) {
        std::cerr << __func__ << ":" << ex.what() << std::endl;
    }

    put_conn(conn);
    return 0;
}
