#pragma once
#include "XTask.h"


class XFtpFactory
{
public:
	static XFtpFactory*Get() 
	{
		static XFtpFactory f;
		return &f;
	}
	XTask *CreateTask();

private:
	XFtpFactory() = default;
	~XFtpFactory() = default;
	XFtpFactory(const XFtpFactory&) = delete;
	XFtpFactory &operator=(const XFtpFactory&) = delete;
};

