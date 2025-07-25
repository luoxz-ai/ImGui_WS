// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealImGuiLibrary.h"

#include "UnrealImGuiAssetPicker.h"
#include "Containers/Utf8String.h"

namespace UnrealImGuiLibrary
{
	UnrealImGui::FObjectPickerSettings ObjectPickerSettings;
	UnrealImGui::FActorPickerSettings ActorPickerSettings;
	UnrealImGui::FClassPickerSettings ClassPickerSettings;

	struct FObjectPickerSettingsScope
	{
		FObjectPickerSettingsScope(const FUnrealImGuiObjectPickerSettings& Settings)
			: FilterHintString(Settings.FilterHint)
			, FilterHint(ObjectPickerSettings.FilterHint)
			, CustomFilter(MoveTemp(ObjectPickerSettings.CustomFilter))
		{
			ObjectPickerSettings.FilterHint = reinterpret_cast<const char*>(*FilterHintString);
			if (Settings.Filter.IsBound())
			{
				ObjectPickerSettings.CustomFilter = [Filter = Settings.Filter](const FAssetData& Asset)
				{
					return Filter.Execute(Asset);
				};
			}
			else
			{
				ObjectPickerSettings.CustomFilter.Reset();
			}
		}
		~FObjectPickerSettingsScope()
		{
			ObjectPickerSettings.FilterHint = FilterHint;
			ObjectPickerSettings.CustomFilter = MoveTemp(CustomFilter);
		}
		
		FUtf8String FilterHintString;
		const char* FilterHint;
		TFunction<bool(const FAssetData&)> CustomFilter;
	};

	struct FActorPickerSettingsScope
	{
		FActorPickerSettingsScope(const FUnrealImGuiActorPickerSettings& Settings)
			: FilterHintString(Settings.FilterHint)
			, FilterHint(ActorPickerSettings.FilterHint)
			, CustomFilter(MoveTemp(ActorPickerSettings.CustomFilter))
		{
			ActorPickerSettings.FilterHint = reinterpret_cast<const char*>(*FilterHintString);
			if (Settings.Filter.IsBound())
			{
				ActorPickerSettings.CustomFilter = [Filter = Settings.Filter](const AActor* Actor)
				{
					return Filter.Execute(Actor);
				};
			}
			else
			{
				ActorPickerSettings.CustomFilter.Reset();
			}
		}
		~FActorPickerSettingsScope()
		{
			ActorPickerSettings.FilterHint = FilterHint;
			ActorPickerSettings.CustomFilter = MoveTemp(CustomFilter);
		}
		
		FUtf8String FilterHintString;
		const char* FilterHint;
		TFunction<bool(const AActor*)> CustomFilter;
	};

	struct FClassPickerSettingsScope
	{
		FClassPickerSettingsScope(const FUnrealImGuiClassPickerSettings& Settings)
			: FilterHintString(Settings.FilterHint)
			, FilterHint(ClassPickerSettings.FilterHint)
			, CustomFilter(MoveTemp(ClassPickerSettings.CustomFilter))
			, CustomFilterUnloadBp(MoveTemp(ClassPickerSettings.CustomFilterUnloadBp))
		{
			ClassPickerSettings.FilterHint = reinterpret_cast<const char*>(*FilterHintString);
			if (Settings.Filter.IsBound())
			{
				ClassPickerSettings.CustomFilter = [Filter = Settings.Filter](const UClass* Class)
				{
					return Filter.Execute(Class);
				};
			}
			else
			{
				ClassPickerSettings.CustomFilter.Reset();
			}
		
			if (Settings.FilterUnloadBp.IsBound())
			{
				ClassPickerSettings.CustomFilterUnloadBp = [Filter = Settings.FilterUnloadBp](const FAssetData& Asset)
				{
					return Filter.Execute(Asset);
				};
			}
			else
			{
				ClassPickerSettings.CustomFilterUnloadBp.Reset();
			}
		}
		~FClassPickerSettingsScope()
		{
			ClassPickerSettings.FilterHint = FilterHint;
			ClassPickerSettings.CustomFilter = MoveTemp(CustomFilter);
			ClassPickerSettings.CustomFilterUnloadBp = MoveTemp(CustomFilterUnloadBp);
		}

		FUtf8String FilterHintString;
		const char* FilterHint;
		TFunction<bool(const UClass*)> CustomFilter;
		TFunction<bool(const FAssetData&)> CustomFilterUnloadBp;
	};
}

bool UUnrealImGuiLibrary::ComboObjectPicker(FName Label, UClass* BaseClass, UObject*& ObjectPtr)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	return UnrealImGui::ComboObjectPicker(TCHAR_TO_UTF8(*Label.ToString()), BaseClass, ObjectPtr, &UnrealImGuiLibrary::ObjectPickerSettings);
}

bool UUnrealImGuiLibrary::ComboSoftObjectPicker(FName Label, UClass* BaseClass, TSoftObjectPtr<UObject>& SoftObjectPtr)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	return UnrealImGui::ComboSoftObjectPicker(TCHAR_TO_UTF8(*Label.ToString()), BaseClass, SoftObjectPtr, &UnrealImGuiLibrary::ObjectPickerSettings);
}

bool UUnrealImGuiLibrary::ComboObjectPickerEx(FName Label, UClass* BaseClass, UObject*& ObjectPtr, const FUnrealImGuiObjectPickerSettings& Settings)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	auto Scope = UnrealImGuiLibrary::FObjectPickerSettingsScope{ Settings };
	return UnrealImGui::ComboObjectPicker(TCHAR_TO_UTF8(*Label.ToString()), BaseClass, ObjectPtr, &UnrealImGuiLibrary::ObjectPickerSettings);
}

bool UUnrealImGuiLibrary::ComboSoftObjectPickerEx(FName Label, UClass* BaseClass, TSoftObjectPtr<UObject>& SoftObjectPtr, const FUnrealImGuiObjectPickerSettings& Settings)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	auto Scope = UnrealImGuiLibrary::FObjectPickerSettingsScope{ Settings };
	return UnrealImGui::ComboSoftObjectPicker(TCHAR_TO_UTF8(*Label.ToString()), BaseClass, SoftObjectPtr, &UnrealImGuiLibrary::ObjectPickerSettings);
}

bool UUnrealImGuiLibrary::ComboActorPicker(UObject* WorldContextObject, FName Label, TSubclassOf<AActor> BaseClass, AActor*& ActorPtr)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	return UnrealImGui::ComboActorPicker(WorldContextObject ? WorldContextObject->GetWorld() : nullptr, TCHAR_TO_UTF8(*Label.ToString()), BaseClass, ActorPtr, &UnrealImGuiLibrary::ActorPickerSettings);
}

bool UUnrealImGuiLibrary::ComboSoftActorPicker(UObject* WorldContextObject, FName Label, TSubclassOf<AActor> BaseClass, TSoftObjectPtr<AActor>& SoftActorPtr)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	return UnrealImGui::ComboSoftActorPicker(WorldContextObject ? WorldContextObject->GetWorld() : nullptr, TCHAR_TO_UTF8(*Label.ToString()), BaseClass, SoftActorPtr, &UnrealImGuiLibrary::ActorPickerSettings);
}

bool UUnrealImGuiLibrary::ComboActorPickerEx(UObject* WorldContextObject, FName Label, TSubclassOf<AActor> BaseClass, AActor*& ActorPtr, const FUnrealImGuiActorPickerSettings& Settings)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	auto Scope = UnrealImGuiLibrary::FActorPickerSettingsScope{ Settings };
	return UnrealImGui::ComboActorPicker(WorldContextObject ? WorldContextObject->GetWorld() : nullptr, TCHAR_TO_UTF8(*Label.ToString()), BaseClass, ActorPtr, &UnrealImGuiLibrary::ActorPickerSettings);
}

bool UUnrealImGuiLibrary::ComboSoftActorPickerEx(UObject* WorldContextObject, FName Label, TSubclassOf<AActor> BaseClass, TSoftObjectPtr<AActor>& SoftActorPtr, const FUnrealImGuiActorPickerSettings& Settings)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	auto Scope = UnrealImGuiLibrary::FActorPickerSettingsScope{ Settings };
	return UnrealImGui::ComboSoftActorPicker(WorldContextObject ? WorldContextObject->GetWorld() : nullptr, TCHAR_TO_UTF8(*Label.ToString()), BaseClass, SoftActorPtr, &UnrealImGuiLibrary::ActorPickerSettings);
}

bool UUnrealImGuiLibrary::ComboClassPicker(FName Label, UClass* BaseClass, TSubclassOf<UObject>& ClassPtr, bool bAllowAbstract)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	return UnrealImGui::ComboClassPicker(TCHAR_TO_UTF8(*Label.ToString()), BaseClass, ClassPtr, bAllowAbstract ? CLASS_Abstract : CLASS_None, &UnrealImGuiLibrary::ClassPickerSettings);
}

bool UUnrealImGuiLibrary::ComboSoftClassPicker(FName Label, UClass* BaseClass, TSoftClassPtr<UObject>& SoftClassPtr, bool bAllowAbstract)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	return UnrealImGui::ComboSoftClassPicker(TCHAR_TO_UTF8(*Label.ToString()), BaseClass, SoftClassPtr, bAllowAbstract ? CLASS_Abstract : CLASS_None, &UnrealImGuiLibrary::ClassPickerSettings);
}

bool UUnrealImGuiLibrary::ComboClassPickerEx(FName Label, UClass* BaseClass, TSubclassOf<UObject>& ClassPtr, bool bAllowAbstract, const FUnrealImGuiClassPickerSettings& Settings)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	auto Scope = UnrealImGuiLibrary::FClassPickerSettingsScope{ Settings };
	return UnrealImGui::ComboClassPicker(TCHAR_TO_UTF8(*Label.ToString()), BaseClass, ClassPtr, bAllowAbstract ? CLASS_Abstract : CLASS_None, &UnrealImGuiLibrary::ClassPickerSettings);
}

bool UUnrealImGuiLibrary::ComboSoftClassPickerEx(FName Label, UClass* BaseClass, TSoftClassPtr<UObject>& SoftClassPtr, bool bAllowAbstract, const FUnrealImGuiClassPickerSettings& Settings)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	auto Scope = UnrealImGuiLibrary::FClassPickerSettingsScope{ Settings };
	return UnrealImGui::ComboSoftClassPicker(TCHAR_TO_UTF8(*Label.ToString()), BaseClass, SoftClassPtr, bAllowAbstract ? CLASS_Abstract : CLASS_None, &UnrealImGuiLibrary::ClassPickerSettings);
}

bool UUnrealImGuiLibrary::ComboEnum(FName Label, uint8& EnumValue, UEnum* EnumType, int32 Flags)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	int64 Value = EnumValue;
	const bool bChanged = UnrealImGui::ComboEnum(TCHAR_TO_UTF8(*Label.ToString()), Value, EnumType, Flags);
	EnumValue = Value;
	return bChanged;
}

void UUnrealImGuiLibrary::DrawObjectDetailTable(FName Label, UObject* Object)
{
	if (!CheckImGuiContextThrowError()) { return; }
	if (Object)
	{
		UnrealImGui::DrawDetailTable(TCHAR_TO_UTF8(*Label.ToString()), Object->GetClass(), { Object });
	}
}

bool UUnrealImGuiLibrary::DrawSingleProperty(FName PropertyName, UObject* Object, FName DisplayNameOverride)
{
	if (!CheckImGuiContextThrowError()) { return false; }
	FProperty* Property = Object ? Object->GetClass()->FindPropertyByName(PropertyName) : nullptr;
	if (Property == nullptr)
	{
		return false;
	}

	bool bChanged = false;
	if (ImGui::BeginTable(TCHAR_TO_UTF8(*PropertyName.ToString()), 2))
	{
		UnrealImGui::FDetailTableContextGuard DetailTableContextGuard{ nullptr, UnrealImGui::FPostPropertyValueChanged::CreateLambda([&bChanged](const FProperty*)
		{
			bChanged = true;
		}) };
		if (DisplayNameOverride != NAME_None)
		{
			const FString DisplayName = DisplayNameOverride.ToString();
			UnrealImGui::DrawUnrealProperty(Property, { reinterpret_cast<uint8*>(Object) }, Property->GetOffset_ForInternal(), &DisplayName);
		}
		else
		{
			UnrealImGui::DrawUnrealProperty(Property, { reinterpret_cast<uint8*>(Object) }, Property->GetOffset_ForInternal());
		}
		ImGui::EndTable();
	}
	return bChanged;
}
