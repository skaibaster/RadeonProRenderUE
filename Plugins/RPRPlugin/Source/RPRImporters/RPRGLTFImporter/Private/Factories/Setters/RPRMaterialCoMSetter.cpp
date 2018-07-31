#include "Factories/Setters/RPRMaterialCoMSetter.h"
#include "Helpers/RPRXMaterialHelpers.h"
#include "Helpers/RPRHelpers.h"

bool RPR::GLTF::Importer::FRPRMaterialCoMSetter::SetParameterValue(
	FSerializationContext& SerializationCtx, 
	FRPRUberMaterialParameterBase* UberParameter, 
	RPRX::EMaterialParameterType ParameterType, 
	RPRX::FParameter Parameter)
{
	FRPRMaterialCoM* map = (FRPRMaterialCoM*) UberParameter;
	RPR::FResult status;

	switch (ParameterType)
	{
		case RPRX::EMaterialParameterType::Float4:
		{
			FLinearColor value;
			status = RPRX::FMaterialHelpers::GetMaterialParameterValue(SerializationCtx.RPRXContext, SerializationCtx.NativeRPRMaterial, Parameter, value);
			map->Constant = value;
			map->Mode = ERPRMaterialMapMode::Constant;
			return (true);
		}
		break;

		case RPRX::EMaterialParameterType::Node:
		{
			if (FRPRMaterialMapSetter::SetParameterValue(SerializationCtx, UberParameter, ParameterType, Parameter))
			{
				map->Mode = ERPRMaterialMapMode::Texture;
				return (true);
			}
		}
		break;

		default:
		break;
	}

	return (false);
}

bool RPR::GLTF::Importer::FRPRMaterialCoMSetter::IsParameterTypeSupported(RPRX::EMaterialParameterType MaterialParameterType)
{
	return (MaterialParameterType == RPRX::EMaterialParameterType::Node || 
		MaterialParameterType == RPRX::EMaterialParameterType::Float4);
}