/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MXVECTORd_UTIL_H
#define HK_MXVECTORd_UTIL_H

#include <Common/Base/Math/Vector/Mx/hkMxVectord.h>
#include <Common/Base/Math/Vector/Mx/hkMxQuaterniond.h>
#include <Common/Base/Math/Vector/hkPackedVector3.h>

typedef hkMxVectord<4> hkMxTransformd;
#define hkMxTransformdParameter const hkMxTransformd&


/// Utility functions for working with long vectors.
///
/// Routines need to be parameterized by vector length M. The methods assume that the pointed to memory is
/// large enough to process all M subvectors. No range checking is done on the base memory pointers or the
/// addresses computed by the parameters.
///
/// The vector transform methods provide optimized implementations for the common use case of 4x4 matrices.
///
/// \sa hkMxVectord hkMxReald hkMxSingled hkMxHalf8
namespace hkMxVectorUtil
{

	//
	// Storage conversion from hkHalf
	//

	/// load a stream of hkHalfs into an hkMxVectord
	template <int M>
	HK_FORCE_INLINE void HK_CALL loadUnpack(const hkHalf* base, hkMxVectord<M>& vOut0);

	/// Write a stream of subvectors of \a v to the a non-contiguous memory addresses \a base + (m * byteAddressIncrement), the dest address needs to be 8 byte aligned
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL scatterPack(hkMxVectordParameter v, hkHalf* base);


// 	template <int M>
// 	HK_FORCE_INLINE void HK_CALL storePacked(const hkMxVectord<M>& vin, const hkHalf* baseOut );

	/// Read subvectors into \a vOut0 and \a vOut1 from the first and second packed half respectively of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpack(const hkHalf* base, hkMxVectord<M>& vOut0, hkMxVectord<M>& vOut1);

	/// Read subvectors into \a vOut0 and \a vOut1 from the first and second packed half respectively of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL gatherUnpack(const hkHalf* base, const hkUint16* indices, hkMxVectord<M>& vOut0, hkMxVectord<M>& vOut1);

	/// Read subvectors into \a vOut0 and \a vOut1 from the first and second packed half respectively of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpack(const hkHalf* base, const hkInt32* indices, hkMxVectord<M>& vOut0, hkMxVectord<M>& vOut1);

	/// Read subvectors into \a vOut0 and \a vOut1 from the first and second packed half respectively of the hkHalf[8] at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackHalf8WithOffset(const void* base[M], hkMxVectord<M>& vOut0, hkMxVectord<M>& vOut1);

	/// Read subvectors into \a vOut from the first packed half of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpackFirst(const hkHalf* base, hkMxVectord<M>& vOut);

	/// Read subvectors into \a vOut from the first packed half of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL gatherUnpackFirst(const hkHalf* base, const hkUint16* indices, hkMxVectord<M>& vOut);

	/// Read subvectors into \a vOut from the first packed half of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpackFirst(const hkHalf* base, const hkInt32* indices, hkMxVectord<M>& vOut);

	/// Read subvectors into \a vOut from the first packed half of the hkHalf[8] at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackFirstHalf8WithOffset(const void* base[M], hkMxVectord<M>& vOut);

	/// Read subvectors into \a vOut from the second packed half of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpackSecond(const hkHalf* base, hkMxVectord<M>& vOut);

	/// Read subvectors into \a vOut from the second packed half of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL gatherUnpackSecond(const hkHalf* base, const hkUint16* indices, hkMxVectord<M>& vOut);
	/// Read subvectors into \a vOut from the second packed half of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpackSecond(const hkHalf* base, const hkInt32* indices, hkMxVectord<M>& vOut);
	/// Read subvectors into \a vOut from the second packed half of the hkHalf[8] at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackSecondHalf8WithOffset(const void* base[M], hkMxVectord<M>& vOut);


	/// Write subvectors of \a v0 and \a v1 to the first and second packed half respectively of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL scatterPack(hkMxVectordParameter v0, hkMxVectordParameter v1, hkHalf* base);

	/// Write subvectors of \a v0 and \a v1 to the first and second packed half respectively of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPack(hkMxVectordParameter v0, hkMxVectordParameter v1, hkHalf* base, const hkUint16* indices);

	/// Write subvectors of \a v0 and \a v1 to the first and second packed half respectively of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPack(hkMxVectordParameter v0, hkMxVectordParameter v1, hkHalf* base, const hkInt32* indices);

	/// Write subvectors of \a v0 and \a v1 to the first and second packed half respectively of the hkHalf[8] at non-linear memory addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL scatterPackHalf8WithOffset(hkMxVectordParameter v0, hkMxVectordParameter v1, void* base[M]);

	/// Write subvectors of \a v to the first packed half of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL scatterPackFirst(hkMxVectordParameter v, hkHalf* base);

	/// Write subvectors of \a v to the first packed half of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPackFirst(hkMxVectordParameter v, hkHalf* base, const hkUint16* indices);

	/// Write subvectors of \a v to the first packed half of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPackFirst(hkMxVectordParameter v, hkHalf* base, const hkInt32* indices);

	/// Write subvectors of \a v to the first packed half of the hkHalf[8] at non-linear memory addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL scatterPackFirstHalf8WithOffset(hkMxVectordParameter v, void* base[M]);

	/// Write subvectors of \a v to the second packed half of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL scatterPackSecond(hkMxVectordParameter v, hkHalf* base);
	/// Write subvectors of \a v to the second packed half of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPackSecond(hkMxVectordParameter v, hkHalf* base, const hkUint16* indices);
	/// Write subvectors of \a v to the second packed half of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPackSecond(hkMxVectordParameter v, hkHalf* base, const hkInt32* indices);
	/// Write subvectors of \a v to the second packed half of the hkHalf[8] at non-linear memory addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL scatterPackSecondHalf8WithOffset(hkMxVectordParameter v, void* base[M]);


	//
	// Storage conversion from hkPackedVector
	//

	/// Read subvectors into \a vOut from the packed 3-component vectors at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackPackedVectorWithOffset(const void* base[M], hkMxVectord<M>& vOut);

	/// Get 3w components of 3 consecutive hkVector4d s
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gather3WComponents(const void* base[M], hkMxVectord<M>& vOut);

	

	/// Read subvectors into \a vOut from the packed 4-component unit vectors at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackPackedUnitVectorWithOffset(const void* base[M], hkMxVectord<M>& vOut);




	//
	// Vector transformations
	//


	/// Transform the 4 position subvectors in \a vIn using matrix \a mat and store in \a vOut.
	/// \warning [M:1-4 only] 
	template <int M>
	HK_FORCE_INLINE void HK_CALL transformPosition(hkMxTransformdParameter mat, hkMxVectordParameter vIn, hkMxVectord<M>& vOut);
	/// Transform the 4 position subvectors in \a vIn using the transpose matrix of \a mat and store in \a vOut.
	/// \warning [M:1-4 only] 
	template <int M>
	HK_FORCE_INLINE void HK_CALL transformTransposePosition(hkMxTransformdParameter mat, hkMxVectordParameter vIn, hkMxVectord<M>& vOut);

	/// Rotate the direction subvectors in \a vIn using matrix \a mat and store in \a vOut.
	/// \warning [M:1-4 only] 
	template <int M>
	HK_FORCE_INLINE void HK_CALL rotateDirection( hkMxTransformdParameter mat, hkMxVectordParameter vIn, hkMxVectord<M>& vOut);
	/// Rotate the direction subvectors in \a vIn using the inverse matrix of \a mat and store in \a vOut.
	/// \warning [M:1-4 only] 
	template <int M>
	HK_FORCE_INLINE void HK_CALL rotateInverseDirection( hkMxTransformdParameter mat, hkMxVectordParameter vIn, hkMxVectord<M>& vOut);

	/// Optimized routine to transform each position subvector in \a vIn with one matrix and store in \a vOut. \a vIn[0] is transformed by \a mat0, \a vIn[1] is transformed by \a mat1, \a vIn[2] is transformed by \a mat2 and \a vIn[3] is transformed by \a mat3.
	/// \warning [M:4 only] 
	HK_FORCE_INLINE void HK_CALL transform4Positions(hkMxTransformdParameter mat0, hkMxTransformdParameter mat1, hkMxTransformdParameter mat2, hkMxTransformdParameter mat3, const hkMxVectord<4>& vIn, hkMxVectord<4>& vOut);
	/// Optimized routine to rotate each direction subvector in \a vIn with one matrix and store in \a vOut. \a vIn[0] is rotated by \a mat0, \a vIn[1] is rotated by \a mat1, \a vIn[2] is rotated by \a mat2 and \a vIn[3] is rotated by \a mat3.
	/// \warning [M:4 only] 
	HK_FORCE_INLINE void HK_CALL rotate4Directions(hkMxTransformdParameter mat0, hkMxTransformdParameter mat1, hkMxTransformdParameter mat2, hkMxTransformdParameter mat3, const hkMxVectord<4>& vIn, hkMxVectord<4>& vOut);

	/// Rotate each subvector in \a vIn using the respective subquaterion in \a mat and store in \a vOut.
	template <int M>	HK_FORCE_INLINE void HK_CALL rotateDirection( hkMxQuaterniondParameter mat, hkMxVectordParameter vIn, hkMxVectord<M>& vOut);

	/// Rotate each subvector in \a vIn using one transform from the array \a mat and store in \a vOut.
	template <int M>	HK_FORCE_INLINE void HK_CALL rotateDirection( const hkTransformd* mat, hkMxVectordParameter vIn, hkMxVectord<M>& vOut);

	/// Transform each subvector in \a vIn using one transform from the array \a mat and store in \a vOut.
	template <int M>	HK_FORCE_INLINE void HK_CALL transformPosition( const hkTransformd* mat, hkMxVectordParameter vIn, hkMxVectord<M>& vOut);
};

#include <Common/Base/Math/Vector/Mx/hkMxVectordUtil.inl>

#endif // HK_MXVECTORd_UTIL_H

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
