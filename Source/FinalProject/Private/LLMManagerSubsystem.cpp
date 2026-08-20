#include "LLMManagerSubsystem.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"

void ULLMManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    LaunchLLMServer();
}

void ULLMManagerSubsystem::LaunchLLMServer()
{
    // Resolve absolute paths
    FString ServerPath = FPaths::ConvertRelativePathToFull(
        FPaths::ProjectContentDir() + TEXT("ThirdParty/LlamaServer/llama-server.exe")
    );

    FString ModelPath = FPaths::ConvertRelativePathToFull(
        FPaths::ProjectContentDir() + TEXT("Models/Gemma-3n-E4B.gguf")
    );

    // Command line flags:
    // -m: Model path
    // --port: Server port
    // -ngl 999: Offload as many layers as possible to GPU (VRAM)
    // -c 2048: Set context size
    FString CommandArgs = FString::Printf(
        TEXT("-m \"%s\" --port 8080 -ngl 999 -c 2048"),
        *ModelPath
    );

    // Launch process hidden in the background
    bool bLaunchDetached = true;
    bool bLaunchHidden = true;
    bool bLaunchReallyHidden = true;

    LLMProcessHandle = FPlatformProcess::CreateProc(
        *ServerPath,
        *CommandArgs,
        bLaunchDetached,
        bLaunchHidden,
        bLaunchReallyHidden,
        nullptr,
        0,
        nullptr,
        nullptr
    );

    if (LLMProcessHandle.IsValid())
    {
        UE_LOG(LogTemp, Log, TEXT("Local LLM Server launched successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to launch Local LLM Server process."));
    }
}

void ULLMManagerSubsystem::Deinitialize()
{
    StopLLMServer();
    Super::Deinitialize();
}

void ULLMManagerSubsystem::StopLLMServer()
{
    if (LLMProcessHandle.IsValid() && FPlatformProcess::IsProcRunning(LLMProcessHandle))
    {
        FPlatformProcess::TerminateProc(LLMProcessHandle, true);
        FPlatformProcess::CloseProc(LLMProcessHandle);
        UE_LOG(LogTemp, Log, TEXT("Local LLM Server process terminated."));
    }
}