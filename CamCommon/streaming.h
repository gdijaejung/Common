//
// ��Ʈ���ֿ� ���õ� ������ �����Ѵ�.
//
#pragma once


namespace cvproc
{
	struct sStreamingData
	{
		unsigned char id;			// streaming id (���� ���̵𳢸� ����Ÿ�� ��ģ �Ŀ� ����Ѵ�.)
		unsigned char chunkSize;	// chunk size (�̹��� �뷮 ������ ������ ����Ÿ ûũ�� ����)
		unsigned char chunkIndex;	// chunk index
		unsigned char isGray;		// gray 0 : 1
		unsigned char isCompressed;	// jpeg compressed 0 : 1
		int imageBytes;				// image size (byte unit)
		BYTE *data;					// image data
	};


	// ���ù��� �������� ���� ��� ��������
	// TCP/IP �θ� ���۵ȴ�.
	struct sStreamingProtocol
	{
		BYTE protocol;		// �������� Ÿ��
									// protocol = 100, ���� �������� ���� (TCP/IP) 
									// Receiver�� IP�� Port, ���� Ÿ�� �۽�

									// protocol = 101, gray, compressed, compressed quality, fps ����
									// gray, compressed, compQuality �� ���.
									//


		BYTE type;			// udp=1, tcp=0
		unsigned int uip; // ip address, type long
		int port;
		bool gray;
		bool compressed;
		int compQuality;
		int fps;					// �ʴ� ���� ������
	};


	const static int g_maxStreamSize = (int)pow(2, 15) - 1;
	//const static int g_maxStreamSize = (int)pow(2, 14) - 1;
}
