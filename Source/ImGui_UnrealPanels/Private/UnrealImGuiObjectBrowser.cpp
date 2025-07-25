// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealImGuiObjectBrowser.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_notify.h"
#include "ImGuiDelegates.h"
#include "ImGuiEx.h"
#include "UnrealImGuiPropertyDetails.h"
#include "UObject/Package.h"

UUnrealImGuiObjectBrowserPanel::UUnrealImGuiObjectBrowserPanel()
	: bDisplayAllProperties(true)
	, bEnableEditVisibleProperty(false)
{
	DefaultState = { false, true };
	Title = TEXT("Object Browser");
	Categories = { TEXT("Tools") };
}

void UUnrealImGuiObjectBrowserPanel::Register(UObject* Owner, UUnrealImGuiPanelBuilder* Builder)
{
	Super::Register(Owner, Builder);

	FImGuiDelegates::OnImGuiContextDestroyed.AddUObject(this, &ThisClass::WhenImGuiContextDestroyed);
}

void UUnrealImGuiObjectBrowserPanel::Unregister(UObject* Owner, UUnrealImGuiPanelBuilder* Builder)
{
	FImGuiDelegates::OnImGuiContextDestroyed.RemoveAll(this);

	Super::Unregister(Owner, Builder);
}

void UUnrealImGuiObjectBrowserPanel::Draw(UObject* Owner, UUnrealImGuiPanelBuilder* Builder, float DeltaSeconds)
{
	if (ImGui::FChildWindow ChildWindow{ "ObjectPathViewer", { 0.f, ImGui::GetFrameHeightWithSpacing() + ImGui::GetStyle().ScrollbarSize }, false, ImGuiWindowFlags_AlwaysHorizontalScrollbar })
	{
		if (ImGui::Button("Root"))
		{
			SelectedObject = nullptr;
		}
		if (SelectedObject)
		{
			TArray<UObject*, TInlineAllocator<16>> Outers;
			for (UObject* TestObject = SelectedObject; TestObject; TestObject = TestObject->GetOuter())
			{
				Outers.Add(TestObject);
			}

			for (int32 Idx = Outers.Num() - 1; Idx >= 0; --Idx)
			{
				ImGui::SameLine();
				ImGui::Text(">");

				ImGui::SameLine();
				UObject* Object = Outers[Idx];
				if (ImGui::Button(TCHAR_TO_UTF8(*Object->GetName())))
				{
					SelectedObject = Object;
				}
			}
		}
	}

	const ImGuiWindowClass* WindowClass = &ImGui::GetCurrentWindowRead()->WindowClass;
	uint32& DockSpaceId = DockSpaceIdMap.FindOrAdd(ImGui::GetCurrentContext(), INDEX_NONE);
	if (DockSpaceId == INDEX_NONE)
	{
		DockSpaceId = ImGui::GetID("ObjectBrowser");
		const ImGuiID DockId = ImGui::DockBuilderAddNode(DockSpaceId, ImGuiDockNodeFlags_AutoHideTabBar);
		ImGuiID RemainAreaId;
		const ImGuiID ViewportId = ImGui::DockBuilderSplitNode(DockSpaceId, ImGuiDir_Left, 0.5f, nullptr, &RemainAreaId);
		ImGui::DockBuilderDockWindow("ObjectBrowserContent", ViewportId);
		ImGui::DockBuilderDockWindow("ObjectBrowserDetails", RemainAreaId);
		ImGui::DockBuilderFinish(DockId);
	}
	ImGui::DockSpace(DockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_AutoHideTabBar, WindowClass);
	
	ImGui::SetNextWindowClass(WindowClass);
	if (ImGui::FWindow Window{ "ObjectBrowserContent" })
	{
		static FString FilterString;
		const bool bInvokeSearch = ImGui::InputTextWithHint("##Filter", "Filter (Input full path then press Enter to search object)", FilterString, ImGuiInputTextFlags_EnterReturnsTrue);
		if (bInvokeSearch && ImGui::IsItemDeactivatedAfterEdit())
		{
			SelectedObject = FindObject<UObject>(nullptr, *FilterString);
			if (SelectedObject == nullptr)
			{
				SelectedObject = LoadObject<UObject>(nullptr, *FilterString);
				if (SelectedObject)
				{
					ImGui::InsertNotification(ImGuiToastType_Info, "load \"%s\" object", *FilterString);
				}
				else
				{
					ImGui::InsertNotification(ImGuiToastType_Error, "\"%s\" object not find", *FilterString);
				}
			}
			FilterString.Empty();
		}
		TArray<UObject*> DisplayObjects;
		int32 AllObjectCount = 0;
		{
			if (SelectedObject == nullptr)
			{
				GetObjectsOfClass(UPackage::StaticClass(), DisplayObjects);
				AllObjectCount = DisplayObjects.Num();
				if (FilterString.Len() > 0)
				{
					DisplayObjects.RemoveAllSwap([](const UObject* E){ return E->GetName().Contains(FilterString) == false; });
				}
			}
			else
			{
				ForEachObjectWithOuter(SelectedObject, [&](UObject* SubObject)
				{
					AllObjectCount += 1;
					if (FilterString.Len() > 0 && SubObject->GetName().Contains(FilterString) == false)
					{
						return;
					}
					DisplayObjects.Add(SubObject);
				}, false);
			}
		}
		ImGui::SameLine();
		ImGui::Text("Filter %d | Total %d", AllObjectCount, DisplayObjects.Num());
		ImGui::Separator();
		
		constexpr ImGuiTableFlags OutlinerTableFlags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable |
			ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_ScrollY;

		if (ImGui::FTable Table{ "ContentTable", 1, OutlinerTableFlags })
		{
			ImGuiListClipper ListClipper{};
			ListClipper.Begin(DisplayObjects.Num());
			while (ListClipper.Step())
			{
				for (int32 Idx = ListClipper.DisplayStart; Idx < ListClipper.DisplayEnd; ++Idx)
				{
					ImGui::TableNextColumn();
					UObject* Object = DisplayObjects[Idx];
					if (ImGui::Selectable(TCHAR_TO_UTF8(*Object->GetName())))
					{
						SelectedObject = Object;
						FilterString.Empty();
					}
					if (ImGui::FItemTooltip ItemTooltip{})
					{
						ImGui::TextUnformatted(TCHAR_TO_UTF8(*FString::Printf(TEXT("Class: %s"), *Object->GetClass()->GetName())));
						ImGui::Text("InPackage: %s", Object->HasAnyFlags(RF_Load) ? "true" : "false");
					}
				}
			}
		}
	}

	ImGui::SetNextWindowClass(WindowClass);
	if (ImGui::FWindow Window{ "ObjectBrowserDetails", nullptr, ImGuiWindowFlags_MenuBar })
	{
		if (ImGui::FMenuBar MenuBar{})
		{
			if (ImGui::FMenu Menu{ "Detail Settings" })
			{
				{
					bool Value = bDisplayAllProperties;
					if (ImGui::Checkbox("Display All Properties", &Value))
					{
						bDisplayAllProperties = Value;
						Owner->SaveConfig();
					}
				}
				{
					bool Value = bEnableEditVisibleProperty;
					if (ImGui::Checkbox("Enable Edit Visible Property", &Value))
					{
						bEnableEditVisibleProperty = Value;
						Owner->SaveConfig();
					}
				}
			}
		}
		static UnrealImGui::FDetailsFilter DetailsFilter;
		DetailsFilter.Draw();
		if (SelectedObject)
		{
			ImGui::TextUnformatted(TCHAR_TO_UTF8(*SelectedObject->GetName()));
			TGuardValue<bool> GDisplayAllPropertiesGuard(UnrealImGui::GlobalValue::GDisplayAllProperties, bDisplayAllProperties);
			TGuardValue<bool> GEnableEditVisiblePropertyGuard(UnrealImGui::GlobalValue::GEnableEditVisibleProperty, bEnableEditVisibleProperty);
			UnrealImGui::DrawDetailTable("Details", SelectedObject->GetClass(), { SelectedObject }, &DetailsFilter);
		}
		else
		{
			ImGui::Text("Not select object");
		}
	}
}

void UUnrealImGuiObjectBrowserPanel::WhenImGuiContextDestroyed(ImGuiContext* Context)
{
	DockSpaceIdMap.Remove(Context);
}
