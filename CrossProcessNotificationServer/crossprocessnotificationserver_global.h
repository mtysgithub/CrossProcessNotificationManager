#ifndef CROSSPROCESSNOTIFICATIONSERVER_GLOBAL_H
#define CROSSPROCESSNOTIFICATIONSERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef CROSSPROCESSNOTIFICATIONSERVER_LIB
# define CROSSPROCESSNOTIFICATIONSERVER_EXPORT Q_DECL_EXPORT
#else
# define CROSSPROCESSNOTIFICATIONSERVER_EXPORT Q_DECL_IMPORT
#endif
#pragma region 全局宏
	//计数单位统一为wchar，2byte/per = ushort
	#define  _HEARTBEAT_CYCLE_ 0
	#define _BYTE_HEAD_FORMAT_ {{0, 1},{1, _TOKEN_LEN_}}
	#define  _TOKEN_LEN_ (8)
	#define  _BYTE_HEAD_LEN_ 1 + (_TOKEN_LEN_)
	#define _BYTE_BODY_LEN_(_size_) (_size_ * (1 << 10))
	#define  _MMF_ALLLEN_BYTE_(_size_) (_BYTE_HEAD_LEN_ + _BYTE_BODY_LEN_(_size_))
	#define  _MAX_MEMORY_BYTE_ (1 << 16)
#pragma endregion 全局宏

bool CROSSPROCESSNOTIFICATIONSERVER_EXPORT g_regist(IN int procCount, IN wchar_t *token[], IN int bufSIzes[]);
void CROSSPROCESSNOTIFICATIONSERVER_EXPORT g_unload();
#endif // CROSSPROCESSNOTIFICATIONSERVER_GLOBAL_H
