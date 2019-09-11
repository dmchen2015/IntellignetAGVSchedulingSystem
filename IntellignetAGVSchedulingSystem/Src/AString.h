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
#include "../Include/json/json.h"

using namespace std;

#define Encode_ACSII "ACSII"
#define Encode_UTF8 "utf-8"
#define Encode_UNICODE "UNICODE"

/*!
 * @class AString
 * @brief ��wstring����������䣬���䳣�õĹ����Լ�����
 * @date 2019-09-09
 * @author FanKaiyu
*/
class AString
{
public:
	AString();
	AString(const char*, const char* encode = Encode_ACSII);
	AString(const wchar_t*);
	AString(const string&, const char* encode = Encode_ACSII);
	AString(const wstring&);
	~AString();

private:
	wstring m_wstr;

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
	AString& append(const wstring& _Right);
	AString& append(const AString& _Right);

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

	/*��
	 * @brief  д�����ļ���־
	 * @date 2019-09-09
	 * @param AString �ļ�Ŀ¼
	 * @return bool д��ɹ�����true,���򷵻�false
	*/
	bool toLogFile(const AString);

	/*!
	 * @brief ���ļ��ж�ȡ����
	 * @date 2019-09-09
	 * @param AStrig �ļ�Ŀ¼
	 * @param const char* �����ʽ
	 * @return AString ��ȡ�ɹ����ض�ȡ���ַ��������򷵻ؿ��ַ���
	*/
	AString& FromFile(const AString, const char* encode = Encode_UTF8);

	/*!
	 * @brief ��ʽ���ַ���
	 * @date 2019-09-09
	 * @param const char* �ַ�����ʽ����ʽ
	 * @param va_list argv	��Ҫ��ʽ���Ĳ���
	*/
	AString& Format(const char* format, ...);
	AString& Format(const wchar_t* format, ...);

	/*!
	 * @brief ת��ΪJSON����
	 * @date 2019-09-09
	 * @return Json::Value ����JSON����
	*/
	Json::Value toJson() const;

	/*!
	 * @brief ����ַ���
	 * @date 2019-09-11
	*/
	void Clear();

	/*!
	 * @brief �ַ����Ƿ�Ϊ��
	 * @date 2019-09-11
	 * @return Ϊ�շ���true,���򷵻�false
	*/
	bool Empty();

	/*!
	 * @brief ��ȡ�ַ���
	 * @date 2019-09-11
	*/
	wstring& Str();

	/*!
	 * @brief ���ز�����
	 * @date 2019-09-11
	*/
	bool operator==(const string& _Right);
	bool operator==(const wstring& _Right);
	bool operator==(const AString& _Right);
	bool operator>(const string& _Right);
	bool operator>(const wstring& _Right);
	bool operator>(const AString& _Right);
	bool operator<(const string& _Right);
	bool operator<(const wstring& _Right);
	bool operator<(const AString& _Right);
	bool operator!=(const string& _Right);
	bool operator!=(const wstring& _Right);
	bool operator!=(const AString& _Right);
	bool operator>=(const string& _Right);
	bool operator>=(const wstring& _Right);
	bool operator>=(const AString& _Right);
	bool operator<=(const string& _Right);
	bool operator<=(const wstring& _Right);
	bool operator<=(const AString& _Right);
	ostream& operator<<(ostream& _Ostr);
	wostream& operator<<(wostream& _Ostr);
	wistream& operator>>(wistream& _Istr);
	istream& operator>>(istream& _Istr);
	operator bool();
	bool operator==(const bool& _Right);
};

