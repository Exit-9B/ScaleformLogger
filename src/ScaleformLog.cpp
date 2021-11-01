#include "ScaleformLog.h"

auto ScaleformLog::GetSingleton() -> ScaleformLog*
{
	static ScaleformLog singleton{};
	return std::addressof(singleton);
}

void ScaleformLog::LogMessageVarg(
	LogMessageType a_messageType,
	const char* a_fmt,
	std::va_list a_argList)
{
	LogMessageType messageType =
		static_cast<LogMessageType>(RE::stl::to_underlying(a_messageType) & 0xF);

	spdlog::level::level_enum level;

	switch (messageType) {
	case LogMessageType::kMessageType_Error:
		level = spdlog::level::level_enum::err;
		break;
	case LogMessageType::kMessageType_Warning:
		level = spdlog::level::level_enum::warn;
		break;
	case LogMessageType::kMessageType_Message:
		level = spdlog::level::level_enum::info;
		break;
	default:
		level = spdlog::level::level_enum::trace;
		break;
	}

	int len = _vscprintf(a_fmt, a_argList);
	if (len == -1) {
		return;
	}

	std::size_t size = static_cast<std::size_t>(len) + 1;

	char* str = static_cast<char*>(malloc(size));
	vsprintf_s(str, size, a_fmt, a_argList);

	std::string_view sv{ str, size };

	spdlog::default_logger()->log(level, sv);
}
