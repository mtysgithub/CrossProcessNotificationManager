#include "stdafx.h"
#include "crossprocessnotificationserver.h"

#define _HEARTBEAT_CYCLE_ 0

CrossProcessNotificationServer::CrossProcessNotificationServer() : m_bIsPause(true)
{
}

CrossProcessNotificationServer::~CrossProcessNotificationServer()
{
	//单例模式，不必手工释放，上层应用只需执行关闭服务器运行的动作
}

CrossProcessNotificationServer *CrossProcessNotificationServer::getInstance()
{
	if (NULL == _instance)
	{
		_instance = new CrossProcessNotificationServer();
	}
	return _instance;
}

void CrossProcessNotificationServer::run()
{
	while(!this->m_bIsPause)
	{
		Sleep(_HEARTBEAT_CYCLE_);
		__poll();
	}
}

HRESULT CrossProcessNotificationServer::startup(int procCount, wchar_t *vToken[], int vBufSIze[])
{
	if (!this->m_bIsPause)
	{
		this->stop();
	}
	//TODO
	for (int i = 0; i < procCount; ++i)
	{
		m_vMMFs.insert(pair<QString, MMF *>(QString::fromWCharArray(vToken[i]), new MMF(vToken[i], vBufSIze[i])));
	}
	this->pause(false);
	//((QThread *)this)->start();
	this->start();
	return S_OK;
}

void CrossProcessNotificationServer::pause(bool flag)
{
	this->m_bIsPause = flag;
}

void CrossProcessNotificationServer::stop()
{
	this->pause(true);

	//同步挂起线程
	this->terminate();
	QThread::wait();

	for (map<QString, MMF *>::iterator it = m_vMMFs.begin(); it != m_vMMFs.end(); ++it)
	{
		it->second->Destory();
	}
	m_vMMFs.clear();
}

void CrossProcessNotificationServer::__poll()
{
	if (!this->m_bIsPause)
	{
		for (map<QString, MMF *>::iterator it = m_vMMFs.begin(); it != m_vMMFs.end();++it)
		{
			MMF *pSourcMMF = it->second;
			if (pSourcMMF)
			{
				PVOID pUpView;
				pSourcMMF->getUpView(&pUpView);
				_USING_MAP_(pUpView)
				if (pUpView && !_MSG_PROCEED_(pUpView))
				{
					QString qstrTargetToken = QString::fromWCharArray(__getTargetToken((PTSTR)pUpView));
					PTSTR ptstrConten = __getContent((PTSTR)pUpView, _BYTE_BODY_LEN_(pSourcMMF->m_mmfSize));

					//注意，消息buff尺寸以消息发出方为准，若接收方buff尺寸不足，则分段发送
					PTSTR tryPostContent = new wchar_t[_MMF_ALLLEN_BYTE_(pSourcMMF->m_mmfSize)];

					_SET_UNDO_(tryPostContent, _DATA_UNPROCED_)
					__setSourcToken(tryPostContent, pSourcMMF->m_mmfToken);
					__setContent(tryPostContent, ptstrConten, _BYTE_BODY_LEN_(pSourcMMF->m_mmfSize));

					if (m_vMMFs.find(qstrTargetToken) != m_vMMFs.end())
					{
						m_vMMFs[qstrTargetToken]->inQueue(tryPostContent);
					}
					_SET_UNDO_(pUpView, _DATA_PROCED_);
				}
			}
		}
		for (map<QString, MMF *>::iterator it = m_vMMFs.begin(); it != m_vMMFs.end(); ++it)
		{
			it->second->tryPost();
		}
	}
}

PTSTR CrossProcessNotificationServer::__getTargetToken(PTSTR pBuff)
{
	PTSTR pRet = NULL;
	if (pBuff)
	{
		pRet = new wchar_t[_TOKEN_LEN_ + 1];
		int p = 1;
		int step = _TOKEN_LEN_;
		while(step--) pRet[p - 1] = (wchar_t)pBuff[p++];
	}
	pRet[_TOKEN_LEN_] = '\0';
	return pRet;
}

PTSTR CrossProcessNotificationServer::__getContent(PTSTR mmfBuff, int buffLen)
{
	PTSTR pRet = NULL;
	if (mmfBuff)
	{
		pRet = new wchar_t[buffLen + 1];
		int p = _BYTE_HEAD_LEN_;
		int step = buffLen;
		while(step--) pRet[p - (1 + _TOKEN_LEN_)] = (wchar_t)mmfBuff[p++];
	}
	pRet[buffLen] = '\0';
	return pRet;
}

void CrossProcessNotificationServer::__setSourcToken(PTSTR mmBuff, PTSTR token)
{
	if (mmBuff && token)
	{
		int step = _TOKEN_LEN_;
		int p = 1;
		while(step--) mmBuff[p++] = token[p - 1];
	}
}

void CrossProcessNotificationServer::__setContent(PTSTR mmBuff, PTSTR content, int bufLen)
{
	if (mmBuff)
	{
		int step = bufLen;
		int p = _BYTE_HEAD_LEN_;
		while(step--) mmBuff[p++] = content[p - (1 + _TOKEN_LEN_)];
	}
}

#pragma region C interface
	bool CROSSPROCESSNOTIFICATIONSERVER_EXPORT g_regist(IN int procCount, IN wchar_t *token[], IN int bufSIzes[])
	{
		return CrossProcessNotificationServer::getInstance()->startup(procCount, token, bufSIzes);
	}
	void CROSSPROCESSNOTIFICATIONSERVER_EXPORT g_unload()
	{
		CrossProcessNotificationServer::getInstance()->stop();
	}
#pragma endregion C interface