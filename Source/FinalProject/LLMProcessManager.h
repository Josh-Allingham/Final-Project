#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LLMProcessManager.generated.h"

UCLASS()
class ULLMProcessManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "LLM")
	static bool LaunchLLMServer(FString ExecPath, FString CommandArgs);

	UFUNCTION(BlueprintCallable, Category = "LLM")
	static void StopLLMServer();
};