#pragma once
#include "RPRMatParamCopier_MaterialMap.h"

class FRPRMatParamCopier_MaterialConstantOrMapChannel1 : public FRPRMatParamCopier_MaterialMap
{
public:

	virtual void Apply(const FRPRUberMaterialParameters& RPRUberMaterialParameters, UStructProperty* Property, UMaterialEditorInstanceConstant* RPRMaterialEditorInstance) override;

};