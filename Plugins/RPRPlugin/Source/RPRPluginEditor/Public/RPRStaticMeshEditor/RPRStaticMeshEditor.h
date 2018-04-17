#pragma once

#include "AssetEditorToolkit.h"
#include "Editor.h"
#include "GCObject.h"
#include "SharedPointer.h"
#include "RPRStaticMeshEditorSelection.h"
#include "Engine/StaticMesh.h"
#include "RPRMeshDataContainer.h"
#include "RPRStaticMeshEditorModesCommands.h"

extern const FName RPRStaticMeshEditorAppIdentifier;

class RPRPLUGINEDITOR_API FRPRStaticMeshEditor : public FAssetEditorToolkit, public FGCObject
{

public:

	static TSharedPtr<FRPRStaticMeshEditor>	CreateRPRStaticMeshEditor(const TArray<UStaticMesh*>& StaticMeshes);

	void	InitRPRStaticMeshEditor(const TArray<UStaticMesh*>& InStaticMeshes);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override;
	virtual FEdMode* GetEditorMode() const override;
	
	virtual void	AddReferencedObjects(FReferenceCollector& Collector) override;
	
	FORCEINLINE FRPRMeshDataContainerPtr	GetMeshDatas() const { return (MeshDatas); }
	const FRPRStaticMeshEditorModesCommands&	GetModeCommands() const;

	FRPRMeshDataContainerPtr		GetSelectedMeshes() const;
	FRPRStaticMeshEditorSelection&	GetSelectionSystem();

	void	AddComponentToViewport(UActorComponent* InComponent, bool bSelectComponent = true);
	void	GetMeshesBounds(FVector& OutCenter, FVector& OutExtents);
	void	RefreshViewport();
	void	SetMode(FEditorModeID ModeID);

	DECLARE_EVENT(FRPRStaticMeshEditor, FOnSelectionChanged)
	FOnSelectionChanged&	OnSelectionChanged() { return OnSelectionChangedEvent; }


private:

	TSharedPtr<FTabManager::FLayout>	GenerateDefaultLayout();
	TSharedRef<class IDetailCustomization>	MakeStaticMeshDetails();

	void	OpenOrCloseSceneOutlinerIfRequired();
	void	WatchSectionSelectionChanges();

	void	InitializeWidgets();
	void	InitializeViewport();
	void	InitializeUVProjectionMappingEditor();
	void	InitializeUVVisualizer();
	void	InitializeSceneComponentsOutliner();
	void	InitializePropertiesView();
	void	InitializeEditorModes();

	TSharedRef<SDockTab>				SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab>				SpawnTab_UVProjectionMappingEditor(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab>				SpawnTab_UVVisualizer(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab>				SpawnTab_SceneComponentsOutliner(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab>				SpawnTab_Properties(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab>				SpawnTab_Modes(const FSpawnTabArgs& Args);

	void	OnSceneComponentOutlinerSelectionChanged(URPRStaticMeshPreviewComponent* NewItemSelected, ESelectInfo::Type SelectInfo);
	void	OnProjectionCompleted();
	void	OnSectionSelectionChanged(bool NewState);

	virtual bool	OnRequestClose() override;


private:

	FRPRMeshDataContainerPtr	MeshDatas;

	TSharedPtr<FEdMode>	CurrentMode;

	TSharedPtr<class SRPRStaticMeshEditorViewport>		Viewport;
	TSharedPtr<class SUVProjectionMappingEditor>		UVProjectionMappingEditor;
	TSharedPtr<class SUVVisualizerEditor>				UVVisualizer;
	TSharedPtr<class SSceneComponentsOutliner>			SceneComponentsOutliner;
	TSharedPtr<class IDetailsView>						PropertiesDetailsView;
	TSharedPtr<class IDetailCustomization>				StaticMeshDetails;
	TSharedPtr<class FRPRStaticMeshEditorModesWindow>	ModesEditor;
		
	FRPRStaticMeshEditorSelection	SelectionSystem;

	/** Events **/
	FOnSelectionChanged OnSelectionChangedEvent;

	/** Tab IDs **/

	static const FName ViewportTabId;
	static const FName UVProjectionMappingEditorTabId;
	static const FName UVVisualizerTabId;
	static const FName SceneComponentsOutlinerTabId;
	static const FName PropertiesTabId;
	static const FName ModesTabId;

};

typedef TSharedPtr<FRPRStaticMeshEditor> FRPRStaticMeshEditorPtr;
typedef TWeakPtr<FRPRStaticMeshEditor> FRPRStaticMeshEditorWeakPtr;