﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealImGuiTypes.h"
#include "UnrealImGuiViewportExtent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealImGuiViewportContextLibrary.generated.h"


UCLASS(meta = (ScriptMixin = FUnrealImGuiViewportContext))
class UUnrealImGuiViewportContextLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static FBox GetViewBounds3D(const FUnrealImGuiViewportContext& Context)
	{
		return Context.GetViewBounds3D();
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static FVector2D GetScreenCenter(const FUnrealImGuiViewportContext& Context)
	{
		return Context.GetScreenCenter();
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static FVector2D WorldToContentLocation(const FUnrealImGuiViewportContext& Context, const FVector2D& Location)
	{
		return Context.WorldToContentLocation(Location);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static FVector2D WorldToScreenLocation(const FUnrealImGuiViewportContext& Context, const FVector2D& Location)
	{
		return Context.WorldToScreenLocation(Location);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static FVector2D ContentToWorldLocation(const FUnrealImGuiViewportContext& Context, const FVector2D& Location)
	{
		return Context.ContentToWorldLocation(Location);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static FVector2D ScreenToWorldLocation(const FUnrealImGuiViewportContext& Context, const FVector2D& Location)
	{
		return Context.ScreenToWorldLocation(Location);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static FVector2D AddScreenOffset(const FUnrealImGuiViewportContext& Context, const FVector2D& Location, const FVector2D& ScreenOffset)
	{
		return Context.AddScreenOffset(Location, ScreenOffset);
	}
	
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawLine(const FUnrealImGuiViewportContext& Context, const FVector2D& Start, const FVector2D& End, const FColor& Color, float Thickness = 1.f)
	{
		Context.DrawLine(Start, End, Color, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawLine(const FUnrealImGuiViewportContext& Context, const FVector2f& Start, const FVector2f& End, const FColor& Color, float Thickness = 1.f)
	{
		Context.FDrawLine(Start, End, Color, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawDashedLine(const FUnrealImGuiViewportContext& Context, const FVector2D& Start, const FVector2D& End, const FColor& Color, float DashSize = 100.f, float Thickness = 1.f)
	{
		Context.DrawDashedLine(Start, End, Color, DashSize, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawDashedLine(const FUnrealImGuiViewportContext& Context, const FVector2f& Start, const FVector2f& End, const FColor& Color, float DashSize = 100.f, float Thickness = 1.f)
	{
		Context.FDrawDashedLine(Start, End, Color, DashSize, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawArc(const FUnrealImGuiViewportContext& Context, const FVector2D& Center, float MinAngle, float MaxAngle, double Radius, const FColor& Color, int NumSegments = 0, float Thickness = 1.f)
	{
		Context.DrawArc(Center, MinAngle, MaxAngle, Radius, Color, NumSegments, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawArc(const FUnrealImGuiViewportContext& Context, const FVector2f& Center, float MinAngle, float MaxAngle, double Radius, const FColor& Color, int NumSegments = 0, float Thickness = 1.f)
	{
		Context.FDrawArc(Center, MinAngle, MaxAngle, Radius, Color, NumSegments, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawArrow(const FUnrealImGuiViewportContext& Context, const FVector2D& Start, const FVector2D& End, const FColor& Color, float ArrowSize = 12.f, float Thickness = 1.f)
	{
		Context.DrawArrow(Start, End, Color, ArrowSize, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawArrow(const FUnrealImGuiViewportContext& Context, const FVector2f& Start, const FVector2f& End, const FColor& Color, float ArrowSize = 12.f, float Thickness = 1.f)
	{
		Context.FDrawArrow(Start, End, Color, ArrowSize, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawTriangle(const FUnrealImGuiViewportContext& Context, const FVector2D& A, const FVector2D& B, const FVector2D& C, const FColor& Color, float Thickness = 1.f)
	{
		Context.DrawTriangle(A, B, C, Color, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawTriangle(const FUnrealImGuiViewportContext& Context, const FVector2f& A, const FVector2f& B, const FVector2f& C, const FColor& Color, float Thickness = 1.f)
	{
		Context.FDrawTriangle(A, B, C, Color, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawTriangleFilled(const FUnrealImGuiViewportContext& Context, const FVector2D& A, const FVector2D& B, const FVector2D& C, const FColor& Color)
	{
		Context.DrawTriangleFilled(A, B, C, Color);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawTriangleFilled(const FUnrealImGuiViewportContext& Context, const FVector2f& A, const FVector2f& B, const FVector2f& C, const FColor& Color)
	{
		Context.FDrawTriangleFilled(A, B, C, Color);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawCircle(const FUnrealImGuiViewportContext& Context, const FVector2D& Center, float Radius, const FColor& Color, int NumSegments = 0, float Thickness = 1.f)
	{
		Context.DrawCircle(Center, Radius, Color, NumSegments, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawCircle(const FUnrealImGuiViewportContext& Context, const FVector2f& Center, float Radius, const FColor& Color, int NumSegments = 0, float Thickness = 1.f)
	{
		Context.FDrawCircle(Center, Radius, Color, NumSegments, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawCircleFilled(const FUnrealImGuiViewportContext& Context, const FVector2D& Center, float Radius, const FColor& Color, int NumSegments = 0)
	{
		Context.DrawCircleFilled(Center, Radius, Color, NumSegments);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawCircleFilled(const FUnrealImGuiViewportContext& Context, const FVector2f& Center, float Radius, const FColor& Color, int NumSegments = 0)
	{
		Context.FDrawCircleFilled(Center, Radius, Color, NumSegments);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawCapsule(const FUnrealImGuiViewportContext& Context, const FVector2D& A, const FVector2D& B, float Radius, const FColor& Color, int NumSegments = 0, float Thickness = 1.f)
	{
		Context.DrawCapsule(A, B, Radius, Color, NumSegments, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawCapsule(const FUnrealImGuiViewportContext& Context, const FVector2f& A, const FVector2f& B, float Radius, const FColor& Color, int NumSegments = 0, float Thickness = 1.f)
	{
		Context.FDrawCapsule(A, B, Radius, Color, NumSegments, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawCapsuleFilled(const FUnrealImGuiViewportContext& Context, const FVector2D& A, const FVector2D& B, float Radius, const FColor& Color, int NumSegments = 0)
	{
		Context.DrawCapsuleFilled(A, B, Radius, Color, NumSegments);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawCapsuleFilled(const FUnrealImGuiViewportContext& Context, const FVector2f& A, const FVector2f& B, float Radius, const FColor& Color, int NumSegments = 0)
	{
		Context.FDrawCapsuleFilled(A, B, Radius, Color, NumSegments);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawTaperedCapsule(const FUnrealImGuiViewportContext& Context, const FVector2D& A, const FVector2D& B, float RadiusA, float RadiusB, const FColor& Color, int NumSegments = 0, float Thickness = 1.f)
	{
		Context.DrawTaperedCapsule(A, B, RadiusA, RadiusB, Color, NumSegments, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawTaperedCapsule(const FUnrealImGuiViewportContext& Context, const FVector2f& A, const FVector2f& B, float RadiusA, float RadiusB, const FColor& Color, int NumSegments = 0, float Thickness = 1.f)
	{
		Context.FDrawTaperedCapsule(A, B, RadiusA, RadiusB, Color, NumSegments, Thickness);
	}
	static void DrawTaperedCapsuleFilled(const FUnrealImGuiViewportContext& Context, const FVector2D& A, const FVector2D& B, float RadiusA, float RadiusB, const FColor& Color, int NumSegments = 0)
	{
		Context.DrawTaperedCapsuleFilled(A, B, RadiusA, RadiusB, Color, NumSegments);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawTaperedCapsuleFilled(const FUnrealImGuiViewportContext& Context, const FVector2f& A, const FVector2f& B, float RadiusA, float RadiusB, const FColor& Color, int NumSegments = 0)
	{
		Context.FDrawTaperedCapsuleFilled(A, B, RadiusA, RadiusB, Color, NumSegments);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawRect(const FUnrealImGuiViewportContext& Context, const FBox2D& Box, const FColor& Color, float Rounding = 0.f, float Thickness = 1.f)
	{
		Context.DrawRect(Box, Color, Rounding, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawRect(const FUnrealImGuiViewportContext& Context, const FBox2f& Box, const FColor& Color, float Rounding = 0.f, float Thickness = 1.f)
	{
		Context.FDrawRect(Box, Color, Rounding, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawRectFilled(const FUnrealImGuiViewportContext& Context, const FBox2D& Box, const FColor& Color, float Rounding = 0.f)
	{
		Context.DrawRectFilled(Box, Color, Rounding);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawRectFilled(const FUnrealImGuiViewportContext& Context, const FBox2f& Box, const FColor& Color, float Rounding = 0.f)
	{
		Context.FDrawRectFilled(Box, Color, Rounding);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawQuad(const FUnrealImGuiViewportContext& Context, const FVector2D& P1, const FVector2D& P2, const FVector2D& P3, const FVector2D& P4, const FColor& Color, float Thickness = 1.f)
	{
		Context.DrawQuad(P1, P2, P3, P4, Color, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawQuad(const FUnrealImGuiViewportContext& Context, const FVector2f& P1, const FVector2f& P2, const FVector2f& P3, const FVector2f& P4, const FColor& Color, float Thickness = 1.f)
	{
		Context.FDrawQuad(P1, P2, P3, P4, Color, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawQuadFilled(const FUnrealImGuiViewportContext& Context, const FVector2D& P1, const FVector2D& P2, const FVector2D& P3, const FVector2D& P4, const FColor& Color)
	{
		Context.DrawQuadFilled(P1, P2, P3, P4, Color);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawQuadFilled(const FUnrealImGuiViewportContext& Context, const FVector2f& P1, const FVector2f& P2, const FVector2f& P3, const FVector2f& P4, const FColor& Color)
	{
		Context.FDrawQuadFilled(P1, P2, P3, P4, Color);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawCoordinateSystem(const FUnrealImGuiViewportContext& Context, const FTransform& Transform, float Scale = 100.f, float Thickness = 1.f)
	{
		Context.DrawCoordinateSystem(Transform, Scale, Thickness);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawTexture(const FUnrealImGuiViewportContext& Context, const FVector2D& Location, EImGuiTextureFormat TextureFormat, FVector2D Size, UTexture* Texture, const FColor& Color = FColor::White, FVector2D UV_Min = FVector2D::ZeroVector, FVector2D UV_Max = FVector2D::UnitVector)
	{
		Context.DrawTexture(Location, static_cast<UnrealImGui::ETextureFormat>(TextureFormat), Texture, Size, Color, UV_Min, UV_Max);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void DrawText(const FUnrealImGuiViewportContext& Context, const FVector2D& Location, const FString& Text, const FColor& Color)
	{
		Context.DrawText(Location, Text, Color);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void FDrawText(const FUnrealImGuiViewportContext& Context, const FVector2f& Location, const FString& Text, const FColor& Color)
	{
		Context.FDrawText(Location, Text, Color);
	}
	UFUNCTION(BlueprintCallable, Category = ImGui)
	static void AddMessageText(const FUnrealImGuiViewportContext& Context, const FString& Message, const FColor& Color = FColor::White)
	{
		Context.AddMessageText(Message, Color);
	}
};
