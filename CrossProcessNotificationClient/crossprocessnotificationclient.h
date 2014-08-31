#ifndef CROSSPROCESSNOTIFICATIONCLIENT_H
#define CROSSPROCESSNOTIFICATIONCLIENT_H

#include "stdafx.h"
#include "crossprocessnotificationclient_global.h"

class CrossProcessNotificationClient : public QThread
{
	class MmfHeadAdapter
	{
	public:
		enum segment
		{
			proced_flag = 0,
			token_name
		};
		
	public:
		static void get(IN PCTSTR inBuf, IN segment type, OUT PCTSTR outBuf)
		{
			int oprRange[][2] = _BYTE_HEAD_FORMAT_;
			memcpy((void *)outBuf, inBuf + oprRange[type][0], oprRange[type][1] * sizeof(WCHAR));
		}
		static void set(IN PCTSTR destBuf, IN segment type, IN PCTSTR contentBuf)
		{
			int oprRange[][2] = _BYTE_HEAD_FORMAT_;
			memcpy((void *)(destBuf + oprRange[type][0]), contentBuf, oprRange[type][1] * sizeof(WCHAR));
		}
	};

	Q_OBJECT
	public:
	/*
	*MapView智能销毁机制
	*/
	class MapViewCtr
	{
	public:
		 MapViewCtr(PVOID pView) : m_pView(pView){}
		 ~MapViewCtr(){if(m_pView) UnmapViewOfFile(m_pView);}
	private:
		PVOID m_pView;
	};

public:
	CrossProcessNotificationClient();
	~CrossProcessNotificationClient();

	static CrossProcessNotificationClient *getInstance();
	bool startUp(wchar_t token[] ,int bufSize);
	void stop();
	void destory();

	HRESULT getUpView(OUT PVOID *ppView);
	HRESULT getDownView(OUT PVOID *ppView);
	

	bool sendMessage(IN wchar_t token[], IN char content[], IN int bufSIze);
	bool getRespons(OUT PTSTR *ppToken, OUT char **ppContent, OUT int &bufSIze);

public slots:
	void __poll();

protected:
	void run();
	void inQueue(IN list<PTSTR> &pQueue, IN PTSTR strContent);
	void outQueue(IN list<PTSTR> &pQueue, OUT PTSTR *strContent);

private:
	bool m_bIsStartup;

	int m_mmfSize;
	wchar_t  m_mmfToken[_TOKEN_LEN_ + 1];

	//上行，下行信道（由服务器管理生命周期，客户端应视为获取了只读句柄）
	HANDLE m_hUpMMF;
	HANDLE m_hDownMMF;

	list<PTSTR> m_vTryPostBuff;
	list<PTSTR> m_vDownLoadBuff;

	QMutex m_UpLoadMutex;
};

static CrossProcessNotificationClient * _instance = NULL;

#endif // CROSSPROCESSNOTIFICATIONCLIENT_H
