// Copyright Epic Games, Inc. All Rights Reserved.

#include "MySQLUEPlugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "ThirdParty/MySQLUEPluginLibrary/MariaDBConnectorC64bit/include/mysql.h"

#define LOCTEXT_NAMESPACE "FMySQLUEPluginModule"

void FMySQLUEPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("MySQLUEPlugin")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/MySQLUEPluginLibrary/Win64/libmariadb.dll"));
#elif PLATFORM_HOLOLENS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/MySQLUEPluginLibrary/Arm64/libmariadb.dll"));
#endif

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	// if (ExampleLibraryHandle)
	// {
	// 	// Call the test function in the third party library that opens a message box
	// 	MYSQL* conn;
	// 	conn = mysql_init(0);
	// 	conn = mysql_real_connect(conn, "0.0.0.0", "dbcon", "password", "databaseName", 3306, NULL, 0);
	// 	if (conn)
	// 	{
	// 		MessageBox(
	// 			NULL,
	// 			(LPCWSTR)L"Connected to the database.",
	// 			(LPCWSTR)L"Database works!",
	// 			MB_OK
	// 		);
	// 		mysql_close(conn);
	// 	}
	// 	else
	// 	{
	// 		const char* error = mysql_error(conn);
	// 		MessageBox(
	// 			NULL,
	// 			(LPCWSTR)error,
	// 			(LPCWSTR)L"Error: ",
	// 			MB_OK
	// 		);
	// 	}
	//
	// }
	// else
	// {
	// 	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Database Plugin", "Failed to load MySQL database plugin!"));
	// }
	
}

void FMySQLUEPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMySQLUEPluginModule, MySQLUEPlugin)
