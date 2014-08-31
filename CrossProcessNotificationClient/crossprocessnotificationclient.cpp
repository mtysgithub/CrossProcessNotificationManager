#include "stdafx.h"
#include "crossprocessnotificationclient.h"

#define  _SET_UNDO_(_buff_, _val_) ((PTSTR)_buff_)[0] = _val_;
#define _USING_MAP_(pView) CrossProcessNotificationClient::MapViewCtr tmpMpvCtr(pView);

#define  _MSG_PROCEED_(_buff_) ((((PTSTR)_buff_)[0])?(false):(true))
#define _DATA_PROCED_ 0
#define _DATA_UNPROCED_ 1

#define _MUTEX_LOCK_(_mutex_) _mutex_.lock();
#define _MUTEX_UNLOCK_(_mutex_) _mutex_.unlock();

CrossProcessNotificationClient::CrossProcessNotificationClient() : m_bIsStartup(false), 
																						m_hUpMMF(NULL),
																						m_hDownMMF(NULL),
																						m_mmfSize(-1)
{
	memset(m_mmfToken, -1, (_TOKEN_LEN_ + 1) * 2);
}

CrossProcessNotificationClient::~CrossProcessNotificationClient()
{
	//TODO
}

CrossProcessNotificationClient *CrossProcessNotificationClient::getInstance()
{
	if (!_instance)
	{
		_instance = new CrossProcessNotificationClient();
	}
	return _instance;
}

HRESULT CrossProcessNotificationClient::getUpView(OUT PVOID *ppView)
{
	*ppView = MapViewOfFile(m_hUpMMF, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	return S_FALSE;
}

HRESULT CrossProcessNotificationClient::getDownView(OUT PVOID *ppView)
{
	*ppView = MapViewOfFile(m_hDownMMF, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	return S_FALSE;
}

/*
*功能描述：启动客户端，注册到指定信道
*remark：若服务器处于运行态，将会被重置
*/
bool CrossProcessNotificationClient::startUp(wchar_t token[] ,int bufSize)
{
	if (m_bIsStartup)
	{
		stop();
	}
	this->m_mmfSize = bufSize;
	memcpy(this->m_mmfToken, token, sizeof(WCHAR) * _TOKEN_LEN_);
	this->m_mmfToken[_TOKEN_LEN_] = '\0';
	this->m_mmfSize = bufSize;

	wchar_t upToken[_TOKEN_LEN_ + 1];
	memcpy(upToken, m_mmfToken, _TOKEN_LEN_ * sizeof(WCHAR));
	upToken[0] = 'u';
	upToken[_TOKEN_LEN_] = '\0';
	this->m_hUpMMF = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
		FALSE, upToken);

	wchar_t downToken[_TOKEN_LEN_ + 1];
	memcpy(downToken, m_mmfToken, _TOKEN_LEN_ * sizeof(WCHAR));
	downToken[0] = 'd';
	downToken[_TOKEN_LEN_] = '\0';
	this->m_hDownMMF = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
		FALSE, downToken);

	this->m_bIsStartup = true;
	this->start();

	return true;
}

/*
*功能描述：停止客户端运行
*remark: 该函数会清空一切buff，停止轮询
*/
void CrossProcessNotificationClient::stop()
{
	m_bIsStartup = false;

	//同步挂起
	this->terminate();
	QThread::wait();

	m_vDownLoadBuff.clear();
	m_vTryPostBuff.clear();
}

/*
*功能描述：开启线程循环
*/
void CrossProcessNotificationClient::run()
{
	while (this->m_bIsStartup)
	{
		Sleep(_HEARTBEAT_CYCLE_);
		__poll();
	}
}

/*
*功能描述：轮询函数
*/
void CrossProcessNotificationClient::__poll()
{
	if (m_bIsStartup)
	{
		{
			//处理上行
			PVOID upMapView;
			this->getUpView(&upMapView);
			_USING_MAP_(upMapView)
			_MUTEX_LOCK_(m_UpLoadMutex)
			bool tmpBufState = m_vTryPostBuff.empty();
			_MUTEX_UNLOCK_(m_UpLoadMutex)
			if ((false == tmpBufState) && (upMapView) && (_MSG_PROCEED_(upMapView)))
			{
				//pop queue
				PTSTR tryPostContent = NULL;
				this->outQueue(this->m_vTryPostBuff, &tryPostContent);

				memcpy(upMapView, tryPostContent, _MMF_ALLLEN_BYTE_(this->m_mmfSize) * sizeof(WCHAR));
				delete [] tryPostContent;

				//为了保证进程间安全，该宏在memcpy后调用是必须的
				_SET_UNDO_(upMapView, _DATA_UNPROCED_)
			}
		}

		{
			//处理下行
			PVOID downMapView;
			this->getDownView(&downMapView);
			_USING_MAP_(downMapView)
			if ((downMapView) && (false == _MSG_PROCEED_(downMapView)))
			{
				PTSTR downContent = new wchar_t[_MMF_ALLLEN_BYTE_(this->m_mmfSize) * sizeof(WCHAR)];
				memcpy(downContent, downMapView, _MMF_ALLLEN_BYTE_(this->m_mmfSize) * sizeof(WCHAR));
				_SET_UNDO_(downContent, _DATA_PROCED_)

				//push queue
				this->inQueue(m_vDownLoadBuff, downContent);

				//为了保证进程间安全，该宏在memcpy后调用是必须的
				_SET_UNDO_(downMapView, _DATA_PROCED_)
			}
		}
	}
}

bool CrossProcessNotificationClient::sendMessage(IN wchar_t token[], IN char content[], IN int bufSIze)
{
	wchar_t newMsg[_MAX_MEMORY_BYTE_];

	_SET_UNDO_(newMsg, _DATA_UNPROCED_)
	memcpy((void *)(newMsg + 1), token, _TOKEN_LEN_ * sizeof(WCHAR));
	memcpy((void *)(newMsg + 1 + _TOKEN_LEN_), &bufSIze, _COTENT_LEN_ * sizeof(WCHAR));

	//若内容为奇数字节，则做一次偶数对齐
	if (0 == (bufSIze % 2))
	{
		memcpy((void *)(newMsg + 1 + _TOKEN_LEN_ + _COTENT_LEN_), content, bufSIze * sizeof(WCHAR));
	}else
	{
		((char *)(newMsg + 1 + _TOKEN_LEN_ + _COTENT_LEN_))[0] = 0;
		memcpy((void *)(newMsg + 1 + _TOKEN_LEN_ + _COTENT_LEN_ + 1), content, bufSIze * sizeof(BYTE));
	}

	PTSTR pushConten = (PTSTR)(new wchar_t[_MMF_ALLLEN_BYTE_(this->m_mmfSize)]);
	memcpy(pushConten, newMsg, _MMF_ALLLEN_BYTE_(this->m_mmfSize) * sizeof(WCHAR));
	
	this->inQueue(m_vTryPostBuff, pushConten);

	return true;
}

bool CrossProcessNotificationClient::getRespons(OUT PTSTR *ppToken, OUT char **ppContent, OUT int &bufSIze)
{
	_MUTEX_LOCK_(m_UpLoadMutex)
	bool tmpBufState = this->m_vDownLoadBuff.empty();
	_MUTEX_UNLOCK_(m_UpLoadMutex)
	if (false == tmpBufState)
	{
		PTSTR outMsg = NULL;
		this->outQueue(this->m_vDownLoadBuff, &outMsg);
		
		PTSTR pToken = new wchar_t[_TOKEN_LEN_ + 1];
		pToken[_TOKEN_LEN_] = '\0';
		memcpy(pToken, outMsg + 1, _TOKEN_LEN_ * sizeof(WCHAR));
		*ppToken = pToken;
		
		memcpy(&bufSIze, outMsg + 1 + _TOKEN_LEN_, _COTENT_LEN_ * sizeof(WCHAR));

		char *pContent = new char[bufSIze];
		if (0 == (bufSIze % 2))
		{
			memcpy(pContent, outMsg + 1 + _TOKEN_LEN_ + _COTENT_LEN_, bufSIze * sizeof(BYTE));
		}else
		{
			memcpy(pContent, (char *)(outMsg + 1 + _TOKEN_LEN_ + _COTENT_LEN_) + 1, bufSIze * sizeof(BYTE));
		}
		*ppContent = (char *)pContent;
		delete [] outMsg;
		return true;
	}else
	{
		//no message
		*ppToken = NULL;
		*ppContent = NULL;
		bufSIze = -1;
		return false;
	}
}

void CrossProcessNotificationClient::destory()
{
	this->stop();
	this->deleteLater();
}

void CrossProcessNotificationClient::inQueue(list<PTSTR> &pQueue, PTSTR strContent)
{
	//lock queue
	_MUTEX_LOCK_(m_UpLoadMutex)
	if (strContent)
	{
		pQueue.push_back(strContent);
	}
	_MUTEX_UNLOCK_(m_UpLoadMutex)
}

void CrossProcessNotificationClient::outQueue(IN list<PTSTR> &pQueue, OUT PTSTR *ppStrContent)
{
	_MUTEX_LOCK_(m_UpLoadMutex)
	if (!pQueue.empty())
	{
		*ppStrContent = *(pQueue.begin());
		pQueue.pop_front();
	}else
	{
		*ppStrContent = NULL;
	}
	_MUTEX_UNLOCK_(m_UpLoadMutex)
}

#pragma region C interface
	bool CROSSPROCESSNOTIFICATIONCLIENT_EXPORT g_regist(wchar_t token[] ,int bufSize)
	{
		return CrossProcessNotificationClient::getInstance()->startUp(token, bufSize);
	}
	bool CROSSPROCESSNOTIFICATIONCLIENT_EXPORT g_sendMessage(IN wchar_t token[], IN char content[], IN int bufSIze)
	{
		return CrossProcessNotificationClient::getInstance()->sendMessage(token, content, bufSIze);
	}
	bool CROSSPROCESSNOTIFICATIONCLIENT_EXPORT g_getRespons(OUT WCHAR *cspToken, OUT char *cspContent, OUT int &bufSIze)
	{
		PTSTR pToken;
		char *pConten;
		bool ret = CrossProcessNotificationClient::getInstance()->getRespons(&pToken, &pConten, bufSIze);
		if (ret && pToken && pConten)
		{
			memcpy(cspToken, pToken, _TOKEN_LEN_ * sizeof(WCHAR));
			memcpy(cspContent, pConten, bufSIze * sizeof(char));
		}
		return ret;
	}
	void CROSSPROCESSNOTIFICATIONCLIENT_EXPORT g_unload()
	{
		CrossProcessNotificationClient::getInstance()->destory();
	}
#pragma endregion C interface