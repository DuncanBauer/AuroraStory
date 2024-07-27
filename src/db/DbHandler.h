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
    u16              : number
    gender           : number
    skin_color       : number
    hair             : number
    face             : number
    party_id         : ObjectId
    guild_id         : ObjectId
    buddy_capacity   : number
    map              : number
    spawn_pou16      : number
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

class DbHandler
{
public:
    DbHandler() = delete;

    static void initialize(const std::string& mongoURI, const std::string& mongoDB);

    static bool createAccount(const std::string& username, const std::string& password);
    static bool createCharacter(const std::string& name, const u16 gender, const u16 skinColor,
        const u16 hair, const u16 face);

private:
    static findOneResult findOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
    static findManyResult findManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
    static insertOneResult insertOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& document,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
    static insertManyResult insertManyWithRetry(mongocxx::collection& collection, const std::vector<bsoncxx::document::view>& documents,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
    static updateResult updateOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
    static updateResult updateManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
    static findOneResult findOneAndUpdateWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
    static deleteResult deleteOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
    static deleteResult deleteManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
    static findOneResult findOneAndDeleteWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries = 3, u16 retry_u16erval_ms = 1000);

private:
    static mongocxx::uri m_uri;
    static mongocxx::client m_client;
    static mongocxx::database m_db;

    // Collections
    static mongocxx::collection m_accountCollection;
    static mongocxx::collection m_characterCollection;
    static mongocxx::collection m_inventoriesCollection;
    static mongocxx::collection m_buddyCollection;
    static mongocxx::collection m_partyCollection;
    static mongocxx::collection m_guildCollection;
    static mongocxx::collection m_alliancesCollection;
    static mongocxx::collection m_shopCollection;
    static mongocxx::collection m_dropCollection;

    // Log collections
    static mongocxx::collection m_ipLogCollection;
    static mongocxx::collection m_banLogCollection;
    static mongocxx::collection m_fameLogCollection;
    static mongocxx::collection m_reportLogCollection;
    static mongocxx::collection m_tradeLogCollection;
};