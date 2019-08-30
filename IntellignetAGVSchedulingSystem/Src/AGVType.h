/*!
 * @file AGVType
 * @brief ����AGV����Ļ�����Ϣ
 * @author FanKaiyu
 * @date 2019-08-29
 * @version 1.0
*/
#pragma once
#include <string>

using namespace std;

#ifndef _AGV_TYPE_H
#define _AGV_TYPE_H

/*!
 * @brief ����AGV�����ı�ʶö��
 * @date 2019-08-29
 */
enum AGVAbility
{
	// ��
	None,
	// ����
	Consign,
	// ����
	Lift,
	// ǣ��
	Pull,
	// Ǳ��
	Dive,
	// ��е��
	Arm,
	// �泵
	Fork,
};

/*!
 * @class AGVType
 * @brief ����AGV���͵Ļ������Ե���
 * @date 2019-08-29
*/
class AGVType
{
public:
	AGVType();
	~AGVType();
	AGVType(const AGVType& type);

public:
	/*!
	 * @brief ��������AGVƷ�Ƶ��ַ���
	 * @date 2019-08-29
	*/
	string m_strBrand;

	/*!
	 * @brief ��������AGV�ͺŵ��ַ���
	 * @date 2019-08-29
	*/
	string m_strVersion;

	/*!
	 * @brief ��������AGV���ܵı�ʶ
	 * @date 2019-08-29
	*/
	unsigned short m_usAbility;

	/*!
	 * @brief ��������AGV����ٶȵ�ֵ,��λ:m/min
	 * @date 2019-08-29
	*/
	float m_fMaxSpeed;

	/*!
	 * @brief ��������AGV�����������ֵ,��λ:kg
	 * @date 2019-08-29
	*/
	float m_fMaxWeight;

public:
	/*!
	 * @brief ����AGV������Ϣ
	 * @param AGVType& AGV������Ϣ
	*/
	void operator=(const AGVType& type);
};

#endif // !_AGV_TYPE_H