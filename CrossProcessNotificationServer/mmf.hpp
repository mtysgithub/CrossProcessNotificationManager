#ifndef MMF_HPP
#define MMF_HPP

#include "stdafx.h"
#include "crossprocessnotificationserver_global.h"

#define _CREATE_MMF_(_size_, _token_) CreateFileMapping(INVALID_HANDLE_VALUE,				\
																					NULL,										\
																					PAGE_READWRITE,					\
																					0,											\
																					_MMF_ALLLEN_BYTE_(_size_),	\
																					_token_);

#define  _SET_UNDO_(_buff_, _val_) ((PTSTR)_buff_)[0] = _val_;
#define _USING_MAP_(pView) MMF::MapViewCtr tmpMpvCtr(pView);

#define  _MSG_PROCEED_(_buff_) ((((PTSTR)_buff_)[0])?(false):(true))
#define _DATA_PROCED_ 0
#define _DATA_UNPROCED_ 1

class MMF
{
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
	MMF(wchar_t *token, int bufSIze)
	{
		memcpy(m_mmfToken, token, _TOKEN_LEN_ * sizeof(WCHAR));
		m_mmfToken[_TOKEN_LEN_] = '\0';

		//create mmf...
		this->m_mmfSize = bufSIze;

		wchar_t upToken[_TOKEN_LEN_ + 1];
		memcpy(upToken, m_mmfToken, _TOKEN_LEN_ * sizeof(WCHAR));
		upToken[0] = 'u';
		upToken[_TOKEN_LEN_] = '\0';
		m_hUpMMF = _CREATE_MMF_(m_mmfSize, upToken)
		if (m_hUpMMF)
		{
			PVOID pUpMapView = NULL;
			this->getUpView(&pUpMapView);
			_USING_MAP_(pUpMapView)
			if (pUpMapView)
			{
				_SET_UNDO_(pUpMapView, _DATA_PROCED_);
			}
		}

		wchar_t downToken[_TOKEN_LEN_ + 1];
		memcpy(downToken, m_mmfToken, _TOKEN_LEN_ * sizeof(WCHAR));
		downToken[0] = 'd';
		downToken[_TOKEN_LEN_] = '\0';
		m_hDownMMF = _CREATE_MMF_(m_mmfSize, downToken)
		if (m_hDownMMF)
		{
			PVOID pDownMapView = NULL;
			this->getDownView(&pDownMapView);
			_USING_MAP_(pDownMapView)
			if (pDownMapView)
			{
				_SET_UNDO_(pDownMapView, _DATA_PROCED_);
			}
		}
	}

	~MMF()
	{
		//Close MMF
		CloseHandle(m_hDownMMF);
		CloseHandle(m_hUpMMF);

		m_vTryPostBuff.clear();
	}

	void Destory(){ delete this; }

	void tryPost()
	{
		PVOID pDownView;
		this->getDownView(&pDownView);
		_USING_MAP_(pDownView);
		if ((pDownView) && _MSG_PROCEED_(pDownView))
		{
			PTSTR tryPostContent = NULL;
			this->outQueue(&tryPostContent);
			if (tryPostContent)
			{
				//post it
				memcpy(pDownView, tryPostContent, _MMF_ALLLEN_BYTE_(this->m_mmfSize) * sizeof(WCHAR));
			}
		}
	}

	void inQueue(PTSTR content)
	{
		m_vTryPostBuff.push_back(content);
	}

	void outQueue(PTSTR *pContent)
	{
		if (!m_vTryPostBuff.empty())
		{
			*pContent = *m_vTryPostBuff.begin();
			m_vTryPostBuff.pop_front();
		}else
		{
			*pContent = NULL;
		}
	}

	HRESULT getUpView(OUT PVOID *ppView)
	{
		*ppView = MapViewOfFile(m_hUpMMF, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
		return S_FALSE;
	}

	HRESULT getDownView(OUT PVOID *ppView)
	{
		*ppView = MapViewOfFile(m_hDownMMF, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
		return S_FALSE;
	}

	void unmapView(PVOID pView)
	{
		UnmapViewOfFile(pView);
	}

public: 
	int m_mmfSize;
	wchar_t  m_mmfToken[_TOKEN_LEN_ + 1];

	//上行，下行信道
	HANDLE m_hUpMMF;
	HANDLE m_hDownMMF;

	list<PTSTR> m_vTryPostBuff;
};

#endif