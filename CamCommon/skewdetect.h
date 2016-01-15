//
// 찌그러진 영역의 Point를 찾아 펼쳐진 상태에서의 좌표를 계산한다.
//
// 찌그러진 영역의 좌표 Point 4개와 Scale 값을 입력으로 한다.
//
// 해상도 640 X 480 으로 간주한다.
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
	Point2f m_pos;		// 가장 최근 정보를 저장한다.
};

