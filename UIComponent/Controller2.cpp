
#include "stdafx.h"
#include "Controller2.h"


cController2::cController2() 
	: m_isLoop(true)
{
}

cController2::~cController2()
{
}


bool cController2::Init()
{
	if (!NotifyInitObserver())
		return false;

	return true;
}


// ���α׷��� ���۵Ǹ�, �� �Լ��� ȣ��ǰ�, ���α׷��� ���� ��, �Լ��� �����Ѵ�.
void cController2::Run()
{

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	int oldT = timeGetTime();
	while (1)
	{
// 		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
// 		{
// 			TranslateMessage(&msg);
// 			DispatchMessage(&msg);
// 		}
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			GetMessage(&msg, NULL, 0, 0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (!m_isLoop)
 			break;

		const int curT = timeGetTime();
 		const float deltaSeconds = (float)(curT - oldT) * 0.001f; // 1�ʰ� ����Ǹ� 1�̵ȴ�.
 		if (deltaSeconds > 0.01f)
 		{
			NotifyUpdateObserver(deltaSeconds);
 			oldT = curT;
 		}

	}

}


