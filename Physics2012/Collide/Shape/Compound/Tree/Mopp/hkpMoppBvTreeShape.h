/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_MOPP_BV_TREE_SHAPE_H
#define HK_COLLIDE2_MOPP_BV_TREE_SHAPE_H

#include <Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Physics2012/Internal/Collide/Mopp/Code/hkpMoppCode.h>

extern const class hkClass hkMoppBvTreeShapeBaseClass;

extern const hkClass hkpMoppBvTreeShapeClass;

class hkpMoppCode;

class hkMoppBvTreeShapeBase: public hkpBvTreeShape
{
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();

		/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkMoppBvTreeShapeBase()
		{}

			/// Constructs a new hkpMoppBvTreeShape. You can use the <hkpMoppUtility.h> to build a MOPP code.
		hkMoppBvTreeShapeBase( ShapeType type, const hkpMoppCode* code);


		inline hkMoppBvTreeShapeBase( hkFinishLoadedObjectFlag flag )
		:	hkpBvTreeShape(flag)
		{
			if( flag.m_finishing )
			{
				m_bvTreeType = BVTREE_MOPP;
			}
		}


		inline ~hkMoppBvTreeShapeBase()
		{
			m_code->removeReference();
		}

			// hkpBvTreeShape interface implementation.
		virtual void queryObb( const hkTransform& obbToMopp, const hkVector4& extent, hkReal tolerance, hkArray<hkpShapeKey>& hits ) const;

			// hkpBvTreeShape interface implementation.
		virtual void queryAabb( const hkAabb& aabb, hkArray<hkpShapeKey>& hits ) const;

			// hkpBvTreeShape interface implementation.
		HKP_SHAPE_VIRTUAL hkUint32 queryAabbImpl(HKP_SHAPE_VIRTUAL_THIS const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) HKP_SHAPE_VIRTUAL_CONST;

	public:

		const class hkpMoppCode*		m_code;
		const  hkUint8*				m_moppData;		//+nosave
		hkUint32					m_moppDataSize; //+nosave
		hkVector4					m_codeInfoCopy; //+nosave
};


	/// This class implements a hkpBvTreeShape using MOPP technology.
class hkpMoppBvTreeShape: public hkMoppBvTreeShapeBase
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::MOPP);

		/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpMoppBvTreeShape()
		{}

			/// Constructs a new hkpMoppBvTreeShape. You can use the <hkpMoppUtility.h> to build a MOPP code.
		hkpMoppBvTreeShape( const hkpShapeCollection* collection, const hkpMoppCode* code);


		inline hkpMoppBvTreeShape( hkFinishLoadedObjectFlag flag );

			// destructor
		virtual ~hkpMoppBvTreeShape();


		//
		// hkpShape implementation
		//
			// hkpShape interface implementation.
		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

			//	hkpShape interface implementation.
		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results) const;

			// hkpShape Interface implementation
		virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector) const;

		//	hkpShape interface implementation.
		virtual hkVector4Comparison castRayBundle(const hkpShapeRayBundleCastInput& input, hkpShapeRayBundleCastOutput& results, hkVector4ComparisonParameter mask) const;

			/// Get the internal data used by the MOPP algorithms
		inline const hkpMoppCode* getMoppCode() const;

		inline void setMoppCode(const hkpMoppCode* code);


			/// Gets the hkpShapeCollection.
		inline const hkpShapeCollection* getShapeCollection() const;

		inline virtual const hkpShapeContainer* getContainer() const;

		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;


		HK_FORCE_INLINE const hkpShape* getChild() const;

	protected:

		class hkpSingleShapeContainer m_child;

	public:
		mutable int					m_childSize;	//+nosave


};

#include <Physics2012/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.inl>

#endif // HK_COLLIDE2_MOPP_BV_TREE_SHAPE_H

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
