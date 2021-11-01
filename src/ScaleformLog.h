#pragma once

class ScaleformLog : public RE::GFxLog
{
public:
	~ScaleformLog() = default;
	ScaleformLog(const ScaleformLog& other) = delete;
	ScaleformLog(ScaleformLog&& other) = delete;
	ScaleformLog& operator=(const ScaleformLog& other) = delete;
	ScaleformLog& operator=(ScaleformLog&& other) = delete;

	static auto GetSingleton() -> ScaleformLog*;

	void LogMessageVarg(
		LogMessageType a_messageType,
		const char* a_fmt,
		std::va_list a_argList) override;

private:
	ScaleformLog() = default;
};

