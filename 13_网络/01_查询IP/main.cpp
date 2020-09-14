#include <stdio.h>
#include <Windows.h>
#include <Wininet.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#pragma comment(lib, "Wininet.lib")

#define URL_SELF "http://202020.ip138.com/"
//#define URL L"https://www.ip138.com/iplookup.asp?ip=86.188.86.114&action=2"
#define URL L"https://www.ip138.com/iplookup.asp?ip=114.86.188.86&action=2"
#define URL_BEG "https://www.ip138.com/iplookup.asp?ip="
#define URL_END "&action=2"
//#define USER_AGENT L"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET4.0C; .NET4.0E; .NET CLR 2.0.50727)"
#define USER_AGENT "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3100.0 Safari/537.36"

string Utf8ToGbk(const char* src_str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

size_t findPos(const std::string& src, std::string& buf, const std::string& key, size_t keyId)
{
	if (!keyId)
		return std::string::npos;

	std::string head = "div";
	std::ostringstream os;
	os << "<" << head << " class=\"" << key << "\">";
	std::string tmpKey = os.str();

	size_t tmpPos = 0;
	bool first = false;
	for (size_t i = 0; i < keyId; ++i)
	{
		size_t keyOffset = 0;
		if (first) first = false;
		else keyOffset = tmpKey.size();

		tmpPos = src.find(tmpKey, tmpPos + keyOffset);
		if (std::string::npos == tmpPos)
			return std::string::npos;

	}

	size_t tmpEnd = tmpPos, endCnt = 0;
	while (std::string::npos != tmpEnd)
	{
		tmpEnd = src.find(head, tmpEnd + head.size());
		if (std::string::npos == tmpEnd)
			return std::string::npos;

		if ('/' == src[tmpEnd - 1])
		{
			if (0 == endCnt)
				break;

			--endCnt;
			continue;
		}

		++endCnt;
	}

	buf = src.substr(tmpPos, tmpEnd + head.size() + 1 - tmpPos);
	return tmpPos;
}

bool findContext(const std::string& src, std::string& buf, std::initializer_list<std::string> il)
{
	std::string tmpSrc;
	for (const std::string& key : il)
	{
		std::string keyName = key.substr(0, key.find('\\'));
		size_t keyIdx = atoi(key.substr(key.find('\\') + 1).c_str());
		if (!keyIdx)
			keyIdx = 1;

		if (std::string::npos == findPos(src, tmpSrc, keyName, keyIdx))
			return false;
	}

	buf = tmpSrc;
	return true;
}

void printASN(const std::string& buf)
{
	size_t findASN = buf.find("\"ASN归属地\"");
	if (std::string::npos == findASN)
	{
		std::cout << std::endl;
		return;
	}
	size_t findASNEnd = buf.find(",", findASN);
	if (std::string::npos == findASNEnd)
	{
		std::cout << std::endl;
		return;
	}
	cout << buf.substr(findASN, findASNEnd - findASN) << endl;
}

bool openUrl(const char* url, size_t witch)
{
	HINTERNET hInternet, hInternetUrl;
	hInternet = InternetOpenA(USER_AGENT, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	if (!hInternet) {
		wprintf(L"InternetOpen error: %d\n", GetLastError());
		return false;
	}
	hInternetUrl = InternetOpenUrlA(hInternet, url, NULL, 0, INTERNET_FLAG_HYPERLINK, NULL);
	if (!hInternetUrl) {
		wprintf(L"InternetOpenUrl error: %d\n", GetLastError());
		InternetCloseHandle(hInternet);
		return false;
	}

	size_t num = 1024 * 1024;
	char* buffer = new char[num];
	memset(buffer, 0, num);
	DWORD dwBytesRead = 0;
	BOOL bRead = ::InternetReadFile(hInternetUrl, buffer, num, &dwBytesRead);
	//cout << Utf8ToGbk(buffer) << endl;
	//cout << buffer << endl;
	//string bufStr = Utf8ToGbk(buffer);
	string bufStr = buffer;

	switch (witch)
	{
	case 0:
		{
			std::string bufStr = Utf8ToGbk(buffer);
			std::string titleBeg = "<title>";
			std::string titleEnd = "</title>";
			size_t titleBegPos = bufStr.find(titleBeg);
			size_t titleEndPos = bufStr.find(titleEnd);

			std::string ASNBeg = "来自：";
			std::string ASNEnd = "\n";
			size_t ASNBegPos = bufStr.find(ASNBeg);
			size_t ASNEndPos = bufStr.find(ASNEnd, ASNBegPos);

			if (std::string::npos == titleBegPos || std::string::npos == titleEndPos ||
				std::string::npos == ASNBegPos || std::string::npos == ASNEndPos)
				break;
			
			cout << bufStr.substr(titleBegPos + titleBeg.size(), titleEndPos - titleBegPos - titleBeg.size()) << "\t" <<
				bufStr.substr(ASNBegPos, ASNEndPos - ASNBegPos) << endl;

			//ofstream ofs("ip.txt");
			//ofs.write(bufStr.c_str(), bufStr.size());
		}
		break;
	case 1:
		printASN(bufStr);
		break;
	default:
		break;
	}
	//size_t findASN = bufStr.find("ASN归属地");
	//size_t findASNEnd = bufStr.find(",", findASN);
	//cout << bufStr.substr(findASN, findASNEnd - findASN) << endl;
	delete[] buffer;
	//string modSearch;
	//string hd = "class=\"hd\"";
	
	//findContext(bufStr, modSearch, { "wrapper", "container", "content", "inner", "mod-search", "hd" });
	//findPos(bufStr, modSearch, "mod-search");

	//findContext(bufStr, modSearch, { "wrapper", "container", "content", "inner", "groups\\2", "group", "module mod-search", "table-outer", "table-inner" });
	//cout << modSearch << endl;


	InternetCloseHandle(hInternetUrl);
	InternetCloseHandle(hInternet);
	return true;
}

int main()
{
	if (!openUrl(URL_SELF, 0))
		return -1;

	std::string ipNumStr;
	bool close = false;
	while (!close)
	{
		cin >> ipNumStr;
		if ("q" == ipNumStr)
			break;

		size_t ipNum = std::stoul(ipNumStr);
		unsigned char(&ip)[4] = (unsigned char(&)[4])ipNum;
		std::ostringstream osIp;
		bool first = true;

		for (unsigned char& i : ip)
		{
			if (first) first = false;
			else osIp << ".";

			osIp << (unsigned short)i;
		}

		std::ostringstream osUrl;
		osUrl << URL_BEG << osIp.str() << URL_END;
		cout << ipNum << "\t" << osIp.str() << "\t";
		openUrl(osUrl.str().c_str(), 1);
	}


	return 0;
}