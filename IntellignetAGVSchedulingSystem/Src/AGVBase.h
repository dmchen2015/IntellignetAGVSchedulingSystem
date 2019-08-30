/*!
 * @file AGVBase
 * @brief ����AGV�������Ե���Ϣ
 * @author FanKaiyu
 * @date 2019-08-29
 * @version 1.0
*/
#pragma once
#include "AGVType.h"
#include "AGVEnum.h"

#include <string>

using namespace std;

#ifndef _AGV_BASE_H
#define _AGV_BASE_H

/*!
 * @class AGVBase
 * @brief ����AGV�������Ե���
 * @date 2019-08-29
*/
class AGVBase
{
public:
	AGVBase();
	~AGVBase();
	AGVBase(const unsigned short usNo,const AGVType& Type);
	AGVBase(const unsigned short usNo, const AGVType& Type,const unsigned short usCurLocation,const unsigned short usEndLocation);

#pragma region AGV Arrtibute
private:
	// AGV���Ա���

	/*!
	 * @brief ����AGV��ŵ�ֵ
	 * @date 2019-08-29
	*/
	unsigned short m_usNo;

	/*!
	 * @brief ����AGV�ͺŵĶ���
	 * @date 2019-08-29
	*/
	AGVType m_Type;

	// ����AGV��ǰ״̬��ֵ

	/*!
	 * @brief ����AGV��ǰλ����Ϣ��ֵ,ͨ����ʾ��ǰRFID����
	 * @date 2019-08-29
	*/
	unsigned short m_usCurLocation;

	/*!
	 * @brief ����AGV��ǰ�ٶȵ�ֵ,ͨ��Ϊ�ٷֱ�
	 * 
	 * ˫����AGV�����ƶ�ʱ�ٶ�Ϊ��ֵ,�����ƶ�ʱ�ٶ�Ϊ��ֵ
	 * @date 2019-08-29
	 * @update 2019-08-30 FanKaiyu ����˫����AGV�ٶ�˵��
	*/
	char m_chCurSpeed;

	/*!
	 * @brief ����AGV��ǰʣ�������ֵ,ͨ��Ϊ�ٷֱ�
	 * @date 2019-08-29
	*/
	unsigned char m_byBattery;

	/*!
	 * @brief ����AGV��ǰ������״̬�ı�ʶ
	 * @date 2019-08-29
	*/
	unsigned char m_byLifter;

	/*!
	 * @brief ����AGV��ǰ��Ͳ������״̬�ı�ʶ
	 * @date 2019-08-29
	*/
	unsigned char m_byRoller;

	// ����AGV��ǰ��е��״̬�ı�ʶ

	/*!
	 * @brief ����AGV��е�۵�ǰִ�еĶ���
	 * @date 2019-08-29
	*/
	unsigned short m_usArmAction;

	/*!
	 * @brief ����AGV��е�۵�ǰִ�ж�����״̬
	 * @date 2019-08-29
	*/
	unsigned char m_byArmStatus;

	/*!
	 * @brief ����AGV��ǰ������״̬
	 * @date 2019-08-29
	*/
	unsigned char m_byStatus;

	/*!
	 * @brief ����AGV��ǰ���쳣��Ϣ
	 * @date 2019-08-29
	*/
	char m_chError;

	/*!
	 * @brief ����AGV��ǰ���ػ�����
	 * @date 2019-08-29
	*/
	unsigned char m_byCargo;

	/*!
	 * @brief ����AGV�ƶ�Ŀ��λ�õ�ֵ,ͨ����ʾ�յ�RFID����
	 * @date 2019-08-29
	*/
	unsigned short m_usEndLocation;

	/*!
	 * @brief ����AGV��е�۶������Ƶ��ַ�����
	 * @date 2019-08-30
	*/
	string m_strActNameArr[0xFF];

	/*!
	 * @brief ����AGV��һλ����Ϣ,ͨ����ʾ��һRFID����
	 * @date 2019-08-30
	*/
	unsigned short m_usOldLocation;

	/*!
	 * @brief ����AGV��һ�յ�λ����Ϣ,ͨ����ʾ��һRFID����
	 * @date 2019-08-30
	*/
	unsigned short m_usOldEndLocation;
#pragma endregion

#pragma region AGV Action Function Code
public:
	// AGV��������

	/*!
	 * @brief �ƶ�����վ
	 *
	 * ֪ͨAGV�ƶ���ָ���Ĺ�վ
	 * @date 2019-08-29
	 * @param unsigned short ��վ���
	*/
	void MoveToStation(const unsigned short usStation);

	/*!
	 * @brief �ƶ�������
	 *
	 * ֪ͨAGV�ƶ���ָ����λ��
	 * @date 2019-08-29
	 * @param unsigned short λ����Ϣ,ͨ��ΪRFID�����
	*/
	void MoveToLocation(const unsigned short usLocation);

	/*!
	 * @brief ���ٵ���
	 *
	 * �����û���ʱ��������,����AGV�ٶȻ򽵵�AGV�ٶ�.
	 * ��1����Ч.
	 * @date 2019-08-29
	 * @param char ����
	*/
	void SetSpeed(const char chSpeed);

	/*!
	 * @brief ��ͣ
	 *
	 * ���ڽ��������Զ��ֹͣAGV
	 * @date 2019-08-29
	*/
	void Scream();

	/*!
	 * @brief ��λ
	 *
	 * ����AGV��״̬��Ϣ,ʹAGV�ָ�����
	 * @date 2019-08-29
	*/
	void Reset();

	/*!
	 * @brief �ָ�Ĭ��ֵ
	 *
	 * ����AGV��״̬��Ϣ,���»�ȡAGV״̬��Ϣ
	 * @date 2019-08-29
	*/
	void Default();

	/*!
	 * @brief �ػ�
	 *
	 * Զ�̿���AGV�رյ�Դ
	 * @date 2019-08-30
	*/
	void Shutdown();

	/*!
	 * @brief ����
	 *
	 * Զ�̿���AGV������״̬
	 * @date 2019-08-30
	*/
	void Sleep();

	/*!
	 * @brief ����/����
	 * 
	 * Զ�̿���AGV������Դ����
	 * @date 2019-08-30
	*/
	void Wakeup();

	/*!
	 * @brief �����˿���
	 *
	 * Զ�̿���AGV�������������½�
	 * @date 2019-08-30
	 * @param unsigned char Ϊ0ʱֹͣ,Ϊ1ʱ����,Ϊ2ʱ�½�
	*/
	void LifterControl(const unsigned char byCtrl);

	/*!
	 * @brief ��Ͳ/��������
	 *
	 * Զ�̿���AGV��Ͳ��������ת��ֹͣ
	 * date 2019-08-30
	 * @param unsigned char Ϊ0ʱֹͣ,Ϊ1ʱ��ת,Ϊ2ʱ��ת
	*/
	void RollerControl(const unsigned char byCtrl);

	/*!
	 * @brief ��е�۶�������
	 *
	 * Զ�̿���AGV��е�۶�����ʼ,ֹͣ
	 * date 2019-08-30
	 * @param unsigned short Ϊ0ʱֹͣ,Ϊ����ֵʱִ����Ӧ����
	*/
	void ArmControl(const unsigned short byCtrl);
#pragma endregion

#pragma region Initialize AGV Attribute
public:
	// ��ʼ��AGV���Ժ���

	/*!
	 * @brief AGV���Գ�ʼ��
	 * @date 2019-08-30
	 * @param unsigned short AGV���
	 * @param AGVType* AGV���Ͷ���
	*/
	void InitializeAttribut(const unsigned short usNo,const AGVType& type);

	/*!
	 * @brief ����AGV���Գ�ʼ��
	 * @date 2019-08-30
	 * @param unsigned short AGV���
	 * @param AGVType* AGV���Ͷ���
	 * @param unsigned short AGV��ǰλ����Ϣ,ͨ��ָRFID�����
	 * @param unsigned short AGV�յ�λ����Ϣ
	*/
	void InitializeAttribut(const unsigned short usNo,const AGVType& type, const unsigned short usCurLocation, const unsigned short usEndLocation = 0);

	/*!
	 * @brief ����AGV��е�۶�������
	 * @date 2019-08-30
	 * @param string AGV�����ļ�·��
	*/
	void LoadActName(string strPath);

	/*!
	 * @brief ����AGV��е�۶�������
	 * @date 2019-08-30
	 * @param string AGV�����ļ�Ŀ¼·��
	*/
	void LoadActNameFile(string strPath);
#pragma endregion

#pragma region Update AGV Attribute
public:
	// ����AGV���Ժ���

	/*!
	 * @brief ����AGV��ǰ���ٶ���Ϣ
	 * @date 2019-08-30
	 * @param char AGV���صĵ�ǰ�ٶ���Ϣ
	*/
	void UpdateSpeed(const char chSpeed);

	/*!
	 * @brief ����AGV��ǰ�ĵ�����Ϣ
	 * @date 2019-08-30
	 * @param char AGV���صĵ�ǰ��ʣ�������Ϣ
	*/
	void UpdateBattery(const unsigned char byBattery);

	/*!
	 * @brief ����AGV��ǰ��״̬��Ϣ
	 * @date 2019-08-30
	 * @param unsigned char AGV���صĵ�ǰ����״̬��Ϣ
	*/
	void UpdateStatus(const unsigned char byStatus);

	/*!
	 * @brief ����AGV��ǰ���ػ�������Ϣ
	 * @date 2019-08-30
	 * @param unsigend char AGV���صĵ�ǰ���ػ�������Ϣ,ͨ��0��ʶ����,255��ʾ����
	*/
	void UpdateCargo(const unsigned char byCargo);

	/*!
	 * @brief ����AGV��ǰ�����˵�״̬��Ϣ
	 * @date 2019-08-30
	 * @param unsigned char AGV���صĵ�ǰ������״̬��Ϣ
	*/
	void UpdateLifter(const unsigned char byLifter);

	/*!
	 * @brief ����AGV��ǰ��Ͳ��״̬��Ϣ
	 * @date 2019-08-30
	 * @param unsigned char AGV���صĵ�ǰ��Ͳ״̬��Ϣ
	*/
	void UpdateRoller(const unsigned char byRoller);

	/*!
	 * @brief ����AGV��ǰ��е��ִ�еĶ�����Ϣ
	 * @date 2019-08-30
	 * @param unsigned short AGV���صĻ�е�۵�ǰִ�еĶ�����Ϣ
	*/
	void UpdateArmAction(const unsigned short usAction);

	/*!
	 * @brief ����AGV��ǰ��е��ִ�ж�����״̬
	 * @date 2019-08-30
	 * @param unsigned char AGV���صĻ�е�۵�ǰִ�ж�����״̬��Ϣ
	*/
	void UpdateArmStatus(const unsigned char byStatus);

	/*!
	 * @brief ����AGV��ǰ��λ����Ϣ
	 * @date 2019-08-30
	 * @param unsigend short AGV���صĵ�ǰλ����Ϣ
	 * @return unsigned short AGV��һλ����Ϣ
	*/
	const unsigned short UpdateCurLocation(const unsigned short usLocation);

	/*!
	 * @brief ����AGV�յ��λ����Ϣ
	 * @date 2019-08-30
	 * @param unsigned short AGV���ص��յ�λ����Ϣ
	 * @return unsigned short AGV��һ�յ�λ����Ϣ
	*/
	const unsigned short UpdateEndLocation(const unsigned short usLocation);

	/*!
	 * @brief ����AGV�쳣״̬��Ϣ
	 * @date 2019-08-30
	 * @param char AGV���ص��쳣״̬��Ϣ
	*/
	void UpdateError(const char chError);
#pragma endregion

#pragma region Get AGV Attribute
public:
	// ��ȡAGV���Ժ���

	/*!
	 * @brief ��ȡAGV�����Ϣ
	 * @date 2019-08-30
	 * @return unsigned short AGV�����Ϣ
	*/
	const unsigned short GetNo() const;

	/*!
	 * @brief ��ȡAGV������Ϣ
	 * @date 2019-08-30
	 * @return AGVType AGV������Ϣ
	*/
	AGVType GetType() const;

	/*!
	 * @brief ��ȡAGV��ǰλ����Ϣ
	 * @date 2019-08-30
	 * @return unsigned short AGV��ǰλ����Ϣ
	*/
	const unsigned short GetCurLocation() const;

	/*!
	 * @brief ��ȡAGV��ǰ�ٶ���Ϣ
	 * @date 2019-08-30
	 * @return char AGV��ǰ�ٶ���Ϣ
	*/
	const char GetSpeed() const;

	/*!
	 * @brief ��ȡAGV��ǰʣ�������Ϣ
	 * @date 2019-08-30
	 * @return unsigned char AGV��ǰʣ�������Ϣ
	*/
	const unsigned char GetBattery() const;

	/*!
	 * @brief ��ȡAGV��ǰ����״̬��Ϣ
	 * @date 2019-08-30
	 * @return unsigned short AGV��ǰ������״̬��Ϣ
	*/
	const unsigned char GetStatus() const;

	/*!
	 * @brief ��ȡAGV��ǰ�쳣��Ϣ
	 * @date 2019-08-30
	 * @return char AGV��ǰ���쳣��Ϣ
	*/
	const char GetError() const;

	/*!
	 * @brief ��ȡAGV��ǰ���ػ�����
	 * @date 2019-08-30
	 * @return unsigned char AGV��ǰ���ػ�����
	*/
	const unsigned char GetCargo() const;

	/*!
	 * @brief ��ȡAGV��ǰ�յ�λ����Ϣ
	 * @date 2019-08-30
	 * @return unsigned short AGV��ǰ�յ�λ����Ϣ
	*/
	const unsigned short GetEndLocation() const;

	/*!
	 * @brief ��ȡAGV��е�۶�����
	 * @date 2019-08-30
	 * @param unsigned char AGV��е�۶������
	 * @return string ��е�۶�����
	*/
	string GetArmActionName(const unsigned char byAction);

	/*!
	 * @brief ��ȡAGV��һλ����Ϣ
	 * @date 2019-08-30
	 * @return unsigned short AGV��һλ����Ϣ
	*/
	const unsigned short GetOldLocation() const;

	/*!
	 * @brief ��ȡAGV��һ�յ�λ����Ϣ
	 * @date 2019-08-30
	 * @return unsigned short AGV��һ�յ�λ����Ϣ
	*/
	const unsigned short GetOldEndLocation() const;

	/*!
	 * @brief ��ȡAGV�����˵�ǰ״̬��Ϣ
	 * @date 2019-08-30
	 * @return unsigned char AGV�����˵�ǰ״̬��Ϣ
	*/
	const unsigned char GetLifter() const;

	/*!
	 * @brief ��ȡAGV��Ͳ��ǰ״̬��Ϣ
	 * @date 2019-08-30
	 * @return unsigned char AGV��Ͳ��ǰ״̬��Ϣ
	*/
	const unsigned char GetRoller() const;

	/*!
	 * @brief ��ȡAGV��е�۵�ǰִ�еĶ�����Ϣ
	 * @date 2019-08-30
	 * @return unsigned short AGV��е�۵�ǰִ�еĶ�����Ϣ 
	*/
	const unsigned short GetArmAction() const;

	/*!
	 * @brief ��ȡAGV��е�۵�ǰִ�ж�����״̬��Ϣ
	 * @date 2019-08-30
	 * @return unsigned char AGV��е�۵�ǰִ�ж�����״̬��Ϣ
	*/
	const unsigned char GetArmStatus() const;
#pragma endregion

#pragma region Set AGV Attribute
public:
	// �޸�AGV���Ժ���

	/*!
	 * @brief �޸�AGV�쳣״̬��Ϣ
	 *
	 * UpdateError�������Խ���AGV�ϴ��ص��쳣״̬��Ϣ�����޸��쳣״̬��Ϣ
	 * SetError����������λ�������޸��쳣״̬��Ϣ
	 * @param char �쳣״̬��Ϣ
	*/
	void SetError(const char chError);
#pragma endregion
};

#endif // !_AGV_BASE_H