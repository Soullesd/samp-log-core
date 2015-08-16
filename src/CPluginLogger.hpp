#pragma once

#include "CLogger.hpp"

#include <memory>

#if defined _WIN32 || defined __CYGWIN__
# ifdef __GNUC__
#  define DLL_PUBLIC __attribute__ ((dllexport))
# else
#  define DLL_PUBLIC __declspec(dllexport)
# endif
#else
# if __GNUC__ >= 4
#  define DLL_PUBLIC __attribute__ ((visibility ("default")))
# else
#  define DLL_PUBLIC
# endif
#endif
//TODO: GCC: -fvisibility=hidden

typedef struct tagAMX AMX;


class IPluginLogger
{
public:
	virtual void Log(const LOGLEVEL &level, const std::string &msg, ...) = 0;
	virtual void LogEx(const LOGLEVEL &level, const std::string &msg, long line, const std::string &file, const std::string &function) = 0;
	virtual bool LogNativeCall(AMX * const amx, const std::string &name, const std::string &params_format) = 0;

	virtual void Destroy() = 0;
};

class CPluginLogger : public IPluginLogger
{
public:
	CPluginLogger(std::string name);
	~CPluginLogger() = default;


	void Log(const LOGLEVEL &level, const std::string &msg, ...);
	void LogEx(const LOGLEVEL &level, const std::string &msg, long line, const std::string &file, const std::string &function);
	bool LogNativeCall(AMX * const amx, const std::string &name, const std::string &params_format);

	void Destroy();

private:
	CLogger m_Logger;
};

extern "C" DLL_PUBLIC IPluginLogger *CreatePluginLoggerPtr(const char *pluginname);
