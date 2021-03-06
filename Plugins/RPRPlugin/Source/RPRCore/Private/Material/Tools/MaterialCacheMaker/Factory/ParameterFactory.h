/*************************************************************************
* Copyright 2020 Advanced Micro Devices
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*************************************************************************/

#pragma once

#include "UObject/UnrealType.h"
#include "Material/Tools/MaterialCacheMaker/ParameterSetters/IMaterialParameter.h"

namespace RPRX
{
	namespace MaterialParameter
	{
		class FFactory
		{

			typedef TSharedPtr<IMaterialParameter>(*FParameterCreator)();

		public:

			static TSharedPtr<IMaterialParameter>	Create(UProperty* Property);

			template<typename ParameterSetterType>
			static void		RegisterParameterSetter(const FName& PropertyTypeName);

		private:

			static void		InitializeMap();
			static void		InitializeMapIfRequired();

			template<typename ParameterSetterType>
			static TSharedPtr<IMaterialParameter>	InstantiateParameterType();

		private:

			static TMap<FName, FParameterCreator> Map;
		};


		template<typename ParameterSetterType>
		void	FFactory::RegisterParameterSetter(const FName& PropertyTypeName)
		{
			Map.Add(PropertyTypeName, &FFactory::InstantiateParameterType<ParameterSetterType>);
		}

		template<typename ParameterSetterType>
		TSharedPtr<IMaterialParameter> FFactory::InstantiateParameterType()
		{
			return MakeShareable(new ParameterSetterType());
		}
	}
}
