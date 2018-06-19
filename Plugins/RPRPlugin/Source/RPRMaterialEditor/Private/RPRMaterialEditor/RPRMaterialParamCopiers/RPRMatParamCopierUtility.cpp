#include "RPRMatParamCopierUtility.h"
#include "RPREditorMaterialConstants.h"
#include "MaterialEditor/DEditorParameterValue.h"
#include "RPRCpMaterialEditor.h"

FString FRPRMatParamCopierUtility::CombinePropertyNameSectionInternal(const FString* SectionsArray, int32 NumSections)
{
	FString output;

	for (int32 i = 0; i < NumSections; ++i)
	{
		output.Append(SectionsArray[i]);
		if (i + 1 < NumSections)
		{
			output.Append(RPR::FEditorMaterialConstants::MaterialPropertyNameSectionSeparatorString);
		}
	}

	return (output);
}

UDEditorParameterValue* FRPRMatParamCopierUtility::FindEditorParameterValue(UMaterialEditorInstanceConstant* MaterialEditorInstance, const FString& PropertyName)
{
	FEditorParameterGroup& parameterGroup = MaterialEditorInstance->ParameterGroups[0];

	TArray<UDEditorParameterValue*>& parameterValues = parameterGroup.Parameters;
	for (int32 i = 0; i < parameterValues.Num(); ++i)
	{
		if (FRPRCpMaterialEditor::GetDEditorParameterName(*parameterValues[i]) == *PropertyName)
		{
			return (parameterValues[i]);
		}
	}

	return (nullptr);
}