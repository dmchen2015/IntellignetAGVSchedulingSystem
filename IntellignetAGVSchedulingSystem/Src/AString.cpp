#include "AString.h"
#include <sstream>
#include <codecvt>
#include <cstdarg>
#include <fstream>
#include <chrono>

using namespace chrono;


using WCHAR_GBK		= codecvt_byname<wchar_t, char, mbstate_t>;
using WCHAR_UTF8	= codecvt_utf8<wchar_t>;

// linux��Ϊ"zh_CN.GBK"
#define GBK_NAME ".936"


AString::AString()
{
	m_wstr = L"";
}

AString::AString(const char* _str,const char* encode)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	// utf8��unicode֮���ת����
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		// ��gbkת��Ϊunicode
		m_wstr = cvtGBK.from_bytes(_str).c_str();
	}
	else if (encode == Encode_UTF8)
	{
		// ��utf8ת��Ϊunicode
		m_wstr = cvtUTF8.from_bytes(_str).c_str();
	}
}

AString::AString(const wchar_t* _wstr)
{
	m_wstr = _wstr;
}

AString::AString(const string& _str, const char* encode)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	// utf8��unicode֮���ת����
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		// ��gbkת��Ϊunicode
		m_wstr = cvtGBK.from_bytes(_str).c_str();
	}
	else if (encode == Encode_UTF8)
	{
		// ��utf8ת��Ϊunicode
		m_wstr = cvtUTF8.from_bytes(_str).c_str();
	}
}

AString::AString(const wstring& _wstr)
{
	m_wstr = _wstr;
}

AString::~AString()
{
	m_wstr.clear();
}

string AString::toACSII() const
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	// ��unicodeת��Ϊgbk
	return cvtGBK.to_bytes(m_wstr.c_str()).c_str();
}

string AString::toUTF_8() const
{
	// utf8��֮���ת����
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	// ��unicodeת��Ϊutf8
	return cvtUTF8.to_bytes(m_wstr.c_str()).c_str();
}

wstring AString::toUNICODE() const
{
	return m_wstr.c_str();
}

AString& AString::append(const string& _Right, const char* encode)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	// utf8��unicode֮���ת����
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		// ��gbkת��Ϊunicode
		m_wstr.append(cvtGBK.from_bytes(_Right).c_str());
	}
	else if (encode == Encode_UTF8)
	{
		// ��utf8ת��Ϊunicode
		m_wstr.append(cvtUTF8.from_bytes(_Right).c_str());
	}

	return *this;
}

AString& AString::append(const wstring& _Right)
{
	m_wstr.append(_Right);

	return *this;
}

AString& AString::append(const AString& _Right)
{
	m_wstr.append(_Right.m_wstr);

	return *this;
}

void AString::toDebug()
{
	// �������ǰʱ��
	auto start = system_clock::now();
	// ת��ΪCʱ��
	std::time_t cur_time = system_clock::to_time_t(start);
	
	// ʱ���ַ���
	char cTimeArr[1024];
	// ��ʽ��ʱ��
	ctime_s(cTimeArr, 1024, &cur_time);
	// �ı��ַ���
	AString str = "";
	// ��ʽ���ı�
	str.Format("%s[Debug] %lld %s\n", cTimeArr, duration_cast<milliseconds>(start.time_since_epoch()).count()%1000,toACSII().c_str());

	// ����������
#ifdef _UNICODE
	OutputDebugString(str.m_wstr.c_str());
#else
	OutputDebugString(str.toACSII().c_str());
#endif

	// ��ӡ�ı�
	printf(str.toACSII().c_str());

	return;
}

bool AString::toFile(const AString _file)
{
	// �ļ������
	ofstream file;

	// ���ļ�
	file.open(_file.toACSII().c_str());

	// �ļ���ʧ��
	if (file.fail())
	{
		// open file failed
		throw("Write to file error:Open file failed!");
		return false;
	}

	// д���ļ�
	file << this->toACSII();

	// �ر��ļ�
	file.close();

	return true;
}

bool AString::toLogFile(const AString _file)
{
	// �ļ������
	ofstream file;

	// ���ļ�
	file.open(_file.toACSII().c_str());

	// �ļ���ʧ��
	if (file.fail())
	{
		// open file failed
		throw("Write to file error:Open file failed!");
		return false;
	}

	// �������ǰʱ��
	auto start = system_clock::now();
	// ת��ΪCʱ��
	std::time_t cur_time = system_clock::to_time_t(start);

	// ʱ���ַ���
	char cTimeArr[1024];
	// ��ʽ��ʱ��
	ctime_s(cTimeArr, 1024, &cur_time);
	// �ı��ַ���
	AString str = "";
	// ��ʽ���ı�
	str.Format("%s[Log] %s\n", cTimeArr, toACSII().c_str());

	// д���ļ�
	file << str.toACSII();

	// �ر��ļ�
	file.close();

	// ����������
#ifdef _UNICODE
	OutputDebugString(str.m_wstr.c_str());
#else
	OutputDebugString(str.toACSII().c_str());
#endif

	// ��ӡ�ı�
	printf(str.toACSII().c_str());

	return true;
}

AString& AString::FromFile(const AString _file, const char* encode)
{
	// �ļ�������
	ifstream file;
	// ���ļ�
	file.open(_file.toACSII().c_str());

	// �ļ���ʧ��
	if (file.fail())
	{
		// open file failed
		throw("Read from file error:Open file failed!");
		m_wstr = L"";
		return *this;
	}

	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	// utf8��unicode֮���ת����
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		// �ַ��������
		ostringstream ostring;
		// ��ȡ�ļ�
		ostring << file.rdbuf();

		// ��gbkת��Ϊunicode
		m_wstr = cvtGBK.from_bytes(ostring.str().c_str()).c_str();
	}
	else if (encode == Encode_UTF8)
	{
		// �ַ��������
		ostringstream ostring;
		// ��ȡ�ļ�
		ostring << file.rdbuf();

		// ��utf8ת��Ϊunicode
		m_wstr = cvtUTF8.from_bytes(ostring.str().c_str()).c_str();
	}
	else
	{
		// ���ַ��������
		wostringstream wostring;
		// ��ȡ�ļ�
		wostring << file.rdbuf();

		m_wstr = wostring.str().c_str();
	}

	// �ر��ļ�
	file.close();

	return *this;
}


Json::Value AString::toJson() const
{
	Json::CharReaderBuilder builder;
	Json::CharReader* JsonReader(builder.newCharReader());
	Json::Value JsonRoot;

	JSONCPP_STRING errs;
	string str = toACSII();
	const char* pstr = str.c_str();

	if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
	{
		// read json string failed
		throw("Loading arm action name error:" + errs);
  		return Json::Value();
	}

	delete JsonReader;

	return JsonRoot;
}

void AString::Clear()
{
	m_wstr.clear();
}

bool AString::Empty()
{
	return m_wstr.empty();;
}

wstring& AString::Str()
{
	return m_wstr;
}

bool AString::operator==(const string& _Right)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	// ��gbkת��Ϊunicode
	return m_wstr == cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator==(const wstring& _Right)
{
	return m_wstr== _Right;
}

bool AString::operator==(const AString& _Right)
{
	return m_wstr == _Right.m_wstr;
}

bool AString::operator>(const string& _Right)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	// ��gbkת��Ϊunicode
	return m_wstr > cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator>(const wstring& _Right)
{
	return m_wstr > _Right;
}

bool AString::operator>(const AString& _Right)
{
	return m_wstr > _Right.m_wstr;
}

bool AString::operator<(const string& _Right)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));

	// ��gbkת��Ϊunicode
	return m_wstr < cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator<(const wstring& _Right)
{
	return m_wstr < _Right;
}

bool AString::operator<(const AString& _Right)
{
	return m_wstr < _Right.m_wstr;
}

bool AString::operator!=(const string& _Right)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));

	// ��gbkת��Ϊunicode
	return m_wstr != cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator!=(const wstring& _Right)
{
	return m_wstr != _Right;
}

bool AString::operator!=(const AString& _Right)
{
	return m_wstr!= _Right.m_wstr;
}

bool AString::operator>=(const string& _Right)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));

	// ��gbkת��Ϊunicode
	return m_wstr >= cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator>=(const wstring& _Right)
{
	return m_wstr >= _Right;
}

bool AString::operator>=(const AString& _Right)
{
	return m_wstr >= _Right.m_wstr;
}

bool AString::operator<=(const string& _Right)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));

	// ��gbkת��Ϊunicode
	return m_wstr <= cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator<=(const wstring& _Right)
{
	return m_wstr <= _Right;
}

bool AString::operator<=(const AString& _Right)
{
	return m_wstr <= _Right.m_wstr;
}

ostream& AString::operator<<(ostream& _Ostr)
{
	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	return _Ostr << cvtGBK.to_bytes(m_wstr.c_str());
}

wostream& AString::operator<<(wostream& _Ostr)
{
	return _Ostr << m_wstr;
}

wistream& AString::operator>>(wistream& _Istr)
{
	return _STD move(_Istr) >> m_wstr;
}

istream& AString::operator>>(istream& _Istr)
{
	string str;
	_STD move(_Istr) >> str;

	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	m_wstr = cvtGBK.from_bytes(str).c_str();

	return _Istr;
}

AString::operator bool()
{
	// ����ַ�����Ϊ����ת��Ϊtrue,����Ϊfalse
	return !m_wstr.empty();
}

bool AString::operator==(const bool& _Right)
{
	// ����ַ�����Ϊ����ת��Ϊtrue,����Ϊfalse
	return (!m_wstr.empty()) == _Right;
}

AString& AString::Format(const char* format, ...)
{
	m_wstr = L"";

	int old_size = strlen(format);
	
	va_list ap;

	va_start(ap, format);
	int new_size = _vscprintf(format, ap);
	if (new_size < 0)
	{
		return *this;
	}

	std::unique_ptr<char[]> buf(new char[new_size+1]);
	new_size = vsnprintf(buf.get(), new_size + 1, format, ap);
	va_end(ap);
	if (new_size < 0)
	{
		return *this;
	}

	// gbk��unicode֮���ת����
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	m_wstr = cvtGBK.from_bytes(std::string(buf.get()).c_str());

	return *this;
}

 AString& AString::Format(const wchar_t* format, ...)
{
	 m_wstr = L"";

	 va_list ap;

	 va_start(ap, format);
	 int new_size = _vscwprintf(format, ap);
	 if (new_size < 0)
	 {
		 return *this;
	 }

	 std::unique_ptr<wchar_t[]> buf(new wchar_t[new_size+1]);
	 new_size = _vsnwprintf_s(buf.get(), new_size + 1, new_size + 1,format, ap);
	 va_end(ap);
	 if (new_size < 0)
	 {
		 return *this;
	 }

	 m_wstr = buf.get();

	 return *this;
}
