//
// 사각 박스를 표현하는 클래스.
//
#pragma once


class cRectContour
{
public:
	cRectContour();
	cRectContour(const vector<cv::Point> &contours);
	cRectContour(const vector<cv::KeyPoint> &contours);
	cRectContour(const cv::Point &center, const float size);
	virtual ~cRectContour();

	bool Init(const vector<cv::Point> &contours);
	bool Init(const vector<cv::Point2f> &contours);
	bool Init(const vector<cv::KeyPoint> &keypoints);
	bool Init(const cv::Point &center, const float size);
	void Normalize();
	void Draw(cv::Mat &dst, const cv::Scalar &color=cv::Scalar(0,0,0), const int thickness=1);

	int Width() const;
	int Height() const;
	cv::Point At(const int index) const;
	cv::Point Center() const;
	void ScaleCenter(const float scale);
	void Scale(const float vscale, const float hscale);

	cRectContour& operator = (const cRectContour &rhs);


public:
	vector<cv::Point> m_contours;
};
