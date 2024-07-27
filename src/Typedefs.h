#pragma once

#include <chrono>
#include <cstdint>
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
using PacketHandlers = std::unordered_map<u16, std::function<void(Player&, Packet&)>>;
using ClientConnection = std::shared_ptr<Player>;

// Mongo result types
using seconds_t = std::chrono::seconds;
using findOneResult = std::optional<bsoncxx::v_noabi::document::value>;
using findManyResult = std::optional<mongocxx::v_noabi::cursor>;
using insertOneResult = std::optional<mongocxx::v_noabi::result::insert_one>;
using insertManyResult = std::optional<mongocxx::v_noabi::result::insert_many>;
using updateResult = std::optional<mongocxx::v_noabi::result::update>;
using deleteResult = std::optional<mongocxx::v_noabi::result::delete_result>;