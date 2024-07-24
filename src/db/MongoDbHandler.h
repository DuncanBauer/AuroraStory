#pragma once

#include <vector>

#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/uri.hpp>

// Accounts collection
//{
//    "_id": "user_id",
//    "username"         : "username",
//    "password_hash"    : "hashed_password",
//    "salt"             : "salt",
//    "created_at"       : "timestamp",
//    "last_login"       : "timestamp",
//    "status"           : "int",
//}

using seconds_t = std::chrono::seconds;

const std::string k_mongoDbUri = "mongodb://localhost:27017";
const std::string k_database = "aurorastory";

typedef std::optional<bsoncxx::v_noabi::document::value> findOneResult;
typedef std::optional<mongocxx::v_noabi::cursor> findManyResult;
typedef std::optional<mongocxx::v_noabi::result::insert_one> insertOneResult;
typedef std::optional<mongocxx::v_noabi::result::insert_many> insertManyResult;
typedef std::optional<mongocxx::v_noabi::result::update> updateResult;
typedef std::optional<mongocxx::v_noabi::result::delete_result> deleteResult;

enum class UserStatus
{
    OFFLINE,
    ONLINE
};

class MongoDbHandler
{

public:
    MongoDbHandler() : m_uri(k_mongoDbUri), m_client(mongocxx::client(m_uri)), m_db(m_client[k_database]) {}
    ~MongoDbHandler() {}

private:
    bool createAccountDoc(const std::string& username, const std::string& password);
    bool deleteAccountDoc(const std::string& accountId);

    findOneResult findOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
                                   int max_retries = 3, int retry_interval_ms = 1000);
    findManyResult findManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
                                     int max_retries = 3, int retry_interval_ms = 1000);
    insertOneResult insertOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& document,
                                       int max_retries = 3, int retry_interval_ms = 1000);
    insertManyResult insertManyWithRetry(mongocxx::collection& collection, const std::vector<bsoncxx::document::view>& documents,
                                         int max_retries = 3, int retry_interval_ms = 1000);
    updateResult updateOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
                                    int max_retries = 3, int retry_interval_ms = 1000);
    updateResult updateManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
                                     int max_retries = 3, int retry_interval_ms = 1000);
    findOneResult findOneAndUpdateWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
                                            int max_retries = 3, int retry_interval_ms = 1000);
    deleteResult deleteOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
                                    int max_retries = 3, int retry_interval_ms = 1000);
    deleteResult deleteManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
                                     int max_retries = 3, int retry_interval_ms = 1000);
    findOneResult findOneAndDeleteWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
                                            int max_retries = 3, int retry_interval_ms = 1000);

private:
    //mongocxx::instance m_instance{};
    mongocxx::uri m_uri;
    mongocxx::client m_client;
    mongocxx::database m_db;

    // Collections
    mongocxx::collection m_accountCollection    = m_db["accounts"];
    mongocxx::collection m_characterCollection  = m_db["characters"];
    // mongocxx::collection m_partyCollection      = m_db["parties"];
    // mongocxx::collection m_guildCollection      = m_db["guilds"];
    // mongocxx::collection m_shopCollection       = m_db["shops"];
    // mongocxx::collection m_dropCollection       = m_db["drops"];
};