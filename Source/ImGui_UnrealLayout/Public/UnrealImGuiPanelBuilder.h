// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealImGuiPanelBuilder.generated.h"

struct FStreamableHandle;
class UUnrealImGuiPanelBase;
class UUnrealImGuiLayoutBase;

UCLASS(Config = GameUserSettings, PerObjectConfig)
class IMGUI_UNREALLAYOUT_API UUnrealImGuiPanelBuilder : public UObject
{
	GENERATED_BODY()

	template<bool bReenter>
	void ConstructPanels(UObject* Owner);
public:
	// Layout name
	FName DockSpaceName = NAME_None;

	void Register(UObject* Owner);
	void Unregister(UObject* Owner);

	void LoadDefaultLayout(UObject* Owner);
	void DrawPanels(UObject* Owner, float DeltaSeconds);

	void DrawPanelStateMenu(UObject* Owner);
	void DrawLayoutStateMenu(UObject* Owner);

#if WITH_EDITOR
	void ReconstructPanels_Editor(UObject* Owner);
#endif

	UFUNCTION(BlueprintCallable, Category = ImGui, meta = (DeterminesOutputType = PanelType))
	UUnrealImGuiPanelBase* FindPanel(const TSubclassOf<UUnrealImGuiPanelBase>& PanelType) const;
	template<typename T>
	T* FindPanel() const
	{
		static_assert(TIsDerivedFrom<T, UUnrealImGuiPanelBase>::Value);
		return (T*)FindPanel(T::StaticClass());
	}

	UPROPERTY(Transient)
	TArray<TObjectPtr<UUnrealImGuiLayoutBase>> Layouts;
	int32 ActiveLayoutIndex = 0;
	UUnrealImGuiLayoutBase* GetActiveLayout() const { return Layouts[ActiveLayoutIndex]; }
	UPROPERTY(Config)
	TSoftClassPtr<UUnrealImGuiLayoutBase> ActiveLayoutClass;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UUnrealImGuiPanelBase>> Panels;
	struct FCategoryPanels
	{
		FCategoryPanels(const FName& Category)
			: Category{ Category }
		{}

		FName Category;
		TArray<UUnrealImGuiPanelBase*> Panels;
		TMap<FName, TUniquePtr<FCategoryPanels>> Children;
	};
	FCategoryPanels CategoryPanels{ NAME_None };

	const auto& GetPanelsMap() const { return PanelsMap; }
private:
	TSharedPtr<FStreamableHandle> StreamableHandle;

	TMap<const UClass*, UUnrealImGuiPanelBase*> PanelsMap;
};
