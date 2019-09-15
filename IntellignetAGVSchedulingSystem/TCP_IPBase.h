/*!
 * @file TCP_IPBase.h
 * @brief TCP/IPͨ�ŵĻ����ļ�
 * @date 2019-09-12
 * @author FanKaiyu
 * @version 1.0
*/
#pragma once
#include <string>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <WinDNS.h>

#pragma comment(lib, "WS2_32")

class TCP_IPBase
{
public:
	TCP_IPBase();
	~TCP_IPBase();

protected:
	// �׽���
	SOCKET m_socket;

protected:
	/*!
	 * @brief ��ȡ����Э���ַ
	 * @date 2019-09-12
	 * @return sockaddr ���ر���Э���ַ
	*/
	inline sockaddr GetLocalAddress();

	/*!
	 * @brief ��ȡԶ��Э���ַ
	 * @date 2019-09-12
	 * @return sockaddr ����Զ��Э���ַ
	*/
	inline sockaddr GetPeerAddress(); 

	/*!
	 * @brief ��ȡ����Э���ַ
	 * @date 2019-09-15
	 * @param SOCKET& socket������
	 * @return sockaddr ���ر���Э���ַ
	*/
	sockaddr GetLocalAddress(const SOCKET& sock);

	/*!
	 * @brief ��ȡԶ��Э���ַ
	 * @date 2019-09-15
	 * @param SOCKET& socket������
	 * @return sockaddr ����Զ��Э���ַ
	*/
	sockaddr GetPeerAddress(const SOCKET& sock);

	/*!
	 * @brief ��ʼ���׽��ֿ�
	 * @date 2019-09-15
	 * @return bool ��ʼ���ɹ�����true,���򷵻�false
	*/
	bool InitWSA();

	/*!
	 * @brief �����׽���
	 * @date 2019-09-15
	*/
	SOCKET CreateSocket();

	/*!
	 * @brief ���׽���
	 * @date 2019-09-15
	 * @param SOCKET& Ҫ�󶨵��׽��� 
	 * @param sockaddr_in& �󶨵ĵ�ַ,Э��IPV4
	 * @return bool �󶨳ɹ�����true,���򷵻�false
	*/
	bool BindSocket(SOCKET& sock,const sockaddr& addr);

	/*!
	 * @brief �ر��׽���
	 * @date 2019-09-15
	*/
	inline void CloseSocket();

	/*!
	 * @brief �ر��׽���
	 * @date 2019-09-15
	 * @param SOCKET& Ҫ�رյ��׽���
	*/
	void CloseSocket(SOCKET& sock);
};

