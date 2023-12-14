#pragma once

#include "CoreMinimal.h"

class ACTIONASSETPLUGIN_API FActionAssetPluginStyle
{
public:
	static TSharedRef<FActionAssetPluginStyle> Get();
	static void Shutdown();

private:
	static TSharedPtr<FActionAssetPluginStyle> Instance;

public:
	FActionAssetPluginStyle();
	~FActionAssetPluginStyle();

private:
	void RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon);

private:
	static const FName StyleSetName;

private:
	TSharedPtr<class FSlateStyleSet> StyleSet;

public:
	FSlateIcon ToolBar_Icon;

	TSharedPtr<struct FSlateBrush> Array_Image;

public:
	const FVector2D DesiredWidth = FVector2D(250, 1000);
};
