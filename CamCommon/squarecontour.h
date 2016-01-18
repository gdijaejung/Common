//
// �簢�� ���� �� ��ġ�� uv ������ ����Ѵ�.
//
//
#pragma once

#include "rectcontour.h"


class cSquareContour : public cRectContour
{
public:
	cSquareContour();
	virtual ~cSquareContour();

	void InitSquare();
	bool GetUV(const Point &pos, OUT Point2f &uv);
	cSquareContour& operator = (const cRectContour &rhs);
	cSquareContour& operator = (const cSquareContour &rhs);


	Vector3 m_v[4];
};
