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

    void MongoDb::initialize(std::string const& uri, std::string const& db)
    {
        try
        {
            if (!m_initialized)
            {
                static mongocxx::instance instance{};
                m_uri = mongocxx::uri(uri);
                m_client = mongocxx::client(m_uri); // Create the client
                m_db = m_client[db]; // Get the database

                // Collections
                m_counterCollection     = m_db["counters"];
                m_accountCollection     = m_db["accounts"];
                m_characterCollection   = m_db["characters"];
                m_inventoriesCollection = m_db["inventories"];
                m_buddyCollection       = m_db["buddies"];
                m_partyCollection       = m_db["parties"];
                m_guildCollection       = m_db["guilds"];
                m_alliancesCollection   = m_db["alliances"];
                m_shopCollection        = m_db["shops"];
                m_dropCollection        = m_db["drops"];
                m_ipLogCollection       = m_db["ipLogs"];
                m_banLogCollection      = m_db["banLogs"];
                m_fameLogCollection     = m_db["fameLogs"];
                m_reportLogCollection   = m_db["reportLogs"];
                m_tradeLogCollection    = m_db["tradeLogs"];

                m_initialized = true; // Mark as initialized
            }
        }
        catch (std::exception e)
        {
            SERVER_ERROR("{}", e.what());
        }
    }

    u32 MongoDb::getNextSequence(std::string const& counterName)
    {
        FindOneResult result;
        try
        {
            // Define filter
            auto filter = bsoncxx::builder::stream::document{}
                << "_id" << counterName
                << bsoncxx::builder::stream::finalize;

            // Define update
            auto update = bsoncxx::builder::stream::document{}
                << "$inc"
                << bsoncxx::builder::stream::open_document
                << "value" << 1
                << bsoncxx::builder::stream::close_document
                << bsoncxx::builder::stream::finalize;

            // Perform find
            result = findOneAndUpdateWithRetry(m_counterCollection, filter.view(), update.view());
        }
        catch (std::exception& e)
        {
            SERVER_ERROR("{}", e.what());
        }

        if (result && result->view().find("value") != result->view().end())
        {
            return result->view()["value"].get_int32().value;
        }
        else
        {
            // Handle case where the document was not found or 'value' does not exist
            SERVER_ERROR("Counter not found or invalid result for {}", counterName);
            return 0; // or some error value
        }
    }

    FindOneResult MongoDb::accountExists(std::string const& username)
    {
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

    InsertOneResult MongoDb::autoRegisterAccount(std::string const& username, std::string const& passwordHash, std::string const& ip)
    {
        InsertOneResult result;
        try
        {
            // Define document
            auto doc = bsoncxx::builder::stream::document{}
                << "_id" << static_cast<i32>(getNextSequence("account_id"))
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

    UpdateResult MongoDb::setPin(std::string const& username, std::string const& pin)
    {
        UpdateResult result;
        try
        {
            // Define filter
            auto filter = bsoncxx::builder::stream::document{}
                << "username" << username
                << bsoncxx::builder::stream::finalize;

            // Define document
            auto doc = bsoncxx::builder::stream::document{}
                << "pin" << pin
                << bsoncxx::builder::stream::finalize;

            // Perform insertion
            result = updateOneWithRetry(m_accountCollection, filter.view(), doc.view());
            if (!result)
            {
                SERVER_INFO("{} account could not be updated", username);
            }
        }
        catch (std::exception& e)
        {
            SERVER_ERROR("{}", e.what());
        }

        return result;
    }

    FindOneResult MongoDb::getCharacterByName(std::string const& name, u16 const worldId)
    {
        FindOneResult result;
        //try
        //{
        //    // Define query
        //    auto query = bsoncxx::builder::stream::document{}
        //        << "name" << name
        //        << "world_id" << worldId
        //        << bsoncxx::builder::stream::finalize;

        //    // Perform find
        //    result = findOneWithRetry(m_characterCollection, query.view());
        //}
        //catch (std::exception& e)
        //{
        //    SERVER_ERROR("{}", e.what());
        //}

        return result;
    }

    FindOneResult MongoDb::getCharacterById(u32 const id, u16 const worldId)
    {
        FindOneResult result;
        //try
        //{
        //    // Define query
        //    auto query = bsoncxx::builder::stream::document{}
        //        << "_id" << id
        //        << "world_id" << worldId
        //        << bsoncxx::builder::stream::finalize;

        //    // Perform find
        //    result = findOneWithRetry(m_characterCollection, query.view());
        //}
        //catch (std::exception& e)
        //{
        //    SERVER_ERROR("{}", e.what());
        //}

        return result;
    }

    InsertOneResult MongoDb::createCharacter(std::string const& name, u16 const gender, u16 const skinColor, u16 const hair, u16 const face)
    {
        InsertOneResult result;
        try
        {
            //// Define document
            //auto newDoc = bsoncxx::builder::stream::document{}
            //    << "account_id" << 
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
        }
        catch (std::exception& e)
        {
            SERVER_ERROR("{}", e.what());
        }

        return result;
    }

    FindOneResult MongoDb::findOneWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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

    FindManyResult MongoDb::findManyWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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

    InsertOneResult MongoDb::insertOneWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& document,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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

    InsertManyResult MongoDb::insertManyWithRetry(mongocxx::collection& collection, std::vector<bsoncxx::document::view> const& documents,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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

    UpdateResult MongoDb::updateOneWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, bsoncxx::document::view const& update,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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

    UpdateResult MongoDb::updateManyWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, bsoncxx::document::view const& update,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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

    FindOneResult MongoDb::findOneAndUpdateWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter, bsoncxx::document::view const& update,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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

    DeleteResult MongoDb::deleteOneWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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

    DeleteResult MongoDb::deleteManyWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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

    FindOneResult MongoDb::findOneAndDeleteWithRetry(mongocxx::collection& collection, bsoncxx::document::view const& filter,
        u16 max_retries, u16 retry_u16erval_ms)
    {
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