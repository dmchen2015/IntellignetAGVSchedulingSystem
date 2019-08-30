/*!
 * @file AGVEnum
 * @brief ����AGV״̬���쳣�ȳ������ļ�
 * @author FanKaiyu
 * @date 2019-08-29
 * @version 1.0
*/
#pragma once

/*!
 * @brief ����AGV�ػ�������ö��
 * @date 2019-08-29
 */
enum AGVCargo
{
	// ����
	None,

	// ����
	Full = 0xFF,
};

/*!
 * @brief ����AGV�쳣״̬��ö��
 *
 * �쳣ֵ����0��ΪAGV�Լ���쳣
 * �쳣ֵ����0��Ϊ��λ�������쳣
 * @date 2019-08-29
 * @update 2019-08-30 FanKaiyu ����AGV�쳣״̬�����˵��
 */
enum AGVError
{
	// ���쳣
	None,

	// �������쳣,�޷�����������ɵ��쳣
	Linkbreak = -1,

	// �����˳�ʱ��δ����λ��δ����������쳣
	LifterError = -2,

	// ��Ͳ��������ʱ��δ�ӵ������δ������ж��������쳣
	RollerError = -3,

	// ��е�۶�����ʱ��δִ�����������쳣
	ArmError = -4,

	// ��ʱ���޷��ҵ��������Ѵ��쳣
	Miss = 1,

	// ����ײ�����AGVֹͣ,��Ҫ��λ����
	Crash,

	// ����·���ϵ�����,�޷������ƶ�
	Obs,
};

/*!
 * @brief ����AGV����״̬��ö��
 * @date 2019-08-29
 */
enum AGVStatus
{
	// ����
	Wait,

	// ֹͣ
	Stop,

	// ����
	Run,

	// ��ͣ
	Scream,

	// Ѱ��
	Find,

	// �ǽӴ����ϼ���
	ObsDown,

	// ��ͨ����ֹͣ
	Traffic,

	// ���� 2019-08-30
	Sleep,
};

/*!
 * @brief ����AGV������״̬��ö��
 * @date 2019-08-29
 */
enum AGVLifter
{
	// ����
	Down,
	// ������
	GoingDown,
	// ������
	GoingUp,
	// ����
	Up,
};

/*!
 * @brief ����AGV��Ͳ״̬��ö��
 * @date 2019-08-30
*/
enum AGVRoller
{
	// ֹͣ
	Stop,
	// ��ת��
	Positive,
	// ��ת��
	Negative,
};

/*!
 * @brief ����AGV��е��״̬��ö��
 * @date 2019-08-30
*/
enum AGVArmStatus
{
	// δִ��
	None,
	// ִ����
	Execute,
	// ���
	Done,
};


/*!
 * @brief ����AGV�������������½���ֹͣ�ı�ʶö��
 * @date 2019-08-30
*/
enum AGVLifterControl
{
	// ֹͣ
	Stop,
	// ������ʼ
	Up,
	// �½���ʼ
	Down,
};

/*!
 * @brief ����AGV��Ͳ��ת����ת��ֹͣ�ı�ʶö��
 * @date 2019-08-30
*/
enum AGVRollerControl
{
	// ֹͣ
	Stop,
	// ��ת��ʼ
	Positive,
	// ��ת��ʼ
	Negative,
};