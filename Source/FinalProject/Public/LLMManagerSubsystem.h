#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HAL/PlatformProcess.h"
#include "LLMManagerSubsystem.generated.h"

UCLASS()
class YOURGAME_API ULLMManagerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

private:
    FProcHandle LLMProcessHandle;
    void LaunchLLMServer();
    void StopLLMServer();
};