# UE4 Weather Report Plugin

<p align="center">
  <img src="Resources/Icon128.png" alt="Weather Report Icon">
</p>

The UE4 Weather Report Plugin is a small custom plugin for Unreal Engine 5.2+ that allows you to retrieve Weather Report data based on geo-location information (latitude and longitude) using the Open-meteo API. With this plugin, you can easily bring Weather Report data into your UE4 projects.

## Features
- Retrieve Weather Report data based on latitude and longitude
- Access current Weather Report information such as temperature, humidity, and windspeed
- Seamless integration with Unreal Engine 4 projects
- Customizable and easy to use

## Requirements
- Unreal Engine 5.2 or later

## Installation
### To install the UE4 Weather Report Plugin, follow these steps:

- Download or clone the plugin repository to your local machine.
- Copy the plugin folder to the Plugins directory of your Unreal Engine project.
- Enable the plugin in the Unreal Editor by going to the Edit menu -> Plugins -> Weather Report Plugin and check the Enabled box.
- Restart the Unreal Editor to ensure the plugin is properly initialized.

## Usage
### To use the Weather Report Plugin in your UE4 project, follow these steps:

- Open your project in the Unreal Editor.
- Create an AActor of type AWeatherReporter.
- Drag and drop your new Weather Report Actor from the Content Browser into your level or blueprint.
- Use the WeatherReportHttpRequest function in the weather report actor blueprint to execute the weather request, make sure to provide location data.
- Bind to OnWeatherReportEvent for a weather report response.

## Credits
The UE4 Weather Report Plugin was developed by Juji-Dev and is inspired by the https://open-meteo.com/

## Feedback and Contributions
Feedback, bug reports, and contributions are welcome! If you encounter any issues or have suggestions for improvement, please open an issue on the GitHub repository.
-----------------------------
With the UE4 Weather Report Report Plugin, integrating Weather Report data into your Unreal Engine 4 projects has never been easier!