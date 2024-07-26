#pragma once

#include <vector>

#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/uri.hpp>

/*
Accounts collection
    _id           : ObjectId
    username      : string
    password_hash : string
    gm_level      : number
    logged_in     : number
    birthday      : number
    email         : string
    created_at    : number
    last_login    : number
    last_ip       : string
    banned        : boolean
    ban_reason    : string
    guest         : boolean
    nx            : number
*/

/*
Characters collection
    _id              : ObjectId
    account_id       : ObjectId
    name             : string
    gm               : number
    fame             : number
    level            : number
    job              : number
    rank             : number
    rank_move        : number
    job_rank         : number
    job_rank_move    : number
    exp              : number
    ap               : number
    sp               : number
    hp               : number
    mp               : number
    maxhp            : number
    maxmp            : number
    hp_ap_used       : number
    mp_ap_used       : number
    str              : number
    dex              : number
    luk              : number
    int              : number
    gender           : number
    skin_color       : number
    hair             : number
    face             : number
    party_id         : ObjectId
    guild_id         : ObjectId
    buddy_capacity   : number
    map              : number
    spawn_point      : number
    match_card_wins  : number
    match_card_loses : number
    match_card_ties  : number
    omok_wins        : number
    omok_loses       : number
    omok_ties        : number
    has_merchant     : ObjectId
    merchant_mesos   : number
    created_at       : number
*/

typedef std::chrono::seconds seconds_t;
typedef std::optional<bsoncxx::v_noabi::document::value> findOneResult;
typedef std::optional<mongocxx::v_noabi::cursor> findManyResult;
typedef std::optional<mongocxx::v_noabi::result::insert_one> insertOneResult;
typedef std::optional<mongocxx::v_noabi::result::insert_many> insertManyResult;
typedef std::optional<mongocxx::v_noabi::result::update> updateResult;
typedef std::optional<mongocxx::v_noabi::result::delete_result> deleteResult;

namespace db
{
    class DbHandler
    {
    public:
        DbHandler() {}
        ~DbHandler() {}

        void initialize(const std::string& mongoURI, const std::string& mongoDB);

        bool createAccount(const std::string& username, const std::string& password);
        bool createCharacter(const std::string& name, const uint16_t gender, const uint16_t skinColor,
            const uint16_t hair, const uint16_t face);

    private:
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
        mongocxx::uri m_uri;
        mongocxx::client m_client;
        mongocxx::database m_db;

        // Collections
        mongocxx::collection m_accountCollection;
        mongocxx::collection m_characterCollection;
        mongocxx::collection m_inventoriesCollection;
        mongocxx::collection m_buddyCollection;
        mongocxx::collection m_partyCollection;
        mongocxx::collection m_guildCollection;
        mongocxx::collection m_alliancesCollection;
        mongocxx::collection m_shopCollection;
        mongocxx::collection m_dropCollection;

        // Log collections
        mongocxx::collection m_ipLogCollection;
        mongocxx::collection m_banLogCollection;
        mongocxx::collection m_fameLogCollection;
        mongocxx::collection m_reportLogCollection;
        mongocxx::collection m_tradeLogCollection;
    };
}