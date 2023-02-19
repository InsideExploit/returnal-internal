#pragma once

struct UKismetSystemLibrary : public UObject
{
	static UKismetSystemLibrary* Instance()
	{
		static UObject* klass = nullptr;
		if (!klass)
			klass = UObject::StaticFindObject(L"Engine.KismetSystemLibrary");

		return (UKismetSystemLibrary*)klass;
	}

	FString GetObjectName(UObject* Object)
	{
		static UObject* fn = nullptr;
		if (!fn)
			fn = UObject::StaticFindObject(L"Engine.KismetSystemLibrary.GetObjectName");

		struct {
			UObject* Object;
			FString ReturnValue;
		} parms = { Object };

		this->ProcessEvent(fn, &parms);
		return parms.ReturnValue;
	}
};

struct UCanvas : public UObject
{
	FVector2D Size()
	{
		return *(FVector2D*)((uint64_t)this + 0x40);
	}

	void K2_DrawText(UObject* RenderFont, FString RenderText, FVector2D ScreenPosition, FLinearColor Color = FLinearColor{1.f, 1.f, 1.f, 1.f})
	{
		static UObject* fn = nullptr;
		if (!fn)
			fn = UObject::StaticFindObject(L"Engine.Canvas.K2_DrawText");

		struct {
			UObject* RenderFont;
			FString RenderText;
			FVector2D ScreenPosition;
			FVector2D Scale;
			FLinearColor RenderColor;
			float Kerning;
			FLinearColor ShadowColor;
			FVector2D ShadowOffset;
			bool bCentreX;
			bool bCentreY;
			bool bOutlined;
			FLinearColor OutlineColor;
		} parms = { RenderFont, RenderText, ScreenPosition, FVector2D{ 1.0f, 1.0f }, Color, 1.0f, FLinearColor{ 0.f, 0.f, 0.f, 1.f }, FVector2D{ 0, 0 }, true, true, true, FLinearColor{ 0.2f, 0.2f, 1.f, 1.f } };

		this->ProcessEvent(fn, &parms);
	}

	void K2_DrawLine(FVector2D ScreenPositionA, FVector2D ScreenPositionB, float Thickness = 1.f, FLinearColor RenderColor = { 255, 255, 255, 255 })
	{
		static UObject* fn = nullptr;
		if (!fn)
			fn = UObject::StaticFindObject(L"Engine.Canvas.K2_DrawLine");

		struct {
			FVector2D ScreenPositionA;
			FVector2D ScreenPositionB;
			float Thickness;
			FLinearColor RenderColor;
		} parms = { ScreenPositionA, ScreenPositionB, Thickness, RenderColor };

		this->ProcessEvent(fn, &parms);
	}
};

struct APlayerController : public UObject
{
	FVector2D ProjectWorldLocationToScreen(FVector WorldLocation)
	{
		static UObject* fn = nullptr;
		if (!fn)
			fn = UObject::StaticFindObject(L"Engine.PlayerController.ProjectWorldLocationToScreen");

		struct {
			FVector WorldLocation;
			FVector2D ScreenLocation;
			bool bPlayerViewportRelative;
			bool ReturnValue;
		} parms = { WorldLocation };

		this->ProcessEvent(fn, &parms);
		return parms.ScreenLocation;
	}
};