/**********************************************************************
* Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
********************************************************************/
#include "Material/Tools/MaterialCacheMaker/ParameterSetters/MaterialMap/MaterialMapParameterSetter.h"
#include "Material/UberMaterialParameters/RPRMaterialMap.h"
#include "Material/RPRMaterialHelpers.h"
#include "Material/MaterialContext.h"
#include "Typedefs/RPRTypedefs.h"
#include "Helpers/RPRXMaterialHelpers.h"
#include "RPRCoreModule.h"
#include "Helpers/RPRHelpers.h"

DECLARE_LOG_CATEGORY_CLASS(LogMaterialMapParameterSetter, Log, All)

namespace RPRX
{

	void FMaterialMapParameterSetter::ApplyParameterX(MaterialParameter::FArgs& SetterParameters)
	{
		const FRPRMaterialMap* materialMap = SetterParameters.GetDirectParameter<FRPRMaterialMap>();
		UE_LOG(LogRPRCore_Steps, Verbose, TEXT("[%s] %s -> Set texture : %s"),
			*SetterParameters.OwnerMaterial->GetName(),
			*SetterParameters.Property->GetName(),
			materialMap->Texture != nullptr ? *materialMap->Texture->GetName() : TEXT("None"));

		ApplyTextureParameter(SetterParameters);
	}

	bool FMaterialMapParameterSetter::ApplyTextureParameter(MaterialParameter::FArgs& SetterParameters)
	{
		RPR::FMaterialContext& materialContext = SetterParameters.MaterialContext;

		RPR::FMaterialNode materialNode = nullptr;
		RPR::FMaterialNode imageNode = nullptr;

		const FRPRMaterialMap* materialMap = SetterParameters.GetDirectParameter<FRPRMaterialMap>();
		if (materialMap->Texture != nullptr && SetterParameters.ImageManager.IsValid())
		{
			RPR::FImagePtr image;
			RPR::FResult imageNodeCreationResult = RPR::FMaterialHelpers::CreateImageNode(
				materialContext.RPRContext,
				materialContext.MaterialSystem,
				*SetterParameters.ImageManager.Get(),
				materialMap->Texture,
				GetImageType(),
				image, materialNode, imageNode
			);

			SetterParameters.Material->AddImage(image);

			if (RPR::IsResultFailed(imageNodeCreationResult))
			{
				UE_LOG(LogRPRCore, Warning, 
					TEXT("Cannot create image node texture for '%s'. Error code : %d"), 
					*SetterParameters.Property->GetName(), 
					imageNodeCreationResult);

				return (false);
			}

			ApplyUVSettings(SetterParameters, imageNode);
		}

		SetterParameters.Material->SetMaterialParameterNode(SetterParameters.GetRprxParam(), materialNode);
		return (true);
	}

	RPR::FImageManager::EImageType FMaterialMapParameterSetter::GetImageType() const
	{
		return RPR::FImageManager::EImageType::Standard;
	}

	bool FMaterialMapParameterSetter::ApplyUVSettings(MaterialParameter::FArgs& SetterParameters, RPR::FMaterialNode ImageMaterialNode)
	{

	#define SET_UV_PARAMETER(Function, ParameterName, Value) \
		status = Function(uvProjectNode, ParameterName, Value); \
		if (RPR::IsResultFailed(status)) \
		{ \
			UE_LOG(LogMaterialMapParameterSetter, Warning, TEXT("Cannot set UV data '%s' for parameter %s"), ParameterName, *SetterParameters.Property->GetName()); \
			return (false); \
		}

		const FRPRMaterialMap* materialMap = SetterParameters.GetDirectParameter<FRPRMaterialMap>();
		const FRPRMaterialMapUV& uvSettings = materialMap->UVSettings;

		RPR::FResult status;
		RPR::FMaterialNode uvProjectNode = nullptr;

		if (uvSettings.UVMode != ETextureUVMode::None)
		{
			RPR::EMaterialNodeType materialNodeType =
				(uvSettings.UVMode == ETextureUVMode::Triplanar) ? RPR::EMaterialNodeType::UVTriplanar : RPR::EMaterialNodeType::UVProcedural;

			status = RPR::FMaterialHelpers::CreateNode(SetterParameters.MaterialContext.MaterialSystem, materialNodeType, uvProjectNode);
			if (RPR::IsResultFailed(status))
			{
				UE_LOG(LogMaterialMapParameterSetter, Warning, TEXT("Cannot create UV node for parameter %s"), *SetterParameters.Property->GetName());
				return (false);
			}

			if (materialNodeType == RPR::EMaterialNodeType::UVProcedural)
			{
				SET_UV_PARAMETER(RPR::FMaterialHelpers::FMaterialNode::SetInputFloats, TEXT("origin"), FVector4(uvSettings.Origin.X, uvSettings.Origin.Y, 0, 1.0f));
				SET_UV_PARAMETER(RPR::FMaterialHelpers::FMaterialNode::SetInputFloats, TEXT("threshold"), FVector4(uvSettings.Threshold.X, uvSettings.Threshold.Y, uvSettings.Threshold.Z, 1.0f));
				SET_UV_PARAMETER(RPR::FMaterialHelpers::FMaterialNode::SetInputUInt, TEXT("uv_type"), uvSettings.GetRPRValueFromTextureUVMode());
			}
			else if (materialNodeType == RPR::EMaterialNodeType::UVTriplanar)
			{
				SET_UV_PARAMETER(RPR::FMaterialHelpers::FMaterialNode::SetInputFloats, TEXT("weight"), uvSettings.UVWeight);
				SET_UV_PARAMETER(RPR::FMaterialHelpers::FMaterialNode::SetInputFloats, TEXT("offset"), FVector4(uvSettings.Origin.X, uvSettings.Origin.Y, 0, 1.0f));
			}

			SET_UV_PARAMETER(RPR::FMaterialHelpers::FMaterialNode::SetInputFloats, TEXT("xaxis"), FVector4(uvSettings.XAxis.X, uvSettings.XAxis.Y, uvSettings.XAxis.Z, 1.0f));
			SET_UV_PARAMETER(RPR::FMaterialHelpers::FMaterialNode::SetInputFloats, TEXT("zaxis"), FVector4(uvSettings.ZAxis.X, uvSettings.ZAxis.Y, uvSettings.ZAxis.Z, 1.0f));
			SET_UV_PARAMETER(RPR::FMaterialHelpers::FMaterialNode::SetInputFloats, TEXT("uv_scale"), uvSettings.Scale);
		}

		FString uvInputDataName = (uvSettings.UVChannel == 0 ? TEXT("uv") : TEXT("uv2"));

		RPR::EMaterialNodeType materialNodeType;
		status = RPR::RPRMaterial::GetNodeInfo(ImageMaterialNode, RPR::EMaterialNodeInfo::Type, &materialNodeType);
		check(materialNodeType == RPR::EMaterialNodeType::ImageTexture);

		status = RPR::FMaterialHelpers::FMaterialNode::SetInputNode(ImageMaterialNode, *uvInputDataName, uvProjectNode);
		if (RPR::IsResultFailed(status))
		{
			UE_LOG(LogMaterialMapParameterSetter, Warning, TEXT("Cannot bind UV node to image node for parameter %s"), *SetterParameters.Property->GetName());
			return (false);
		}

		return (true);

	#undef SET_UV_PARAMETER
	}

}
