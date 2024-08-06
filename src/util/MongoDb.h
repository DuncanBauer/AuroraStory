#pragma once

#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>

#include "util/LoggingTool.h"
#include "util/TimeTool.h"
#include "Typedefs.h"

/*
Accounts collection
    _id           : ObjectId
    account_id    : number
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
    ban_reason    : number
    guest         : boolean
    nx            : number
*/

/*
Characters collection
    _id              : ObjectId
    account_id       : number
    character_id     : number
    world_id         : number
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

namespace util
{
    class MongoDb
    {
    public:
        // Delete copy constructor and assignment operator
        MongoDb(MongoDb const&)            = delete;
        MongoDb& operator=(MongoDb const&) = delete;

        // Static method to access the singleton instance
        static MongoDb&  getInstance();

        void             initialize(std::string const& uri, std::string const& db);
        u32              getNextSequence(std::string const& counterName);

        FindOneResult    accountExists(std::string const& username);
        InsertOneResult  autoRegisterAccount(std::string const& username, std::string const& passwordHash, std::string const& ip);
        UpdateResult     setPin(std::string const& username, std::string const& pin);
        FindOneResult    getCharacterByName(std::string const& name, u16 const worldId);
        FindOneResult    getCharacterById(u32 const id, u16 const worldId);
        InsertOneResult  createCharacter(std::string const& name, u16 const gender, u16 const skinColor, u16 const hair, u16 const face);

    private:
        // Private constructor to prevent instantiation
        MongoDb() = default;

        FindOneResult    findOneWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
        FindManyResult   findManyWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
        InsertOneResult  insertOneWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& document, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
        InsertManyResult insertManyWithRetry(mongocxx::collection& collection, std::vector<bsoncxx::document::view> const& documents, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
        UpdateResult     updateOneWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, bsoncxx::document::view const& update, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
        UpdateResult     updateManyWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, bsoncxx::document::view const& update, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
        FindOneResult    findOneAndUpdateWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, bsoncxx::document::view const& update, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
        DeleteResult     deleteOneWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
        DeleteResult     deleteManyWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
        FindOneResult    findOneAndDeleteWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, u16 max_retries = 3, u16 retry_u16erval_ms = 1000);
   
    private:
        bool                 m_initialized = false;
        mongocxx::uri        m_uri;
        mongocxx::client     m_client;
        mongocxx::database   m_db;

        // Collections
        mongocxx::collection m_counterCollection;
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