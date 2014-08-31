#ifndef CROSSPROCESSNOTIFICATIONSERVER_H
#define CROSSPROCESSNOTIFICATIONSERVER_H

#include "stdafx.h"
#include "crossprocessnotificationserver_global.h"
#include "mmf.hpp"

class CrossProcessNotificationServer : public QThread
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

protected:
	CrossProcessNotificationServer();
	~CrossProcessNotificationServer();

public:
	HRESULT startup(int procCount, wchar_t *vToken[], int vBufSIze[]);
	void pause(bool);
	void stop();

public: 
	static CrossProcessNotificationServer *getInstance();

protected slots:
		void __poll();
protected:
		void run();
private:
		PTSTR __getTargetToken(PTSTR mmfBuff);
		PTSTR __getContent(PTSTR mmfBuff, int buffLen);

		void __setSourcToken(PTSTR mmBuff, PTSTR token);
		void __setContent(PTSTR mmBuff, PTSTR content, int buffLen);

private:
	map<QString ,MMF *> m_vMMFs;
	bool m_bIsPause;
};

static CrossProcessNotificationServer *_instance = NULL;

#endif // CROSSPROCESSNOTIFICATIONSERVER_H
