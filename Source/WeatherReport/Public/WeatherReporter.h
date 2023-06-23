// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "WeatherReporter.generated.h"

USTRUCT(BlueprintType)
struct FWeatherReportData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float temperature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int weathercode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float windspeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float winddirection;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeatherReportResponseDelegate, const FWeatherReportData &, weatherReportData);

UCLASS()
class WEATHERREPORT_API AWeatherReporter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeatherReporter();

	UFUNCTION(BlueprintCallable, meta = (Category = "Weather Report Request"))
	bool WeatherReportHttpRequest(const float &latitude, const float &longitude, FString &errormsg);

	UPROPERTY(BlueprintAssignable, meta = (Category = "Weather Report Event"))
	FWeatherReportResponseDelegate OnWeatherReportDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void ProcessWeatherReportResponse(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful);
};