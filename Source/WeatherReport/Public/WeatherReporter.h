// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "WeatherReporter.generated.h"

// TODO Broadcast Dictionary or JSON object with current weather
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStringWeatherReportEvent, FString, WeatherReportString);

UCLASS()
class WEATHERREPORT_API AWeatherReporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeatherReporter();

	UFUNCTION(BlueprintCallable, meta= (Category = "Weather Report Request"))
	bool WeatherReportHttpRequest(const float &latitude, const float& longitude, FString& errormsg);

	// TODO replace with dictionary or JSON object with current weather
	UPROPERTY(BlueprintAssignable, meta= (Category = "Weather Report Event"))
	FStringWeatherReportEvent OnWeatherReportEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void ProcessWeatherReportResponse(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful);
};
