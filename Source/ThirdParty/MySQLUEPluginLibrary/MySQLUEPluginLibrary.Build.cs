// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class MySQLUEPluginLibrary : ModuleRules
{
	public MySQLUEPluginLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "MariaDBConnectorC64bit", "include"));

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "MariaDBConnectorC64bit", "lib",
				"libmariadb.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "MariaDBConnectorC64bit", "lib",
				"libmariadbclient.lib"));


			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("libmariadb.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/MySQLUEPluginLibrary/Win64/libmariadb.dll");
		}
		else if (base.Target.Platform == UnrealTargetPlatform.HoloLens)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "MariaDBConnectorC64bit", "lib_arm64",
				"libmariadb.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "MariaDBConnectorC64bit", "lib_arm64",
				"libmariadbclient.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("libmariadb.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/MySQLUEPluginLibrary/Arm64/libmariadb.dll");
		}
	}
}