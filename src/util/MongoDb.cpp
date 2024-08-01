#pragma once

#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>

#include "MongoDb.h"
#include "util/LoggingTool.h"
#include "util/TimeTool.h"
#include "Typedefs.h"

namespace util
{
    // Static method to access the singleton instance
    MongoDb& MongoDb::getInstance()
    {
        static MongoDb instance; // Guaranteed to be destroyed
        return instance;
    }

    void MongoDb::initialize(const std::string& uri, const std::string& db)
    {
        try
        {
            if (!m_initialized)
            {
                static mongocxx::instance instance{};
                m_uri = mongocxx::uri(uri);
                m_client = mongocxx::client(m_uri); // Create the client
                m_db = m_client[db]; // Get the database
                m_initialized = true; // Mark as initialized

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
                m_ipLogCollection = m_db["ipLogs"];
                m_banLogCollection = m_db["banLogs"];
                m_fameLogCollection = m_db["fameLogs"];
                m_reportLogCollection = m_db["reportLogs"];
                m_tradeLogCollection = m_db["tradeLogs"];
            }
        }
        catch (std::exception e)
        {
            SERVER_ERROR("{}", e.what());
        }
    }

    FindOneResult MongoDb::accountExists(const std::string& username)
    {
        SERVER_INFO("MongoDb::accountExists");
        FindOneResult result;
        try
        {
            // Define filter
            auto filter = bsoncxx::builder::stream::document{}
                << "username" << username
                << bsoncxx::builder::stream::finalize;

            // Perform find
            result = findOneWithRetry(m_accountCollection, filter.view());
        }
        catch (std::exception& e)
        {
            SERVER_ERROR("{}", e.what());
        }

        return result;
    }

    InsertOneResult MongoDb::autoRegisterAccount(const std::string& username, const std::string& passwordHash, const std::string& ip)
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
                << "birthday" << util::TimeTool::dateToEpochSeconds(1990, 01, 01) // MongoDb only supports signed 64 bit int, so we need to cast it back to unsigned when reading
                << "created_at" << util::TimeTool::getEpochSeconds()              // MongoDb only supports signed 64 bit int, so we need to cast it back to unsigned when reading
                << "last_login" << 0
                << "last_ip" << ip
                << "banned" << false
                << "guest" << false
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

    InsertOneResult MongoDb::registerAccount(const std::string& username, const std::string& password)
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

    InsertOneResult MongoDb::createCharacter(const std::string& name, const u16 gender, const u16 skinColor, const u16 hair, const u16 face)
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

    FindOneResult MongoDb::findOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries, u16 retry_u16erval_ms)
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

    FindManyResult MongoDb::findManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries, u16 retry_u16erval_ms)
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

    InsertOneResult MongoDb::insertOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& document,
        u16 max_retries, u16 retry_u16erval_ms)
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

    InsertManyResult MongoDb::insertManyWithRetry(mongocxx::collection& collection, const std::vector<bsoncxx::document::view>& documents,
        u16 max_retries, u16 retry_u16erval_ms)
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

    UpdateResult MongoDb::updateOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
        u16 max_retries, u16 retry_u16erval_ms)
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

    UpdateResult MongoDb::updateManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
        u16 max_retries, u16 retry_u16erval_ms)
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

    FindOneResult MongoDb::findOneAndUpdateWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
        u16 max_retries, u16 retry_u16erval_ms)
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

    DeleteResult MongoDb::deleteOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries, u16 retry_u16erval_ms)
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

    DeleteResult MongoDb::deleteManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries, u16 retry_u16erval_ms)
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

    FindOneResult MongoDb::findOneAndDeleteWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        u16 max_retries, u16 retry_u16erval_ms)
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
}