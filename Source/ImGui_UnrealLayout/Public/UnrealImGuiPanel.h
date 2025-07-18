﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UnrealImGuiPanel.generated.h"

class UUnrealImGuiLayoutBase;

USTRUCT()
struct FImGuiDefaultPanelState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bOpen{ false };
	UPROPERTY(EditAnywhere, Category = Settings)
	bool bEnableDock{ true };
};

USTRUCT()
struct FImGuiDefaultDockLayout : public FImGuiDefaultPanelState
{
	GENERATED_BODY()

	FImGuiDefaultDockLayout() = default;
	FImGuiDefaultDockLayout(int32 DockId)
		: FImGuiDefaultDockLayout(DockId, true)
	{}
	FImGuiDefaultDockLayout(int32 DockId, bool bOpen, bool bEnableDock = true)
		: FImGuiDefaultPanelState{ bOpen, bEnableDock }
		, DockId(DockId)
	{}
	FImGuiDefaultDockLayout(int32 DockId, const FImGuiDefaultPanelState& DefaultPanelState)
		: FImGuiDefaultPanelState{ DefaultPanelState }
		, DockId(DockId)
	{}

	UPROPERTY(EditAnywhere, Category = Settings)
	int32 DockId = 0;
};

UCLASS(Abstract, Config = GameUserSettings, PerObjectConfig, Blueprintable)
class IMGUI_UNREALLAYOUT_API UUnrealImGuiPanelBase : public UObject
{
	GENERATED_BODY()

public:
	UUnrealImGuiPanelBase();

#if WITH_EDITOR
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCDOConstruct_Editor, const UUnrealImGuiPanelBase*);
	static FOnCDOConstruct_Editor OnCDOConstruct_Editor;

	void PostCDOContruct() override;
#endif

	UPROPERTY(EditDefaultsOnly, meta = (Bitmask, BitmaskEnum = "/Script/ImGui.EImGuiWindowFlags"), Category = Settings)
	int32 ImGuiWindowFlags;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FName Title;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TArray<FName> Categories;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FImGuiDefaultPanelState DefaultState{ false, true };
	// Key is type name
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TMap<FName, FImGuiDefaultDockLayout> DefaultDockSpace;

	bool IsOpenedInLayout() const { return ConfigObjectPrivate->bIsOpen; }
	bool IsOpenedInLocal() const { return LocalOpenCounter > 0; }

	bool IsOpened() const { return IsOpenedInLayout() || IsOpenedInLocal(); }
	void SetOpenState(bool bOpen);
	FString GetLayoutPanelName(const FString& LayoutName) const { return FString::Printf(TEXT("%s##%s_%s"), *Title.ToString(), *GetClass()->GetName(), *LayoutName); }

	void LocalPanelOpened();
	void LocalPanelClosed();

	void SaveConfig() { Super::SaveConfig(CPF_Config, nullptr, GConfig, false); }
	UFUNCTION(BlueprintCallable, Category = ImGui)
	void SaveImGuiConfig() { ConfigObjectPrivate->SaveConfig(); }

	template<typename T>
	T* GetConfigObject() const { return CastChecked<T>(ConfigObjectPrivate); }
private:
	void InitialConfigObject();

	friend class UUnrealImGuiPanelBuilder;
	friend class UUnrealImGuiLayoutBase;

	uint8 bIsOpen : 1 { false };
	uint8 LocalOpenCounter : 7 { 0 };
	UPROPERTY(Config)
	TMap<FName, bool> PanelOpenState;

	UPROPERTY(Transient)
	TObjectPtr<UUnrealImGuiPanelBase> ConfigObjectPrivate;
public:
	struct FScriptExecutionGuard
	{
		FScriptExecutionGuard(const UUnrealImGuiPanelBase* Panel);
		TOptional<FEditorScriptExecutionGuard> EditorScriptExecutionGuard;
	};
	
	virtual bool ShouldCreatePanel(UObject* Owner) const { FScriptExecutionGuard ScriptExecutionGuard{ this }; return ReceiveShouldCreatePanel(Owner); }

	virtual void Register(UObject* Owner, UUnrealImGuiPanelBuilder* Builder) { FScriptExecutionGuard ScriptExecutionGuard{ this }; ReceiveRegister(Owner, Builder); }
	virtual void Unregister(UObject* Owner, UUnrealImGuiPanelBuilder* Builder) { FScriptExecutionGuard ScriptExecutionGuard{ this }; ReceiveUnregister(Owner, Builder); }

	virtual void WhenOpen(UObject* Owner, UUnrealImGuiPanelBuilder* Builder) { FScriptExecutionGuard ScriptExecutionGuard{ this }; ReceiveWhenOpen(Owner, Builder); }
	virtual void WhenClose(UObject* Owner, UUnrealImGuiPanelBuilder* Builder) { FScriptExecutionGuard ScriptExecutionGuard{ this }; ReceiveWhenClose(Owner, Builder); }
	
	virtual void Draw(UObject* Owner, UUnrealImGuiPanelBuilder* Builder, float DeltaSeconds) { FScriptExecutionGuard ScriptExecutionGuard{ this }; ReceiveDraw(Owner, Builder, DeltaSeconds); }
	virtual void DrawWindow(UUnrealImGuiLayoutBase* Layout, UObject* Owner, UUnrealImGuiPanelBuilder* Builder, float DeltaSeconds, bool& bOpen);
protected:
	UFUNCTION(BlueprintNativeEvent)
	bool ReceiveShouldCreatePanel(UObject* Owner) const;
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveRegister(UObject* Owner, UUnrealImGuiPanelBuilder* Builder);
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveUnregister(UObject* Owner, UUnrealImGuiPanelBuilder* Builder);
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveWhenOpen(UObject* Owner, UUnrealImGuiPanelBuilder* Builder);
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveWhenClose(UObject* Owner, UUnrealImGuiPanelBuilder* Builder);
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveDraw(UObject* Owner, UUnrealImGuiPanelBuilder* Builder, float DeltaSeconds);
};

UCLASS(Abstract, Config = GameUserSettings, Blueprintable)
class IMGUI_UNREALLAYOUT_API UUnrealImGuiPanelGlobalConfig : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = ImGui)
	void SaveImGuiConfig() { SaveConfig(); }
private:
	// parent class must have more than one config property, otherwise save config not work.
	UPROPERTY(Config)
	bool DummyConfigValue = false;
};
