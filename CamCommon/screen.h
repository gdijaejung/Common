//
// ȭ�鿡 ǥ�õǴ� ���� ��ũ�� ������ �����Ѵ�.
// ȭ�� �ػ�, ī�޶󿡼� �ν��� ��ũ�� ũ�� ���� ������ �����Ѵ�.
// 
#pragma once


class cCapture;
class cScreen
{
public:
	cScreen();
	virtual ~cScreen();

	void Init(const cv::Rect &screenResolution, const vector<cv::Point> &screenContour);
	void InitResolution(const cv::Rect &screenResolution);

	void DetectScreen(cCamera &camera, const float minScreenArea);
	void SetScreenContour(const cv::Point contours[4]);

	void ShowChessBoard(const int rows, const int cols);
	cv::Point2f ShowPingpong(const cv::Point2f &ballPos, const cv::Point2f &velocity, const cv::Size2f &ballSize);
	void ShowBoxLines(const int rows, const int cols, const bool isClear=false);
	void ShowPoints(const vector<cv::Point2f> &points, const cv::Size2f &size=cv::Size2f(20,20), 
		const cv::Scalar &color = cv::Scalar(0, 0, 0),
		const bool isClear = false, const cv::Scalar &bgColor=cv::Scalar(255,255,255));

	Mat SkewTransform(const int width, const int height, const float scale=1.f);
	void CloseScreen();

	int GetWidth();
	int GetHeight();
	int GetRecogWidth();
	int GetRecogHeight();
	pair<float, float> GetResolutionRecognitionRate();

	const cv::Rect& GetScreenResolution() const;
	const vector<cv::Point>& GetScreenContour() const;
	cv::Mat& GetScreen();


protected:
	bool m_show;
	cv::Rect m_screenResolution; // {0,0,w,h}
	vector<cv::Point> m_screenContour;	// �νĵ� ��ũ���� ũ�� (�ε��� ����)
	// 0 ---------- 1
	// |            |
	// |            |
	// |            |
	// 2 ---------- 3
	//

	cv::Mat m_screen;
	int m_oldT;
	cv::Point2f m_ballPos;
	cv::Point2f m_ballVelocity;
};


inline const cv::Rect& cScreen::GetScreenResolution() const { return m_screenResolution; }
inline const vector<cv::Point>& cScreen::GetScreenContour() const { return m_screenContour; }
inline cv::Mat& cScreen::GetScreen() { return m_screen;  }