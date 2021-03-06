#ifndef NET_SERVER_H
#define NET_SERVER_H

#include "enumeration.h"
#include "types.h"
#include "../table/sound.h"

extern void Server_RestockStarport(enum UnitType type);

extern void Server_ResetCache(void);

extern void Server_Send_UpdateLandscape(unsigned char **buf);
extern void Server_Send_UpdateFogOfWar(enum HouseType houseID, unsigned char **buf);
extern void Server_Send_UpdateHouse(enum HouseType houseID, unsigned char **buf);
extern void Server_Send_UpdateCHOAM(unsigned char **buf);
extern void Server_Send_UpdateStructures(unsigned char **buf);
extern void Server_Send_UpdateUnits(unsigned char **buf);
extern void Server_Send_UpdateExplosions(unsigned char **buf);
extern void Server_Send_ScreenShake(uint16 packed);
extern void Server_Send_StatusMessage1(enum HouseFlag houses, uint8 priority, uint16 str1);
extern void Server_Send_StatusMessage2(enum HouseFlag houses, uint8 priority, uint16 str1, uint16 str2);
extern void Server_Send_StatusMessage3(enum HouseFlag houses, uint8 priority, uint16 str1, uint16 str2, uint16 str3);
extern void Server_Send_PlaySound(enum HouseFlag houses, enum SoundID soundID);
extern void Server_Send_PlaySoundAtTile(enum HouseFlag houses, enum SoundID soundID, tile32 position);
extern void Server_Send_PlayVoice(enum HouseFlag houses, enum VoiceID voiceID);
extern void Server_Send_PlayVoiceAtTile(enum HouseFlag houses, enum VoiceID voiceID, uint16 packed);
extern void Server_Send_PlayBattleMusic(enum HouseFlag houses);
extern void Server_Send_WinLose(enum HouseType houseID, bool win);
extern void Server_Send_ClientList(unsigned char **buf);
extern void Server_Send_Scenario(unsigned char **buf);

extern void Server_Recv_ReturnToLobby(enum HouseType houseID, bool log_message);
extern void Server_Recv_PrefName(int peerID, const char *name);
extern void Server_Recv_PrefHouse(int peerID, enum HouseType houseID);
extern void Server_ProcessMessage(int peerID, enum HouseType houseID, const unsigned char *buf, int count);
extern bool Server_ProcessCommand(const char *msg);

#endif
