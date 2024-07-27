#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

class TCPConnection;
class Player;

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