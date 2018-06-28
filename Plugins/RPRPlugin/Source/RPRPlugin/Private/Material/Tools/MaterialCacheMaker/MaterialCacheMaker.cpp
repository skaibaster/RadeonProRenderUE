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
#include "MaterialCacheMaker.h"
#include "RPRHelpers.h"
#include "RPRMaterialHelpers.h"
#include "Factory/ParameterFactory.h"
#include "RPRXMaterialHelpers.h"

namespace RPRX
{

	FMaterialCacheMaker::FMaterialCacheMaker(RPR::FMaterialContext& InMaterialContext, const URPRMaterial* InRPRMaterial, RPR::FImageManagerPtr InImageManager)
		: MaterialContext(InMaterialContext)
		, RPRMaterial(InRPRMaterial)
		, ImageManager(InImageManager)
	{}

	bool FMaterialCacheMaker::CacheUberMaterial(RPRX::FMaterial& OutMaterial)
	{
		return 
			RPR::IsResultSuccess(RPRX::FMaterialHelpers::CreateMaterial(MaterialContext.RPRXContext, EMaterialType::Uber, OutMaterial)) && 
			UpdateUberMaterial(OutMaterial);
	}

	bool	FMaterialCacheMaker::UpdateUberMaterial(RPRX::FMaterial& InOutMaterial)
	{
		return RPR::IsResultSuccess(
			BrowseUberMaterialParameters(
				FUberMaterialParametersPropertyVisitor::CreateRaw(this, &FMaterialCacheMaker::ApplyUberMaterialParameter),
				InOutMaterial
			));
	}

	RPR::FResult FMaterialCacheMaker::BrowseUberMaterialParameters(FUberMaterialParametersPropertyVisitor Visitor, 
																				FMaterial& OutMaterial)
	{
		const FRPRUberMaterialParameters& uberMaterialParameters = RPRMaterial->MaterialParameters;
		UScriptStruct* parametersStruct = FRPRUberMaterialParameters::StaticStruct();
		RPR::FResult result = RPR_SUCCESS;

		UProperty* currentProperty = parametersStruct->PropertyLink;
		while (currentProperty != nullptr)
		{
			result = Visitor.Execute(uberMaterialParameters, parametersStruct, currentProperty, OutMaterial);
			if (RPR::IsResultFailed(result))
			{
				return (result);
			}

			currentProperty = currentProperty->PropertyLinkNext;
		}
		return (result);
	}

	RPR::FResult FMaterialCacheMaker::ApplyUberMaterialParameter(const FRPRUberMaterialParameters& InParameters,
																			UScriptStruct* InParametersStruct,
																			UProperty* InParameterProperty,
																			FMaterial& InOutMaterial)
	{
		RPR::FResult result = RPR_SUCCESS;

		RPRX::MaterialParameter::FArgs materialCacheParametersSetterArgs(
			InParameters,
			InParameterProperty,
			ImageManager,
			MaterialContext,
			InOutMaterial
		);

		if (materialCacheParametersSetterArgs.CanUseParam())
		{
			TSharedPtr<RPRX::IMaterialParameter> mapSetter =
				RPRX::MaterialParameter::FFactory::Create(InParameterProperty);

			if (mapSetter.IsValid())
			{
				mapSetter->ApplyParameterX(materialCacheParametersSetterArgs);
			}
		}

		return (result);
	}
}
