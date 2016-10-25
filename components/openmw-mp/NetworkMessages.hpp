//
// Created by koncord on 05.01.16.
//

#ifndef OPENMW_NETWORKMESSAGES_HPP
#define OPENMW_NETWORKMESSAGES_HPP

#include <MessageIdentifiers.h>

enum GameMessages
{
    ID_GAME_BASE_INFO = ID_USER_PACKET_ENUM+1,
    ID_GAME_CHARGEN,
    ID_GAME_POS,
    ID_GAME_DYNAMICSTATS,
    ID_GAME_ATTACK,
    ID_USER_MYID,
    ID_GAME_EQUIPMENT,
    ID_USER_DISCONNECTED,
    ID_GAME_DIE,
    ID_GAME_RESURRECT,
    ID_CHAT_MESSAGE,
    ID_GAME_CELL,
    ID_GAME_DRAWSTATE,

    ID_GAME_ATTRIBUTE,
    ID_GAME_SKILL,
    ID_GAME_LEVEL,
    ID_GAME_CHARCLASS,
    ID_HANDSHAKE,
    ID_LOADED,
    ID_GUI_MESSAGEBOX,
    ID_GAME_TIME,
    ID_GAME_INVENTORY,

    ID_OBJECT_PLACE,
    ID_OBJECT_DELETE,
    ID_OBJECT_LOCK,
    ID_OBJECT_UNLOCK,
    ID_OBJECT_SCALE,

    ID_CONTAINER_ADD,
    ID_CONTAINER_REMOVE,
    ID_DOOR_ACTIVATE,
    ID_ACTIVATOR_ACTIVATE,
    ID_VIDEO_PLAY
};


#endif //OPENMW_NETWORKMESSAGES_HPP
