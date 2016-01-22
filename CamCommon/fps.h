//
// 2016-01-20, jjuiddong
//
// Frame per Seconds ���� Ŭ����
//
//
#pragma once

#include <mmsystem.h>


namespace cvproc
{
	
	class cFps
	{
	public:
		cFps();
		virtual ~cFps() {}

		int Update();
		void Update(Mat &dst);
		void UpdateConsole();
		bool UpdateSeconds(OUT int &out);


	protected:
		bool CalcFps();

	public:
		int m_lastUpdateTime;
		int m_fps;
		int m_inc;
	};


	cFps::cFps() : m_lastUpdateTime(0), m_fps(0), m_inc(0)
	{
	}


	// fps�� �����Ѵ�.
	int cFps::Update()
	{
		CalcFps();
		return m_fps;
	}


	// fps�� Mat�� ����Ѵ�.
	void cFps::Update(Mat &dst)
	{
		CalcFps();
		cv::putText(dst, common::format("%d", m_fps), Point(10, 30), 1, 2, Scalar(255, 255, 255));
	}

	// fps�� �ܼ�â�� ����Ѵ�.
	void cFps::UpdateConsole()
	{
		if (CalcFps())
		{
			std::cout << "FPS : " << m_fps << std::endl;
		}
	}


	// 1�ʸ��� true�� �����Ѵ�.
	bool cFps::UpdateSeconds(OUT int &out)
	{
		const bool reval = CalcFps();
		out = m_fps;
		return reval;
	}


	// fps ���
	bool cFps::CalcFps()
	{
		const int curT = timeGetTime();
		if (0 == m_lastUpdateTime)
			m_lastUpdateTime = curT;

		++m_inc;
		if (curT - m_lastUpdateTime > 1000)
		{
			m_fps = m_inc;
			m_inc = 0;
			m_lastUpdateTime = curT;
			return true;
		}

		return false;
	}
}
