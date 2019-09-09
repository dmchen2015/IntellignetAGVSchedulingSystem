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
	Cargo_None,

	// ����
	Cargo_Full = 0xFF,
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
	Error_None,

	// �������쳣,�޷�����������ɵ��쳣
	Error_Linkbreak = -1,

	// �����˳�ʱ��δ����λ��δ����������쳣
	Error_LifterError = -2,

	// ��Ͳ��������ʱ��δ�ӵ������δ������ж��������쳣
	Error_RollerError = -3,

	// ��е�۶�����ʱ��δִ�����������쳣
	Error_ArmError = -4,

	// ��ʱ���޷��ҵ��������Ѵ��쳣
	Error_Miss = 1,

	// ����ײ�����AGVֹͣ,��Ҫ��λ����
	Error_Crash,

	// ����·���ϵ�����,�޷������ƶ�
	Error_Obs,
};

/*!
 * @brief ����AGV����״̬��ö��
 * @date 2019-08-29
 */
enum AGVStatus
{
	// ����
	Status_Wait,

	// ����
	Status_Run,

	// ֹͣ
	Status_Stop,

	// ��ͣ
	Status_Scream,

	// Ѱ��
	Status_Find,

	// �ǽӴ����ϼ���
	Status_ObsDown,

	// ��ͨ����ֹͣ
	Status_Traffic,

	// ���� 2019-08-30
	Status_Sleep,

	// ����� 2019-09-03
	Status_Charging,

	// Զ�̼�ͣ 2019-09-03
	Status_RemoteScream,

	// ȫ�߼�ͣ 2019-09-03
	Status_AllScream,

	// ���� 2019-09-03
	Status_SpeedUp,

	// ���� 2019-09-03
	Status_SpeedDown,

	// ��ͣ 2019-09-03
	Status_Pause,
};

/*!
 * @brief ����AGV������״̬��ö��
 * @date 2019-08-29
 */
enum AGVLifter
{
	// ����
	Lifter_Down,
	// ������
	Lifter_GoingDown,
	// ������
	Lifter_GoingUp,
	// ����
	Lifter_Up,
};

/*!
 * @brief ����AGV��Ͳ״̬��ö��
 * @date 2019-08-30
*/
enum AGVRoller
{
	// ֹͣ
	Roller_Stop,
	// ��ת��
	Roller_Positive,
	// ��ת��
	Roller_Negative,
};

/*!
 * @brief ����AGV��е��״̬��ö��
 * @date 2019-08-30
*/
enum AGVArmStatus
{
	// δִ��
	Arm_Status_None,
	// ִ����
	Arm_Status_Execute,
	// ���
	Arm_Status_Done,
};


/*!
 * @brief ����AGV�������������½���ֹͣ�ı�ʶö��
 * @date 2019-08-30
*/
enum AGVLifterControl
{
	// ֹͣ
	Lifter_Ctrl_Stop,
	// ������ʼ
	Lifter_Ctrl_Up,
	// �½���ʼ
	Lifter_Ctrl_Down,
};

/*!
 * @brief ����AGV��Ͳ��ת����ת��ֹͣ�ı�ʶö��
 * @date 2019-08-30
*/
enum AGVRollerControl
{
	// ֹͣ
	Roller_Ctrl_Stop,
	// ��ת��ʼ
	Roller_Ctrl_Positive,
	// ��ת��ʼ
	Roller_Ctrl_Negative,
};

/*!
 * @brief ����AGVģʽ�ı�ʶö��
 * @date 2019-09-03
*/
enum AGVMode
{
	// ����
	Mode_Offline,
	// ����
	Mode_Online,
};