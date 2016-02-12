
#include "stdafx.h"
#include "streamingreceiver.h"


using namespace cvproc;


cStreamingReceiver::cStreamingReceiver() 
	: m_rcvBuffer(NULL)
{
}

cStreamingReceiver::~cStreamingReceiver()
{
	SAFE_DELETEA(m_rcvBuffer);
}


bool cStreamingReceiver::Init(const bool isUDP, const string &ip, const int port, const int networkCardIdx,
	const int gray, const int compressed, const int jpgComQuality)
{
	m_isUDP = isUDP;

	m_udpServer.Close();
	m_tcpClient.Close();
	
// 	if (isUDP)
// 	{
// 		m_udpServer.SetMaxBufferLength(307200);
// 		m_udpServer.Init(0, port);
// 	}
// 	else
// 	{
// 		if (!m_tcpClient.Init(ip, port, g_maxStreamSize, 10, 10))
// 			return false;
// 	}

	// �켱 TCP/IP�� ������ ��, udp/tcp ������ ���� �Ѵ�.
	if (!m_tcpClient.Init(ip, port, g_maxStreamSize, 10, 10))
		return false;

	// UDP�� ���� �ޱ�����, ���� ��ǻ���� IP�� ��Ʈ��ȣ�� �����Ѵ�.
	// ��Ʈ��ȣ�� tcp/ip��Ʈ�� +1 �� ���̴�.
	if (isUDP)
	{
		const string rcvIp = common::GetHostIP(networkCardIdx);
		std::cout << "UDP Receive IP = " << rcvIp << std::endl;

		sStreamingProtocol data;
		data.protocol = 100;
		data.type = 1;
		data.port = port + 1;
		data.uip = inet_addr(rcvIp.c_str());
		m_tcpClient.Send((BYTE*)&data, sizeof(data));

		m_udpServer.SetMaxBufferLength(307200);
		if (!m_udpServer.Init(0, port + 1))
		{
			// udp�� ���ŵǴ� ���� �����ߴٸ�, tcp/ip�� �޴´�.
			m_isUDP = false;
		}
	}

	{
		// gray, compressed, jpgCompQuality ���� ��������
		Sleep(500);
		sStreamingProtocol data;
		data.protocol = 101;
		data.gray = gray==1? true : false;
		data.compressed = compressed==1? true : false;
		data.compQuality = jpgComQuality;
		m_tcpClient.Send((BYTE*)&data, sizeof(data));
	}


	if (m_src.empty())
		m_src = Mat(480, 640, CV_8UC1);
	if (m_finalImage.empty())
		m_finalImage = Mat(480, 640, CV_8UC1);

	if (!m_rcvBuffer)
		m_rcvBuffer = new BYTE[g_maxStreamSize];

	return true;
}


cv::Mat& cStreamingReceiver::Update()
{
	RETV(!IsConnect(), m_finalImage);

	const static int sizePerChunk = g_maxStreamSize - sizeof(sStreamingData); // size per chunk

	int len = 0;
	if (m_isUDP)
	{
		len = m_udpServer.GetRecvData(m_rcvBuffer, g_maxStreamSize);
	}
	else
	{
		network::sPacket packet;
		if (m_tcpClient.m_recvQueue.Front(packet))
		{
			len = packet.actualLen;
			memcpy(m_rcvBuffer, packet.buffer, packet.actualLen);
			m_tcpClient.m_recvQueue.Pop();
		}
	}

	if (len <= 0)
		return m_finalImage;

	sStreamingData *packet = (sStreamingData*)m_rcvBuffer;
	static int oldCompressed = -1;
	static int oldGray = -1;
	if (oldCompressed != (int)packet->isCompressed)
	{
		oldCompressed = (int)packet->isCompressed;
		std::cout << "compressed = " << (int)packet->isCompressed << std::endl;
	}
	if (oldGray != (int)packet->isGray)
	{
		oldGray = (int)packet->isGray;
		std::cout << "gray = " << (int)packet->isGray << std::endl;
	}


	if (packet->chunkSize == 1)
	{
		packet->data = m_rcvBuffer + sizeof(sStreamingData);

		if (packet->isCompressed)
		{
			if (packet->imageBytes <= len)
			{
				memcpy((char*)m_src.data, packet->data, packet->imageBytes);
				cv::imdecode(m_src, 1, &m_finalImage);
			}
		}
		else
		{
			// �ٷ� decode �� �����ؼ� �����Ѵ�.
			memcpy((char*)m_finalImage.data, packet->data, packet->imageBytes);
		}
	}
	else if (packet->chunkSize > 1)
	{
		static unsigned char oldId = 0;

		if (oldId != packet->id)
		{
			if (packet->isCompressed)
			{
				cv::imdecode(m_src, 1, &m_finalImage);
			}
			else
			{
				// �ٷ� decode �� �����ؼ� �����Ѵ�.
				memcpy((char*)m_finalImage.data, (char*)m_src.data, m_src.total() * m_src.elemSize());
			}

			oldId = packet->id;
		}

		packet->data = m_rcvBuffer + sizeof(sStreamingData);
		char *dst = (char*)m_src.data + packet->chunkIndex * sizePerChunk;
		const int copyLen = max(0, (len - (int)sizeof(sStreamingData)));
		memcpy(dst, packet->data, copyLen);
	}

	return m_finalImage;
}


bool cStreamingReceiver::IsConnect()
{
	if (m_isUDP)
		return m_udpServer.IsConnect();
	return m_tcpClient.IsConnect();
}


void cStreamingReceiver::Close()
{
	m_udpServer.Close();
	m_tcpClient.Close();
}
