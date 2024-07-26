#include "pch.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>

#include "util/Logger.h"
#include "util/TimeTool.h"
#include "DbHandler.h"

namespace db
{
    void DbHandler::initialize(const std::string& mongoURI, const std::string& mongoDB)
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

    bool DbHandler::createAccount(const std::string& username, const std::string& password)
    {
        SERVER_INFO("DbHandler::createAccount");
        try
        {
            // Define document
            auto newDoc = bsoncxx::builder::stream::document{}
                << "username" << username
                << "password_hash" << password
                << "gm_level" << 0
                << "logged_in" << 0
                << "birthday" << 0
                << "email" << ""
                << "created_at" << util::getEpochSeconds()
                << "last_login" << 0
                << "last_ip" << ""
                << "banned" << 0
                << "ban_reason" << ""
                << "guest" << 1
                << "nx" << 0
                << bsoncxx::builder::stream::finalize;

            // Perform insertion
            auto creationResult = insertOneWithRetry(m_accountCollection, newDoc.view());
            if (!creationResult)
                SERVER_INFO("User document could not be created");

            return true;
        }
        catch (std::exception& e)
        {
            SERVER_ERROR("{}", e.what());
            return false;
        }

        return true;
    }

    bool DbHandler::createCharacter(const std::string& name, const uint16_t gender, const uint16_t skinColor,
                                    const uint16_t hair, const uint16_t face)
    {
        SERVER_INFO("DbHandler::createCharacter");
        try
        {
            // Define document
            auto newDoc = bsoncxx::builder::stream::document{}
                << "account_id" << bsoncxx::oid()
                << "name" << name
                << "gm" << 0
                << "fame" << 0
                << "level" << 1
                << "job" << 0
                << "rank" << 0
                << "rank_move" << 0
                << "job_rank" << 0
                << "job_rank_move" << 0
                << "exp" << 0
                << "ap" << 9
                << "sp" << 0
                << "hp" << 50
                << "mp" << 5
                << "maxhp" << 50
                << "maxmp" << 5
                << "hp_ap_used" << 0
                << "mp_ap_used" << 0
                << "str" << 0
                << "dex" << 0
                << "luk" << 0
                << "int" << 0
                << "gender" << gender
                << "skin_color" << skinColor
                << "hair" << hair
                << "face" << face
                << "party_id" << bsoncxx::oid()
                << "guild_id" << bsoncxx::oid()
                << "buddy_capacity" << 20
                << "map" << 0
                << "spawn_point" << 0
                << "match_card_wins" << 0
                << "match_card_loses" << 0
                << "match_card_ties" << 0
                << "omok_wins" << 0
                << "omok_loses" << 0
                << "omok_ties" << 0
                << "has_merchant" << bsoncxx::oid()
                << "merchant_mesos" << 0
                << "created_at" << util::getEpochSeconds()
                << bsoncxx::builder::stream::finalize;

            // Perform insertion
            auto creationResult = insertOneWithRetry(m_characterCollection, newDoc.view());
            if (!creationResult)
                SERVER_INFO("User document could not be created");

            return true;
        }
        catch (std::exception& e)
        {
            SERVER_ERROR("{}", e.what());
            return false;
        }

        return true;
    }

    findOneResult DbHandler::findOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::findOneWithRetry");
        int attempt = 0;
        findOneResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.find_one(filter);
                if (result)
                    SERVER_INFO("Document found successfully.");
                else
                    SERVER_ERROR("Document not found.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }

    findManyResult DbHandler::findManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::findManyWithRetry");
        int attempt = 0;
        findManyResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.find(filter);
                if (result)
                    SERVER_INFO("Documents found successfully.");
                else
                    SERVER_ERROR("Documents not found.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }

    insertOneResult DbHandler::insertOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& document,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::insertOneWithRetry");
        int attempt = 0;
        insertOneResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.insert_one(document);
                if (result)
                    SERVER_INFO("Document inserted successfully.");
                else
                    SERVER_ERROR("Document not inserted.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }

    insertManyResult DbHandler::insertManyWithRetry(mongocxx::collection& collection, const std::vector<bsoncxx::document::view>& documents,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::insertManyWithRetry");
        int attempt = 0;
        insertManyResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.insert_many(documents);
                if (result)
                    SERVER_INFO("Documents inserted successfully.");
                else
                    SERVER_ERROR("Documents not inserted.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }

    updateResult DbHandler::updateOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::updateOneWithRetry");
        int attempt = 0;
        updateResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.update_one(filter, update);
                if (result)
                    SERVER_INFO("Document updated successfully.");
                else
                    SERVER_ERROR("Document not updated.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }

    findOneResult DbHandler::findOneAndUpdateWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::findOneAndUpdateWithRetry");
        int attempt = 0;
        findOneResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.find_one_and_update(filter, update);
                if (result)
                    SERVER_INFO("Document updated successfully.");
                else
                    SERVER_ERROR("Document not updated.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }

    updateResult DbHandler::updateManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::updateManyWithRetry");
        int attempt = 0;
        updateResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.update_many(filter, update);
                if (result)
                    SERVER_INFO("Documents updated successfully.");
                else
                    SERVER_ERROR("Documents not updated.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }

    deleteResult DbHandler::deleteOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::deleteOneWithRetry");
        int attempt = 0;
        deleteResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.delete_one(filter);
                if (result)
                    SERVER_INFO("Document deleted successfully.");
                else
                    SERVER_ERROR("Document not deleted.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }

    deleteResult DbHandler::deleteManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::deleteManyWithRetry");
        int attempt = 0;
        deleteResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.delete_many(filter);
                if (result)
                    SERVER_INFO("Documents deleted successfully.");
                else
                    SERVER_ERROR("Documents not deleted.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }

    findOneResult DbHandler::findOneAndDeleteWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
        int max_retries, int retry_interval_ms)
    {
        SERVER_INFO("MongoDbHandle::findOneAndDeleteWithRetry");
        int attempt = 0;
        findOneResult result;
        while (attempt < max_retries)
        {
            try
            {
                result = collection.find_one_and_delete(filter);
                if (result)
                    SERVER_INFO("Document deleted successfully.");
                else
                    SERVER_ERROR("Document not deleted.");
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
                std::this_thread::sleep_for(std::chrono::milliseconds(retry_interval_ms));
            }
            attempt++;
        }
        return result;
    }
}