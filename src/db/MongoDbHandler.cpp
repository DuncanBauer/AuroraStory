#include <algorithm>
#include <chrono>
#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include "util/Logger.h"
#include "MongoDbHandler.h"

bool MongoDbHandler::createAccountDoc(const std::string& username, const std::string& password)
{
    return true;
}

bool MongoDbHandler::deleteAccountDoc(const std::string& accountId)
{
    return true;
}

findOneResult MongoDbHandler::findOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
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

findManyResult MongoDbHandler::findManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
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

insertOneResult MongoDbHandler::insertOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& document,
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

insertManyResult MongoDbHandler::insertManyWithRetry(mongocxx::collection& collection, const std::vector<bsoncxx::document::view>& documents,
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

updateResult MongoDbHandler::updateOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
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

findOneResult MongoDbHandler::findOneAndUpdateWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
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


updateResult MongoDbHandler::updateManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter, const bsoncxx::document::view& update,
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

deleteResult MongoDbHandler::deleteOneWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
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

deleteResult MongoDbHandler::deleteManyWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
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

findOneResult MongoDbHandler::findOneAndDeleteWithRetry(mongocxx::collection& collection, const bsoncxx::document::view& filter,
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