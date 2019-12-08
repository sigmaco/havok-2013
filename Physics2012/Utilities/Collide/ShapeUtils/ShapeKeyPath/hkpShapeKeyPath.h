/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SHAPE_KEY_PATH_UTIL_H
#define HK_SHAPE_KEY_PATH_UTIL_H

#include <Physics2012/Collide/Shape/hkpShape.h>
#include <Physics2012/Collide/Shape/hkpShapeBuffer.h>

class  hkpContactPointEvent;
struct hkpWorldRayCastOutput;
struct hkpShapeRayBundleCastOutput;
struct hkpRootCdPoint;


/// The hkpShapeKeyPath and its iterator class provide a unified interface to walk through a shape hierarchy using a
/// list of shape key array, from the root shape to a leaf shape.
/// 
/// The hkpShapeKeyPath constructors allows to create it from different situations where a shape hierarchy has to be
/// traversed (ray casting, contact point callbacks), allowing to use a common interface for these various cases.
/// The getIterator() function generates an iterator which will provide access to the shapes along the path.
/// 
/// Every iteration goes one level down in the hierarchy until the leaf shape is reached.
/// However, keep in mind that :
///  - The hkpShape* returned by getShape() is only guaranteed to be valid until the subsequent call to next() or
///    the destruction of the iterator. To get the shapes in a more permanent storage, use the getShapes() function
///    which take user-supplied buffers as arguments.
///  - When the leaf shape is reached, the subsequent call to next() will invalidate the iterator.
///    The getShape() function will then return HK_NULL. 
class hkpShapeKeyPath
{
	public:
        
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkpShapeKeyPath );
		
		class Iterator;
		
		// Constructors.
		
			/// Goes through one of the shapes hierarchy colliding in a contact point
		hkpShapeKeyPath( const hkpContactPointEvent& event, int bodyIdx );

			/// Goes through the shape hierarchy hit by a ray casting. The raycast must have hit.
		hkpShapeKeyPath( const hkpWorldRayCastOutput& output );

			/// Goes through the shape hierarchy hit by a ray casting in  a shape. The raycast must have hit.
		hkpShapeKeyPath( const hkpShape* shape, const hkpShapeRayCastOutput& output );


			/// Returns the shape key corresponding to the given index, in root to leaf order.
		hkpShapeKey getShapeKey( int keyIndex ) const;

			/// Returns a new iterator initialized to the root shape of the path.
		Iterator getIterator() const;
		
			/// Gets all the branch of shapes from the shape pointed by the iterator to the leaf.
			/// This allows to keep the intermediate shapes pointers valid even after destroying the iterator.
			/// \param maxShapesOut the maximum number of shapes for which temporary storage has been made
			///   available. The method asserts if this isn't big enough.
			/// \param buffers a pointer to an array of size (maxShapesOut - 1) used for temporary shape storage.
			/// \param shapesOut a pointer to an array of size maxShapes used to store the shape pointers.
			///   All but the first pointer may point into the buffers.
			/// \param numShapesOut the number of shapes written out.
		void getShapes( int maxShapesOut, hkpShapeBuffer* buffers, const hkpShape** shapesOut, int& numShapesOut );

	public:

		/// Iterator allowing access to the shapes along the path.
		class Iterator
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkpShapeKeyPath::Iterator );

				friend class hkpShapeKeyPath;

					/// Returns the current shape pointed to by the iterator. Subsequent calls to getNext(),
					/// or destruction of the iterator, can invalidate this pointer.
					/// Returns HK_NULL if the iterator is invalid.
				const hkpShape* getShape() const;

					/// Advances the iterator along the path.
					/// Calling this after the leaf shape has been reached invalidates the iterator.
				void next();
	
					/// Returns true if the iterator is valid.
				hkBool isValid() const;

			private:
				
				// Creates an iterator pointing at the beginning of the path (root shape).
				// Iterators can only be created by a ShapeKeyPath through getIterator().
				Iterator( const hkpShapeKeyPath* path, const hkpShape* rootShape );

				// Advances the iterator, storing temporary shapes in the given buffer
				void nextImpl( hkpShapeBuffer* buf );

			private:

				const hkpShapeKeyPath*	m_path;
				const hkpShape*			m_currentShape;
				int						m_currentKeyIdx;
				hkBool					m_isValid;
				hkpShapeBuffer			m_tempBuffer;
		};

	private:

		// Common initialization function.
		void init( const hkpShape* shape, const hkpShapeKey* keys, int maxKeys );

	private:

		const hkpShape*		m_rootShape;	
		const hkpShapeKey*	m_keys;
		int					m_numKeys;
		hkBool				m_isOrderLeafToRoot;
};

#include <Physics2012/Utilities/Collide/ShapeUtils/ShapeKeyPath/hkpShapeKeyPath.inl>

#endif //HK_SHAPE_KEY_PATH_UTIL_H

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
