#pragma once
#include <event2/bufferevent.h>

#include "XTask.h"

#include <string>
using namespace std;

struct bufferevent;

class XFtpTask : public XTask
{
public:
	string curDir = "/";
	string rootDir = "/";
	string ip = "";
	int port = 0;
	XFtpTask *cmdTask = nullptr;

	// 解析函数，根据指定的参数解析命令
	virtual void Parse(std::string, std::string) {}

	// 响应命令，发送消息给客户端
	void ResCMD(string msg);

	// 连接到PORT模式（主动模式）
	void ConnectoPORT();

	void ClosePORT();

	void Send(const string& data);
	void Send(const char *data, size_t datasize);

	virtual void Event(bufferevent *, short) {}
	virtual void Read(bufferevent *) {}
	virtual void Write(bufferevent *) {}

	// 设置事件回调函数
	void Setcb(struct bufferevent*);

	bool Init() 
	{ 
		return true; 
	}

	~XFtpTask();

protected:
	static void EventCB(bufferevent *, short, void *);
	static void ReadCB(bufferevent *, void *);
	static void WriteCB(bufferevent *, void *);

	bufferevent *bev = 0;
	FILE *fp = 0;
};

