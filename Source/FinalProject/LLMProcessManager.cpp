#include "LLMProcessManager.h"
#include "HAL/PlatformProcess.h"

static FProcHandle GlobalLLMHandle;

bool ULLMProcessManager::LaunchLLMServer(FString ExecPath, FString CommandArgs)
{
	// Launch the background process silently
	GlobalLLMHandle = FPlatformProcess::CreateProc(*ExecPath, *CommandArgs, true, true, true, nullptr, 0, nullptr, nullptr);

	// Returns true if process successfully launched
	return GlobalLLMHandle.IsValid();
}

void ULLMProcessManager::StopLLMServer()
{
	if (GlobalLLMHandle.IsValid())
	{
		FPlatformProcess::TerminateProc(GlobalLLMHandle);
		FPlatformProcess::CloseProc(GlobalLLMHandle);
	}
}