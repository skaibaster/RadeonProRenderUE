#pragma once

#include "NameTypes.h"
#include "Array.h"
#include "RPRMaterialXmlNode.h"
#include "RPRMaterialXmlUberNode.h"
#include "RPRMaterialGraph.h"

/*
 * Load the datas required for a RPR Material by creating a graph from a Xml file
 */
class RPRMATERIALIMPORTER_API FRPRMaterialXmlGraph : public FRPRMaterialGraph<FXmlNode, FRPRMaterialXmlNode>
{
public:

	virtual ~FRPRMaterialXmlGraph() {}

	bool	ParseFromXmlFile(const FString& Filename);

	virtual bool	Parse(const class FXmlNode& Node) override;
	virtual void	Load(FRPRMaterialGraphSerializationContext& SerializationContext) override;
	virtual bool	IsUberNode(FRPRMaterialXmlNodePtr Node) const override;

private:

	void	ParseNodes(const class FXmlNode& Node);

};