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
#pragma once
#include "STableRow.h"
#include "STableViewBase.h"
#include "SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"
#include "SListView.h"
#include "SScrollBox.h"
#include "SBorder.h"
#include "STextBlock.h"
#include "SBox.h"


template<typename TObjectType>
class SObjectsOutliner : public SCompoundWidget
{
public:
	DECLARE_DELEGATE_RetVal_OneParam(FText, FOverrideGetObjectName, TObjectType)

	typedef typename TSlateDelegates<TObjectType>::FOnSelectionChanged FOnSelectionChanged;

public:

	SLATE_BEGIN_ARGS(SObjectsOutliner<TObjectType>) {}
		SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged)
		SLATE_EVENT(FOverrideGetObjectName, OverrideGetObjectName)
	SLATE_END_ARGS()

	void	Construct(const FArguments& InArgs);
	void	AddObject(const TObjectType& Object);
	void	AddObjects(const TArray<TObjectType>& Objects);
	void	ClearObjects();
	void	SelectAll();
	int32	GetSelectedItems(TArray<TObjectType>& SelectedItems) const;
	int32	GetNumSelectedItems() const;

private:

	TSharedRef<ITableRow>	OnGenerateRow(TObjectType Item, const TSharedRef<STableViewBase>& Table);
	
private:

	TArray<TObjectType> Objects;
	TSharedPtr<SListView<TObjectType>> ObjectListView;
	FOnSelectionChanged	OnSelectionChanged;
	FOverrideGetObjectName OverrideGetObjectName;
};

template<typename TObjectType>
void SObjectsOutliner<TObjectType>::Construct(const FArguments& InArgs)
{
	OnSelectionChanged = InArgs._OnSelectionChanged;
	OverrideGetObjectName = InArgs._OverrideGetObjectName;

	ChildSlot
		[
			SNew(SBox)
			.Padding(2.0f)
			.VAlign(EVerticalAlignment::VAlign_Fill)
			[
				SNew(SScrollBox)
				+SScrollBox::Slot()
				[
					SAssignNew(ObjectListView, SListView<TObjectType>)
					.ListItemsSource(&Objects)
					.OnGenerateRow(SListView<TObjectType>::FOnGenerateRow::CreateSP(this, &SObjectsOutliner::OnGenerateRow))
					.OnSelectionChanged(OnSelectionChanged)
				]
			]
		];
}

template<typename TObjectType>
TSharedRef<ITableRow> SObjectsOutliner<TObjectType>::OnGenerateRow(TObjectType Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	FText text = FText::FromString(Item->GetName());

	if (OverrideGetObjectName.IsBound())
	{
		text = OverrideGetObjectName.Execute(Item);
	}

	return
		SNew(STableRow<UObject*>, OwnerTable)
		.Content()
		[
			SNew(SBox)
			.Padding(FMargin(5.f, 2.0f))
			[
				SNew(STextBlock)
				.Text(text)
			]
		]
	;
}

template<typename TObjectType>
void SObjectsOutliner<TObjectType>::AddObject(const TObjectType& Object)
{
	Objects.Add(Objects);
}

template<typename TObjectType>
void SObjectsOutliner<TObjectType>::AddObjects(const TArray<TObjectType>& InObjects)
{
	Objects.Append(InObjects);
}

template<typename TObjectType>
void SObjectsOutliner<TObjectType>::ClearObjects()
{
	ObjectListView->ClearSelection();
	Objects.Empty();
}

template<typename TObjectType>
void SObjectsOutliner<TObjectType>::SelectAll()
{
	for (int32 i = 0; i < Objects.Num(); ++i)
	{
		ObjectListView->SetItemSelection(Objects[i], true);
	}
}

template<typename TObjectType>
int32 SObjectsOutliner<TObjectType>::GetSelectedItems(TArray<TObjectType>& SelectedItems) const
{
	return (ObjectListView->GetSelectedItems(SelectedItems));
}

template<typename TObjectType>
int32 SObjectsOutliner<TObjectType>::GetNumSelectedItems() const
{
	return (ObjectListView->GetNumItemsSelected());
}
