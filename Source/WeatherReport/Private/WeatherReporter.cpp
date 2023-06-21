// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherReporter.h"

// Sets default values
AWeatherReporter::AWeatherReporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeatherReporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeatherReporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

