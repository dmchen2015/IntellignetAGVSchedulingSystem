/*!
 * @file AString.h
 * @brief ����ϵͳ���Զ�����ַ����ļ���ʽ
 * @date 2019-09-09
 * @author FanKaiyu
 * @version 1.0
*/
#pragma once
#include <string>
#include <Windows.h>
#include "../IntellignetAGVSchedulingSystem/Include/json/json.h"

using namespace std;

#define Encode_ACSII "ACSII"
#define Encode_UTF8 "utf-8"
#define Encode_UNICODE "UNICODE"

/*!
 * @class AString
 * @brief ��wstring����������䣬���䳣�õĹ����Լ�����
*/
class AString:
	public wstring
{
public:
	AString();
	AString(const char*, const char* encode = Encode_ACSII);
	AString(const wchar_t*);
	AString(const string&, const char* encode = Encode_ACSII);
	AString(const wstring&);
	~AString();

public:
	/*!
	 * @brief ���ACSII��ʽ���ַ���
	 * @date 2019-09-09
	*/
	string toACSII() const;

	/*!
	 * @breif ���UTF-8��ʽ���ַ���
	 * @date 2019-09-09
	*/
	string toUTF_8() const;

	/*!
	 * @brief ���UNICODE��ʽ���ַ���
	 * @date 2019-09-09
	*/
	wstring toUNICODE() const;
	
	/*!
	 * @brief ����ַ���
	 * @date 2019-09-09
	 * @param string& Ҫ��ӵ��ַ���
	 * @param const char* �����ʽ
	*/
	AString& append(const string& _Right, const char* encode = Encode_ACSII);

	/*!
	 * @brief ��ӡ������̨
	 * @date 2019-09-09
	*/
	void toDebug();

	/*!
	 * @brief д�����ļ�
	 * @date 2019-09-09
	 * @param AString �ļ�Ŀ¼
	 * @return bool д��ɹ�����true,���򷵻�false
	*/
	bool toFile(const AString);

	/*!
	 * @brief ���ļ��ж�ȡ����
	 * @date 2019-09-09
	 * @param AStrig �ļ�Ŀ¼
	 * @return bool ��ȡ�ɹ�����true,���򷵻�false
	*/
	bool FromFile(const AString);

	/*!
	 * @brief ��ʽ���ַ���
	 * @date 2019-09-09
	 * @param const char* �ַ�����ʽ����ʽ
	 * @param ...	��Ҫ��ʽ���Ĳ���
	*/
	AString& Format(const char* format,...);
	AString& Format(const wchar_t* format, ...);

	/*!
	 * @brief ת��ΪJSON����
	 * @date 2019-09-09
	 * @return Json::Value ����JSON����
	*/
	Json::Value toJson() const;

	/*!
	 * @brief ת��ΪLPCTSTR�ַ���
	 * @date 2019-09-09
	*/
	LPCTSTR toLPCTSTR() const;
};

