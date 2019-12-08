/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#define MXV_NO_OPERANDS(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void METHOD##H(hkVector4d* v) { METHOD##H<I-1>(v); v[I-1].OP(); } \
	template <> HK_FORCE_INLINE void METHOD##H<1>(hkVector4d* v) { v[0].OP(); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD() { hkMxVectord_Implementation::METHOD##H<M>(m_vec.v); }

#define MXV_OPd_MXVECTOR(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void METHOD##MXV_MXV_MXV(hkVector4d* v, const hkVector4d* v0) { METHOD##MXV_MXV_MXV<I-1>(v, v0); v[I-1].OP(v0[I-1]); } \
	template <> HK_FORCE_INLINE void METHOD##MXV_MXV_MXV<1>(hkVector4d* v, const hkVector4d* v0) { v[0].OP(v0[0]); }	\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxVectordParameter m) { hkMxVectord_Implementation::METHOD##MXV_MXV_MXV<M>(m_vec.v, m.m_vec.v); }

#define MXV_OPd_MXVECTOR_MXVECTOR(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
		template <int I> HK_FORCE_INLINE void OP##H(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1) { OP##H<I-1>(v, v0, v1); v[I-1].OP(v0[I-1], v1[I-1]); } \
		template <> HK_FORCE_INLINE void OP##H<1>(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1) { v[0].OP(v0[0], v1[0]); }								\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxVectordParameter v0, hkMxVectordParameter v1) { hkMxVectord_Implementation::OP##H<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v);	}

#define MXV_OPd_MXQUATERNION_MXVECTOR(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
		template <int I> HK_FORCE_INLINE void OP##H(hkVector4d* v, const hkQuaterniond* v0, const hkVector4d* v1) { OP##H<I-1>(v, v0, v1); v[I-1].OP(v0[I-1], v1[I-1]); } \
		template <> HK_FORCE_INLINE void OP##H<1>(hkVector4d* v, const hkQuaterniond* v0, const hkVector4d* v1) { v[0].OP(v0[0], v1[0]); }									\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxQuaterniondParameter v0, hkMxVectordParameter v1) { hkMxVectord_Implementation::OP##H<M>(m_vec.v, (const hkQuaterniond*)v0.m_vec.v, v1.m_vec.v);	}

#define MXV_OPd_MXVECTOR_MXVECTOR_MXVECTOR(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##H(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1, const hkVector4d* v2) { OP##H<I-1>(v, v0, v1, v2); v[I-1].OP(v0[I-1], v1[I-1], v2[I-1]); } \
	template <> HK_FORCE_INLINE void OP##H<1>(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1, const hkVector4d* v2) { v[0].OP(v0[0], v1[0], v2[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxVectordParameter v0, hkMxVectordParameter v1, hkMxVectordParameter v2) { hkMxVectord_Implementation::OP##H<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v, v2.m_vec.v); }

#define MXV_OPd_MXVECTOR_MXVECTOR_MXSINGLE(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##S2H(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1, hkVector4dParameter v2) { OP##S2H<I-1>(v, v0, v1, v2); v[I-1].OP(v0[I-1], v1[I-1], v2); }\
	template <> HK_FORCE_INLINE void OP##S2H<1>(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1, hkVector4dParameter v2) { v[0].OP(v0[0], v1[0], v2); }\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxVectordParameter v0, hkMxVectordParameter v1, hkMxSingledParameter v2) { hkMxVectord_Implementation::OP##S2H<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v, v2.m_single.s); }

#define MXV_OPd_MXVECTOR_MXVECTOR_MXREAL(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##S2R(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1, const hkSimdDouble64* v2) { OP##S2R<I-1>(v, v0, v1, v2); v[I-1].OP(v0[I-1], v1[I-1], v2[I-1]); }\
	template <> HK_FORCE_INLINE void OP##S2R<1>(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1, const hkSimdDouble64* v2) { v[0].OP(v0[0], v1[0], v2[0]); }\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxVectordParameter v0, hkMxVectordParameter v1, hkMxRealdParameter v2) { hkMxVectord_Implementation::OP##S2R<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v, v2.m_real.r); }

#define MXV_OPd_MXVECTOR_MXSINGLE_MXREAL(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##S2SR(hkVector4d* v, const hkVector4d* v0, hkVector4dParameter v1, const hkSimdDouble64* v2) { OP##S2SR<I-1>(v, v0, v1, v2); v[I-1].OP(v0[I-1], v1, v2[I-1]); }\
	template <> HK_FORCE_INLINE void OP##S2SR<1>(hkVector4d* v, const hkVector4d* v0, hkVector4dParameter v1,   const hkSimdDouble64* v2) { v[0].OP(v0[0], v1, v2[0]); }\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxVectordParameter v0, hkMxSingledParameter v1, hkMxRealdParameter v2) { hkMxVectord_Implementation::OP##S2SR<M>(m_vec.v, v0.m_vec.v, v1.m_single.s, v2.m_real.r); }


#define MXV_OPd_MXREAL(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SHR(hkVector4d* v, const hkSimdDouble64* v0) { OP##SHR<I-1>(v, v0); v[I-1].OP(v0[I-1]); }\
	template <> HK_FORCE_INLINE void OP##SHR<1>(hkVector4d* v, const hkSimdDouble64* v0) { v[0].OP(v0[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxRealdParameter s) { hkMxVectord_Implementation::OP##SHR<M>(m_vec.v, s.m_real.r); }


#define MXV_OPd_MXSINGLE(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SH(hkVector4d* v, hkVector4dParameter v0) { OP##SH<I-1>(v, v0); v[I-1].OP(v0); }\
	template <> HK_FORCE_INLINE void OP##SH<1>(hkVector4d* v, hkVector4dParameter v0) { v[0].OP(v0); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxSingledParameter s) { hkMxVectord_Implementation::OP##SH<M>(m_vec.v, s.m_single.s); }


#define MXV_OPd_MXVECTOR_MXREAL(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SH2R(hkVector4d* v, const hkVector4d* v0, const hkSimdDouble64* v1) { OP##SH2R<I-1>(v, v0, v1); v[I-1].OP(v0[I-1], v1[I-1]); }	\
	template <>   HK_FORCE_INLINE void OP##SH2R<1>(hkVector4d* v, const hkVector4d* v0, const hkSimdDouble64* v1) { v[0].OP(v0[0],v1[0]); }							\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxVectordParameter v0, hkMxRealdParameter r) { hkMxVectord_Implementation::OP##SH2R<M>(m_vec.v, v0.m_vec.v, r.m_real.r); }

#define MXV_OPd_MXREAL_MXVECTOR(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SHR2(hkVector4d* v, const hkSimdDouble64* s0, const hkVector4d* v1) { OP##SHR2<I-1>(v, s0, v1); v[I-1].OP(s0[I-1], v1[I-1]); }	\
	template <>   HK_FORCE_INLINE void OP##SHR2<1>(hkVector4d* v, const hkSimdDouble64* s0, const hkVector4d* v1 ) { v[0].OP(s0[0],v1[0]); }							\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxRealdParameter r, hkMxVectordParameter v0 ) { hkMxVectord_Implementation::OP##SHR2<M>(m_vec.v, r.m_real.r, v0.m_vec.v ); }

#define MXV_OPd_MXREAL_MXSINGLE(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##MX_OP_REAL_SINGLE   (hkVector4d* v, const hkSimdDouble64* s0, hkVector4dParameter v1) { OP##MX_OP_REAL_SINGLE<I-1>(v, s0, v1); v[I-1].OP(s0[I-1], v1); }	\
	template <>      HK_FORCE_INLINE void OP##MX_OP_REAL_SINGLE<1>(hkVector4d* v, const hkSimdDouble64* s0, hkVector4dParameter v1 ) { v[0].OP(s0[0],v1); }							\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxRealdParameter r, hkMxSingledParameter v0 ) { hkMxVectord_Implementation::OP##MX_OP_REAL_SINGLE<M>(m_vec.v, r.m_real.r, v0.m_single.s ); }


#define MXV_OPd_MXVECTOR_MXSINGLE(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SH(hkVector4d* v, const hkVector4d* v0, hkVector4dParameter v1) { OP##SH<I-1>(v, v0, v1); v[I-1].OP(v0[I-1], v1); } \
	template <> HK_FORCE_INLINE void OP##SH<1>(hkVector4d* v, const hkVector4d* v0, hkVector4dParameter v1) { v[0].OP(v0[0], v1); }	\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxVectordParameter v, hkMxSingledParameter s) { hkMxVectord_Implementation::OP##SH<M>(m_vec.v, v.m_vec.v, s.m_single.s); }

#define MXV_OPd_MXSINGLE_MXSINGLE(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##MX_SS(hkVector4d* v, hkVector4dParameter v0, hkVector4dParameter v1) { OP##MX_SS<I-1>(v, v0, v1); v[I-1].OP(v0, v1); } \
	template <> HK_FORCE_INLINE void OP##MX_SS<1>(  hkVector4d* v, hkVector4dParameter v0, hkVector4dParameter v1) { v[0].OP(v0, v1); }	\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxSingledParameter s0, hkMxSingledParameter s1) { hkMxVectord_Implementation::OP##MX_SS<M>(m_vec.v, s0.m_single.s, s1.m_single.s); }

#define MXV_OPd_MXSINGLE_MXVECTOR(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##RSH(hkVector4d* v, hkVector4dParameter v1, const hkVector4d* v0) { OP##RSH<I-1>(v, v1, v0); v[I-1].OP(v1, v0[I-1]); }\
	template <> HK_FORCE_INLINE void OP##RSH<1>(hkVector4d* v, hkVector4dParameter v1, const hkVector4d* v0) { v[0].OP(v1, v0[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxSingledParameter s, hkMxVectordParameter v) { hkMxVectord_Implementation::OP##RSH<M>(m_vec.v, s.m_single.s, v.m_vec.v); }

#define MXV_COMPARE(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##CH(const hkVector4d* v0, const hkVector4d* v1, hkVector4dComparison* mask) { OP##CH<I-1>(v0,v1,mask); mask[I-1] = v0[I-1].OP(v1[I-1]); } \
	template <> HK_FORCE_INLINE void OP##CH<1>(const hkVector4d* v0, const hkVector4d* v1, hkVector4dComparison* mask) { mask[0] = v0[0].OP(v1[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxVectordParameter v1, hkMxMaskd<M>& mask) const { hkMxVectord_Implementation::OP##CH<M>(m_vec.v, v1.m_vec.v, mask.m_comp.c); }

#define MXV_COMPARE_SINGLE(METHOD, OP) \
	namespace hkMxVectord_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##CHS(const hkVector4d* v0, hkVector4dParameter v1, hkVector4dComparison* mask) { OP##CHS<I-1>(v0,v1,mask); mask[I-1] = v0[I-1].OP(v1); }\
	template <> HK_FORCE_INLINE void OP##CHS<1>(const hkVector4d* v0, hkVector4dParameter v1, hkVector4dComparison* mask) { mask[0] = v0[0].OP(v1); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectord<M>::METHOD(hkMxSingledParameter v1, hkMxMaskd<M>& mask) const { hkMxVectord_Implementation::OP##CHS<M>(m_vec.v, v1.m_single.s, mask.m_comp.c); }


#ifndef HK_DISABLE_MATH_CONSTRUCTORS

namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void constructH(hkVector4d* v, hkVector4dParameter v0) { constructH<I-1>(v, v0); v[I-1] = v0; }
template <> HK_FORCE_INLINE void constructH<1>(hkVector4d* v, hkVector4dParameter v0) { v[0] = v0; }
}
template <int M>
HK_FORCE_INLINE hkMxVectord<M>::hkMxVectord(hkVector4dParameter v)
{
	hkMxVectord_Implementation::constructH<M>(m_vec.v, v);
}


namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void constructRealH(hkVector4d* v, const hkSimdDouble64* v0) { constructRealH<I-1>(v, v0); v[I-1].setAll(v0[I-1]); }
template <> HK_FORCE_INLINE void constructRealH<1>(hkVector4d* v, const hkSimdDouble64* v0) { v[0].setAll(v0[0]); }
}
template <int M>
HK_FORCE_INLINE hkMxVectord<M>::hkMxVectord(hkMxRealdParameter v)
{
	hkMxVectord_Implementation::constructRealH<M>(m_vec.v, v.m_real.r);
}


namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void constructSRealH(hkVector4d* v, hkSimdDouble64Parameter r) { constructSRealH<I-1>(v, r); v[I-1].setAll(r); }
template <> HK_FORCE_INLINE void constructSRealH<1>(hkVector4d* v, hkSimdDouble64Parameter r) { v[0].setAll(r); }
}
template <int M>
HK_FORCE_INLINE hkMxVectord<M>::hkMxVectord(hkSimdDouble64Parameter r)
{
	hkMxVectord_Implementation::constructSRealH<M>(m_vec.v, r);
}

#endif

namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void setBCH(hkVector4d* v, const hkSimdDouble64* v0) { setBCH<I-1>(v, v0); v[I-1].setAll(v0[I-1]); }
template <> HK_FORCE_INLINE void setBCH<1>(hkVector4d* v, const hkSimdDouble64* v0) { v[0].setAll(v0[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::setBroadcast( hkMxRealdParameter r )
{
	hkMxVectord_Implementation::setBCH<M>(m_vec.v, r.m_real.r);
}


namespace hkMxVectord_Implementation
{
	template <int I> HK_FORCE_INLINE void setBCH(hkVector4d* v, hkSimdDouble64Parameter v0) { setBCH<I-1>(v, v0); v[I-1].setAll(v0); }
	template <> HK_FORCE_INLINE void setBCH<1>(hkVector4d* v, hkSimdDouble64Parameter v0) { v[0].setAll(v0); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::setAll( hkSimdDouble64Parameter r )
{
	hkMxVectord_Implementation::setBCH<M>(m_vec.v, r);
}


namespace hkMxVectord_Implementation
{
template <int I, int idx> struct setScalarBroadcastH { HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* v0) { setScalarBroadcastH<I-1,idx>::apply(v, v0); v[I-1].setBroadcast<idx>(v0[I-1]); } };
template <int idx> struct setScalarBroadcastH<1,idx> { HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* v0) { v[0].setBroadcast<idx>(v0[0]); } };
}
template <int M>
template <int I>
HK_FORCE_INLINE void hkMxVectord<M>::setScalarBroadcast(hkMxVectordParameter v)
{
	HK_VECTOR4d_SUBINDEX_CHECK;
	hkMxVectord_Implementation::setScalarBroadcastH<M,I>::apply(m_vec.v, v.m_vec.v);
}


template <int M>
template <int I>
HK_FORCE_INLINE void hkMxVectord<M>::setVector(hkVector4dParameter v)
{
	HK_MXVECTORd_MX_SUBINDEX_CHECK;
	m_vec.v[I] = v;
}

template <int M>
template <int I>
HK_FORCE_INLINE const hkVector4d& hkMxVectord<M>::getVector() const
{
	HK_MXVECTORd_MX_SUBINDEX_CHECK;
	return m_vec.v[I];
}

template <int M>
template <int I>
HK_FORCE_INLINE void hkMxVectord<M>::getVector(hkVector4d& vOut) const
{
	HK_MXVECTORd_MX_SUBINDEX_CHECK;
	vOut = m_vec.v[I];
}

namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void setConstH(hkVector4d* v, hkVector4dParameter vC) { setConstH<I-1>(v,vC); v[I-1] = vC; }
template <> HK_FORCE_INLINE void setConstH<1>(hkVector4d* v, hkVector4dParameter vC) { v[0] = vC; }
}
template <int M>
template<int vectorConstant> 
HK_FORCE_INLINE void hkMxVectord<M>::setConstant()
{
	const hkVector4d vC = hkVector4d::getConstant<vectorConstant>();
	hkMxVectord_Implementation::setConstH<M>(m_vec.v, vC);
}


namespace hkMxVectord_Implementation
{
template <int I, int N> struct isOkH { HK_FORCE_INLINE static hkBool32 apply(const hkVector4d* v) { if (v[I-1].isOk<N>()) return isOkH<I-1,N>::apply(v); else return 0; } };
template <int N> struct isOkH<1,N> { HK_FORCE_INLINE static hkBool32 apply(const hkVector4d* v) { return v[0].isOk<N>(); } };
}
template <int M>
template <int N>
HK_FORCE_INLINE hkBool32 hkMxVectord<M>::isOk() const
{
#if !defined(HK_DEBUG)
	// pragma compiler perf warning
#endif
	return hkMxVectord_Implementation::isOkH<M,N>::apply(m_vec.v);
}


namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void moveH(hkVector4d* HK_RESTRICT v, const hkVector4d* HK_RESTRICT v0) { moveH<I-1>(v, v0); v[I-1] = v0[I-1]; }
template <> HK_FORCE_INLINE void moveH<1>(hkVector4d* HK_RESTRICT v, const hkVector4d* HK_RESTRICT v0) { v[0] = v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::moveLoad(const hkVector4d* HK_RESTRICT v)
{
	hkMxVectord_Implementation::moveH<M>(m_vec.v, v);
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::moveStore(hkVector4d* HK_RESTRICT v) const
{
	hkMxVectord_Implementation::moveH<M>(v, m_vec.v);
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::operator= ( hkMxVectordParameter v )
{
	hkMxVectord_Implementation::moveH<M>(m_vec.v, v.m_vec.v);
}


namespace hkMxVectord_Implementation
{
template <int I, int N> struct loadRH {
	HK_FORCE_INLINE static void apply(hkVector4d* v, const hkDouble64* r) 
	{ 
		loadRH<I-1,N>::apply(v, r); 
		v[I-1].load<N>(r+((I-1)*N)); 
	}
};
template <int N> struct loadRH<1,N> {
	HK_FORCE_INLINE static void apply(hkVector4d* v, const hkDouble64* r) 
	{ 
		v[0].load<N>(r); 
	}
};
}

template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectord<M>::load(const hkDouble64* r)
{
	hkMxVectord_Implementation::loadRH<M,N>::apply(m_vec.v, r);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct loadHC {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkDouble64* base)
{
	loadHC<I-1, byteAddressIncrement, N, A>::apply(v, base);
	v[I-1].load<N, A>(hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement ));
} };
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct loadHC<1, byteAddressIncrement, N, A> {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkDouble64* base)
{
	v[0].load<N, A>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A>
HK_FORCE_INLINE void hkMxVectord<M>::load(const hkDouble64* base)
{
	hkMxVectord_Implementation::loadHC<M, byteAddressIncrement, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct loadUnpackHC {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkHalf* base)
{
	loadUnpackHC<I-1, byteAddressIncrement, N, A>::apply(v, base);
	v[I-1].load<N, A>(hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement ));
} };
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct loadUnpackHC<1, byteAddressIncrement, N, A> {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkHalf* base)
{
	v[0].load<N, A>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A>
HK_FORCE_INLINE void hkMxVectord<M>::loadUnpack(const hkHalf* base)
{
	hkMxVectord_Implementation::loadUnpackHC<M, byteAddressIncrement, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void loadNRH(hkVector4d* v, const hkDouble64* r) { loadNRH<I-1>(v, r); v[I-1].load<4,HK_IO_NATIVE_ALIGNED>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void loadNRH<1>(hkVector4d* v, const hkDouble64* r) { v[0].load<4,HK_IO_NATIVE_ALIGNED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::loadNotAligned(const hkDouble64* r)
{
	hkMxVectord_Implementation::loadNRH<M>(m_vec.v, r);
}

namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void loadCNRH(hkVector4d* v, const hkDouble64* r) { loadCNRH<I-1>(v, r); v[I-1].load<4,HK_IO_NOT_CACHED>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void loadCNRH<1>(hkVector4d* v, const hkDouble64* r) { v[0].load<4,HK_IO_NOT_CACHED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::loadNotCached(const hkDouble64* r)
{
	hkMxVectord_Implementation::loadCNRH<M>(m_vec.v, r);
}

namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void storeRH(const hkVector4d* v, hkDouble64* r) { storeRH<I-1>(v, r); v[I-1].store<4>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void storeRH<1>(const hkVector4d* v, hkDouble64* r) { v[0].store<4>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::store(hkDouble64* r) const
{
	hkMxVectord_Implementation::storeRH<M>(m_vec.v, r);
}

namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct storeHC {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkDouble64* base)
{
	hkDouble64* HK_RESTRICT ptr0 = hkAddByteOffset(base, (I-1) * byteAddressIncrement); 
	storeHC<I-1, byteAddressIncrement, N, A>::apply(v, base);
	v[I-1].store<N, A>(ptr0);
} };
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct storeHC<1, byteAddressIncrement, N, A> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkDouble64* base)
{
	v[0].store<N, A>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A>
HK_FORCE_INLINE void hkMxVectord<M>::store(hkDouble64* base) const
{
	hkMxVectord_Implementation::storeHC<M, byteAddressIncrement, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement, int N, hkMathIoMode A, hkMathRoundingMode R> struct storePackHC {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkHalf* base)
{
	hkHalf* HK_RESTRICT ptr0 = hkAddByteOffset(base, (I-1) * byteAddressIncrement); 
	storePackHC<I-1, byteAddressIncrement, N, A, R>::apply(v, base);
	v[I-1].store<N, A, R>(ptr0);
} };
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A, hkMathRoundingMode R> struct storePackHC<1, byteAddressIncrement, N, A, R> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkHalf* base)
{
	v[0].store<N, A, R>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkMxVectord<M>::storePack(hkHalf* base) const
{
	hkMxVectord_Implementation::storePackHC<M, byteAddressIncrement, N, A, R>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void storeNRH(const hkVector4d* v, hkDouble64* r) { storeNRH<I-1>(v, r); v[I-1].store<4,HK_IO_NATIVE_ALIGNED>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void storeNRH<1>(const hkVector4d* v, hkDouble64* r) { v[0].store<4,HK_IO_NATIVE_ALIGNED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::storeNotAligned(hkDouble64* r) const
{
	hkMxVectord_Implementation::storeNRH<M>(m_vec.v, r);
}

namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void storeCNRH(const hkVector4d* v, hkDouble64* r) { storeCNRH<I-1>(v, r); v[I-1].store<4,HK_IO_NOT_CACHED>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void storeCNRH<1>(const hkVector4d* v, hkDouble64* r) { v[0].store<4,HK_IO_NOT_CACHED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::storeNotCached(hkDouble64* r) const
{
	hkMxVectord_Implementation::storeCNRH<M>(m_vec.v, r);
}



namespace hkMxVectord_Implementation
{
template <int I, int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct normalizeH { HK_FORCE_INLINE static void apply(hkVector4d* v) { normalizeH<I-1,N,A,S>::apply(v); v[I-1].normalize<N,A,S>(); } };
template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct normalizeH<1,N,A,S> { HK_FORCE_INLINE static void apply(hkVector4d* v) { v[0].normalize<N,A,S>(); } };
}
template <int M> template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void hkMxVectord<M>::normalize() { hkMxVectord_Implementation::normalizeH<M,N,A,S>::apply(m_vec.v); }

template <int M> template <int N> HK_FORCE_INLINE void hkMxVectord<M>::normalize() { hkMxVectord_Implementation::normalizeH<M,N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_vec.v); }



namespace hkMxVectord_Implementation
{
template <int I, int N> struct setNegH { HK_FORCE_INLINE static void apply(hkVector4d* v0, const hkVector4d* v1) { setNegH<I-1,N>::apply(v0,v1); v0[I-1].setNeg<N>(v1[I-1]); } };
template <int N> struct setNegH<1,N> { HK_FORCE_INLINE static void apply(hkVector4d* v0, const hkVector4d* v1) { v0[0].setNeg<N>(v1[0]); } };
}
template <int M> template <int N> HK_FORCE_INLINE void hkMxVectord<M>::setNeg(hkMxVectordParameter v0) { hkMxVectord_Implementation::setNegH<M,N>::apply(m_vec.v, v0.m_vec.v); }

namespace hkMxVectord_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setDivH { HK_FORCE_INLINE static void apply(hkVector4d* v0, const hkVector4d* v1, const hkVector4d* v2) { setDivH<I-1,A,D>::apply(v0,v1,v2); v0[I-1].setDiv<A,D>(v1[I-1],v2[I-1]); } };
template <hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setDivH<1,A,D> { HK_FORCE_INLINE static void apply(hkVector4d* v0, const hkVector4d* v1, const hkVector4d* v2) { v0[0].setDiv<A,D>(v1[0],v2[0]); } };
}
template <int M> template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void hkMxVectord<M>::setDiv(hkMxVectordParameter v0, hkMxVectordParameter v1) { hkMxVectord_Implementation::setDivH<M,A,D>::apply(m_vec.v, v0.m_vec.v, v1.m_vec.v); }

template <int M> HK_FORCE_INLINE void hkMxVectord<M>::setDiv(hkMxVectordParameter v0, hkMxVectordParameter v1) { hkMxVectord_Implementation::setDivH<M,HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_vec.v, v0.m_vec.v, v1.m_vec.v); }

namespace hkMxVectord_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct setSqrtInverseH { HK_FORCE_INLINE static void apply(hkVector4d* v0, const hkVector4d* v1) { setSqrtInverseH<I-1,A,S>::apply(v0,v1); v0[I-1].setSqrtInverse<A,S>(v1[I-1]); } };
template <hkMathAccuracyMode A, hkMathNegSqrtMode S> struct setSqrtInverseH<1,A,S> { HK_FORCE_INLINE static void apply(hkVector4d* v0, const hkVector4d* v1) { v0[0].setSqrtInverse<A,S>(v1[0]); } };
}
template <int M> template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void hkMxVectord<M>::setSqrtInverse(hkMxVectordParameter v0) { hkMxVectord_Implementation::setSqrtInverseH<M,A,S>::apply(m_vec.v, v0.m_vec.v); }

template <int M> HK_FORCE_INLINE void hkMxVectord<M>::setSqrtInverse(hkMxVectordParameter v0) { hkMxVectord_Implementation::setSqrtInverseH<M,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_vec.v, v0.m_vec.v); }

MXV_NO_OPERANDS( setZero, setZero )

namespace hkMxVectord_Implementation
{
template <int I, int N> struct zeroCompH { HK_FORCE_INLINE static void apply(hkVector4d* v) { zeroCompH<I-1,N>::apply(v); v[I-1].zeroComponent<N>(); } };
template <int N> struct zeroCompH<1,N> { HK_FORCE_INLINE static void apply(hkVector4d* v) { v[0].zeroComponent<N>(); } };
}
template <int M> 
template <int N> 
HK_FORCE_INLINE void hkMxVectord<M>::zeroComponent() 
{ 
	hkMxVectord_Implementation::zeroCompH<M,N>::apply(m_vec.v); 
}

MXV_OPd_MXVECTOR( setAbs, setAbs )
MXV_OPd_MXVECTOR( add, add )
MXV_OPd_MXVECTOR( sub, sub )
MXV_OPd_MXVECTOR( mul, mul )
MXV_OPd_MXREAL( mul, mul )

MXV_OPd_MXVECTOR( setXYZ, setXYZ )
MXV_OPd_MXVECTOR( setW, setW )

MXV_OPd_MXVECTOR_MXVECTOR( setCross, setCross )

MXV_OPd_MXVECTOR_MXVECTOR( setAdd, setAdd )
MXV_OPd_MXVECTOR_MXVECTOR( setSub, setSub )
MXV_OPd_MXVECTOR_MXVECTOR( setMul, setMul )

MXV_OPd_MXVECTOR_MXVECTOR( addMul, addMul )
MXV_OPd_MXVECTOR_MXVECTOR( subMul, subMul )
MXV_OPd_MXVECTOR_MXVECTOR( setMin, setMin )
MXV_OPd_MXVECTOR_MXVECTOR( setMax, setMax )

MXV_OPd_MXREAL_MXVECTOR( addMul, addMul )
MXV_OPd_MXREAL_MXVECTOR( subMul, subMul )
MXV_OPd_MXREAL_MXVECTOR( setMul, setMul )
MXV_OPd_MXREAL_MXSINGLE( setMul, setMul )

MXV_OPd_MXQUATERNION_MXVECTOR( setRotatedDir, _setRotatedDir )
MXV_OPd_MXQUATERNION_MXVECTOR( setRotatedInverseDir, _setRotatedInverseDir )

MXV_OPd_MXVECTOR_MXVECTOR_MXVECTOR( setAddMul, setAddMul )
MXV_OPd_MXVECTOR_MXVECTOR_MXVECTOR( setSubMul, setSubMul )
MXV_OPd_MXVECTOR_MXVECTOR_MXSINGLE( setAddMul, setAddMul )
MXV_OPd_MXVECTOR_MXVECTOR_MXSINGLE( setSubMul, setSubMul )
MXV_OPd_MXVECTOR_MXVECTOR_MXREAL( setSubMul, setSubMul )
MXV_OPd_MXVECTOR_MXSINGLE_MXREAL( setSubMul, setSubMul )

MXV_OPd_MXVECTOR_MXVECTOR_MXREAL( setInterpolate, setInterpolate )

MXV_OPd_MXSINGLE( add, add )
MXV_OPd_MXSINGLE( sub, sub )
MXV_OPd_MXSINGLE( mul, mul )
MXV_OPd_MXSINGLE( setW, setW )
MXV_OPd_MXREAL( setW, setW )
MXV_OPd_MXVECTOR_MXREAL( setXYZ_W, setXYZ_W )


MXV_OPd_MXVECTOR_MXSINGLE( addMul, addMul )
MXV_OPd_MXSINGLE_MXSINGLE( addMul, addMul )
MXV_OPd_MXVECTOR_MXSINGLE( setAdd, setAdd )
MXV_OPd_MXVECTOR_MXSINGLE( setSub, setSub )
MXV_OPd_MXSINGLE_MXVECTOR( setSub, setSub )
MXV_OPd_MXVECTOR_MXSINGLE( setMul, setMul )
MXV_OPd_MXVECTOR_MXSINGLE( setCross, setCross )
MXV_OPd_MXSINGLE_MXVECTOR( setCross, setCross )
MXV_OPd_MXVECTOR_MXSINGLE( setMin, setMin )
MXV_OPd_MXVECTOR_MXSINGLE( setMax, setMax )

MXV_COMPARE( equal, equal )
MXV_COMPARE( notEqual, notEqual )
MXV_COMPARE( less, less )
MXV_COMPARE( greater, greater )
MXV_COMPARE( lessEqual, lessEqual )
MXV_COMPARE( greaterEqual, greaterEqual )

MXV_COMPARE_SINGLE( equal, equal )
MXV_COMPARE_SINGLE( notEqual, notEqual )
MXV_COMPARE_SINGLE( less, less )
MXV_COMPARE_SINGLE( greater, greater )
MXV_COMPARE_SINGLE( lessEqual, lessEqual )
MXV_COMPARE_SINGLE( greaterEqual, greaterEqual )





namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void setAddMulH(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1, hkVector4dParameter v2) { setAddMulH<I-1>(v, v0, v1, v2); v[I-1].setAddMul(v0[I-1], v1[I-1], v2.getComponent<I-1>()); }
template <> HK_FORCE_INLINE void setAddMulH<1>(hkVector4d* v, const hkVector4d* v0, const hkVector4d* v1, hkVector4dParameter v2) { v[0].setAddMul(v0[0], v1[0], v2.getComponent<0>()); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::setAddMul(hkMxVectordParameter v0, hkMxVectordParameter v1, hkVector4dParameter v2)
{
	hkMxVectord_Implementation::setAddMulH<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v, v2); // this is safe because v2.getComponent<> asserts M<=4
}


template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::setXYZ_W(hkMxVectordParameter v0, hkMxVectordParameter v1)
{
	setXYZ(v0);
	setW(v1);
}


template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::storeTransposed4(hkMatrix4d& matrix4) const
{
	HK_MXVECTORd_MX_NOT_IMPLEMENTED;
}

template <>
HK_FORCE_INLINE void hkMxVectord<1>::storeTransposed4(hkMatrix4d& matrix4) const
{
	hkVector4d a; a.setBroadcast<0>(m_vec.v[0]);
	hkVector4d b; b.setBroadcast<1>(m_vec.v[0]);
	hkVector4d c; c.setBroadcast<2>(m_vec.v[0]);
	hkVector4d d; d.setBroadcast<3>(m_vec.v[0]);

	matrix4.setCols(a,b,c,d);
	// todo. for debug: set .yzw to 0x23456789
}

template <>
HK_FORCE_INLINE void hkMxVectord<2>::storeTransposed4(hkMatrix4d& matrix4) const
{
	matrix4.setRows(m_vec.v[0], m_vec.v[1], m_vec.v[1], m_vec.v[1]);
}

template <>
HK_FORCE_INLINE void hkMxVectord<3>::storeTransposed4(hkMatrix4d& matrix4) const
{
	matrix4.setRows(m_vec.v[0], m_vec.v[1], m_vec.v[2], m_vec.v[2]);
}

template <>
HK_FORCE_INLINE void hkMxVectord<4>::storeTransposed4(hkMatrix4d& matrix4) const
{
	matrix4.setRows(m_vec.v[0], m_vec.v[1], m_vec.v[2], m_vec.v[3]);
}


namespace hkMxVectord_Implementation
{
template <int M, int N> struct hAddH { HK_FORCE_INLINE static void apply(hkMxVectordParameter v, hkVector4d& addsOut) { HK_MXVECTORd_MX_NOT_IMPLEMENTED; } };
template <int M, int N> struct hAddHS { HK_FORCE_INLINE static void apply(hkMxVectordParameter v, hkSimdDouble64& addsOut) { HK_MXVECTORd_MX_NOT_IMPLEMENTED; } };
template <> struct hAddH<4,4> { HK_FORCE_INLINE static void apply(const hkMxVectord<4>& v, hkVector4d& addsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4d t1; t1.setAdd( f.getColumn<2>(), f.getColumn<3>() );
	addsOut.setAdd( t0, t1 );
} };
template <> struct hAddH<4,3> { HK_FORCE_INLINE static void apply(const hkMxVectord<4>& v, hkVector4d& addsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	addsOut.setAdd( t0, f.getColumn<2>() );
} };
template <> struct hAddH<3,4> { HK_FORCE_INLINE static void apply(const hkMxVectord<3>& v, hkVector4d& addsOut) 
{ 
	// optimize!
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4d t1; t1.setAdd( f.getColumn<2>(), f.getColumn<3>() );
	addsOut.setAdd( t0, t1 );
} };
template <> struct hAddH<3,3> { HK_FORCE_INLINE static void apply(const hkMxVectord<3>& v, hkVector4d& addsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	addsOut.setAdd( t0, f.getColumn<2>() );
} };
template <> struct hAddH<2,4> { HK_FORCE_INLINE static void apply(const hkMxVectord<2>& v, hkVector4d& addsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4d t1; t1.setAdd( f.getColumn<2>(), f.getColumn<3>() );
	addsOut.setAdd( t0, t1 );
} };
template <> struct hAddH<2,3> { HK_FORCE_INLINE static void apply(const hkMxVectord<2>& v, hkVector4d& addsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	addsOut.setAdd( t0, f.getColumn<2>() );
} };

template <int N> struct hAddH<1,N> { HK_FORCE_INLINE static void apply(const hkMxVectord<1>& v, hkVector4d& addsOut) 
{ 
	addsOut.setHorizontalAdd<N>(v.m_vec.v[0]);
} };
template <int N> struct hAddHS<1,N> { HK_FORCE_INLINE static void apply(const hkMxVectord<1>& v, hkSimdDouble64& addsOut) 
{ 
	addsOut = v.m_vec.v[0].horizontalAdd<N>();
} };
}
template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectord<M>::horizontalAdd( hkVector4d& addsOut ) const
{
	hkMxVectord_Implementation::hAddH<M,N>::apply(*this, addsOut);
}

template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectord<M>::horizontalAdd( hkSimdDouble64& addsOut ) const
{
	hkMxVectord_Implementation::hAddHS<M,N>::apply(*this, addsOut);
}


namespace hkMxVectord_Implementation
{
template <int M, int N> struct hMinH { HK_FORCE_INLINE static void apply(hkMxVectordParameter v, hkVector4d& minsOut) { HK_MXVECTORd_MX_NOT_IMPLEMENTED; } };
template <> struct hMinH<4,4> { HK_FORCE_INLINE static void apply(const hkMxVectord<4>& v, hkVector4d& minsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4d t1; t1.setMin( f.getColumn<2>(), f.getColumn<3>() );
	minsOut.setMin( t0, t1 );
} };
template <> struct hMinH<4,3> { HK_FORCE_INLINE static void apply(const hkMxVectord<4>& v, hkVector4d& minsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	minsOut.setMin( t0, f.getColumn<2>() );
} };
template <> struct hMinH<3,4> { HK_FORCE_INLINE static void apply(const hkMxVectord<3>& v, hkVector4d& minsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4d t1; t1.setMin( f.getColumn<2>(), f.getColumn<3>() );
	minsOut.setMin( t0, t1 );
} };
template <> struct hMinH<3,3> { HK_FORCE_INLINE static void apply(const hkMxVectord<3>& v, hkVector4d& minsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	minsOut.setMin( t0, f.getColumn<2>() );
} };
template <> struct hMinH<2,4> { HK_FORCE_INLINE static void apply(const hkMxVectord<2>& v, hkVector4d& minsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4d t1; t1.setMin( f.getColumn<2>(), f.getColumn<3>() );
	minsOut.setMin( t0, t1 );
} };
template <> struct hMinH<2,3> { HK_FORCE_INLINE static void apply(const hkMxVectord<2>& v, hkVector4d& minsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	minsOut.setMin( t0, f.getColumn<2>() );
} };
template <int N> struct hMinH<1,N> { HK_FORCE_INLINE static void apply(const hkMxVectord<1>& v, hkVector4d& minsOut) 
{ 
	minsOut.setHorizontalMin<N>(v.m_vec.v[0]);
} };
}
template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectord<M>::horizontalMin( hkVector4d& minsOut ) const
{
	hkMxVectord_Implementation::hMinH<M,N>::apply(*this, minsOut);
}


namespace hkMxVectord_Implementation
{
template <int M, int N> struct hMaxH { HK_FORCE_INLINE static void apply(hkMxVectordParameter v, hkVector4d& maxsOut) { HK_MXVECTORd_MX_NOT_IMPLEMENTED; } };
template <> struct hMaxH<4,4> { HK_FORCE_INLINE static void apply(const hkMxVectord<4>& v, hkVector4d& maxsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4d t1; t1.setMax( f.getColumn<2>(), f.getColumn<3>() );
	maxsOut.setMax( t0, t1 );
} };
template <> struct hMaxH<4,3> { HK_FORCE_INLINE static void apply(const hkMxVectord<4>& v, hkVector4d& maxsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	maxsOut.setMax( t0, f.getColumn<2>() );
} };
template <> struct hMaxH<3,4> { HK_FORCE_INLINE static void apply(const hkMxVectord<3>& v, hkVector4d& maxsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4d t1; t1.setMax( f.getColumn<2>(), f.getColumn<3>() );
	maxsOut.setMax( t0, t1 );
} };
template <> struct hMaxH<3,3> { HK_FORCE_INLINE static void apply(const hkMxVectord<3>& v, hkVector4d& maxsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	maxsOut.setMax( t0, f.getColumn<2>() );
} };
template <> struct hMaxH<2,4> { HK_FORCE_INLINE static void apply(const hkMxVectord<2>& v, hkVector4d& maxsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4d t1; t1.setMax( f.getColumn<2>(), f.getColumn<3>() );
	maxsOut.setMax( t0, t1 );
} };
template <> struct hMaxH<2,3> { HK_FORCE_INLINE static void apply(const hkMxVectord<2>& v, hkVector4d& maxsOut) 
{ 
	hkMatrix4d f; v.storeTransposed4(f);
	hkVector4d t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	maxsOut.setMax( t0, f.getColumn<2>() );
} };
template <int N> struct hMaxH<1,N> { HK_FORCE_INLINE static void apply(const hkMxVectord<1>& v, hkVector4d& maxsOut) 
{ 
	maxsOut.setHorizontalMax<N>(v.m_vec.v[0]);
} };
}
template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectord<M>::horizontalMax( hkVector4d& maxsOut ) const
{
	hkMxVectord_Implementation::hMaxH<M,N>::apply(*this, maxsOut);
}


namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void reduceAddH(const hkVector4d* v, hkVector4d& addOut) { reduceAddH<I-1>(v, addOut); addOut.add(v[I-1]); }
template <> HK_FORCE_INLINE void reduceAddH<1>(const hkVector4d* v, hkVector4d& addOut) { addOut = v[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::reduceAdd(hkVector4d& addOut) const
{
	hkMxVectord_Implementation::reduceAddH<M>(m_vec.v, addOut);
}


namespace hkMxVectord_Implementation
{
template <int I, int N> struct dotH { HK_FORCE_INLINE static void apply(const hkVector4d* v, const hkVector4d* v0, hkSimdDouble64* dotsOut) { dotH<I-1,N>::apply(v, v0, dotsOut); dotsOut[I-1] = v[I-1].dot<N>(v0[I-1]); } };
template <int N> struct dotH<1,N> { HK_FORCE_INLINE static void apply(const hkVector4d* v, const hkVector4d* v0, hkSimdDouble64* dotsOut) { dotsOut[0] = v[0].dot<N>(v0[0]); } };
}
template <int M> 
template <int N> 
HK_FORCE_INLINE void hkMxVectord<M>::dot(hkMxVectordParameter v, hkMxReald<M>& dotsOut) const 
{ 
	hkMxVectord_Implementation::dotH<M,N>::apply(m_vec.v, v.m_vec.v, dotsOut.m_real.r); 
}


namespace hkMxVectord_Implementation
{
template <int I, int N> struct dotHSingle { HK_FORCE_INLINE static void apply(const hkVector4d* v, const hkVector4d& v0, hkSimdDouble64* dotsOut) { dotHSingle<I-1,N>::apply(v, v0, dotsOut); dotsOut[I-1] = v[I-1].dot<N>(v0); } };
template <int N> struct dotHSingle<1,N> {   HK_FORCE_INLINE static void apply(const hkVector4d* v, const hkVector4d& v0, hkSimdDouble64* dotsOut) { dotsOut[0] = v[0].dot<N>(v0); } };
}
template <int M> 
template <int N> 
HK_FORCE_INLINE void hkMxVectord<M>::dot(hkMxSingledParameter v, hkMxReald<M>& dotsOut) const 
{ 
	hkMxVectord_Implementation::dotHSingle<M,N>::apply(m_vec.v, v.m_single.s, dotsOut.m_real.r); 
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherH {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* HK_RESTRICT base)
{
	gatherH<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1] = *hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement );
} };
template <hkUint32 byteAddressIncrement> struct gatherH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* HK_RESTRICT base)
{
	v[0] = *base;
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectord<M>::gather(const hkVector4d* HK_RESTRICT base)
{
	hkMxVectord_Implementation::gatherH<M, byteAddressIncrement>::apply(m_vec.v, base);
}

namespace hkMxVectord_Implementation
{
	template <int N> struct componentCountToSelectMask {};
	template <> struct componentCountToSelectMask<0> { 	enum { Mask = hkVector4ComparisonMask::MASK_NONE }; };
	template <> struct componentCountToSelectMask<1> { 	enum { Mask = hkVector4ComparisonMask::MASK_X }; };
	template <> struct componentCountToSelectMask<2> { 	enum { Mask = hkVector4ComparisonMask::MASK_XY }; };
	template <> struct componentCountToSelectMask<3> { 	enum { Mask = hkVector4ComparisonMask::MASK_XYZ }; };
	template <> struct componentCountToSelectMask<4> { 	enum { Mask = hkVector4ComparisonMask::MASK_XYZW }; };
}

namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement, hkVector4ComparisonMask::Mask MASK> struct gatherHC {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* HK_RESTRICT base)
{
	gatherHC<I-1, byteAddressIncrement, MASK>::apply(v, base);
	v[I-1].setSelect<MASK>(*hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement), v[I-1]);
} };
template <hkUint32 byteAddressIncrement, hkVector4ComparisonMask::Mask MASK> struct gatherHC<1, byteAddressIncrement, MASK> {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* HK_RESTRICT base)
{
	v[0].setSelect<MASK>(*base, v[0]);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N>
HK_FORCE_INLINE void hkMxVectord<M>::gather(const hkVector4d* HK_RESTRICT base)
{
	hkMxVectord_Implementation::gatherHC<M, byteAddressIncrement, hkVector4ComparisonMask::Mask(hkMxVectord_Implementation::componentCountToSelectMask<N>::Mask)>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUintH {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* HK_RESTRICT base, const hkUint16* indices)
{
	gatherUintH<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1] = *hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement );
} };
template <hkUint32 byteAddressIncrement> struct gatherUintH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* HK_RESTRICT base, const hkUint16* indices)
{
	v[0] = *hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement );
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectord<M>::gather(const hkVector4d* HK_RESTRICT base, const hkUint16* indices)
{
	hkMxVectord_Implementation::gatherUintH<M, byteAddressIncrement>::apply(m_vec.v, base, indices);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherIntH {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* HK_RESTRICT base, const hkInt32* indices)
{
	gatherIntH<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1] = *hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement );
} };
template <hkUint32 byteAddressIncrement> struct gatherIntH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* HK_RESTRICT base, const hkInt32* indices)
{
	v[0] = *hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement );
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectord<M>::gather(const hkVector4d* HK_RESTRICT base, const hkInt32* indices)
{
	hkMxVectord_Implementation::gatherIntH<M, byteAddressIncrement>::apply(m_vec.v, base, indices);
}


namespace hkMxVectord_Implementation
{
	template <int I, hkUint32 byteOffset> struct gatherWithOffsetH {
	HK_FORCE_INLINE static void apply(hkVector4d* v, const void** base)
	{
		const hkVector4d* HK_RESTRICT ptr0 = (const hkVector4d*)hkAddByteOffsetConst(base[I-1], byteOffset); 
		gatherWithOffsetH<I-1, byteOffset>::apply(v, base);
		v[I-1] = *ptr0;
	} };
	template <hkUint32 byteOffset> struct gatherWithOffsetH<0, byteOffset> {
		HK_FORCE_INLINE static void apply(hkVector4d* v, const void** base){} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxVectord<M>::gatherWithOffset(const void* base[M])
{
	hkMxVectord_Implementation::gatherWithOffsetH<M, byteOffset>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
	template <int I, hkUint32 byteOffset, hkVector4ComparisonMask::Mask M> struct gatherWithOffsetHC {
		HK_FORCE_INLINE static void apply(hkVector4d* v, const void** base)
		{
			const hkVector4d* HK_RESTRICT ptr0 = (const hkVector4d*)hkAddByteOffsetConst(base[I-1], byteOffset); 
			gatherWithOffsetHC<I-1, byteOffset, M>::apply(v, base);
			v[I-1].setSelect<M>(*ptr0, v[I-1]);
		}
	};
	template <hkUint32 byteOffset, hkVector4ComparisonMask::Mask M> struct gatherWithOffsetHC<0, byteOffset, M> {
		HK_FORCE_INLINE static void apply(hkVector4d* v, const void** base){}
	};
}
template <int M>
template <hkUint32 byteOffset, int N> 
HK_FORCE_INLINE void hkMxVectord<M>::gatherWithOffset(const void* base[M])
{
	hkMxVectord_Implementation::gatherWithOffsetHC<M, byteOffset, hkVector4ComparisonMask::Mask( hkMxVectord_Implementation::componentCountToSelectMask<N>::Mask) >::apply(m_vec.v, base);
}



namespace hkMxVectord_Implementation
{
	template <int I, hkUint32 byteOffset> struct gatherHalfsWithOffsetH {
		HK_FORCE_INLINE static void apply(hkVector4d* v, const void** base)
		{
			const hkHalf* HK_RESTRICT ptr0 = (const hkHalf*)hkAddByteOffsetConst(base[I-1], byteOffset); 
			gatherHalfsWithOffsetH<I-1, byteOffset>::apply(v, base);
			v[I-1].load<4>( ptr0 );
		}
	};
	template <hkUint32 byteOffset> struct gatherHalfsWithOffsetH<0, byteOffset> {
		HK_FORCE_INLINE static void apply(hkVector4d* v, const void** base){}
	};
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxVectord<M>::gatherHalfsWithOffset(const void* base[M])
{
	hkMxVectord_Implementation::gatherHalfsWithOffsetH<M, byteOffset>::apply(m_vec.v, base);
}

namespace hkMxVectord_Implementation
{
	template <int I, hkUint32 byteOffset, int N, hkMathIoMode A> struct loadWithOffsetHC {
		HK_FORCE_INLINE static void apply(hkVector4d* v, const hkDouble64** base)
		{
			const hkDouble64* ptr0 = (const hkDouble64*)hkAddByteOffsetConst(base[I-1], byteOffset); 
			loadWithOffsetHC<I-1, byteOffset, N, A>::apply(v, base);
			v[I-1].load<N, A>(ptr0);
		}
	};
	template <hkUint32 byteOffset, int N, hkMathIoMode A> struct loadWithOffsetHC<0, byteOffset, N, A> {
		HK_FORCE_INLINE static void apply(hkVector4d* v, const hkDouble64** base){}
	 };
}
template <int M>
template <hkUint32 byteOffset, int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkMxVectord<M>::loadWithOffset(const hkDouble64* base[M])
{
	hkMxVectord_Implementation::loadWithOffsetHC<M, byteOffset, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteOffset, int N, hkMathIoMode A> struct loadUnpackWithOffsetHC {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkHalf** base)
{
	const hkHalf* ptr0 = (const hkHalf*)hkAddByteOffsetConst(base[I-1], byteOffset); 
	loadUnpackWithOffsetHC<I-1, byteOffset, N, A>::apply(v, base);
	v[I-1].load<N, A>(ptr0);
} };
template <hkUint32 byteOffset, int N, hkMathIoMode A> struct loadUnpackWithOffsetHC<1, byteOffset, N, A> {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkHalf** base)
{
	const hkHalf* ptr = (const hkHalf*)hkAddByteOffsetConst(base[0], byteOffset); 
	v[0].load<N, A>(ptr);
} };
}
template <int M>
template <hkUint32 byteOffset, int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkMxVectord<M>::loadUnpackWithOffset(const hkHalf* base[M])
{
	hkMxVectord_Implementation::loadUnpackWithOffsetHC<M, byteOffset, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterUintH {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkVector4d* base, const hkUint16* indices)
{
	hkVector4d* HK_RESTRICT ptr = hkAddByteOffset(base, indices[I-1] * byteAddressIncrement);
	scatterUintH<I-1, byteAddressIncrement>::apply(v, base, indices);
	*ptr = v[I-1];
} };
template <hkUint32 byteAddressIncrement> struct scatterUintH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkVector4d* base, const hkUint16* indices)
{
	hkVector4d* HK_RESTRICT ptr = hkAddByteOffset(base, indices[0] * byteAddressIncrement);
	*ptr = v[0];
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectord<M>::scatter(hkVector4d* base, const hkUint16* indices) const
{
	hkMxVectord_Implementation::scatterUintH<M, byteAddressIncrement>::apply(m_vec.v, base, indices);
}



namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterIntH {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkVector4d* base, const hkInt32* indices)
{
	hkVector4d* HK_RESTRICT ptr = hkAddByteOffset(base, indices[I-1] * byteAddressIncrement);
	scatterIntH<I-1, byteAddressIncrement>::apply(v, base, indices);
	*ptr = v[I-1];
} };
template <hkUint32 byteAddressIncrement> struct scatterIntH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkVector4d* base, const hkInt32* indices)
{
	hkVector4d* HK_RESTRICT ptr = hkAddByteOffset(base, indices[0] * byteAddressIncrement);
	*ptr = v[0];
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectord<M>::scatter(hkVector4d* base, const hkInt32* indices) const
{
	hkMxVectord_Implementation::scatterIntH<M, byteAddressIncrement>::apply(m_vec.v, base, indices);
}



namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterH {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkVector4d* base)
{
	hkVector4d* HK_RESTRICT ptr0 = hkAddByteOffset(base, (I-1) * byteAddressIncrement); 
	scatterH<I-1, byteAddressIncrement>::apply(v, base);
	*ptr0 = v[I-1];
} };
template <hkUint32 byteAddressIncrement> struct scatterH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkVector4d* base)
{
	*base = v[0];
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectord<M>::scatter(hkVector4d* base) const
{
	hkMxVectord_Implementation::scatterH<M, byteAddressIncrement>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
	template <int I, hkUint32 byteAddressIncrement, hkVector4ComparisonMask::Mask M> struct scatterHC {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkVector4d* base)
{
	hkVector4d* HK_RESTRICT ptr0 = hkAddByteOffset(base, (I-1) * byteAddressIncrement); 
	scatterHC<I-1, byteAddressIncrement, M>::apply(v, base);
	ptr0->setSelect<M>(v[I-1], *ptr0);
} };
template <hkUint32 byteAddressIncrement, hkVector4ComparisonMask::Mask M> struct scatterHC<1, byteAddressIncrement, M> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkVector4d* base)
{
	base->setSelect<M>(v[0], *base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N>
HK_FORCE_INLINE void hkMxVectord<M>::scatter(hkVector4d* base) const
{
	hkMxVectord_Implementation::scatterHC<M, byteAddressIncrement, hkVector4ComparisonMask::Mask( hkMxVectord_Implementation::componentCountToSelectMask<N>::Mask) >::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteOffset> struct scatterWithOffsetH {
HK_FORCE_INLINE static void apply(const hkVector4d* v, void** base)
{
	hkVector4d* HK_RESTRICT ptr0 = (hkVector4d*)hkAddByteOffset(base[I-1], byteOffset); 
	scatterWithOffsetH<I-1, byteOffset>::apply(v, base);
	*ptr0 = v[I-1];
} };
template <hkUint32 byteOffset> struct scatterWithOffsetH<1, byteOffset> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, void** base)
{
	hkVector4d* HK_RESTRICT ptr0 = (hkVector4d*)hkAddByteOffset(base[0], byteOffset); 
	*ptr0 = v[0];
} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxVectord<M>::scatterWithOffset(void* base[M]) const 
{
	hkMxVectord_Implementation::scatterWithOffsetH<M, byteOffset>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteOffset, hkVector4ComparisonMask::Mask M> struct scatterWithOffsetHC {
HK_FORCE_INLINE static void apply(const hkVector4d* v, void** base)
{
	hkVector4d* HK_RESTRICT ptr0 = (hkVector4d*)hkAddByteOffset(base[I-1], byteOffset); 
	scatterWithOffsetHC<I-1, byteOffset, M>::apply(v, base);
	ptr0->setSelect<M>(v[I-1], *ptr0);
} };
template <hkUint32 byteOffset, hkVector4ComparisonMask::Mask M> struct scatterWithOffsetHC<1, byteOffset, M> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, void** base)
{
	hkVector4d* HK_RESTRICT ptr0 = (hkVector4d*)hkAddByteOffset(base[0], byteOffset); 
	ptr0->setSelect<M>(v[0], *ptr0);
} };
}
template <int M>
template <hkUint32 byteOffset, int N> 
HK_FORCE_INLINE void hkMxVectord<M>::scatterWithOffset(void* base[M]) const 
{
	hkMxVectord_Implementation::scatterWithOffsetHC<M, byteOffset, hkVector4ComparisonMask::Mask(hkMxVectord_Implementation::componentCountToSelectMask<N>::Mask)>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteOffset, int N, hkMathIoMode A> struct storeWithOffsetHC {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkDouble64** base)
{
	hkDouble64* ptr0 = (hkDouble64*)hkAddByteOffset(base[I-1], byteOffset); 
	storeWithOffsetHC<I-1, byteOffset, N, A>::apply(v, base);
	v[I-1].store<N, A>(ptr0);
} };
template <hkUint32 byteOffset, int N, hkMathIoMode A> struct storeWithOffsetHC<1, byteOffset, N, A> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkDouble64** base)
{
	hkDouble64* ptr0 = (hkDouble64*)hkAddByteOffset(base[0], byteOffset); 
	v[0].store<N, A>(ptr0);
} };
}
template <int M>
template <hkUint32 byteOffset, int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkMxVectord<M>::storeWithOffset(hkDouble64* base[M]) const 
{
	hkMxVectord_Implementation::storeWithOffsetHC<M, byteOffset, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, hkUint32 byteOffset, int N, hkMathIoMode A, hkMathRoundingMode R> struct storePackWithOffsetHC {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkHalf** base)
{
	hkHalf* ptr0 = (hkHalf*)hkAddByteOffset(base[I-1], byteOffset); 
	storePackWithOffsetHC<I-1, byteOffset, N, A, R>::apply(v, base);
	v[I-1].store<N, A, R>(ptr0);
} };
template <hkUint32 byteOffset, int N, hkMathIoMode A, hkMathRoundingMode R> struct storePackWithOffsetHC<1, byteOffset, N, A, R> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkHalf** base)
{
	hkHalf* ptr0 = (hkHalf*)hkAddByteOffset(base[0], byteOffset); 
	v[0].store<N, A, R>(ptr0);
} };
}
template <int M>
template <hkUint32 byteOffset, int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkMxVectord<M>::storePackWithOffset(hkHalf* base[M]) const 
{
	hkMxVectord_Implementation::storePackWithOffsetHC<M, byteOffset, N, A, R>::apply(m_vec.v, base);
}


namespace hkMxVectord_Implementation
{
template <int I, int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct lengthH { HK_FORCE_INLINE static void apply(const hkVector4d* v, hkSimdDouble64* lensOut) { lengthH<I-1,N,A,S>::apply(v, lensOut); lensOut[I-1] = v[I-1].length<N,A,S>(); } };
template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct lengthH<1,N,A,S> { HK_FORCE_INLINE static void apply(const hkVector4d* v, hkSimdDouble64* lensOut) { lensOut[0] = v[0].length<N,A,S>(); } };
}
template <int M> template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void hkMxVectord<M>::length(hkMxReald<M>& lensOut) const { hkMxVectord_Implementation::lengthH<M,N,A,S>::apply(m_vec.v, lensOut.m_real.r); }

template <int M> template <int N> HK_FORCE_INLINE void hkMxVectord<M>::length(hkMxReald<M>& lensOut) const { hkMxVectord_Implementation::lengthH<M,N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_vec.v, lensOut.m_real.r); }

namespace hkMxVectord_Implementation
{
template <int I, int N> struct lengthSqrH { HK_FORCE_INLINE static void apply(const hkVector4d* v, hkSimdDouble64* lensOut) { lengthSqrH<I-1,N>::apply(v, lensOut); lensOut[I-1] = v[I-1].lengthSquared<N>(); } };
template <int N> struct lengthSqrH<1,N> { HK_FORCE_INLINE static void apply(const hkVector4d* v, hkSimdDouble64* lensOut) { lensOut[0] = v[0].lengthSquared<N>(); } };
}
template <int M> template <int N> HK_FORCE_INLINE void hkMxVectord<M>::lengthSquared(hkMxReald<M>& lensOut) const { hkMxVectord_Implementation::lengthSqrH<M,N>::apply(m_vec.v, lensOut.m_real.r); }

namespace hkMxVectord_Implementation
{
template <int I, int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct lengthInvH { HK_FORCE_INLINE static void apply(const hkVector4d* v, hkSimdDouble64* lensOut) { lengthInvH<I-1,N,A,S>::apply(v, lensOut); lensOut[I-1] = v[I-1].lengthInverse<N,A,S>(); } };
template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct lengthInvH<1,N,A,S> { HK_FORCE_INLINE static void apply(const hkVector4d* v, hkSimdDouble64* lensOut) { lensOut[0] = v[0].lengthInverse<N,A,S>(); } };
}
template <int M> template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void hkMxVectord<M>::lengthInverse(hkMxReald<M>& lensOut) const { hkMxVectord_Implementation::lengthInvH<M,N,A,S>::apply(m_vec.v, lensOut.m_real.r); }

template <int M> template <int N> HK_FORCE_INLINE void hkMxVectord<M>::lengthInverse(hkMxReald<M>& lensOut) const { hkMxVectord_Implementation::lengthInvH<M,N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_vec.v, lensOut.m_real.r); }



namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void selectH(hkVector4d* v, const hkVector4dComparison* mask, const hkVector4d* tVal, const hkVector4d* fVal) { selectH<I-1>(v, mask, tVal, fVal); v[I-1].setSelect(mask[I-1], tVal[I-1], fVal[I-1]); }
template <> HK_FORCE_INLINE void selectH<1>(hkVector4d* v, const hkVector4dComparison* mask, const hkVector4d* tVal, const hkVector4d* fVal) { v[0].setSelect(mask[0], tVal[0], fVal[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::setSelect(hkMxMaskParameterd mask, hkMxVectordParameter trueValue, hkMxVectordParameter falseValue )
{
	hkMxVectord_Implementation::selectH<M>(m_vec.v, mask.m_comp.c, trueValue.m_vec.v, falseValue.m_vec.v);
}
namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void selectSH(hkVector4d* v, const hkVector4dComparison* mask, hkVector4dParameter tVal, const hkVector4d* fVal) { selectSH<I-1>(v, mask, tVal, fVal); v[I-1].setSelect(mask[I-1], tVal, fVal[I-1]); }
template <> HK_FORCE_INLINE void selectSH<1>(hkVector4d* v, const hkVector4dComparison* mask, hkVector4dParameter tVal, const hkVector4d* fVal) { v[0].setSelect(mask[0], tVal, fVal[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::setSelect(hkMxMaskParameterd mask, hkMxSingledParameter trueValue, hkMxVectordParameter falseValue )
{
	hkMxVectord_Implementation::selectSH<M>(m_vec.v, mask.m_comp.c, trueValue.m_single.s, falseValue.m_vec.v);
}
namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void selectHS(hkVector4d* v, const hkVector4dComparison* mask, const hkVector4d* tVal, hkVector4dParameter fVal) { selectHS<I-1>(v, mask, tVal, fVal); v[I-1].setSelect(mask[I-1], tVal[I-1], fVal); }
template <> HK_FORCE_INLINE void selectHS<1>(hkVector4d* v, const hkVector4dComparison* mask, const hkVector4d* tVal, hkVector4dParameter fVal) { v[0].setSelect(mask[0], tVal[0], fVal); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::setSelect(hkMxMaskParameterd mask, hkMxVectordParameter trueValue, hkMxSingledParameter falseValue )
{
	hkMxVectord_Implementation::selectHS<M>(m_vec.v, mask.m_comp.c, trueValue.m_vec.v, falseValue.m_single.s);
}


namespace hkMxVectord_Implementation
{
	template <int I, int idx> struct revertH {
	HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* v0)
	{ 
		revertH<I-1,idx+1>::apply(v, v0); 
		v[I-1] = v0[idx]; 
	} };
	template <int idx> struct revertH<1,idx> {
	HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* v0)
	{
		v[0] = v0[idx]; 
	} };
	template <int I> 
	HK_FORCE_INLINE void leftCH(hkVector4d* v, const hkVector4d* v0)
	{ 
		leftCH<I-1>(v, v0); 
		v[I-1] = v0[I]; 
	}
	template <> 
	HK_FORCE_INLINE void leftCH<1>(hkVector4d* v, const hkVector4d* v0)
	{
		v[0] = v0[1]; 
	}
	template <int I> 
	HK_FORCE_INLINE void rightCH(hkVector4d* v, const hkVector4d* v0)
	{ 
		rightCH<I-1>(v, v0); 
		v[I] = v0[I-1]; 
	}
	template <> 
	HK_FORCE_INLINE void rightCH<1>(hkVector4d* v, const hkVector4d* v0)
	{
		v[1] = v0[0]; 
	}
}

template <int M>
template <hkMxVectorPermutation::Permutation P>
HK_FORCE_INLINE void hkMxVectord<M>::setVectorPermutation(hkMxVectordParameter m)
{
	HK_COMPILE_TIME_ASSERT2((P==hkMxVectorPermutation::SHIFT_LEFT_CYCLIC)||(P==hkMxVectorPermutation::SHIFT_RIGHT_CYCLIC)||(P==hkMxVectorPermutation::REVERSE),MX_UNKNOWNd_PERMUTATION);

	if (P == hkMxVectorPermutation::SHIFT_LEFT_CYCLIC )
	{
		hkMxVectord_Implementation::leftCH<M-1>(m_vec.v, m.m_vec.v);
		m_vec.v[M-1] = m.m_vec.v[0];
	}
	else if ( P == hkMxVectorPermutation::SHIFT_RIGHT_CYCLIC )
	{
		m_vec.v[0] = m.m_vec.v[M-1];
		hkMxVectord_Implementation::rightCH<M-1>(m_vec.v, m.m_vec.v);
	}
	else /*if ( P == hkMxVectorPermutation::REVERSE )*/
	{
		hkMxVectord_Implementation::revertH<M,0>::apply(m_vec.v, m.m_vec.v);
	}
}


namespace hkMxVectord_Implementation
{
	template <int I, hkVectorPermutation::Permutation P> struct permuteComponents {
		HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* v0)
		{ 
			permuteComponents<I-1,P>::apply(v, v0); 
			v[I-1].setPermutation<P>( v0[I-1] ); 
		} };
		template <hkVectorPermutation::Permutation P> struct permuteComponents<0,P> {
			HK_FORCE_INLINE static void apply(hkVector4d* v, const hkVector4d* v0){}
			};
}

template <int M>
template <hkVectorPermutation::Permutation P>
HK_FORCE_INLINE void hkMxVectord<M>::setComponentPermutation(hkMxVectordParameter m)
{
	hkMxVectord_Implementation::permuteComponents<M,P>::apply(m_vec.v, m.m_vec.v);
}


namespace hkMxVectord_Implementation
{
template <int I> HK_FORCE_INLINE void setAllH(hkVector4d* v, hkVector4dParameter v0) { setAllH<I-1>(v, v0); v[I-1].setAll(v0.getComponent<I-1>()); }
template <> HK_FORCE_INLINE void setAllH<1>(hkVector4d* v, hkVector4dParameter v0) { v[0].setAll(v0.getComponent<0>()); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectord<M>::setAsBroadcast(hkVector4dParameter v)
{
	hkMxVectord_Implementation::setAllH<M>(m_vec.v, v); // safe, v.getComponent will assert M<=4
}

#undef MXV_NO_OPERANDS
#undef MXV_OPd_MXVECTOR
#undef MXV_OPd_MXVECTOR_MXVECTOR
#undef MXV_OPd_MXQUATERNION_MXVECTOR
#undef MXV_OPd_MXVECTOR_MXVECTOR_MXVECTOR
#undef MXV_OPd_MXVECTOR_MXVECTOR_MXSINGLE
#undef MXV_OPd_MXVECTOR_MXVECTOR_MXREAL
#undef MXV_OPd_MXVECTOR_MXSINGLE_MXREAL
#undef MXV_OPd_MXREAL
#undef MXV_OPd_MXSINGLE
#undef MXV_OPd_MXVECTOR_MXREAL
#undef MXV_OPd_MXREAL_MXVECTOR
#undef MXV_OPd_MXVECTOR_MXSINGLE
#undef MXV_OPd_MXSINGLE_MXSINGLE
#undef MXV_OPd_MXSINGLE_MXVECTOR
#undef MXV_COMPARE
#undef MXV_COMPARE_SINGLE

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
