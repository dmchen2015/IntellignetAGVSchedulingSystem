/*!
 * @file TCP_IPClient.h
 * @breief ����TCP/IP�ͻ��������Լ����ܵ��ļ�
 * @date 2019-09-15
 * @author FanKaiyu
 * @version 1..0
*/
#pragma once
#include "TCP_IPBase.h"

class TCP_IPClient :
	public TCP_IPBase
{
public:
	TCP_IPClient();
	~TCP_IPClient();

private:
	/*!
	 * @brief �ͻ������������ӷ����ʱ���ɵ�SOCKET������
	 * ��ͨ���رմ˱���ʹ��connect������ǰ����������
	 * @date 2019-09-15
	*/
	SOCKET m_sockTmp;

	/*!
	 * @brief ����˵�ַ
	 * 
	 * �����������ӷ����
	 * ����շ��������ʱ��ͻ���ƥ��
	 * @date 2019-09-15
	*/
	sockaddr m_sockaddrSrv;

	/*!
	 * @brief �ͻ��˵�ַ
	 *
	 * ���԰�SOCKET,�Թ̶�IP�ķ�ʽ����������
	 * @date 2019-09-15
	*/
	sockaddr m_sockaddrClnt;

private:
	/*!
	 * @brief ���ӷ����
	 *
	 * ���Թ̶�IP���˿ڵķ�ʽ����TCP�����
	 * @date 2019-09-15
	 * @param sockaddr �ͻ��˵�ַ
	 * @param sockaddr ����˵�ַ
	 * @return bool ���ӳɹ�����true,���򷵻�false
	*/
	inline bool Connect(const sockaddr& clienaddr,const sockaddr& srvaddr);

	/*!
	 * @brief ���ӷ����
	 *
	 * ��������˿ڵķ�ʽ����TCP�����
	 * @date 2019-09-15
	 * @param sockaddr ����˵�ַ
	 * @return bool ���ӳɹ�����true,���򷵻�false
	*/
	inline bool Connect(const sockaddr& srvaddr);

	/*!
	 * @brief ���ӷ����
	 * @date 2019-09-15
	 * @param sockaddr ��������ַ
	 * @return bool ���ӳɹ�����true,���򷵻�false
	*/
	bool ConnectServer(const sockaddr& srvaddr);

	/*!
	 * @brief ���ӿͻ���
	 * @date 2019-09-15
	 * @param sockaddr �ͻ��˵�ַ
	 * @return bool ���ӳɹ�����true,���򷵻�false
	*/
	bool ConnectClient(const sockaddr& clntaddr);

public:
	/*!
	 * @brief ���ӿͻ���
	 * @date 2019-09-15
	 * @param SOCKET �ͻ���socket������
	 * @return bool ���ӳɹ�����true,���򷵻�false
	*/
	bool Connect(const SOCKET& sock);

	/*!
	 * @brief ���ӷ����
	 * @date 2019-09-15
	 * @return bool ���ӳɹ�����true,���򷵻�false
	*/
	bool Connect();
};

