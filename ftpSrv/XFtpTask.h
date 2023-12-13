#pragma once
#include <event2/bufferevent.h>

#include "XTask.h"

#include <string>
using namespace std;

struct bufferevent;

class XFtpTask :
	public XTask
{
public:
	string curDir = "/";
	string rootDir = "/";
	string ip = "";
	int port = 0;
	XFtpTask *cmdTask = 0;

	// 锟斤拷锟斤拷协锟斤拷
	virtual void Parse(std::string, std::string) {}

	// 锟截革拷cmd锟斤拷息
	void ResCMD(string msg);

	// 锟斤拷锟斤拷锟斤拷锟斤拷通锟斤拷
	void ConnectoPORT();
	// 锟截憋拷锟斤拷锟斤拷
	void ClosePORT();

	// 通锟斤拷锟斤拷锟斤拷通锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	void Send(const string& data);
	void Send(const char *data, size_t datasize);

	virtual void Event(bufferevent *, short) {}
	virtual void Read(bufferevent *) {}
	virtual void Write(bufferevent *) {}

	void Setcb(struct bufferevent*);
	bool Init() { return true; }

	~XFtpTask();

protected:
	static void EventCB(bufferevent *, short, void *);
	static void ReadCB(bufferevent *, void *);
	static void WriteCB(bufferevent *, void *);

	// 锟斤拷CMD锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷通锟斤拷锟斤拷锟斤拷LIST锟斤拷RETR锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷通锟斤拷
	bufferevent *bev = 0;
	FILE *fp = 0;
};

