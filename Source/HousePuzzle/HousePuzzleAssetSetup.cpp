#include "HousePuzzleAssetSetup.h"

#include "Curves/CurveFloat.h"

#if WITH_EDITOR
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"
#endif

namespace
{
	void ConfigurePhotoFlipCurve(UCurveFloat* Curve)
	{
		if (!Curve)
		{
			return;
		}

		Curve->FloatCurve.Reset();
		Curve->FloatCurve.AddKey(0.f, 0.f);
		Curve->FloatCurve.AddKey(0.5f, 1.f);
		Curve->FloatCurve.AddKey(1.f, 1.f);

		for (FRichCurveKey& Key : Curve->FloatCurve.Keys)
		{
			Key.InterpMode = RCIM_Cubic;
			Key.TangentMode = RCTM_Auto;
		}
	}
}

UCurveFloat* UHousePuzzleAssetSetup::EnsurePhotoFlipCurveAsset()
{
#if WITH_EDITOR
	const TCHAR* AssetPath = TEXT("/Game/Curves/Curve_PhotoFlip.Curve_PhotoFlip");
	UCurveFloat* Curve = LoadObject<UCurveFloat>(nullptr, AssetPath);

	if (!Curve)
	{
		UPackage* Package = CreatePackage(TEXT("/Game/Curves/Curve_PhotoFlip"));
		Curve = NewObject<UCurveFloat>(Package, TEXT("Curve_PhotoFlip"), RF_Public | RF_Standalone);
	}

	ConfigurePhotoFlipCurve(Curve);
	Curve->MarkPackageDirty();

	const FString PackageFileName = FPackageName::LongPackageNameToFilename(
		Curve->GetOutermost()->GetName(),
		FPackageName::GetAssetPackageExtension());

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.SaveFlags = SAVE_NoError;

	if (UPackage::SavePackage(Curve->GetOutermost(), Curve, *PackageFileName, SaveArgs))
	{
		FAssetRegistryModule::AssetCreated(Curve);
		return Curve;
	}

	return nullptr;
#else
	return nullptr;
#endif
}
