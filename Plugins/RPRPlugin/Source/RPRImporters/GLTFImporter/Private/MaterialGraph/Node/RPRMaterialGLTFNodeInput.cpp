//~ RPR copyright

#include "RPRMaterialGLTFNodeInput.h"

#include "GLTF.h"
#include "INodeParamType.h"
#include "RPRUberMaterialParameters.h"
#include "UberMaterialPropertyHelper.h"

#include "GLTFImporterModule.h"
#include "Helpers/GLTFNodeHelper.h"
#include "Factory/NodeParamTypeGLTFFactory.h"

TMap<GLTF::ERPRInputValueType, ERPRMaterialGLTFNodeInputValueType> FRPRMaterialGLTFNodeInput::GLTFTypeEnumToUETypeEnumMap;

FRPRMaterialGLTFNodeInput::FRPRMaterialGLTFNodeInput()
{
    if (GLTFTypeEnumToUETypeEnumMap.Num() == 0)
    {
        GLTFTypeEnumToUETypeEnumMap.Add(GLTF::ERPRInputValueType::NODE, ERPRMaterialGLTFNodeInputValueType::Node);
        GLTFTypeEnumToUETypeEnumMap.Add(GLTF::ERPRInputValueType::FLOAT4, ERPRMaterialGLTFNodeInputValueType::Float4);
        GLTFTypeEnumToUETypeEnumMap.Add(GLTF::ERPRInputValueType::UINT, ERPRMaterialGLTFNodeInputValueType::UInt);
        GLTFTypeEnumToUETypeEnumMap.Add(GLTF::ERPRInputValueType::IMAGE, ERPRMaterialGLTFNodeInputValueType::Image);
    }
}

bool FRPRMaterialGLTFNodeInput::Parse(const amd::Input& Node, int32 NodeIndex)
{
	Name = FGLTFNodeHelper::GetNodeNameOfDefault(Node, NodeIndex);
	RawNode = &Node;
	InputType = ParseType(Node.type);

	FGLTFPtr TheGLTF;
	if (!FGLTFImporterModule::GetGLTF(TheGLTF))
	{
		UE_LOG(LogRPRGLTFImporter, Error, TEXT("FRPRMaterialGLTFNodeInput::Parse: glTF context is not valid."));
		return false;
	}

	bool bValueIsValid = false;
	switch (InputType)
	{
		case ERPRMaterialGLTFNodeInputValueType::Node:
		{
			int32 inputNodeIndex = Node.value.integer;
			IRPRMaterialNodePtr parentPtr = GetParent();
			const TArray<IRPRMaterialNodePtr> children = parentPtr->GetChildren();
			if (inputNodeIndex >= 0 && inputNodeIndex < children.Num())
			{
				const IRPRMaterialNodePtr inputNodePtr = children[inputNodeIndex];
				if (inputNodePtr.IsValid())
				{
					FString InputNodeName = inputNodePtr->GetName().ToString();
					StringValue = InputNodeName;
					bValueIsValid = !StringValue.IsEmpty();
				}
			}
		}
		break;
		case ERPRMaterialGLTFNodeInputValueType::Float4:
		{
			Vec4Value = FVector4(Node.value.array[0], Node.value.array[1], Node.value.array[2], Node.value.array[3]);
			bValueIsValid = true;
		}
		break;
		case ERPRMaterialGLTFNodeInputValueType::UInt:
		{
			int InputIntValue = Node.value.integer;
			if (InputIntValue >= 0)
			{
				IntValue = Node.value.integer;
				bValueIsValid = true;
			}
		}
		break;
		case ERPRMaterialGLTFNodeInputValueType::Image:
		{
			int InputImageIndex = Node.value.integer;
			if (InputImageIndex >= 0 && InputImageIndex < TheGLTF->Data->images.size())
			{
				const GLTF::FImage& Image = TheGLTF->Data->images[InputImageIndex];
				if (Image.uri.empty())
				{
					StringValue = Image.uri.c_str();
					bValueIsValid = !StringValue.IsEmpty();
				}
			}
		}
		break;
	}

	return (Name.IsValid() && InputType != ERPRMaterialGLTFNodeInputValueType::Unsupported && bValueIsValid);
}

void FRPRMaterialGLTFNodeInput::LoadRPRMaterialParameters(FRPRMaterialGraphSerializationContext& SerializationContext, UProperty* PropertyPtr)
{
    const FRPRUberMaterialParameterBase* UberMatParams =
        FUberMaterialPropertyHelper::GetParameterBaseFromProperty(SerializationContext.MaterialParameters, PropertyPtr);

    FString type = UberMatParams->GetPropertyTypeName(PropertyPtr);

	TSharedPtr<INodeParamType> NodeParam = FNodeParamTypeGLTFFactory::Get()->CreateNewNodeParam(type);
    if (NodeParam.IsValid())
    {
        NodeParam->LoadRPRMaterialParameters(SerializationContext, AsShared(), PropertyPtr);
    }
}

RPRMaterialGLTF::ERPRMaterialNodeType FRPRMaterialGLTFNodeInput::GetNodeType() const
{
	return RPRMaterialGLTF::ERPRMaterialNodeType::Input;
}

ERPRMaterialGLTFNodeInputValueType FRPRMaterialGLTFNodeInput::GetInputType() const
{
    return InputType;
}

void FRPRMaterialGLTFNodeInput::GetValue(FString& OutString) const
{
    check((InputType == ERPRMaterialGLTFNodeInputValueType::Node || InputType == ERPRMaterialGLTFNodeInputValueType::Image)
        && "NodeInput does not contain a string (node connection, file path) value.");
    OutString = StringValue;
}

void FRPRMaterialGLTFNodeInput::GetValue(FVector4& OutVec4) const
{
    check(InputType == ERPRMaterialGLTFNodeInputValueType::Float4 && "NodeInput does not contain a float4 value.");
    OutVec4 = Vec4Value;
}

void FRPRMaterialGLTFNodeInput::GetValue(int32& OutInt) const
{
    check(InputType == ERPRMaterialGLTFNodeInputValueType::UInt && "NodeInput does not contain an integer value.");
    OutInt = IntValue;
}

ERPRMaterialGLTFNodeInputValueType FRPRMaterialGLTFNodeInput::ParseType(GLTF::ERPRInputValueType ValueType)
{
    const ERPRMaterialGLTFNodeInputValueType* VT = GLTFTypeEnumToUETypeEnumMap.Find(ValueType);
    if (VT != nullptr)
    {
        return *VT;
    }
    return ERPRMaterialGLTFNodeInputValueType::Unsupported;
}