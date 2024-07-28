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

namespace util
{
    class MongoDb
    {
    public:
        MongoDb() = delete;

        static inline void initialize(const std::string& mongoURI, const std::string& mongoDB)
        {
            m_uri = mongocxx::uri(mongoURI);
            m_client = mongocxx::client(mongocxx::client(m_uri));
            m_db = mongocxx::database(m_client[mongoDB]);
            mongocxx::instance m_instance{};

            // Collections
            m_accountCollection = m_db["accounts"];
            m_characterCollection = m_db["characters"];
            m_inventoriesCollection = m_db["inventories"];
            m_buddyCollection = m_db["buddies"];
            m_partyCollection = m_db["parties"];
            m_guildCollection = m_db["guilds"];
            m_alliancesCollection = m_db["alliances"];
            m_shopCollection = m_db["shops"];
            m_dropCollection = m_db["drops"];

            // Log collections
            m_ipLogCollection = m_db["ipLogs"];
            m_banLogCollection = m_db["banLogs"];
            m_fameLogCollection = m_db["fameLogs"];
            m_reportLogCollection = m_db["reportLogs"];
            m_tradeLogCollection = m_db["tradeLogs"];
        }

        static inline FindOneResult accountExists(const std::string& username)
        {
            SERVER_INFO("MongoDb::accountExists");
            FindOneResult result;
            try
            {
                // Define query
                auto query = bsoncxx::builder::stream::document{}
                    << "username" << username
                    << bsoncxx::builder::stream::finalize;

                // Perform insertion
                result = findOneWithRetry(m_accountCollection, query.view());
                if (!result)
                {
                    SERVER_INFO("{} account could not be found", username);
                }
            }
            catch (std::exception& e)
            {
                SERVER_ERROR("{}", e.what());
            }

            return result;
        }

        static inline InsertOneResult autoRegisterAccount(const std::string& username, const std::string& passwordHash, const std::string& ip)
        {
            SERVER_INFO("MongoDb::autoRegisterAccount");
            InsertOneResult result;
            try
            {
                // Define document
                auto doc = bsoncxx::builder::stream::document{}
                    << "username" << username
                    << "password_hash" << passwordHash
                    << "gm_level" << 0
                    << "logged_in" << 0
                    << "birthday" << static_cast<i64>(util::dateToEpochSeconds(1990, 01, 01)) // MongoDb only supports signed 64 bit int, so we need to cast it back to unsigned when reading
                    << "created_at" << static_cast<i64>(util::getEpochSeconds())              // MongoDb only supports signed 64 bit int, so we need to cast it back to unsigned when reading
                    << "last_login" << 0
                    << "last_ip" << ip
                    << "banned" << 0
                    << "nx" << 0
                    << bsoncxx::builder::stream::finalize;

                // Perform insertion
                result = insertOneWithRetry(m_accountCollection, doc.view());
                if (!result)
                {
                    SERVER_INFO("{} account could not be registered", username);
                }
            }
            catch (std::exception& e)
            {
                SERVER_ERROR("{}", e.what());
            }

            return result;
        }

        static inline InsertOneResult registerAccount(const std::string& username, const std::string& password)
        {
            SERVER_INFO("MongoDb::registerAccount");
            InsertOneResult result;
            try
            {
                //// Define document
                //auto newDoc = bsoncxx::builder::stream::document{}
                //    << "username" << username
                //    << "password_hash" << password
                //    << "gm_level" << 0
                //    << "logged_in" << 0
                //    << "birthday" << 0
                //    << "email" << ""
                //    << "created_at" << util::getEpochSeconds()
                //    << "last_login" << 0
                //    << "last_ip" << ""
                //    << "banned" << 0
                //    << "ban_reason" << ""
                //    << "guest" << 1
                //    << "nx" << 0
                //    << bsoncxx::builder::stream::finalize;

                //// Perform insertion
                //auto result = insertOneWithRetry(m_accountCollection, newDoc.view());
                //if (!result)
                //    SERVER_INFO("User document could not be created");

                return result;
            }
            catch (std::exception& e)
            {
                SERVER_ERROR("{}", e.what());
            }

            return result;
        }

        static inline InsertOneResult createCharacter(const std::string& name, const u16 gender, const u16 skinColor, const u16 hair, const u16 face)
        {
            SERVER_INFO("MongoDb::createCharacter");
            InsertOneResult result;
            try
            {
                //// Define document
                //auto newDoc = bsoncxx::builder::stream::document{}
                //    << "account_id" << bsoncxx::oid()
                //    << "name" << name
                //    << "gm" << 0
                //    << "fame" << 0
                //    << "level" << 1
                //    << "job" << 0
                //    << "rank" << 0
                //    << "rank_move" << 0
                //    << "job_rank" << 0
                //    << "job_rank_move" << 0
                //    << "exp" << 0
                //    << "ap" << 9
                //    << "sp" << 0
                //    << "hp" << 50
                //    << "mp" << 5
                //    << "maxhp" << 50
                //    << "maxmp" << 5
                //    << "hp_ap_used" << 0
                //    << "mp_ap_used" << 0
                //    << "str" << 0
                //    << "dex" << 0
                //    << "luk" << 0
                //    << "u16" << 0
                //    << "gender" << gender
                //    << "skin_color" << skinColor
                //    << "hair" << hair
                //    << "face" << face
                //    << "party_id" << bsoncxx::oid()
                //    << "guild_id" << bsoncxx::oid()
                //    << "buddy_capacity" << 20
                //    << "map" << 0
                //    << "spawn_pou16" << 0
                //    << "match_card_wins" << 0
                //    << "match_card_loses" << 0
                //    << "match_card_ties" << 0
                //    << "omok_wins" << 0
                //    << "omok_loses" << 0
                //    << "omok_ties" << 0
                //    << "has_merchant" << bsoncxx::oid()
                //    << "merchant_mesos" << 0
                //    << "created_at" << util::getEpochSeconds()
                //    << bsoncxx::builder::stream::finalize;

                //// Perform insertion
                //auto result = insertOneWithRetry(m_characterCollection, newDoc.view());
                //if (!result)
                //    SERVER_INFO("User document could not be created");

                return result;
            }
            catch (std::exception& e)
            {
                SERVER_ERROR("{}", e.what());
            }

            return result;
        }

    private:
        static inline FindOneResult findOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::findOneWithRetry");
            u16 attempt = 0;
            FindOneResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.find_one(filter);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Find attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

        static inline FindManyResult findManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::findManyWithRetry");
            u16 attempt = 0;
            FindManyResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.find(filter);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Find attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

        static inline InsertOneResult insertOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& document,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::insertOneWithRetry");
            u16 attempt = 0;
            InsertOneResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.insert_one(document);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Insert attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

        static inline InsertManyResult insertManyWithRetry(mongocxx::collection& collection, const std::vector<bsoncxx::document::view>& documents,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::insertManyWithRetry");
            u16 attempt = 0;
            InsertManyResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.insert_many(documents);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Insert attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

        static inline UpdateResult updateOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::updateOneWithRetry");
            u16 attempt = 0;
            UpdateResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.update_one(filter, update);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Update attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

        static inline UpdateResult updateManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::updateManyWithRetry");
            u16 attempt = 0;
            UpdateResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.update_many(filter, update);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Update attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

        static inline FindOneResult findOneAndUpdateWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::findOneAndUpdateWithRetry");
            u16 attempt = 0;
            FindOneResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.find_one_and_update(filter, update);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Update attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

        static inline DeleteResult deleteOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::deleteOneWithRetry");
            u16 attempt = 0;
            DeleteResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.delete_one(filter);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Delete attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

        static inline DeleteResult deleteManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::deleteManyWithRetry");
            u16 attempt = 0;
            DeleteResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.delete_many(filter);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Delete attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

        static inline FindOneResult findOneAndDeleteWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
            u16 max_retries = 3, u16 retry_u16erval_ms = 1000)
        {
            SERVER_INFO("MongoDbHandle::findOneAndDeleteWithRetry");
            u16 attempt = 0;
            FindOneResult result;
            while (attempt < max_retries)
            {
                try
                {
                    result = collection.find_one_and_delete(filter);
                    break;
                }
                catch (const std::exception& e)
                {
                    SERVER_ERROR("Delete attempt {} failed: {}", (attempt + 1), e.what());
                    if (attempt + 1 >= max_retries)
                    {
                        SERVER_ERROR("Maximum retries reached. Giving up.");
                        throw e;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(retry_u16erval_ms));
                }
            }
            return result;
        }

    private:
        static inline mongocxx::uri m_uri;
        static inline mongocxx::client m_client;
        static inline mongocxx::database m_db;

        // Collections
        static inline mongocxx::collection m_accountCollection;
        static inline mongocxx::collection m_characterCollection;
        static inline mongocxx::collection m_inventoriesCollection;
        static inline mongocxx::collection m_buddyCollection;
        static inline mongocxx::collection m_partyCollection;
        static inline mongocxx::collection m_guildCollection;
        static inline mongocxx::collection m_alliancesCollection;
        static inline mongocxx::collection m_shopCollection;
        static inline mongocxx::collection m_dropCollection;

        // Log collections
        static inline mongocxx::collection m_ipLogCollection;
        static inline mongocxx::collection m_banLogCollection;
        static inline mongocxx::collection m_fameLogCollection;
        static inline mongocxx::collection m_reportLogCollection;
        static inline mongocxx::collection m_tradeLogCollection;
    };
}