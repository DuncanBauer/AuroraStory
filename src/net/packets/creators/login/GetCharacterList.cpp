#include <set>

#include "Master.h"
#include "game/Inventory.h"
#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    /**
     * Gets a packet with a list of characters.
     *
     * @param c The MapleClient to load characters of.
     * @param serverId The ID of the server requested.
     * @return The character list packet.
     */
    Packet getCharacterList(std::shared_ptr<Player> player, u32 serverId)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_CHAR_LIST);
        util::PacketTool::writeIntAsByte(packet, 0);

        std::vector<Character> characters = player->loadCharacters(serverId);
        util::PacketTool::writeByte(packet, (byte)characters.size());

        for (Character character : characters)
        {
            addCharacterEntry(packet, character);
        }

        util::PacketTool::writeInt(packet, Master::getInstance().getSettings().defaultMaxCharactersPerWorld);

        return packet;
    }

    /**
     * Adds an entry for a character to an existing
     * Packet.
     *
     * @param mplew The MaplePacketLittleEndianWrite instance to write the stats to.
     * @param chr The character to add.
     */
    void addCharacterEntry(Packet packet, Character character)
    {
        addCharacterStats(packet, character);
        addCharacterLook(packet, character, false);

        if (character.getJob() == Job::k_GM)
        {
            util::PacketTool::writeIntAsByte(packet, 0);
            return;
        }

        util::PacketTool::writeIntAsByte(packet, 1); // world rank enabled (next 4 ints are not sent if disabled)
        util::PacketTool::writeInt(packet, character.getRank()); // world rank
        util::PacketTool::writeInt(packet, character.getRankMove()); // move (negative is downwards)
        util::PacketTool::writeInt(packet, character.getJobRank()); // job rank
        util::PacketTool::writeInt(packet, character.getJobRankMove()); // move (negative is downwards)
    }

    /**
     * Adds character stats to an existing Packet.
     *
     * @param mplew The Packet instance to write the stats to.
     * @param chr The character to add the stats of.
     */
    void addCharacterStats(Packet packet, Character character)
    {
        util::PacketTool::writeInt(packet, character.getCharacterId()); // character id

        util::PacketTool::writeString(packet, character.getCharacterName());
        for (size_t x = character.getCharacterName().length(); x < 13; x++) { // fill to maximum name length

            util::PacketTool::writeIntAsByte(packet, 0);
        }
        util::PacketTool::writeIntAsByte(packet, character.getGenderId()); // gender (0 = male, 1 = female)
        util::PacketTool::writeIntAsByte(packet, character.getSkinId()); // skin color
        util::PacketTool::writeInt(packet, character.getFaceId()); // face
        util::PacketTool::writeInt(packet, character.getHairId()); // hair

        util::PacketTool::writeLong(packet, 0);
        util::PacketTool::writeLong(packet, 0);
        util::PacketTool::writeLong(packet, 0);
        
        util::PacketTool::writeIntAsByte(packet, character.getLevel()); // level
        util::PacketTool::writeShort(packet, character.getJob()); // job
        util::PacketTool::writeShort(packet, character.getBaseStr()); // str
        util::PacketTool::writeShort(packet, character.getBaseDex()); // dex
        util::PacketTool::writeShort(packet, character.getBaseInt()); // int
        util::PacketTool::writeShort(packet, character.getBaseLuk()); // luk
        util::PacketTool::writeShort(packet, character.getCurrentHp()); // hp (?)
        util::PacketTool::writeShort(packet, character.getMaxHp()); // maxhp
        util::PacketTool::writeShort(packet, character.getCurrentMp()); // mp (?)
        util::PacketTool::writeShort(packet, character.getMaxMp()); // maxmp
        util::PacketTool::writeShort(packet, character.getUnspentAp()); // remaining ap
        util::PacketTool::writeShort(packet, character.getUnspentSp()); // remaining sp
        util::PacketTool::writeInt(packet, character.getExp()); // current exp
        util::PacketTool::writeShort(packet, character.getFame()); // fame

        util::PacketTool::writeInt(packet, 0);

        util::PacketTool::writeInt(packet, character.getMapId()); // current map id
        util::PacketTool::writeIntAsByte(packet, character.getSpawnpoint()); // spawnpoint

        util::PacketTool::writeInt(packet, 0);
    }

    /**
     * Adds the aesthetic aspects of a character to an existing
     * packet.
     *
     * @param packet to write the stats to.
     * @param chr The character to add the looks of.
     * @param mega Unknown
     */
    void addCharacterLook(Packet packet, Character character, bool mega) 
    {
        util::PacketTool::writeIntAsByte(packet, character.getGenderId());
        util::PacketTool::writeIntAsByte(packet, character.getSkinId());
        util::PacketTool::writeInt(packet, character.getFaceId());
        util::PacketTool::writeIntAsByte(packet, mega ? 0 : 1); // whats mega??
        util::PacketTool::writeInt(packet, character.getHairId());

        Inventory equipInventory = character.getInventory(InventoryType::k_EQUIPPED);
        std::map<byte, u32> visibleEquip;
        std::map<byte, u32> maskedEquip;
        for (const auto& pair : equipInventory.getItems())
        {
            byte position = (byte)(pair.second.getPosition() * -1);
            if (position < 100 && visibleEquip[position]) 
            {
                visibleEquip.emplace(position, pair.second.getId());
            }
            else if (position > 100 && position != 111) // don't ask. o.o
            {
                position -= 100;
                if (visibleEquip[position])
                {
                    maskedEquip.emplace(position, visibleEquip[position]);
                }
                visibleEquip.emplace(position, pair.second.getId());
            }
            else if (visibleEquip[position])
            {
                maskedEquip.emplace(position, pair.second.getId());
            }
        }

        // Visible Items
        for (const auto& pair : visibleEquip)
        {
            util::PacketTool::writeByte(packet, pair.first);
            util::PacketTool::writeInt(packet, pair.second);
        }
        util::PacketTool::writeIntAsByte(packet, 0xFF);

        // Masked Itens
        for (const auto& pair : maskedEquip)
        {
            util::PacketTool::writeByte(packet, pair.first);
            util::PacketTool::writeInt(packet, pair.second);
        }

        // Ending Markers
        util::PacketTool::writeIntAsByte(packet, 0xFF);

        // Cash Weapon
        // Weird that this is last
        const Item& cWeapon = equipInventory.getItemInSlot((byte)-111);
        if (cWeapon.getId() != -1) 
        {
            util::PacketTool::writeInt(packet, cWeapon.getId());
        }
        else 
        {
            util::PacketTool::writeInt(packet, 0); 
        }

        util::PacketTool::writeInt(packet, 0);
        util::PacketTool::writeLong(packet, 0);
    }
}