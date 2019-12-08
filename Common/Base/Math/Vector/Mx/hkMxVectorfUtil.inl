/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

namespace hkMxVectorUtil
{

namespace hkMxVectorfUtil_Implementation
{
template <int I> struct loadUnpack2H {
	HK_FORCE_INLINE static void apply(const hkHalf* base, hkVector4f* vOut0)
	{
		HK_COMPILE_TIME_ASSERT( (I&1) == 0);
		hkVector4f h0,h1; 
		h0.load<4,HK_IO_NATIVE_ALIGNED>(base+((I-2)*4));
		h1.load<4,HK_IO_NATIVE_ALIGNED>(base+((I-1)*4));
		loadUnpack2H<I-2>::apply(base, vOut0);
		vOut0[I-2] = h0;
		vOut0[I-1] = h1;
	} };

	template <> struct loadUnpack2H<2> {
		HK_FORCE_INLINE static void apply(const hkHalf* base, hkVector4f* vOut0)
		{
			hkVector4f h0,h1;
			h0.load<4,HK_IO_NATIVE_ALIGNED>(base);
			h1.load<4,HK_IO_NATIVE_ALIGNED>(base+4);
			vOut0[0] = h0;
			vOut0[1] = h1;
		} };
}

template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL loadUnpack(const hkHalf* base, hkMxVectorf<M>& vOut0)
{
	hkMxVectorfUtil_Implementation::loadUnpack2H<M>::apply(base, vOut0.m_vec.v);
}





namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUnpackH {
HK_FORCE_INLINE static void apply(const hkHalf* base, hkVector4f* vOut0, hkVector4f* vOut1)
{
	hkVector4f h0,h1;
	const hkHalf* ptr = hkAddByteOffsetConst( base, (I-1) * byteAddressIncrement ); 
	h0.load<4,HK_IO_NATIVE_ALIGNED>(ptr);
	h1.load<4,HK_IO_NATIVE_ALIGNED>(ptr+4);
	gatherUnpackH<I-1, byteAddressIncrement>::apply(base, vOut0, vOut1);
	vOut0[I-1] = h0;
	vOut1[I-1] = h1;
} };
template <hkUint32 byteAddressIncrement> struct gatherUnpackH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkHalf* base, hkVector4f* vOut0, hkVector4f* vOut1)
{
	hkVector4f h0,h1;
	h0.load<4,HK_IO_NATIVE_ALIGNED>(base);
	h1.load<4,HK_IO_NATIVE_ALIGNED>(base+4);
	vOut0[0] = h0;
	vOut1[0] = h1;
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpack(const hkHalf* base, hkMxVectorf<M>& vOut0, hkMxVectorf<M>& vOut1)
{
	hkMxVectorfUtil_Implementation::gatherUnpackH<M, byteAddressIncrement>::apply(base, vOut0.m_vec.v, vOut1.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUnpack2Hu {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkUint16* indices, hkVector4f* vOut0, hkVector4f* vOut1)
{
	hkVector4f h0,h1;
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement ); 
	h0.load<4,HK_IO_NATIVE_ALIGNED>(ptr);
	h1.load<4,HK_IO_NATIVE_ALIGNED>(ptr+4);
	gatherUnpack2Hu<I-1, byteAddressIncrement>::apply(base, indices, vOut0, vOut1);
	vOut0[I-1] = h0;
	vOut1[I-1] = h1;
} };
template <hkUint32 byteAddressIncrement> struct gatherUnpack2Hu<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkUint16* indices, hkVector4f* vOut0, hkVector4f* vOut1)
{
	hkVector4f h0,h1;
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement ); 
	h0.load<4,HK_IO_NATIVE_ALIGNED>(ptr);
	h1.load<4,HK_IO_NATIVE_ALIGNED>(ptr+4);
	vOut0[0] = h0;
	vOut1[0] = h1;
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpack(const hkHalf* base, const hkUint16* indices, hkMxVectorf<M>& vOut0, hkMxVectorf<M>& vOut1)
{
	hkMxVectorfUtil_Implementation::gatherUnpack2Hu<M, byteAddressIncrement>::apply(base, indices, vOut0.m_vec.v, vOut1.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUnpack2H {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkInt32* indices, hkVector4f* vOut0, hkVector4f* vOut1)
{
	hkVector4f h0,h1;
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement ); 
	h0.load<4,HK_IO_NATIVE_ALIGNED>(ptr);
	h1.load<4,HK_IO_NATIVE_ALIGNED>(ptr+4);
	gatherUnpack2H<I-1, byteAddressIncrement>::apply(base, indices, vOut0, vOut1);
	vOut0[I-1] = h0;
	vOut1[I-1] = h1;
} };
template <hkUint32 byteAddressIncrement> struct gatherUnpack2H<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkInt32* indices, hkVector4f* vOut0, hkVector4f* vOut1)
{
	hkVector4f h0,h1;
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement ); 
	h0.load<4,HK_IO_NATIVE_ALIGNED>(ptr);
	h1.load<4,HK_IO_NATIVE_ALIGNED>(ptr+4);
	vOut0[0] = h0;
	vOut1[0] = h1;
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpack(const hkHalf* base, const hkInt32* indices, hkMxVectorf<M>& vOut0, hkMxVectorf<M>& vOut1)
{
	hkMxVectorfUtil_Implementation::gatherUnpack2H<M, byteAddressIncrement>::apply(base, indices, vOut0.m_vec.v, vOut1.m_vec.v);
}





namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteOffset> struct gatherUnpackWithOffsetH {
HK_FORCE_INLINE static void apply(hkVector4f* v0, hkVector4f* v1, const void** base)
{
	const hkHalf* ptr = (const hkHalf*)hkAddByteOffsetConst( base[I-1], byteOffset ); 
	gatherUnpackWithOffsetH<I-1, byteOffset>::apply(v0, v1, base);
	v0[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
	v1[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr+4);
} };
template <hkUint32 byteOffset> struct gatherUnpackWithOffsetH<1, byteOffset> {
HK_FORCE_INLINE static void apply(hkVector4f* v0, hkVector4f* v1, const void** base)
{
	const hkHalf* ptr = (const hkHalf*)hkAddByteOffsetConst( base[0], byteOffset ); 
	v0[0].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
	v1[0].load<4,HK_IO_NATIVE_ALIGNED>(ptr+4);
} };
}
template <int M, hkUint32 byteAddressOffset>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackHalf8WithOffset(const void* base[M], hkMxVectorf<M>& vOut0, hkMxVectorf<M>& vOut1)
{
	hkMxVectorfUtil_Implementation::gatherUnpackWithOffsetH<M, byteAddressOffset>::apply(vOut0.m_vec.v, vOut1.m_vec.v, base);
}





namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUnpackFirstH {
HK_FORCE_INLINE static void apply(const hkHalf* base, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, (I-1) * byteAddressIncrement ); 
	gatherUnpackFirstH<I-1, byteAddressIncrement>::apply(base, vOut);
	vOut[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
template <hkUint32 byteAddressIncrement> struct gatherUnpackFirstH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkHalf* base, hkVector4f* vOut)
{
	vOut[0].load<4,HK_IO_NATIVE_ALIGNED>(base);
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackFirst(const hkHalf* base, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackFirstH<M, byteAddressIncrement>::apply(base, vOut.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUnpackFirst2Hu {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkUint16* indices, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement ); 
	gatherUnpackFirst2Hu<I-1, byteAddressIncrement>::apply(base, indices, vOut);
	vOut[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
template <hkUint32 byteAddressIncrement> struct gatherUnpackFirst2Hu<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkUint16* indices, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement ); 
	vOut[0].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackFirst(const hkHalf* base, const hkUint16* indices, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackFirst2Hu<M, byteAddressIncrement>::apply(base, indices, vOut.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUnpackFirst2H {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkInt32* indices, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement ); 
	gatherUnpackFirst2H<I-1, byteAddressIncrement>::apply(base, indices, vOut);
	vOut[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };

template <hkUint32 byteAddressIncrement> struct gatherUnpackFirst2H<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkInt32* indices, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement ); 
	vOut[0].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackFirst(const hkHalf* base, const hkInt32* indices, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackFirst2H<M, byteAddressIncrement>::apply(base, indices, vOut.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteOffset> struct gatherUnpackFirstWithOffsetH {
HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
{
	const hkHalf* ptr = (const hkHalf*)hkAddByteOffsetConst( base[I-1], byteOffset ); 
	gatherUnpackFirstWithOffsetH<I-1, byteOffset>::apply(v, base);
	v[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
template <hkUint32 byteOffset> struct gatherUnpackFirstWithOffsetH<1, byteOffset> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
{
	const hkHalf* ptr = (const hkHalf*)hkAddByteOffsetConst( base[0], byteOffset ); 
	v[0].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
}
template <int M, hkUint32 byteAddressOffset>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackFirstHalf8WithOffset(const void* base[M], hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackFirstWithOffsetH<M, byteAddressOffset>::apply(vOut.m_vec.v, base);
}



namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUnpackSecondH {
HK_FORCE_INLINE static void apply(const hkHalf* base, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, (I-1) * byteAddressIncrement + 4 * sizeof(hkHalf) ); 
	gatherUnpackSecondH<I-1, byteAddressIncrement>::apply(base, vOut);
	vOut[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
template <hkUint32 byteAddressIncrement> struct gatherUnpackSecondH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkHalf* base, hkVector4f* vOut)
{
	vOut[0].load<4,HK_IO_NATIVE_ALIGNED>(base+4);
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackSecond(const hkHalf* base, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackSecondH<M, byteAddressIncrement>::apply(base, vOut.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUnpackSecond2H {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkInt32* indices, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement +4); 
	gatherUnpackSecond2H<I-1, byteAddressIncrement>::apply(base, indices, vOut);
	vOut[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
template <hkUint32 byteAddressIncrement> struct gatherUnpackSecond2H<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkInt32* indices, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement +4); 
	vOut[0].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackSecond(const hkHalf* base, const hkInt32* indices, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackSecond2H<M, byteAddressIncrement>::apply(base, indices, vOut.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUnpackSecond2Hu {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkUint16* indices, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement +4); 
	gatherUnpackSecond2Hu<I-1, byteAddressIncrement>::apply(base, indices, vOut);
	vOut[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
template <hkUint32 byteAddressIncrement> struct gatherUnpackSecond2Hu<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkHalf* base, const hkUint16* indices, hkVector4f* vOut)
{
	const hkHalf* ptr = hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement +4); 
	vOut[0].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackSecond(const hkHalf* base, const hkUint16* indices, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackSecond2Hu<M, byteAddressIncrement>::apply(base, indices, vOut.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteOffset> struct gatherUnpackSecondWithOffsetH {
HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
{
	const hkHalf* ptr = (const hkHalf*)hkAddByteOffsetConst( base[I-1], byteOffset+4 ); 
	gatherUnpackSecondWithOffsetH<I-1, byteOffset>::apply(v, base);
	v[I-1].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
template <hkUint32 byteOffset> struct gatherUnpackSecondWithOffsetH<1, byteOffset> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
{
	const hkHalf* ptr = (const hkHalf*)hkAddByteOffsetConst( base[0], byteOffset+4 ); 
	v[0].load<4,HK_IO_NATIVE_ALIGNED>(ptr);
} };
}
template <int M, hkUint32 byteAddressOffset>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackSecondHalf8WithOffset(const void* base[M], hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackSecondWithOffsetH<M, byteAddressOffset>::apply(vOut.m_vec.v, base);
}







namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackH {
HK_FORCE_INLINE static void apply(const hkVector4f* v0, const hkVector4f* v1, hkHalf* HK_RESTRICT base)
{
	hkHalf* base0 = hkAddByteOffset( base, (I-1) * byteAddressIncrement ); 
	scatterPackH<I-1, byteAddressIncrement>::apply(v0, v1, base);
	v0[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
	v1[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0+4);
} };
template <hkUint32 byteAddressIncrement> struct scatterPackH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v0, const hkVector4f* v1, hkHalf* HK_RESTRICT base)
{
	v0[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base);
	v1[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base+4);
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPack(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkHalf* HK_RESTRICT base)
{
	hkMxVectorfUtil_Implementation::scatterPackH<M, byteAddressIncrement>::apply(v0.m_vec.v, v1.m_vec.v, base);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackHu {
HK_FORCE_INLINE static void apply(const hkVector4f* v0, const hkVector4f* v1, hkHalf* HK_RESTRICT base, const hkUint16* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[I-1] * byteAddressIncrement ); 
	scatterPackHu<I-1, byteAddressIncrement>::apply(v0, v1, base, indices);
	v0[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
	v1[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0+4);
} };
template <hkUint32 byteAddressIncrement> struct scatterPackHu<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v0, const hkVector4f* v1, hkHalf* HK_RESTRICT base, const hkUint16* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[0] * byteAddressIncrement ); 
	v0[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
	v1[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0+4);
} };
}
template <int M, hkUint32 byteAddressIncrement> 
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPack(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkHalf* base, const hkUint16* indices)
{
	hkMxVectorfUtil_Implementation::scatterPackHu<M, byteAddressIncrement>::apply(v0.m_vec.v, v1.m_vec.v, base, indices);
}

namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackHui {
HK_FORCE_INLINE static void apply(const hkVector4f* v0, const hkVector4f* v1, hkHalf* HK_RESTRICT base, const hkInt32* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[I-1] * byteAddressIncrement ); 
	scatterPackHui<I-1, byteAddressIncrement>::apply(v0, v1, base, indices);
	v0[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
	v1[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0+4);
} };
template <hkUint32 byteAddressIncrement> struct scatterPackHui<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v0, const hkVector4f* v1, hkHalf* HK_RESTRICT base, const hkInt32* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[0] * byteAddressIncrement ); 
	v0[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
	v1[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0+4);
} };
}
template <int M, hkUint32 byteAddressIncrement> 
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPack(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkHalf* base, const hkInt32* indices)
{
	hkMxVectorfUtil_Implementation::scatterPackHui<M, byteAddressIncrement>::apply(v0.m_vec.v, v1.m_vec.v, base, indices);
}



namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteOffset> struct scatterPackWithOffsetH {
HK_FORCE_INLINE static void apply(const hkVector4f* v0, const hkVector4f* v1, void** base)
{
	hkHalf* base0 = (hkHalf*)hkAddByteOffset( base[I-1], byteOffset ); 
	scatterPackWithOffsetH<I-1, byteOffset>::apply(v0, v1, base);
	v0[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
	v1[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0+4);
} };
template <hkUint32 byteOffset> struct scatterPackWithOffsetH<1, byteOffset> {
HK_FORCE_INLINE static void apply(const hkVector4f* v0, const hkVector4f* v1, void** base)
{
	hkHalf* base0 = (hkHalf*)hkAddByteOffset( base[0], byteOffset ); 
	v0[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
	v1[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0+4);
} };
}
template <int M, hkUint32 byteOffset>
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPackHalf8WithOffset(hkMxVectorfParameter v0, hkMxVectorfParameter v1, void* base[M])
{
	hkMxVectorfUtil_Implementation::scatterPackWithOffsetH<M, byteOffset>::apply(v0.m_vec.v, v1.m_vec.v, base);
}




//
//
//
namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackFirstH {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base)
{
	hkHalf* base0 = hkAddByteOffset( base, (I-1) * byteAddressIncrement ); 
	scatterPackFirstH<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
template <hkUint32 byteAddressIncrement> struct scatterPackFirstH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base)
{
	v[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base);
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPackFirst(hkMxVectorfParameter v, hkHalf* HK_RESTRICT base)
{
	hkMxVectorfUtil_Implementation::scatterPackFirstH<M, byteAddressIncrement>::apply(v.m_vec.v, base);
}



//
//
//
namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackOneH {
	HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base)
	{
		hkHalf* base0 = hkAddByteOffset( base, (I-1) * byteAddressIncrement ); 
		scatterPackOneH<I-1, byteAddressIncrement>::apply(v, base);
		v[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
	} };
template <hkUint32 byteAddressIncrement> struct scatterPackOneH<1, byteAddressIncrement> {
	HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base)
	{
		v[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base);
	} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPack(hkMxVectorfParameter v, hkHalf* HK_RESTRICT base)
{
	hkMxVectorfUtil_Implementation::scatterPackOneH<M, byteAddressIncrement>::apply(v.m_vec.v, base);
}




//
//
//

namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackFirstHu {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base, const hkUint16* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[I-1] * byteAddressIncrement ); 
	scatterPackFirstHu<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
template <hkUint32 byteAddressIncrement> struct scatterPackFirstHu<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base, const hkUint16* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[0] * byteAddressIncrement ); 
	v[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
}
template <int M, hkUint32 byteAddressIncrement> 
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPackFirst(hkMxVectorfParameter v, hkHalf* base, const hkUint16* indices)
{
	hkMxVectorfUtil_Implementation::scatterPackFirstHu<M, byteAddressIncrement>::apply(v.m_vec.v, base, indices);
}

namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackFirstHui {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base, const hkInt32* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[I-1] * byteAddressIncrement ); 
	scatterPackFirstHui<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
template <hkUint32 byteAddressIncrement> struct scatterPackFirstHui<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base, const hkInt32* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[0] * byteAddressIncrement ); 
	v[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
}
template <int M, hkUint32 byteAddressIncrement> 
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPackFirst(hkMxVectorfParameter v, hkHalf* base, const hkInt32* indices)
{
	hkMxVectorfUtil_Implementation::scatterPackFirstHui<M, byteAddressIncrement>::apply(v.m_vec.v, base, indices);
}



namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteOffset> struct scatterPackFirstWithOffsetH {
HK_FORCE_INLINE static void apply(const hkVector4f* v, void** base)
{
	hkHalf* base0 = (hkHalf*)hkAddByteOffset( base[I-1], byteOffset );
	scatterPackFirstWithOffsetH<I-1, byteOffset>::apply(v, base);
	v[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
template <hkUint32 byteOffset> struct scatterPackFirstWithOffsetH<1, byteOffset> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, void** base)
{
	hkHalf* base0 = (hkHalf*)hkAddByteOffset( base[0], byteOffset ); 
	v[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
}
template <int M, hkUint32 byteOffset>
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPackFirstHalf8WithOffset(hkMxVectorfParameter v, void* base[M])
{
	hkMxVectorfUtil_Implementation::scatterPackFirstWithOffsetH<M, byteOffset>::apply(v.m_vec.v, base);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackSecondH {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base)
{
	hkHalf* base0 = hkAddByteOffset( base, (I-1) * byteAddressIncrement +4 ); 
	scatterPackSecondH<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
template <hkUint32 byteAddressIncrement> struct scatterPackSecondH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base)
{
	v[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base+4);
} };
}
template <int M, hkUint32 byteAddressIncrement>
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPackSecond(hkMxVectorfParameter v, hkHalf* HK_RESTRICT base)
{
	hkMxVectorfUtil_Implementation::scatterPackSecondH<M, byteAddressIncrement>::apply(v.m_vec.v, base);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackSecondHu {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base, const hkUint16* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[I-1] * byteAddressIncrement +4); 
	scatterPackSecondHu<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
template <hkUint32 byteAddressIncrement> struct scatterPackSecondHu<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base, const hkUint16* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[0] * byteAddressIncrement +4); 
	v[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
}
template <int M, hkUint32 byteAddressIncrement> 
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPackSecond(hkMxVectorfParameter v, hkHalf* base, const hkUint16* indices)
{
	hkMxVectorfUtil_Implementation::scatterPackSecondHu<M, byteAddressIncrement>::apply(v.m_vec.v, base, indices);
}

namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterPackSecondHui {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base, const hkInt32* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[I-1] * byteAddressIncrement +4); 
	scatterPackSecondHui<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
template <hkUint32 byteAddressIncrement> struct scatterPackSecondHui<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* HK_RESTRICT base, const hkInt32* indices)
{
	hkHalf* base0 = hkAddByteOffset( base, indices[0] * byteAddressIncrement +4); 
	v[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
}
template <int M, hkUint32 byteAddressIncrement> 
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPackSecond(hkMxVectorfParameter v, hkHalf* base, const hkInt32* indices)
{
	hkMxVectorfUtil_Implementation::scatterPackSecondHui<M, byteAddressIncrement>::apply(v.m_vec.v, base, indices);
}



namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteOffset> struct scatterPackSecondWithOffsetH {
HK_FORCE_INLINE static void apply(const hkVector4f* v, void** base)
{
	hkHalf* base0 = (hkHalf*)hkAddByteOffset( base[I-1], byteOffset ); 
	scatterPackSecondWithOffsetH<I-1, byteOffset>::apply(v, base);
	v[I-1].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
template <hkUint32 byteOffset> struct scatterPackSecondWithOffsetH<1, byteOffset> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, void** base)
{
	hkHalf* base0 = (hkHalf*)hkAddByteOffset( base[0], byteOffset ); 
	v[0].store<4,HK_IO_NATIVE_ALIGNED,HK_ROUND_TRUNCATE>(base0);
} };
}
template <int M, hkUint32 byteOffset>
HK_FORCE_INLINE /*static*/ void HK_CALL scatterPackSecondHalf8WithOffset(hkMxVectorfParameter v, void* base[M])
{
	hkMxVectorfUtil_Implementation::scatterPackSecondWithOffsetH<M, byteOffset>::apply(v.m_vec.v, base);
}










namespace hkMxVectorfUtil_Implementation
{
	template <int I, hkUint32 byteOffset> struct gatherUnpackPackedVectorWithOffsetH {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
		{
			const hkPackedVector3* HK_RESTRICT ptr0 = (const hkPackedVector3*)hkAddByteOffsetConst(base[I-1], byteOffset); 
			gatherUnpackPackedVectorWithOffsetH<I-1, byteOffset>::apply(v, base);
			ptr0->unpack(v[I-1]);
		}
	};

	template <hkUint32 byteOffset> struct gatherUnpackPackedVectorWithOffsetH<0, byteOffset> {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base){}
	};
}	// namespace

template <int M, hkUint32 byteAddressOffset>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackPackedVectorWithOffset(const void* base[M], hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackPackedVectorWithOffsetH<M, byteAddressOffset>::apply(vOut.m_vec.v, base);
}





namespace hkMxVectorfUtil_Implementation
{
	template <int I, hkUint32 byteOffset> struct gather3WComponentsH {
		HK_FORCE_INLINE static void apply(hkVector4f* HK_RESTRICT v, const void** base)
		{
			const hkVector4f* HK_RESTRICT ptr0 = (const hkVector4f*)hkAddByteOffsetConst(base[I-1], byteOffset); 
			gather3WComponentsH<I-1, byteOffset>::apply(v, base);

			hkSimdFloat32 x = ptr0[0].getComponent<3>();
			hkSimdFloat32 y = ptr0[1].getComponent<3>();
			hkSimdFloat32 z = ptr0[2].getComponent<3>();
			v[I-1].set( x,y,z,z);
		}
	};

	template <hkUint32 byteOffset> struct gather3WComponentsH<0, byteOffset> {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base){}
	};
}	// namespace

template <int M, hkUint32 byteAddressOffset>
HK_FORCE_INLINE /*static*/ void HK_CALL gather3WComponents(const void* base[M], hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gather3WComponentsH<M, byteAddressOffset>::apply(vOut.m_vec.v, base);
}





namespace hkMxVectorfUtil_Implementation
{
template <int I, hkUint32 byteOffset> struct gatherUnpackPackedUnitVectorWithOffsetH {
HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
{
	const hkPackedUnitVector<4>* HK_RESTRICT ptr0 = (const hkPackedUnitVector<4>*)hkAddByteOffsetConst(base[I-1], byteOffset); 
	gatherUnpackPackedUnitVectorWithOffsetH<I-1, byteOffset>::apply(v, base);
	ptr0->unpack(&v[I-1]);
} };
template <hkUint32 byteOffset> struct gatherUnpackPackedUnitVectorWithOffsetH<1, byteOffset> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
{
	const hkPackedUnitVector<4>* HK_RESTRICT ptr = (const hkPackedUnitVector<4>*)hkAddByteOffsetConst(base[0], byteOffset); 
	ptr->unpack(&v[0]);
} };
}
template <int M, hkUint32 byteAddressOffset>
HK_FORCE_INLINE /*static*/ void HK_CALL gatherUnpackPackedUnitVectorWithOffset(const void* base[M], hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::gatherUnpackPackedUnitVectorWithOffsetH<M, byteAddressOffset>::apply(vOut.m_vec.v, base);
}






















namespace hkMxVectorfUtil_Implementation
{

HK_FORCE_INLINE static void transformPositionH(hkMxTransformfParameter mat, const hkMxVectorf<4>& vIn, hkMxVectorf<4>& vOut)
{
	// the vectors in mat are the columns of a transform matrix
	hkVector4f m0,m1,m2,m3;
	{
		mat.getVector<0>(m0);
		mat.getVector<1>(m1);
		mat.getVector<2>(m2);
		mat.getVector<3>(m3);
	}

	hkVector4f in0,in1,in2,in3;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
		vIn.getVector<2>(in2);
		vIn.getVector<3>(in3);
	}

	hkVector4f xb,yb,zb;
	hkVector4f out;
	{
		xb.setBroadcast<0>(in0);
		yb.setBroadcast<1>(in0);
		zb.setBroadcast<2>(in0);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<0>(out);
	}
	{
		xb.setBroadcast<0>(in1);
		yb.setBroadcast<1>(in1);
		zb.setBroadcast<2>(in1);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<1>(out);
	}
	{
		xb.setBroadcast<0>(in2);
		yb.setBroadcast<1>(in2);
		zb.setBroadcast<2>(in2);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<2>(out);
	}
	{
		xb.setBroadcast<0>(in3);
		yb.setBroadcast<1>(in3);
		zb.setBroadcast<2>(in3);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<3>(out);
	}
}

HK_FORCE_INLINE static void transformPositionH(hkMxTransformfParameter mat, const hkMxVectorf<3>& vIn, hkMxVectorf<3>& vOut)
{
	// the vectors in mat are the columns of a transform matrix
	hkVector4f m0,m1,m2,m3;
	{
		mat.getVector<0>(m0);
		mat.getVector<1>(m1);
		mat.getVector<2>(m2);
		mat.getVector<3>(m3);
	}

	hkVector4f in0,in1,in2;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
		vIn.getVector<2>(in2);
	}

	hkVector4f xb,yb,zb;
	hkVector4f out;
	{
		xb.setBroadcast<0>(in0);
		yb.setBroadcast<1>(in0);
		zb.setBroadcast<2>(in0);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<0>(out);
	}
	{
		xb.setBroadcast<0>(in1);
		yb.setBroadcast<1>(in1);
		zb.setBroadcast<2>(in1);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<1>(out);
	}
	{
		xb.setBroadcast<0>(in2);
		yb.setBroadcast<1>(in2);
		zb.setBroadcast<2>(in2);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<2>(out);
	}
}

HK_FORCE_INLINE static void transformPositionH(hkMxTransformfParameter mat, const hkMxVectorf<2>& vIn, hkMxVectorf<2>& vOut)
{
	// the vectors in mat are the columns of a transform matrix
	hkVector4f m0,m1,m2,m3;
	{
		mat.getVector<0>(m0);
		mat.getVector<1>(m1);
		mat.getVector<2>(m2);
		mat.getVector<3>(m3);
	}

	hkVector4f in0,in1;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
	}

	hkVector4f xb,yb,zb;
	hkVector4f out;
	{
		xb.setBroadcast<0>(in0);
		yb.setBroadcast<1>(in0);
		zb.setBroadcast<2>(in0);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<0>(out);
	}
	{
		xb.setBroadcast<0>(in1);
		yb.setBroadcast<1>(in1);
		zb.setBroadcast<2>(in1);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<1>(out);
	}
}

HK_FORCE_INLINE static void transformPositionH(hkMxTransformfParameter mat, const hkMxVectorf<1>& vIn, hkMxVectorf<1>& vOut)
{
	vOut.m_vec.v[0]._setTransformedPos((const hkTransformf&)mat.m_vec.v[0], vIn.m_vec.v[0]);
}
}
template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL transformPosition(hkMxTransformfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::transformPositionH(mat, vIn, vOut);
}



namespace hkMxVectorfUtil_Implementation
{

HK_FORCE_INLINE static void transformTransposePositionH(hkMxTransformfParameter mat, const hkMxVectorf<4>& vIn, hkMxVectorf<4>& vOut)
{
	// the vectors in mat are the columns of a transform matrix
	hkVector4f m0,m1,m2,m3;
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	mat.getVector<0>(m0);
	mat.getVector<1>(m1);
	mat.getVector<2>(m2);
	mat.getVector<3>(m3);
	HK_TRANSPOSE4f( m0, m1, m2, m3 );
#else
	m0.set( mat.m_vec.v[0](0), mat.m_vec.v[1](0), mat.m_vec.v[2](0), mat.m_vec.v[3](0) );
	m1.set( mat.m_vec.v[0](1), mat.m_vec.v[1](1), mat.m_vec.v[2](1), mat.m_vec.v[3](1) );
	m2.set( mat.m_vec.v[0](2), mat.m_vec.v[1](2), mat.m_vec.v[2](2), mat.m_vec.v[3](2) );
	m3.set( mat.m_vec.v[0](3), mat.m_vec.v[1](3), mat.m_vec.v[2](3), mat.m_vec.v[3](3) );
#endif

	hkVector4f in0,in1,in2,in3;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
		vIn.getVector<2>(in2);
		vIn.getVector<3>(in3);
	}

	hkVector4f xb,yb,zb;
	hkVector4f out;
	{
		xb.setBroadcast<0>(in0);
		yb.setBroadcast<1>(in0);
		zb.setBroadcast<2>(in0);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<0>(out);
	}
	{
		xb.setBroadcast<0>(in1);
		yb.setBroadcast<1>(in1);
		zb.setBroadcast<2>(in1);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<1>(out);
	}
	{
		xb.setBroadcast<0>(in2);
		yb.setBroadcast<1>(in2);
		zb.setBroadcast<2>(in2);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<2>(out);
	}
	{
		xb.setBroadcast<0>(in3);
		yb.setBroadcast<1>(in3);
		zb.setBroadcast<2>(in3);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<3>(out);
	}
}

HK_FORCE_INLINE static void transformTransposePositionH(hkMxTransformfParameter mat, const hkMxVectorf<3>& vIn, hkMxVectorf<3>& vOut)
{
	// the vectors in mat are the columns of a transform matrix
	hkVector4f m0,m1,m2,m3;
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	mat.getVector<0>(m0);
	mat.getVector<1>(m1);
	mat.getVector<2>(m2);
	mat.getVector<3>(m3);
	HK_TRANSPOSE4f( m0, m1, m2, m3 );
#else
	m0.set( mat.m_vec.v[0](0), mat.m_vec.v[1](0), mat.m_vec.v[2](0), mat.m_vec.v[3](0) );
	m1.set( mat.m_vec.v[0](1), mat.m_vec.v[1](1), mat.m_vec.v[2](1), mat.m_vec.v[3](1) );
	m2.set( mat.m_vec.v[0](2), mat.m_vec.v[1](2), mat.m_vec.v[2](2), mat.m_vec.v[3](2) );
	m3.set( mat.m_vec.v[0](3), mat.m_vec.v[1](3), mat.m_vec.v[2](3), mat.m_vec.v[3](3) );
#endif

	hkVector4f in0,in1,in2;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
		vIn.getVector<2>(in2);
	}

	hkVector4f xb,yb,zb;
	hkVector4f out;
	{
		xb.setBroadcast<0>(in0);
		yb.setBroadcast<1>(in0);
		zb.setBroadcast<2>(in0);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<0>(out);
	}
	{
		xb.setBroadcast<0>(in1);
		yb.setBroadcast<1>(in1);
		zb.setBroadcast<2>(in1);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<1>(out);
	}
	{
		xb.setBroadcast<0>(in2);
		yb.setBroadcast<1>(in2);
		zb.setBroadcast<2>(in2);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<2>(out);
	}
}

HK_FORCE_INLINE static void transformTransposePositionH(hkMxTransformfParameter mat, const hkMxVectorf<2>& vIn, hkMxVectorf<2>& vOut)
{
	// the vectors in mat are the columns of a transform matrix
	hkVector4f m0,m1,m2,m3;
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	mat.getVector<0>(m0);
	mat.getVector<1>(m1);
	mat.getVector<2>(m2);
	mat.getVector<3>(m3);
	HK_TRANSPOSE4f( m0, m1, m2, m3 );
#else
	m0.set( mat.m_vec.v[0](0), mat.m_vec.v[1](0), mat.m_vec.v[2](0), mat.m_vec.v[3](0) );
	m1.set( mat.m_vec.v[0](1), mat.m_vec.v[1](1), mat.m_vec.v[2](1), mat.m_vec.v[3](1) );
	m2.set( mat.m_vec.v[0](2), mat.m_vec.v[1](2), mat.m_vec.v[2](2), mat.m_vec.v[3](2) );
	m3.set( mat.m_vec.v[0](3), mat.m_vec.v[1](3), mat.m_vec.v[2](3), mat.m_vec.v[3](3) );
#endif

	hkVector4f in0,in1;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
	}

	hkVector4f xb,yb,zb;
	hkVector4f out;
	{
		xb.setBroadcast<0>(in0);
		yb.setBroadcast<1>(in0);
		zb.setBroadcast<2>(in0);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<0>(out);
	}
	{
		xb.setBroadcast<0>(in1);
		yb.setBroadcast<1>(in1);
		zb.setBroadcast<2>(in1);

		out.setAddMul( m3, xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<1>(out);
	}
}

HK_FORCE_INLINE static void transformTransposePositionH(hkMxTransformfParameter mat, const hkMxVectorf<1>& vIn, hkMxVectorf<1>& vOut)
{
	vOut.m_vec.v[0]._setTransformedInversePos((const hkTransformf&)mat.m_vec.v[0], vIn.m_vec.v[0]);
}
}

template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL transformTransposePosition(hkMxTransformfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::transformTransposePositionH(mat, vIn, vOut);
}





namespace hkMxVectorfUtil_Implementation
{


	HK_FORCE_INLINE static void rotateDirectionH( hkMxTransformfParameter mat, const hkMxVectorf<4>& vIn, hkMxVectorf<4>& vOut)
	{
		// the vectors in mat are the columns of a transform matrix
		hkVector4f m0,m1,m2; 
		{
			mat.getVector<0>(m0);
			mat.getVector<1>(m1);
			mat.getVector<2>(m2);
		}

		hkVector4f in0,in1,in2,in3;
		{
			vIn.getVector<0>(in0);
			vIn.getVector<1>(in1);
			vIn.getVector<2>(in2);
			vIn.getVector<3>(in3);
		}

		hkVector4f xb,yb,zb;
		hkVector4f out;
		{
			xb.setBroadcast<0>(in0);
			yb.setBroadcast<1>(in0);
			zb.setBroadcast<2>(in0);

			out.setMul( xb, m0 );
			out.addMul( yb, m1 );
			out.addMul( zb, m2 );
			vOut.setVector<0>(out);
		}
		{
			xb.setBroadcast<0>(in1);
			yb.setBroadcast<1>(in1);
			zb.setBroadcast<2>(in1);

			out.setMul( xb, m0 );
			out.addMul( yb, m1 );
			out.addMul( zb, m2 );
			vOut.setVector<1>(out);
		}
		{
			xb.setBroadcast<0>(in2);
			yb.setBroadcast<1>(in2);
			zb.setBroadcast<2>(in2);

			out.setMul( xb, m0 );
			out.addMul( yb, m1 );
			out.addMul( zb, m2 );
			vOut.setVector<2>(out);
		}
		{
			xb.setBroadcast<0>(in3);
			yb.setBroadcast<1>(in3);
			zb.setBroadcast<2>(in3);

			out.setMul( xb, m0 );
			out.addMul( yb, m1 );
			out.addMul( zb, m2 );
			vOut.setVector<3>(out);
		}
	}

	HK_FORCE_INLINE static void rotateDirectionH( hkMxTransformfParameter mat, const hkMxVectorf<3>& vIn, hkMxVectorf<3>& vOut)
	{
		// the vectors in mat are the columns of a transform matrix
		hkVector4f m0,m1,m2; 
		{
			mat.getVector<0>(m0);
			mat.getVector<1>(m1);
			mat.getVector<2>(m2);
		}

		hkVector4f in0,in1,in2;
		{
			vIn.getVector<0>(in0);
			vIn.getVector<1>(in1);
			vIn.getVector<2>(in2);
		}

		hkVector4f xb,yb,zb;
		hkVector4f out;
		{
			xb.setBroadcast<0>(in0);
			yb.setBroadcast<1>(in0);
			zb.setBroadcast<2>(in0);

			out.setMul( xb, m0 );
			out.addMul( yb, m1 );
			out.addMul( zb, m2 );
			vOut.setVector<0>(out);
		}
		{
			xb.setBroadcast<0>(in1);
			yb.setBroadcast<1>(in1);
			zb.setBroadcast<2>(in1);

			out.setMul( xb, m0 );
			out.addMul( yb, m1 );
			out.addMul( zb, m2 );
			vOut.setVector<1>(out);
		}
		{
			xb.setBroadcast<0>(in2);
			yb.setBroadcast<1>(in2);
			zb.setBroadcast<2>(in2);

			out.setMul( xb, m0 );
			out.addMul( yb, m1 );
			out.addMul( zb, m2 );
			vOut.setVector<2>(out);
		}
	}

	HK_FORCE_INLINE static void rotateDirectionH( hkMxTransformfParameter mat, const hkMxVectorf<2>& vIn, hkMxVectorf<2>& vOut)
	{
		// the vectors in mat are the columns of a transform matrix
		hkVector4f m0,m1,m2; 
		{
			mat.getVector<0>(m0);
			mat.getVector<1>(m1);
			mat.getVector<2>(m2);
		}

		hkVector4f in0,in1;
		{
			vIn.getVector<0>(in0);
			vIn.getVector<1>(in1);
		}

		hkVector4f xb,yb,zb;
		hkVector4f out;
		{
			xb.setBroadcast<0>(in0);
			yb.setBroadcast<1>(in0);
			zb.setBroadcast<2>(in0);

			out.setMul( xb, m0 );
			out.addMul( yb, m1 );
			out.addMul( zb, m2 );
			vOut.setVector<0>(out);
		}
		{
			xb.setBroadcast<0>(in1);
			yb.setBroadcast<1>(in1);
			zb.setBroadcast<2>(in1);

			out.setMul( xb, m0 );
			out.addMul( yb, m1 );
			out.addMul( zb, m2 );
			vOut.setVector<1>(out);
		}
	}

	HK_FORCE_INLINE static void rotateDirectionH( hkMxTransformfParameter mat, const hkMxVectorf<1>& vIn, hkMxVectorf<1>& vOut)
	{
		vOut.m_vec.v[0]._setRotatedDir((const hkRotationf&)mat.m_vec.v[0], vIn.m_vec.v[0]);
	}
}

template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL rotateDirection( hkMxTransformfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::rotateDirectionH(mat, vIn, vOut);
}


namespace hkMxVectorfUtil_Implementation
{
HK_FORCE_INLINE static void rotateInverseDirectionH( hkMxTransformfParameter mat, const hkMxVectorf<4>& vIn, hkMxVectorf<4>& vOut)
{
	// the vectors in mat are the columns of a transform matrix
	hkVector4f m0,m1,m2; 
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	mat.getVector<0>(m0);
	mat.getVector<1>(m1);
	mat.getVector<2>(m2);
	HK_TRANSPOSE3f( m0, m1, m2 );
#else
	m0.set( mat.m_vec.v[0](0), mat.m_vec.v[1](0), mat.m_vec.v[2](0), hkFloat32(0) );
	m1.set( mat.m_vec.v[0](1), mat.m_vec.v[1](1), mat.m_vec.v[2](1), hkFloat32(0) );
	m2.set( mat.m_vec.v[0](2), mat.m_vec.v[1](2), mat.m_vec.v[2](2), hkFloat32(0) );
#endif

	hkVector4f in0,in1,in2,in3;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
		vIn.getVector<2>(in2);
		vIn.getVector<3>(in3);
	}

	hkVector4f xb,yb,zb;
	hkVector4f out;
	{
		xb.setBroadcast<0>(in0);
		yb.setBroadcast<1>(in0);
		zb.setBroadcast<2>(in0);

		out.setMul( xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<0>(out);
	}
	{
		xb.setBroadcast<0>(in1);
		yb.setBroadcast<1>(in1);
		zb.setBroadcast<2>(in1);

		out.setMul( xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<1>(out);
	}
	{
		xb.setBroadcast<0>(in2);
		yb.setBroadcast<1>(in2);
		zb.setBroadcast<2>(in2);

		out.setMul( xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<2>(out);
	}
	{
		xb.setBroadcast<0>(in3);
		yb.setBroadcast<1>(in3);
		zb.setBroadcast<2>(in3);

		out.setMul( xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<3>(out);
	}
}


HK_FORCE_INLINE static void rotateInverseDirectionH( hkMxTransformfParameter mat, const hkMxVectorf<3>& vIn, hkMxVectorf<3>& vOut)
{
	// the vectors in mat are the columns of a transform matrix
	hkVector4f m0,m1,m2; 
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	mat.getVector<0>(m0);
	mat.getVector<1>(m1);
	mat.getVector<2>(m2);
	HK_TRANSPOSE3f( m0, m1, m2 );
#else
	m0.set( mat.m_vec.v[0](0), mat.m_vec.v[1](0), mat.m_vec.v[2](0), hkFloat32(0) );
	m1.set( mat.m_vec.v[0](1), mat.m_vec.v[1](1), mat.m_vec.v[2](1), hkFloat32(0) );
	m2.set( mat.m_vec.v[0](2), mat.m_vec.v[1](2), mat.m_vec.v[2](2), hkFloat32(0) );
#endif

	hkVector4f in0,in1,in2;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
		vIn.getVector<2>(in2);
	}

	hkVector4f xb,yb,zb;
	hkVector4f out;
	{
		xb.setBroadcast<0>(in0);
		yb.setBroadcast<1>(in0);
		zb.setBroadcast<2>(in0);

		out.setMul( xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<0>(out);
	}
	{
		xb.setBroadcast<0>(in1);
		yb.setBroadcast<1>(in1);
		zb.setBroadcast<2>(in1);

		out.setMul( xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<1>(out);
	}
	{
		xb.setBroadcast<0>(in2);
		yb.setBroadcast<1>(in2);
		zb.setBroadcast<2>(in2);

		out.setMul( xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<2>(out);
	}
}

HK_FORCE_INLINE static void rotateInverseDirectionH( hkMxTransformfParameter mat, const hkMxVectorf<2>& vIn, hkMxVectorf<2>& vOut)
{
	// the vectors in mat are the columns of a transform matrix
	hkVector4f m0,m1,m2; 
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	mat.getVector<0>(m0);
	mat.getVector<1>(m1);
	mat.getVector<2>(m2);
	HK_TRANSPOSE3f( m0, m1, m2 );
#else
	m0.set( mat.m_vec.v[0](0), mat.m_vec.v[1](0), mat.m_vec.v[2](0), hkFloat32(0) );
	m1.set( mat.m_vec.v[0](1), mat.m_vec.v[1](1), mat.m_vec.v[2](1), hkFloat32(0) );
	m2.set( mat.m_vec.v[0](2), mat.m_vec.v[1](2), mat.m_vec.v[2](2), hkFloat32(0) );
#endif

	hkVector4f in0,in1;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
	}

	hkVector4f xb,yb,zb;
	hkVector4f out;
	{
		xb.setBroadcast<0>(in0);
		yb.setBroadcast<1>(in0);
		zb.setBroadcast<2>(in0);

		out.setMul( xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<0>(out);
	}
	{
		xb.setBroadcast<0>(in1);
		yb.setBroadcast<1>(in1);
		zb.setBroadcast<2>(in1);

		out.setMul( xb, m0 );
		out.addMul( yb, m1 );
		out.addMul( zb, m2 );
		vOut.setVector<1>(out);
	}
}
HK_FORCE_INLINE static void rotateInverseDirectionH( hkMxTransformfParameter mat, const hkMxVectorf<1>& vIn, hkMxVectorf<1>& vOut)
{
	vOut.m_vec.v[0]._setRotatedInverseDir((const hkRotationf&)mat.m_vec.v[0], vIn.m_vec.v[0]); 
}
}

template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL rotateInverseDirection( hkMxTransformfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::rotateInverseDirectionH(mat, vIn, vOut);
}




namespace hkMxVectorfUtil_Implementation
{
template <int I>
HK_FORCE_INLINE void rotateDirH(const hkQuaternionf* mat, const hkVector4f* vIn, hkVector4f* vOut)
{
	rotateDirH<I-1>(mat, vIn, vOut);
	vOut[I-1]._setRotatedDir( mat[I-1], vIn[I-1] );
}
template <>
HK_FORCE_INLINE void rotateDirH<1>(const hkQuaternionf* mat, const hkVector4f* vIn, hkVector4f* vOut)
{
	vOut[0]._setRotatedDir( mat[0], vIn[0] );
}
}
template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL rotateDirection( hkMxQuaternionfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::rotateDirH<M>((const hkQuaternionf*)mat.m_vec.v, vIn.m_vec.v, vOut.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I>
HK_FORCE_INLINE void rotateDirH(const hkTransformf* mat, const hkVector4f* vIn, hkVector4f* vOut)
{
	rotateDirH<I-1>(mat, vIn, vOut);
	vOut[I-1]._setRotatedDir( mat[I-1].getRotation(), vIn[I-1] );
}
template <>
HK_FORCE_INLINE void rotateDirH<1>(const hkTransformf* mat, const hkVector4f* vIn, hkVector4f* vOut)
{
	vOut[0]._setRotatedDir( mat[0].getRotation(), vIn[0] );
}
}
template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL rotateDirection( const hkTransformf* mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::rotateDirH<M>(mat, vIn.m_vec.v, vOut.m_vec.v);
}


namespace hkMxVectorfUtil_Implementation
{
template <int I>
HK_FORCE_INLINE void transformPosH(const hkTransformf* mat, const hkVector4f* vIn, hkVector4f* vOut)
{
	transformPosH<I-1>(mat, vIn, vOut);
	vOut[I-1]._setTransformedPos( mat[I-1], vIn[I-1] );
}
template <>
HK_FORCE_INLINE void transformPosH<1>(const hkTransformf* mat, const hkVector4f* vIn, hkVector4f* vOut)
{
	vOut[0]._setTransformedPos( mat[0], vIn[0] );
}
}
template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL transformPosition( const hkTransformf* mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut)
{
	hkMxVectorfUtil_Implementation::transformPosH<M>(mat, vIn.m_vec.v, vOut.m_vec.v);
}


HK_FORCE_INLINE /*static*/ void HK_CALL transform4Positions(hkMxTransformfParameter mat0, hkMxTransformfParameter mat1, hkMxTransformfParameter mat2, hkMxTransformfParameter mat3, const hkMxVectorf<4>& vIn, hkMxVectorf<4>& vOut)
{
	hkVector4f in0,in1,in2,in3;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
		vIn.getVector<2>(in2);
		vIn.getVector<3>(in3);
	}

	//	creates better assembly
	//	mat0 x in0
	hkVector4f m00,m10,m20,m30;
	hkVector4f xb0,yb0,zb0;
	hkVector4f out0;

	//	mat1 x in1
	hkVector4f m01,m11,m21,m31;
	hkVector4f xb1,yb1,zb1;
	hkVector4f out1;

	//	mat2 x in2
	hkVector4f m02,m12,m22,m32;
	hkVector4f xb2,yb2,zb2;
	hkVector4f out2;

	//	mat3 x in3
	hkVector4f m03,m13,m23,m33;
	hkVector4f xb3,yb3,zb3;
	hkVector4f out3;
	{
		// get matrix
		mat0.getVector<0>(m00);
		mat0.getVector<1>(m10);
		mat0.getVector<2>(m20);
		mat0.getVector<3>(m30);

		mat1.getVector<0>(m01);
		mat1.getVector<1>(m11);
		mat1.getVector<2>(m21);
		mat1.getVector<3>(m31);

		mat2.getVector<0>(m02);
		mat2.getVector<1>(m12);
		mat2.getVector<2>(m22);
		mat2.getVector<3>(m32);

		mat3.getVector<0>(m03);
		mat3.getVector<1>(m13);
		mat3.getVector<2>(m23);
		mat3.getVector<3>(m33);

		//	set vector
		xb0.setBroadcast<0>(in0);
		yb0.setBroadcast<1>(in0);
		zb0.setBroadcast<2>(in0);

		xb1.setBroadcast<0>(in1);
		yb1.setBroadcast<1>(in1);
		zb1.setBroadcast<2>(in1);

		xb2.setBroadcast<0>(in2);
		yb2.setBroadcast<1>(in2);
		zb2.setBroadcast<2>(in2);

		xb3.setBroadcast<0>(in3);
		yb3.setBroadcast<1>(in3);
		zb3.setBroadcast<2>(in3);

		//	execute
		out0.setAddMul( m30, xb0, m00 );
		out0.addMul( yb0, m10 );
		out0.addMul( zb0, m20 );
		vOut.setVector<0>(out0);

		out1.setAddMul( m31, xb1, m01 );
		out1.addMul( yb1, m11 );
		out1.addMul( zb1, m21 );
		vOut.setVector<1>(out1);

		out2.setAddMul( m32, xb2, m02 );
		out2.addMul( yb2, m12 );
		out2.addMul( zb2, m22 );
		vOut.setVector<2>(out2);

		out3.setAddMul( m33, xb3, m03 );
		out3.addMul( yb3, m13 );
		out3.addMul( zb3, m23 );
		vOut.setVector<3>(out3);
	}
}

HK_FORCE_INLINE /*static*/ void HK_CALL rotate4Directions(hkMxTransformfParameter mat0, hkMxTransformfParameter mat1, hkMxTransformfParameter mat2, hkMxTransformfParameter mat3, const hkMxVectorf<4>& vIn, hkMxVectorf<4>& vOut)
{
	hkVector4f in0,in1,in2,in3;
	{
		vIn.getVector<0>(in0);
		vIn.getVector<1>(in1);
		vIn.getVector<2>(in2);
		vIn.getVector<3>(in3);
	}

	//	creates better assembly
	//	mat0 x in0
	hkVector4f m00,m10,m20;
	hkVector4f xb0,yb0,zb0;
	hkVector4f out0;

	//	mat1 x in1
	hkVector4f m01,m11,m21;
	hkVector4f xb1,yb1,zb1;
	hkVector4f out1;

	//	mat2 x in2
	hkVector4f m02,m12,m22;
	hkVector4f xb2,yb2,zb2;
	hkVector4f out2;

	//	mat3 x in3
	hkVector4f m03,m13,m23;
	hkVector4f xb3,yb3,zb3;
	hkVector4f out3;
	{
		// get matrix
		mat0.getVector<0>(m00);
		mat0.getVector<1>(m10);
		mat0.getVector<2>(m20);

		mat1.getVector<0>(m01);
		mat1.getVector<1>(m11);
		mat1.getVector<2>(m21);

		mat2.getVector<0>(m02);
		mat2.getVector<1>(m12);
		mat2.getVector<2>(m22);

		mat3.getVector<0>(m03);
		mat3.getVector<1>(m13);
		mat3.getVector<2>(m23);

		//	set vector
		xb0.setBroadcast<0>(in0);
		yb0.setBroadcast<1>(in0);
		zb0.setBroadcast<2>(in0);

		xb1.setBroadcast<0>(in1);
		yb1.setBroadcast<1>(in1);
		zb1.setBroadcast<2>(in1);

		xb2.setBroadcast<0>(in2);
		yb2.setBroadcast<1>(in2);
		zb2.setBroadcast<2>(in2);

		xb3.setBroadcast<0>(in3);
		yb3.setBroadcast<1>(in3);
		zb3.setBroadcast<2>(in3);

		//	execute
		out0.setMul( xb0, m00 );
		out0.addMul( yb0, m10 );
		out0.addMul( zb0, m20 );
		vOut.setVector<0>(out0);

		out1.setMul( xb1, m01 );
		out1.addMul( yb1, m11 );
		out1.addMul( zb1, m21 );
		vOut.setVector<1>(out1);

		out2.setMul( xb2, m02 );
		out2.addMul( yb2, m12 );
		out2.addMul( zb2, m22 );
		vOut.setVector<2>(out2);

		out3.setMul( xb3, m03 );
		out3.addMul( yb3, m13 );
		out3.addMul( zb3, m23 );
		vOut.setVector<3>(out3);
	}
}

} // namespace hkMxVectorUtil

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
