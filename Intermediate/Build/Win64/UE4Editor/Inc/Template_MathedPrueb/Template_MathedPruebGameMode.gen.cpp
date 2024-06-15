// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Template_MathedPrueb/Template_MathedPruebGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTemplate_MathedPruebGameMode() {}
// Cross Module References
	TEMPLATE_MATHEDPRUEB_API UClass* Z_Construct_UClass_ATemplate_MathedPruebGameMode_NoRegister();
	TEMPLATE_MATHEDPRUEB_API UClass* Z_Construct_UClass_ATemplate_MathedPruebGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Template_MathedPrueb();
// End Cross Module References
	void ATemplate_MathedPruebGameMode::StaticRegisterNativesATemplate_MathedPruebGameMode()
	{
	}
	UClass* Z_Construct_UClass_ATemplate_MathedPruebGameMode_NoRegister()
	{
		return ATemplate_MathedPruebGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ATemplate_MathedPruebGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATemplate_MathedPruebGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Template_MathedPrueb,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATemplate_MathedPruebGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "Template_MathedPruebGameMode.h" },
		{ "ModuleRelativePath", "Template_MathedPruebGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATemplate_MathedPruebGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATemplate_MathedPruebGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATemplate_MathedPruebGameMode_Statics::ClassParams = {
		&ATemplate_MathedPruebGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_ATemplate_MathedPruebGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATemplate_MathedPruebGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATemplate_MathedPruebGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATemplate_MathedPruebGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATemplate_MathedPruebGameMode, 2490199918);
	template<> TEMPLATE_MATHEDPRUEB_API UClass* StaticClass<ATemplate_MathedPruebGameMode>()
	{
		return ATemplate_MathedPruebGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATemplate_MathedPruebGameMode(Z_Construct_UClass_ATemplate_MathedPruebGameMode, &ATemplate_MathedPruebGameMode::StaticClass, TEXT("/Script/Template_MathedPrueb"), TEXT("ATemplate_MathedPruebGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATemplate_MathedPruebGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
