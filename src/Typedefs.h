#pragma once

#include <chrono>
#include <cstdint>
#include <ctime>
#include <functional>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>

class TCPConnection;
class Player;

// Integer types
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

using byte = unsigned char;
using Packet = std::vector<byte>;
using PacketHandlers = std::unordered_map<u32, std::function<void(Player&, Packet&)>>;
using ClientConnection = std::shared_ptr<Player>;

// Mongo result types
using FindOneResult = std::optional<bsoncxx::v_noabi::document::value>;
using FindManyResult = std::optional<mongocxx::v_noabi::cursor>;
using InsertOneResult = std::optional<mongocxx::v_noabi::result::insert_one>;
using InsertManyResult = std::optional<mongocxx::v_noabi::result::insert_many>;
using UpdateResult = std::optional<mongocxx::v_noabi::result::update>;
using DeleteResult = std::optional<mongocxx::v_noabi::result::delete_result>;

// Time
using seconds_t = std::chrono::seconds;
using Calendar = std::tm;

using Point = struct {
    u32 x;
    u32 y;
};