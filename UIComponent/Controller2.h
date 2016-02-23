//
// 2016-02-19, jjuiddong
//
//
// ���� ���� ��ü
// MainLoop�� �����Ѵ�.
//
// Upate����� �� ��ü���� Update() �Լ��� ȣ���Ѵ�.
//
#pragma once


#include "UpdateObserver.h"


class cController2 : public common::cSingleton < cController2 >
	, public cUpdateObservable
{
public:
	cController2();
	virtual ~cController2();

	bool Init();
	void Run();
	float GetGlobalSeconds() const;


	bool m_isLoop;
	float m_globalSeconds;
};


inline float cController2::GetGlobalSeconds() const { return m_globalSeconds; }
