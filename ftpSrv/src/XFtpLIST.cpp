#include "XFtpLIST.h"
#include "event2/bufferevent.h"
#include "event2/event.h"
#include "testUtil.h"
#include <string>
#include <sys/stat.h>
using namespace std;

 


void XFtpLIST::Write(bufferevent *bev) 
{
	testout("XFtpLIST::Write");
	ResCMD("226 Transfer comlete");
	ClosePORT();
}

void XFtpLIST::Event(bufferevent *bev, short events) 
{
	testout("At XFtpLIST::Event");
	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT)) {
		ClosePORT();
	}
	else if (events & BEV_EVENT_CONNECTED)
		cout << "XFtpLIST BEV_EVENT_CONNECTED" << endl;
}

void XFtpLIST::Parse(std::string type, std::string msg) 
{
	testout("At XFtpLIST::Parse");
	string resmsg = "";
	if (type == "PWD") {
		// 257 "/" is current directory.
		resmsg = "257 \"";
		resmsg += cmdTask->curDir;
		resmsg += "\" is current dir.";
		ResCMD(resmsg);
	}
	else if (type == "LIST") {
		// 1 闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氾拷150闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氳锛冨Δ鍛櫢闁跨噦鎷�
		// 2 闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺顐ｅ哺閺佹捇寮妶鍡楊伓闂佽法鍠愰弸濠氬箯閻戣В鍋撳鑸垫櫢闁哄倶鍊栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺顐ｅ哺閺佹捇寮妶鍡楊伓闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏�
		// 3 闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氾拷226闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氳锛冨Δ鍛櫢闁哄倶鍊栫€氬綊鏌ㄩ悢鍛婄伄闁瑰嚖鎷�
		// 4 闂佽法鍠愰崺鍛村箟鐎ｎ偄顏堕梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫€氾拷
		// 闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氬綊鏌呭鑸垫櫢闁哄倶鍊栫€氬綊鏌ㄩ悢绋跨劵闂傚牃鏅滅€氬綊鏌ㄩ悢鍛婄伄闁圭兘鏀辨导锟� 濞达絽娼￠弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫€氬綊鏌呭鑸垫櫢闁哄倶鍊栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕柣鈺婂枛缂嶏拷
		//  "-rwxrwxrwx 1 root root      418 Mar 21 16:10 XFtpFactory.cpp";
		string path = cmdTask->rootDir + cmdTask->curDir;
		testout("listpath: " << path);
		string listdata = GetListData(path);
		ConnectoPORT();
		ResCMD("150 Here coms the directory listing.");
		Send(listdata);
	}
	else if (type == "CWD") //闂佽法鍠庤ぐ銊﹀濞嗘劕顏堕柣鈺婂枛缂嶏拷
	{
		//闁告瑦鐗犻弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫€氬綊鏌ㄩ悢宄板缓缁炬澘顦扮€氬湱鎹勯鐐存櫢闁哄倶鍊栫€氾拷
		//CWD test\r\n
		int pos = msg.rfind(" ") + 1;
		//闁告ê顭烽弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忓畡鎵暡闂佽法鍠愰弸濠氬箯缁屽児\n
		string path = msg.substr(pos, msg.size() - pos - 2);
		string curDir = cmdTask->curDir;
		if (path[0] == '/') //闂佽法鍠曢、婊呮媼鐟欏嫬顏堕悹渚灦閺佹捇寮妶鍡楊伓
		{
			curDir = path;
		}
		else
		{
			if (curDir[curDir.size() - 1] != '/')
				curDir += "/";
			curDir += path + "/";
		}
		if (curDir[curDir.size() - 1] != '/')
			curDir += "/";
		struct stat s_buf;
		stat(curDir.c_str(),&s_buf);
		if(S_ISDIR(s_buf.st_mode))
		{
			cmdTask->curDir = curDir;
			ResCMD("250 Directory succes chanaged.\r\n");
		}
		else
		{
			ResCMD("501 Directory not chanaged.\r\n");
		}
		//cmdTask->curDir = curDir;
		//  /test/
		//ResCMD("250 Directory succes chanaged.\r\n");

		//cmdTask->curDir += 
	}
	else if (type == "CDUP") //闂佽法鍠愰崺鍛枈婢跺顏堕梺璺ㄥ枙缁舵繄鎷犺鐎氬綊鎯勯鑲╃Э
	{
		cout << "msg:" << msg << endl;
		cout << "cmdTask->curDir:" << cmdTask->curDir << endl;
		// if (msg[4] == '\r') {
		// 	cmdTask->curDir = "/";
		// }
		// else {
		// 	//  /Debug/test_ser.A3C61E95.tlog /Debug   /Debug/
		// 	string path = cmdTask->curDir;
		// 	//缂備胶鍠嶇粩鎾储婵犳碍鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁瑰嘲鍢查悢顒勬煥閻斿憡鐏柟鍑ゆ嫹 /
		// 	////  /Debug/test_ser.A3C61E95.tlog /Debug  
			
		// 	if (path[path.size() - 1] == '/')
		// 	{
		// 		path = path.substr(0, path.size() - 1);
		// 	}
		// 	int pos = path.rfind("/");
		// 	path = path.substr(0, pos);
		// 	cmdTask->curDir = path;
		// 	if (cmdTask->curDir[cmdTask->curDir.size() - 1] != '/')
		// 		cmdTask->curDir += "/";
		// }
		//  /Debug/test_ser.A3C61E95.tlog /Debug   /Debug/
			string path = cmdTask->curDir;
			//缂備胶鍠嶇粩鎾储婵犳碍鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁瑰嘲鍢查悢顒勬煥閻斿憡鐏柟鍑ゆ嫹 /
			////  /Debug/test_ser.A3C61E95.tlog /Debug  
			
		if (path[path.size() - 1] == '/')
		{
			path = path.substr(0, path.size() - 1);
		}
		int pos = path.rfind("/");
		path = path.substr(0, pos);
		cmdTask->curDir = path;
		if (cmdTask->curDir[cmdTask->curDir.size() - 1] != '/')
			cmdTask->curDir += "/";
		cout << "cmdTask->curDir:" << cmdTask->curDir << endl;
		ResCMD("250 Directory succes chanaged.\r\n");
	}
}

string XFtpLIST::GetListData(string path) {
	// -rwxrwxrwx 1 root root 418 Mar 21 16:10 XFtpFactory.cpp

	string data = "";
	string cmd = "ls -l ";
	cmd += path;
	cout << cmd << endl;
	FILE *f = popen(cmd.c_str(), "r");
	if (!f) return data;
	char buf[1024] = {0};
	while (1) {
		int len = fread(buf, 1, sizeof(buf) - 1, f);
		if (len <= 0)break;
		buf[len] = '\0';
		data += buf;
	}
	pclose(f);
 
	return data;
}
