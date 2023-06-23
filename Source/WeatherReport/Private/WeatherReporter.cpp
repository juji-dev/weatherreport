
#include "WeatherReporter.h"

const float LTMX = 90;
const float LTMN = LTMX * -1;
const float LNMX = 180;
const float LNMN = LNMX * -1;
const FString WEATHER_API_URL = TEXT("https://api.open-meteo.com/v1/forecast");

AWeatherReporter::AWeatherReporter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeatherReporter::BeginPlay()
{
	Super::BeginPlay();
}

void AWeatherReporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AWeatherReporter::WeatherReportHttpRequest(const float &latitude, const float &longitude, FString &errormsg)
{
	errormsg = "";
	bool isValidParams = !(latitude < LTMN || latitude > LTMX || longitude < LNMN || longitude > LNMX);
	if (!isValidParams)
	{
		errormsg += "Invalid parameters, check latitiude and longitude does not over or under flow range. Lat(-90, 90), Long(-180, 180)";
		return false;
	}
	FString currentWeather = "true";
	FString requestURL = WEATHER_API_URL + TEXT("?latitude=") + FString::SanitizeFloat(latitude) + TEXT("&longitude=") + FString::SanitizeFloat(longitude) + TEXT("&current_weather=") + currentWeather;

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> WeatherHttpRequest = FHttpModule::Get().CreateRequest();
	WeatherHttpRequest->SetVerb(TEXT("GET"));
	WeatherHttpRequest->SetURL(requestURL);

	// Set the completion callback
	WeatherHttpRequest->OnProcessRequestComplete().BindUObject(this, &AWeatherReporter::ProcessWeatherReportResponse);

	// Send the request
	WeatherHttpRequest->ProcessRequest();

	return true;
}

void AWeatherReporter::ProcessWeatherReportResponse(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful)
{
	if (bWasSuccessful && response.IsValid())
	{
		FString contentStr = response->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("Weather Report Sucessful. Unprocessed: %s"), *contentStr);

		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(contentStr);
		FJsonSerializer::Deserialize(JsonReader, JsonObject);

		if (JsonObject.IsValid())
		{
			if (JsonObject->HasField("current_weather"))
			{
				const TSharedPtr<FJsonObject> &CurrentWeatherObject = JsonObject->GetObjectField("current_weather");
				FWeatherReportData weatherReportData;

				CurrentWeatherObject->TryGetStringField("time", weatherReportData.time);
				CurrentWeatherObject->TryGetNumberField("temperature", weatherReportData.temperature);
				CurrentWeatherObject->TryGetNumberField("weathercode", weatherReportData.weathercode);
				CurrentWeatherObject->TryGetNumberField("windspeed", weatherReportData.windspeed);
				CurrentWeatherObject->TryGetNumberField("winddirection", weatherReportData.winddirection);

				OnWeatherReportDelegate.Broadcast(weatherReportData);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Weather Report HTTP Request Unsuccessful"));
	}
}
