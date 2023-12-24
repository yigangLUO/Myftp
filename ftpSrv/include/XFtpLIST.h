#pragma once
#include "XFtpTask.h"
#include <string>
using namespace std;

class XFtpLIST : public XFtpTask
{
public:
	virtual void Parse(std::string, std::string);
	virtual void Event(bufferevent *, short);
	virtual void Write(bufferevent *);

private:
	// 获取linux文件基本属性列表
	string GetListData(string path); 
};

