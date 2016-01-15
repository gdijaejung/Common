//
// ��׷��� ������ Point�� ã�� ������ ���¿����� ��ǥ�� ����Ѵ�.
//
// ��׷��� ������ ��ǥ Point 4���� Scale ���� �Է����� �Ѵ�.
//
// �ػ� 640 X 480 ���� �����Ѵ�.
//
#pragma once


class cSkewDetect
{
public:
	cSkewDetect();
	cSkewDetect(const cRecognitionConfig &recogConfig);
	virtual ~cSkewDetect();

	bool Init(const cRectContour &contour, const float scale, const int width=640, const int height=480);
	bool Read(const string &fileName, const bool createContourSize=false);
	bool Write(const string &fileName);
	bool Detect(const Point pos, OUT Point2f &out);
	Mat& Transform(const Mat &src);
	bool DetectCalc(const Point pos, OUT Point2f &out);


public:
	bool m_isInit;
	float m_scale;
	cSquareContour m_contour;
	Mat m_transmtx;
	Mat m_bkgnd;
	Mat m_skewBkgnd;
	cDetectPoint m_detectPoint;
	Point2f m_pos;		// ���� �ֱ� ������ �����Ѵ�.
};

