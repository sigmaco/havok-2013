/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_QEM_VERTEX_CONTRACTION_CONTROLLER_H
#define HK_QEM_VERTEX_CONTRACTION_CONTROLLER_H

#include <Common/GeometryUtilities/Mesh/Simplifiers/QemSimplifier/hkQemSimplifier.h>

class hkQemVertexContractionController: public hkQemSimplifier::ContractionController
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);

		typedef hkQemSimplifier::EdgeContraction EdgeContraction;

		// hkQemSimplifier::ContractionController implementation
		virtual hkBool32 allowContraction(const EdgeContraction& contraction);

			/// Enable a vertex 
		void setVertexCanContract(int index, bool enable);

			/// Returns true if the vertex can contract
		bool canVertexContract(int index) const;

			/// Set vertex contract state from an aabb. The positions must have the same indices as in the mesh.
			/// Generally this means the positions are the contents of the hkFindUniquePositionsUtil used for previous processing
		void setVertexCanContractFromAabb(const hkArray<hkVector4>& positions, const hkAabb& aabb, bool enable);

	protected:
		hkArray<hkUint32> m_bitField;			///< Has a bit set if the vertex cannot contract
};


#endif // HK_QUADRIC_METRIC_H

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20130718)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2013
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
