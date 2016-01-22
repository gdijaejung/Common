//
// 2016-01-22, jjuiddong
//
// ��׷��� ������ Point�� ã�� ������ ���¿����� ��ǥ�� ����Ѵ�.
//
// ��׷��� ������ ��ǥ Point 4���� Scale ���� �Է����� �Ѵ�.
//
#pragma once


class cSkewDetect
{
public:
	cSkewDetect(const int rows=480, const int cols=640);
	cSkewDetect(const cRecognitionConfig &recogConfig, const int rows = 480, const int cols = 640);
	virtual ~cSkewDetect();

	bool Init(const cRectContour &contour, const float scale, const int width=640, const int height=480);
	bool Read(const string &contourFileName, const bool createContourSize=false);
	bool Write(const string &contourFileName);
	bool Detect(const Point pos, OUT Point2f &out);
	Mat& Transform(const Mat &src);
	bool DetectCalc(const Point pos, OUT Point2f &out);


public:
	bool m_isInit;
	float m_scale;
	int m_rows;
	int m_cols;
	cSquareContour m_contour;
	Mat m_transmtx;
	Mat m_bkgnd;
	Mat m_skewBkgnd;
	cDetectPoint m_detectPoint;
	Point2f m_pos;		// ���� �ֱ� ������ �����Ѵ�.
};

