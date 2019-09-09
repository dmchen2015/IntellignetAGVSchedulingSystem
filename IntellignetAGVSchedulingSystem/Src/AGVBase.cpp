#include "AGVBase.h"
#include "../Include/json/json.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <codecvt>

#ifdef _AGV_BASE_H

using WCHAR_GBK		= codecvt_byname<wchar_t, char, mbstate_t>;
using WCHAR_UTF8	= codecvt_utf8<wchar_t>;

// linux��Ϊ"zh_CN.GBK"
#define GBK_NAME ".936"

AGVBase::AGVBase()
{
	/*!
	 * @brief ��ʼ��AGV���Ա���
	 * @date 2019-08-30
	*/
	for (unsigned char i = 0; i < 0xFF; ++i)
	{
		m_strActNameArr[i] = "";
	}

	InitializeAttribut(0, AGVType());
}


AGVBase::~AGVBase()
{
}

AGVBase::AGVBase(const unsigned short usNo, const AGVType & Type)
{
	/*!
	 * @brief ��ʼ��AGV���Ա���
	 * @date 2019-08-30
	*/
	for (unsigned char i = 0; i < 0xFF; ++i)
	{
		m_strActNameArr[i] = "";
	}

	InitializeAttribut(usNo, Type);
}

AGVBase::AGVBase(const unsigned short usNo, const AGVType & Type, const unsigned short usCurLocation, const unsigned short usEndLocation)
{
	/*!
	 * @brief ��ʼ��AGV���Ա���
	 * @date 2019-08-30
	*/
	for (unsigned char i = 0; i < 0xFF; ++i)
	{
		m_strActNameArr[i] = "";
	}

	InitializeAttribut(usNo, Type, usCurLocation, usEndLocation);
}

void AGVBase::InitializeAttribut(const unsigned short usNo, const AGVType & Type)
{
	/*!
	 * @brief ��ʼ��AGV���Ա���
	 * @date 2019-08-30
	*/
	m_usNo = usNo;
	m_Type = Type;

	m_usCurLocation = 0;
	m_usEndLocation = 0;
	m_usOldLocation = 0;
	m_usEndLocation = 0;
	m_chCurSpeed = 0;
	m_byBattery = 0;
	m_byLifter = AGVLifter::Lifter_Down;
	m_byRoller = AGVRoller::Roller_Stop;
	m_usArmAction = 0;
	m_byArmStatus = AGVArmStatus::Arm_Status_None;
	m_byStatus = AGVStatus::Status_Wait;
	m_byCargo = AGVCargo::Cargo_None;
	m_chError = AGVError::Error_None;
	m_byMode = AGVMode::Mode_Offline;

	return;
}

void AGVBase::InitializeAttribut(const unsigned short usNo, const AGVType & Type, const unsigned short usCurLocation, const unsigned short usEndLocation)
{
	/*!
	 * @brief ��ʼ��AGV���Ա���
	 * @date 2019-08-30
	*/
	InitializeAttribut(usNo, Type);

	m_usCurLocation = usCurLocation;
	m_usEndLocation = usEndLocation;

	return;
}

void AGVBase::LoadActNameFile(string strPath)
{
	/*!
	 * @brief ��ȡ�����ļ��л�е�۶���������
	 * Ĭ���ļ�λ��Ϊ./Config/Arm.json
	 * @date 2019-09-02
	*/

	ifstream fin;
	fin.open(strPath);
	if (!fin)
	{
		// open file failed
		throw("Loading arm action name error:Open arm config file failed!");
		return;
	}

	ostringstream ostring;
	ostring << fin.rdbuf();
	fin.close();

	string strContext = ostring.str();
	// CharReaderBuilder
	Json::CharReaderBuilder builder;
	Json::CharReader* JsonReader(builder.newCharReader());
	Json::Value JsonRoot;

	JSONCPP_STRING errs;
	const char* pstr = strContext.c_str();

	if (!JsonReader->parse(pstr,pstr+strlen(pstr),&JsonRoot,&errs))
	{
		// read json string failed
		throw("Loading arm action name error:" + errs);
		return;
	}

	// ��е������Json������
	Json::Value ArmArr = JsonRoot["Arm"];

	for (size_t k = 0; k < ArmArr.size(); ++k)
	{
		// ��е������
		Json::Value Arm = ArmArr[k];

		// AGV���
		int no = Json_ReadInt(Arm["No"]);

		// �����AGV��������ȫ��������ʹ�ô�������Ϣ
		if (no != m_usNo && no != 0)
		{
			continue;
		}

		for (int i = 1; i < 0xFF; ++i)
		{
			ostringstream ostrName;
			string strAction = "";

			ostrName << i;

			Json::Value action = Arm.get(ostrName.str(),Json::Value());

			if (action.isNull())
			{
				continue;
			}

			// UTF-8 ת ACSII
			strAction = action.asString();

			if (strAction.empty())
			{
				continue;
			}

			// gbk��unicode֮���ת����
			wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
			// utf8��unicode֮���ת����
			wstring_convert<WCHAR_UTF8> cvtUTF8;
			// ��utf8ת��Ϊunicode
			wstring ustr = cvtUTF8.from_bytes(strAction);
			// ��unicodeת��Ϊgbk
			strAction = cvtGBK.to_bytes(ustr);

			// ����ŵ�ֵ��AGVֵ���ʱ �� ��ŵ�ֵΪȫ�ֱ�ʶʱ ���涯������
			if (no == m_usNo || (no == 0 && m_strActNameArr[i].empty() == false))
			{
				m_strActNameArr[i] = strAction;
			}
		}
	}
	
	delete JsonReader;
	return;
}

void AGVBase::UpdateSpeed(const char chSpeed)
{
	/*!
	 * @brief �Ƚϵ�ǰ��¼��AGV�ٶ���Ϣ��AGV�ϴ����ٶ���Ϣ�Ƿ�һ��
	 * ���һ�����޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_chCurSpeed == chSpeed)
	{
		return;
	}

	/*!
	 * @brief �����һ�����޸ļ�¼����ϢΪAGV�ϴ�����Ϣ
	 * @date 2019-08-30
	*/
	m_chCurSpeed = chSpeed;

	return;
}

void AGVBase::UpdateBattery(const unsigned char byBattery)
{
	/*!
	 * @brief �Ƚϵ�ǰ��¼��AGVʣ�������Ϣ��AGV�ϴ���ʣ�������Ϣ�Ƿ�һ��
	 * ���һ�����޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_byBattery == byBattery)
	{
		return;
	}

	/*!
	 * @breif �����һ�����޸ļ�¼����ϢΪAGV�ϴ�����Ϣ
	 * @date 2019-08-30
	*/
	m_byBattery = byBattery;

	return;
}

void AGVBase::UpdateStatus(const unsigned char byStatus)
{
	/*!
	 * @brief �Ƚϵ�ǰ��¼��AGV����״̬��Ϣ��AGV�ϴ�������״̬��Ϣ�Ƿ�һ��
	 * ���һ�����޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_byStatus == byStatus)
	{
		return;
	}

	/*!
	 * @brief �����һ�����޸ļ�¼����ϢΪAGV�ϴ�����Ϣ
	 * @date 2019-08-30
	*/
	m_byStatus = byStatus;

	return;
}

void AGVBase::UpdateCargo(const unsigned char byCargo)
{
	/*!
	 * @brief �Ƚϵ�ǰ��¼��AGV�ػ�������Ϣ��AGV�ϴ����ػ�������Ϣ�Ƿ�һ��
	 * ���һ�����޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_byCargo == byCargo)
	{
		return;
	}

	/*!
	 * @brief �����һ�����޸ļ�¼����ϢΪAGV�ϴ�����Ϣ
	 * @date 2019-08-30
	*/
	m_byCargo = byCargo;

	return;
}

void AGVBase::UpdateLifter(const unsigned char byLifter)
{
	/*!
	 * @brief �Ƚϵ�ǰ��¼��AGV������״̬��Ϣ��AGV�ϴ��ľ�����״̬��Ϣ�Ƿ�һ��
	 * ���һ�����޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_byLifter == byLifter)
	{
		return;
	}

	/*!
	 * @breif �����һ�����޸ļ�¼����ϢΪAGV�ϴ�����Ϣ
	 * @date 2019-08-30
	*/
	m_byLifter = byLifter;

	return;
}

void AGVBase::UpdateRoller(const unsigned char byRoller)
{
	/*!
	 * @brief �Ƚϵ�ǰ��¼��AGV��Ͳ��Ϣ��AGV�ϴ��Ĺ�Ͳ��Ϣ�Ƿ�һ��
	 * ���һ�����޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_byRoller == byRoller)
	{
		return;
	}

	/*!
	 * @brief �����һ�����޸ļ�¼����ϢΪAGV�ϴ�����Ϣ
	 * @date 2019-08-20
	*/
	m_byRoller = byRoller;

	return;
}

void AGVBase::UpdateArmAction(const unsigned short usAction)
{
	/*!
	 * @brief �Ƚϵ�ǰ��¼�Ļ�е�۶�����Ϣ��AGV�ϴ��Ļ�е�۶�����Ϣ�Ƿ�һ��
	 * ���һ�����޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_usArmAction == usAction)
	{
		return;
	}

	/*!
	 * @brief ���һ�����޸ļ�¼����ϢΪAGV�ϴ�����Ϣ
	 * @date 2019-08-30
	*/
	m_usArmAction = usAction;

	return;
}

void AGVBase::UpdateArmStatus(const unsigned char byStatus)
{
	/*!
	 * @brief �Ƚϼ�¼�Ļ�е�۵�ǰ������״̬��Ϣ��AGV�ϴ��Ļ�е�۵�ǰ������״̬��Ϣ�Ƿ�һ��
	 * ���һ�²��޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_byArmStatus == byStatus)
	{
		return;
	}

	/*!
	 * @brief ���һ���޸ļ�¼����ϢΪAGV�ϴ�����Ϣ
	 * @date 2019-08-30
	*/
	m_byArmStatus = byStatus;

	return;
}

const unsigned short AGVBase::UpdateCurLocation(const unsigned short usLocation)
{
	/*!
	 * @brief �Ƚϼ�¼�ĵ�ǰλ����Ϣ��AGV�ϴ��ĵ�ǰλ����Ϣ�Ƿ�һ��
	 * ���һ�²��޸ļ�¼����Ϣ
	 * ��������һλ����Ϣ
	 * @date 2019-08-30
	*/
	if (m_usCurLocation == usLocation)
	{
		return m_usOldLocation;
	}

	/*!
	 * @brief �����һ�£�
	 * �޸ļ�¼����һλ����ϢΪ��¼�ĵ�ǰλ����Ϣ
	 * �� �޸ļ�¼�ĵ�ǰλ����ϢΪAGV�ϴ�����Ϣ
	 * Ȼ�� ������һλ����Ϣ
	 * @date 2019-08-30
	*/
	m_usOldLocation = m_usCurLocation;
	m_usCurLocation = usLocation;

	return m_usOldLocation;
}

const unsigned short AGVBase::UpdateEndLocation(const unsigned short usLocation)
{
	/*!
	 * @brief �Ƚϼ�¼���յ�λ����Ϣ��AGV�ϴ����յ�λ����Ϣ�Ƿ�һ��
	 * ���һ�²��޸ļ�¼����Ϣ
	 * ��������һ�յ�λ����Ϣ
	 * @date 2019-08-30
	*/
	if (m_usEndLocation == usLocation)
	{
		return m_usOldEndLocation;
	}

	/*!
	 * @brief �����һ�£�
	 * �޸ļ�¼����һ�յ�λ����ϢΪ��¼�ĵ�ǰ�յ�λ����Ϣ
	 * �� �޸ļ�¼���յ�λ����ϢΪAGV�ϴ�����Ϣ
	 * Ȼ�� ������һ�յ�λ����Ϣ
	 * @date 2019-08-30
	*/
	m_usOldEndLocation = m_usEndLocation;
	m_usEndLocation = usLocation;

	return m_usOldEndLocation;
}

void AGVBase::UpdateError(const char chError)
{
	/*!
	 * @brief �Ƚϵ�ǰ��¼���쳣״̬��Ϣ�Ƿ���AGV���ص��쳣״̬��Ϣһ��
	 * ���һ�����޸ļ�¼����Ϣ
	 * @date 2019-08-30 
	*/
	if (m_chError == chError)
	{
		return;
	}

	/*!
	 * @brief �����ǰ��¼���쳣��ϢΪ��λ�������쳣������AGV���ص��쳣״̬��ϢΪ���쳣
	 * ���޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (chError == AGVError::Error_None && m_chError < AGVError::Error_None)
	{
		return;
	}
	
	/*!
	 * @brief �����һ�����޸ļ�¼����ϢΪAGV�ϴ�����Ϣ
	 * @date 2019-08-30
	*/
	m_chError = chError;

	return;
}

const unsigned short AGVBase::GetNo() const
{
	/*!
	 * @brief ����AGV�ı����Ϣ
	 * @date 2019-08-30
	*/
	return m_usNo;
}

AGVType AGVBase::GetType() const
{
	/*!
	 * @brief ����AGV��������Ϣ
	 * @date 2019-08-30
	*/
	return m_Type;
}

const unsigned short AGVBase::GetCurLocation() const
{
	/*!
	 * @brief ����AGV��ǰλ����Ϣ
	 * @date 2019-08-30
	*/
	return m_usCurLocation;
}

const char AGVBase::GetSpeed() const
{
	/*!
	 * @brief ����AGV��ǰ���ٶ���Ϣ
	 * @date 2019-08-30
	*/
	return m_chCurSpeed;
}

const unsigned char AGVBase::GetBattery() const
{
	/*!
	 * @brief ����AGV��ǰ��ʣ�������Ϣ
	 * @date 2019-08-30
	*/
	return m_byBattery;
}

const unsigned char AGVBase::GetStatus() const
{
	/*!
	 * @brief ����AGV��ǰ������״̬
	 * @date 2019-08-30
	*/
	return m_byStatus;
}

const char AGVBase::GetError() const
{
	/*!
	 * @brief ����AGV��ǰ���쳣��Ϣ
	 * @date 2019-08-30
	*/
	return m_chError;
}

const unsigned char AGVBase::GetCargo() const
{
	/*!
	 * @brief ����AGV��ǰ���ػ�����
	 * @date 2019-08-30
	*/
	return m_byCargo;
}

const unsigned short AGVBase::GetEndLocation() const
{
	/*!
	 * @brief ����AGV��ǰ�յ�λ����Ϣ
	 * @date 2019-08-30
	*/
	return m_usEndLocation;
}

string AGVBase::GetArmActionName(const unsigned char byAction)
{
	/*!
	 * @brief ����AGV��е�۶�����
	 * @date 2019-08-30
	*/
	return m_strActNameArr[byAction];
}

const unsigned short AGVBase::GetOldLocation() const
{
	/*!
	 * @brief ����AGV��һλ����Ϣ
	 * @date 2019-08-30
	*/
	return m_usOldLocation;
}

const unsigned short AGVBase::GetOldEndLocation() const
{
	/*!
	 * @brief ����AGV��һ�յ�λ����Ϣ
	 * @date 2019-08-30
	*/
	return m_usOldEndLocation;
}

const unsigned char AGVBase::GetLifter() const
{
	/*!
	 * @brief ����AGV�����˵�ǰ��״̬��Ϣ
	 * @date 2019-08-30
	*/
	return m_byLifter;
}

const unsigned char AGVBase::GetRoller() const
{
	/*!
	 * @brief ����AGV��Ͳ��ǰ��״̬��Ϣ
	 * @date 2019-08-30
	*/
	return m_byRoller;
}

const unsigned short AGVBase::GetArmAction() const
{
	/*!
	 * @brief ����AGV��е�۵�ǰִ�еĶ�����Ϣ
	 * @date 2019-08-30
	*/
	return m_usArmAction;
}

const unsigned char AGVBase::GetArmStatus() const
{
	/*!
	 * @brief ����AGV��е�۵�ǰִ�ж�����״̬��Ϣ
	 * @date 2019-08-30
	*/
	return m_byArmStatus;
}

void AGVBase::SetError(const char chError)
{
	/*!
	 * @brief �Ƚϵ�ǰ��¼���쳣״̬��Ϣ�Ƿ���ָ�����쳣״̬��Ϣһ��
	 * ���һ�����޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_chError == chError)
	{
		return;
	}

	/*!
	 * @brief �����ǰ��¼���쳣��ϢΪAGV�ϴ��ص��쳣��Ϣ
	 * ���޸ļ�¼����Ϣ
	 * @date 2019-08-30
	*/
	if (m_chError > AGVError::Error_None)
	{
		return;
	}

	/*!
	 * @brief �����һ�����޸ļ�¼����ϢΪָ������Ϣ
	 * @date 2019-08-30
	*/
	m_chError = chError;

	return;
}
#endif // _AGV_BASE_H