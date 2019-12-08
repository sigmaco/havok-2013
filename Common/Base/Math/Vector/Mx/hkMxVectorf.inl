/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#define MXV_NO_OPERANDS(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void METHOD##H(hkVector4f* v) { METHOD##H<I-1>(v); v[I-1].OP(); } \
	template <> HK_FORCE_INLINE void METHOD##H<1>(hkVector4f* v) { v[0].OP(); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD() { hkMxVectorf_Implementation::METHOD##H<M>(m_vec.v); }

#define MXV_OPf_MXVECTOR(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void METHOD##MXV_MXV_MXV(hkVector4f* v, const hkVector4f* v0) { METHOD##MXV_MXV_MXV<I-1>(v, v0); v[I-1].OP(v0[I-1]); } \
	template <> HK_FORCE_INLINE void METHOD##MXV_MXV_MXV<1>(hkVector4f* v, const hkVector4f* v0) { v[0].OP(v0[0]); }	\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxVectorfParameter m) { hkMxVectorf_Implementation::METHOD##MXV_MXV_MXV<M>(m_vec.v, m.m_vec.v); }

#define MXV_OPf_MXVECTOR_MXVECTOR(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
		template <int I> HK_FORCE_INLINE void OP##H(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1) { OP##H<I-1>(v, v0, v1); v[I-1].OP(v0[I-1], v1[I-1]); } \
		template <> HK_FORCE_INLINE void OP##H<1>(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1) { v[0].OP(v0[0], v1[0]); }								\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxVectorfParameter v0, hkMxVectorfParameter v1) { hkMxVectorf_Implementation::OP##H<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v);	}

#define MXV_OPf_MXQUATERNION_MXVECTOR(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
		template <int I> HK_FORCE_INLINE void OP##H(hkVector4f* v, const hkQuaternionf* v0, const hkVector4f* v1) { OP##H<I-1>(v, v0, v1); v[I-1].OP(v0[I-1], v1[I-1]); } \
		template <> HK_FORCE_INLINE void OP##H<1>(hkVector4f* v, const hkQuaternionf* v0, const hkVector4f* v1) { v[0].OP(v0[0], v1[0]); }									\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxQuaternionfParameter v0, hkMxVectorfParameter v1) { hkMxVectorf_Implementation::OP##H<M>(m_vec.v, (const hkQuaternionf*)v0.m_vec.v, v1.m_vec.v);	}

#define MXV_OPf_MXVECTOR_MXVECTOR_MXVECTOR(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##H(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1, const hkVector4f* v2) { OP##H<I-1>(v, v0, v1, v2); v[I-1].OP(v0[I-1], v1[I-1], v2[I-1]); } \
	template <> HK_FORCE_INLINE void OP##H<1>(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1, const hkVector4f* v2) { v[0].OP(v0[0], v1[0], v2[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkMxVectorfParameter v2) { hkMxVectorf_Implementation::OP##H<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v, v2.m_vec.v); }

#define MXV_OPf_MXVECTOR_MXVECTOR_MXSINGLE(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##S2H(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1, hkVector4fParameter v2) { OP##S2H<I-1>(v, v0, v1, v2); v[I-1].OP(v0[I-1], v1[I-1], v2); }\
	template <> HK_FORCE_INLINE void OP##S2H<1>(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1, hkVector4fParameter v2) { v[0].OP(v0[0], v1[0], v2); }\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkMxSinglefParameter v2) { hkMxVectorf_Implementation::OP##S2H<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v, v2.m_single.s); }

#define MXV_OPf_MXVECTOR_MXVECTOR_MXREAL(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##S2R(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1, const hkSimdFloat32* v2) { OP##S2R<I-1>(v, v0, v1, v2); v[I-1].OP(v0[I-1], v1[I-1], v2[I-1]); }\
	template <> HK_FORCE_INLINE void OP##S2R<1>(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1, const hkSimdFloat32* v2) { v[0].OP(v0[0], v1[0], v2[0]); }\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkMxRealfParameter v2) { hkMxVectorf_Implementation::OP##S2R<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v, v2.m_real.r); }

#define MXV_OPf_MXVECTOR_MXSINGLE_MXREAL(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##S2SR(hkVector4f* v, const hkVector4f* v0, hkVector4fParameter v1, const hkSimdFloat32* v2) { OP##S2SR<I-1>(v, v0, v1, v2); v[I-1].OP(v0[I-1], v1, v2[I-1]); }\
	template <> HK_FORCE_INLINE void OP##S2SR<1>(hkVector4f* v, const hkVector4f* v0, hkVector4fParameter v1,   const hkSimdFloat32* v2) { v[0].OP(v0[0], v1, v2[0]); }\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxVectorfParameter v0, hkMxSinglefParameter v1, hkMxRealfParameter v2) { hkMxVectorf_Implementation::OP##S2SR<M>(m_vec.v, v0.m_vec.v, v1.m_single.s, v2.m_real.r); }


#define MXV_OPf_MXREAL(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SHR(hkVector4f* v, const hkSimdFloat32* v0) { OP##SHR<I-1>(v, v0); v[I-1].OP(v0[I-1]); }\
	template <> HK_FORCE_INLINE void OP##SHR<1>(hkVector4f* v, const hkSimdFloat32* v0) { v[0].OP(v0[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxRealfParameter s) { hkMxVectorf_Implementation::OP##SHR<M>(m_vec.v, s.m_real.r); }


#define MXV_OPf_MXSINGLE(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SH(hkVector4f* v, hkVector4fParameter v0) { OP##SH<I-1>(v, v0); v[I-1].OP(v0); }\
	template <> HK_FORCE_INLINE void OP##SH<1>(hkVector4f* v, hkVector4fParameter v0) { v[0].OP(v0); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxSinglefParameter s) { hkMxVectorf_Implementation::OP##SH<M>(m_vec.v, s.m_single.s); }


#define MXV_OPf_MXVECTOR_MXREAL(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SH2R(hkVector4f* v, const hkVector4f* v0, const hkSimdFloat32* v1) { OP##SH2R<I-1>(v, v0, v1); v[I-1].OP(v0[I-1], v1[I-1]); }	\
	template <>   HK_FORCE_INLINE void OP##SH2R<1>(hkVector4f* v, const hkVector4f* v0, const hkSimdFloat32* v1) { v[0].OP(v0[0],v1[0]); }							\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxVectorfParameter v0, hkMxRealfParameter r) { hkMxVectorf_Implementation::OP##SH2R<M>(m_vec.v, v0.m_vec.v, r.m_real.r); }

#define MXV_OPf_MXREAL_MXVECTOR(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SHR2(hkVector4f* v, const hkSimdFloat32* s0, const hkVector4f* v1) { OP##SHR2<I-1>(v, s0, v1); v[I-1].OP(s0[I-1], v1[I-1]); }	\
	template <>   HK_FORCE_INLINE void OP##SHR2<1>(hkVector4f* v, const hkSimdFloat32* s0, const hkVector4f* v1 ) { v[0].OP(s0[0],v1[0]); }							\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxRealfParameter r, hkMxVectorfParameter v0 ) { hkMxVectorf_Implementation::OP##SHR2<M>(m_vec.v, r.m_real.r, v0.m_vec.v ); }

#define MXV_OPf_MXREAL_MXSINGLE(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##MX_OP_REAL_SINGLE   (hkVector4f* v, const hkSimdFloat32* s0, hkVector4fParameter v1) { OP##MX_OP_REAL_SINGLE<I-1>(v, s0, v1); v[I-1].OP(s0[I-1], v1); }	\
	template <>      HK_FORCE_INLINE void OP##MX_OP_REAL_SINGLE<1>(hkVector4f* v, const hkSimdFloat32* s0, hkVector4fParameter v1 ) { v[0].OP(s0[0],v1); }							\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxRealfParameter r, hkMxSinglefParameter v0 ) { hkMxVectorf_Implementation::OP##MX_OP_REAL_SINGLE<M>(m_vec.v, r.m_real.r, v0.m_single.s ); }


#define MXV_OPf_MXVECTOR_MXSINGLE(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##SH(hkVector4f* v, const hkVector4f* v0, hkVector4fParameter v1) { OP##SH<I-1>(v, v0, v1); v[I-1].OP(v0[I-1], v1); } \
	template <> HK_FORCE_INLINE void OP##SH<1>(hkVector4f* v, const hkVector4f* v0, hkVector4fParameter v1) { v[0].OP(v0[0], v1); }	\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxVectorfParameter v, hkMxSinglefParameter s) { hkMxVectorf_Implementation::OP##SH<M>(m_vec.v, v.m_vec.v, s.m_single.s); }

#define MXV_OPf_MXSINGLE_MXSINGLE(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##MX_SS(hkVector4f* v, hkVector4fParameter v0, hkVector4fParameter v1) { OP##MX_SS<I-1>(v, v0, v1); v[I-1].OP(v0, v1); } \
	template <> HK_FORCE_INLINE void OP##MX_SS<1>(  hkVector4f* v, hkVector4fParameter v0, hkVector4fParameter v1) { v[0].OP(v0, v1); }	\
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxSinglefParameter s0, hkMxSinglefParameter s1) { hkMxVectorf_Implementation::OP##MX_SS<M>(m_vec.v, s0.m_single.s, s1.m_single.s); }

#define MXV_OPf_MXSINGLE_MXVECTOR(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##RSH(hkVector4f* v, hkVector4fParameter v1, const hkVector4f* v0) { OP##RSH<I-1>(v, v1, v0); v[I-1].OP(v1, v0[I-1]); }\
	template <> HK_FORCE_INLINE void OP##RSH<1>(hkVector4f* v, hkVector4fParameter v1, const hkVector4f* v0) { v[0].OP(v1, v0[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxSinglefParameter s, hkMxVectorfParameter v) { hkMxVectorf_Implementation::OP##RSH<M>(m_vec.v, s.m_single.s, v.m_vec.v); }

#define MXV_COMPARE(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##CH(const hkVector4f* v0, const hkVector4f* v1, hkVector4fComparison* mask) { OP##CH<I-1>(v0,v1,mask); mask[I-1] = v0[I-1].OP(v1[I-1]); } \
	template <> HK_FORCE_INLINE void OP##CH<1>(const hkVector4f* v0, const hkVector4f* v1, hkVector4fComparison* mask) { mask[0] = v0[0].OP(v1[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxVectorfParameter v1, hkMxMaskf<M>& mask) const { hkMxVectorf_Implementation::OP##CH<M>(m_vec.v, v1.m_vec.v, mask.m_comp.c); }

#define MXV_COMPARE_SINGLE(METHOD, OP) \
	namespace hkMxVectorf_Implementation { \
	template <int I> HK_FORCE_INLINE void OP##CHS(const hkVector4f* v0, hkVector4fParameter v1, hkVector4fComparison* mask) { OP##CHS<I-1>(v0,v1,mask); mask[I-1] = v0[I-1].OP(v1); }\
	template <> HK_FORCE_INLINE void OP##CHS<1>(const hkVector4f* v0, hkVector4fParameter v1, hkVector4fComparison* mask) { mask[0] = v0[0].OP(v1); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::METHOD(hkMxSinglefParameter v1, hkMxMaskf<M>& mask) const { hkMxVectorf_Implementation::OP##CHS<M>(m_vec.v, v1.m_single.s, mask.m_comp.c); }


#ifndef HK_DISABLE_MATH_CONSTRUCTORS

namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void constructH(hkVector4f* v, hkVector4fParameter v0) { constructH<I-1>(v, v0); v[I-1] = v0; }
template <> HK_FORCE_INLINE void constructH<1>(hkVector4f* v, hkVector4fParameter v0) { v[0] = v0; }
}
template <int M>
HK_FORCE_INLINE hkMxVectorf<M>::hkMxVectorf(hkVector4fParameter v)
{
	hkMxVectorf_Implementation::constructH<M>(m_vec.v, v);
}


namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void constructRealH(hkVector4f* v, const hkSimdFloat32* v0) { constructRealH<I-1>(v, v0); v[I-1].setAll(v0[I-1]); }
template <> HK_FORCE_INLINE void constructRealH<1>(hkVector4f* v, const hkSimdFloat32* v0) { v[0].setAll(v0[0]); }
}
template <int M>
HK_FORCE_INLINE hkMxVectorf<M>::hkMxVectorf(hkMxRealfParameter v)
{
	hkMxVectorf_Implementation::constructRealH<M>(m_vec.v, v.m_real.r);
}


namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void constructSRealH(hkVector4f* v, hkSimdFloat32Parameter r) { constructSRealH<I-1>(v, r); v[I-1].setAll(r); }
template <> HK_FORCE_INLINE void constructSRealH<1>(hkVector4f* v, hkSimdFloat32Parameter r) { v[0].setAll(r); }
}
template <int M>
HK_FORCE_INLINE hkMxVectorf<M>::hkMxVectorf(hkSimdFloat32Parameter r)
{
	hkMxVectorf_Implementation::constructSRealH<M>(m_vec.v, r);
}

#endif

namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void setBCH(hkVector4f* v, const hkSimdFloat32* v0) { setBCH<I-1>(v, v0); v[I-1].setAll(v0[I-1]); }
template <> HK_FORCE_INLINE void setBCH<1>(hkVector4f* v, const hkSimdFloat32* v0) { v[0].setAll(v0[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::setBroadcast( hkMxRealfParameter r )
{
	hkMxVectorf_Implementation::setBCH<M>(m_vec.v, r.m_real.r);
}


namespace hkMxVectorf_Implementation
{
	template <int I> HK_FORCE_INLINE void setBCH(hkVector4f* v, hkSimdFloat32Parameter v0) { setBCH<I-1>(v, v0); v[I-1].setAll(v0); }
	template <> HK_FORCE_INLINE void setBCH<1>(hkVector4f* v, hkSimdFloat32Parameter v0) { v[0].setAll(v0); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::setAll( hkSimdFloat32Parameter r )
{
	hkMxVectorf_Implementation::setBCH<M>(m_vec.v, r);
}


namespace hkMxVectorf_Implementation
{
template <int I, int idx> struct setScalarBroadcastH { HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* v0) { setScalarBroadcastH<I-1,idx>::apply(v, v0); v[I-1].setBroadcast<idx>(v0[I-1]); } };
template <int idx> struct setScalarBroadcastH<1,idx> { HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* v0) { v[0].setBroadcast<idx>(v0[0]); } };
}
template <int M>
template <int I>
HK_FORCE_INLINE void hkMxVectorf<M>::setScalarBroadcast(hkMxVectorfParameter v)
{
	HK_VECTOR4f_SUBINDEX_CHECK;
	hkMxVectorf_Implementation::setScalarBroadcastH<M,I>::apply(m_vec.v, v.m_vec.v);
}


template <int M>
template <int I>
HK_FORCE_INLINE void hkMxVectorf<M>::setVector(hkVector4fParameter v)
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	m_vec.v[I] = v;
}

template <int M>
template <int I>
HK_FORCE_INLINE const hkVector4f& hkMxVectorf<M>::getVector() const
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	return m_vec.v[I];
}

template <int M>
template <int I>
HK_FORCE_INLINE void hkMxVectorf<M>::getVector(hkVector4f& vOut) const
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	vOut = m_vec.v[I];
}

namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void setConstH(hkVector4f* v, hkVector4fParameter vC) { setConstH<I-1>(v,vC); v[I-1] = vC; }
template <> HK_FORCE_INLINE void setConstH<1>(hkVector4f* v, hkVector4fParameter vC) { v[0] = vC; }
}
template <int M>
template<int vectorConstant> 
HK_FORCE_INLINE void hkMxVectorf<M>::setConstant()
{
	const hkVector4f vC = hkVector4f::getConstant<vectorConstant>();
	hkMxVectorf_Implementation::setConstH<M>(m_vec.v, vC);
}


namespace hkMxVectorf_Implementation
{
template <int I, int N> struct isOkH { HK_FORCE_INLINE static hkBool32 apply(const hkVector4f* v) { if (v[I-1].isOk<N>()) return isOkH<I-1,N>::apply(v); else return 0; } };
template <int N> struct isOkH<1,N> { HK_FORCE_INLINE static hkBool32 apply(const hkVector4f* v) { return v[0].isOk<N>(); } };
}
template <int M>
template <int N>
HK_FORCE_INLINE hkBool32 hkMxVectorf<M>::isOk() const
{
#if !defined(HK_DEBUG)
	// pragma compiler perf warning
#endif
	return hkMxVectorf_Implementation::isOkH<M,N>::apply(m_vec.v);
}


namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void moveH(hkVector4f* HK_RESTRICT v, const hkVector4f* HK_RESTRICT v0) { moveH<I-1>(v, v0); v[I-1] = v0[I-1]; }
template <> HK_FORCE_INLINE void moveH<1>(hkVector4f* HK_RESTRICT v, const hkVector4f* HK_RESTRICT v0) { v[0] = v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::moveLoad(const hkVector4f* HK_RESTRICT v)
{
	hkMxVectorf_Implementation::moveH<M>(m_vec.v, v);
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::moveStore(hkVector4f* HK_RESTRICT v) const
{
	hkMxVectorf_Implementation::moveH<M>(v, m_vec.v);
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::operator= ( hkMxVectorfParameter v )
{
	hkMxVectorf_Implementation::moveH<M>(m_vec.v, v.m_vec.v);
}


namespace hkMxVectorf_Implementation
{
template <int I, int N> struct loadRH {
	HK_FORCE_INLINE static void apply(hkVector4f* v, const hkFloat32* r) 
	{ 
		loadRH<I-1,N>::apply(v, r); 
		v[I-1].load<N>(r+((I-1)*N)); 
	}
};
template <int N> struct loadRH<1,N> {
	HK_FORCE_INLINE static void apply(hkVector4f* v, const hkFloat32* r) 
	{ 
		v[0].load<N>(r); 
	}
};
}

template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectorf<M>::load(const hkFloat32* r)
{
	hkMxVectorf_Implementation::loadRH<M,N>::apply(m_vec.v, r);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct loadHC {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkFloat32* base)
{
	loadHC<I-1, byteAddressIncrement, N, A>::apply(v, base);
	v[I-1].load<N, A>(hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement ));
} };
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct loadHC<1, byteAddressIncrement, N, A> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkFloat32* base)
{
	v[0].load<N, A>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A>
HK_FORCE_INLINE void hkMxVectorf<M>::load(const hkFloat32* base)
{
	hkMxVectorf_Implementation::loadHC<M, byteAddressIncrement, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct loadUnpackHC {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkHalf* base)
{
	loadUnpackHC<I-1, byteAddressIncrement, N, A>::apply(v, base);
	v[I-1].load<N, A>(hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement ));
} };
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct loadUnpackHC<1, byteAddressIncrement, N, A> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkHalf* base)
{
	v[0].load<N, A>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A>
HK_FORCE_INLINE void hkMxVectorf<M>::loadUnpack(const hkHalf* base)
{
	hkMxVectorf_Implementation::loadUnpackHC<M, byteAddressIncrement, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void loadNRH(hkVector4f* v, const hkFloat32* r) { loadNRH<I-1>(v, r); v[I-1].load<4,HK_IO_NATIVE_ALIGNED>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void loadNRH<1>(hkVector4f* v, const hkFloat32* r) { v[0].load<4,HK_IO_NATIVE_ALIGNED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::loadNotAligned(const hkFloat32* r)
{
	hkMxVectorf_Implementation::loadNRH<M>(m_vec.v, r);
}

namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void loadCNRH(hkVector4f* v, const hkFloat32* r) { loadCNRH<I-1>(v, r); v[I-1].load<4,HK_IO_NOT_CACHED>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void loadCNRH<1>(hkVector4f* v, const hkFloat32* r) { v[0].load<4,HK_IO_NOT_CACHED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::loadNotCached(const hkFloat32* r)
{
	hkMxVectorf_Implementation::loadCNRH<M>(m_vec.v, r);
}

namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void storeRH(const hkVector4f* v, hkFloat32* r) { storeRH<I-1>(v, r); v[I-1].store<4>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void storeRH<1>(const hkVector4f* v, hkFloat32* r) { v[0].store<4>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::store(hkFloat32* r) const
{
	hkMxVectorf_Implementation::storeRH<M>(m_vec.v, r);
}

namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct storeHC {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkFloat32* base)
{
	hkFloat32* HK_RESTRICT ptr0 = hkAddByteOffset(base, (I-1) * byteAddressIncrement); 
	storeHC<I-1, byteAddressIncrement, N, A>::apply(v, base);
	v[I-1].store<N, A>(ptr0);
} };
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A> struct storeHC<1, byteAddressIncrement, N, A> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkFloat32* base)
{
	v[0].store<N, A>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A>
HK_FORCE_INLINE void hkMxVectorf<M>::store(hkFloat32* base) const
{
	hkMxVectorf_Implementation::storeHC<M, byteAddressIncrement, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement, int N, hkMathIoMode A, hkMathRoundingMode R> struct storePackHC {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* base)
{
	hkHalf* HK_RESTRICT ptr0 = hkAddByteOffset(base, (I-1) * byteAddressIncrement); 
	storePackHC<I-1, byteAddressIncrement, N, A, R>::apply(v, base);
	v[I-1].store<N, A, R>(ptr0);
} };
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A, hkMathRoundingMode R> struct storePackHC<1, byteAddressIncrement, N, A, R> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf* base)
{
	v[0].store<N, A, R>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkMxVectorf<M>::storePack(hkHalf* base) const
{
	hkMxVectorf_Implementation::storePackHC<M, byteAddressIncrement, N, A, R>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void storeNRH(const hkVector4f* v, hkFloat32* r) { storeNRH<I-1>(v, r); v[I-1].store<4,HK_IO_NATIVE_ALIGNED>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void storeNRH<1>(const hkVector4f* v, hkFloat32* r) { v[0].store<4,HK_IO_NATIVE_ALIGNED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::storeNotAligned(hkFloat32* r) const
{
	hkMxVectorf_Implementation::storeNRH<M>(m_vec.v, r);
}

namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void storeCNRH(const hkVector4f* v, hkFloat32* r) { storeCNRH<I-1>(v, r); v[I-1].store<4,HK_IO_NOT_CACHED>(r+((I-1)*4)); }
template <> HK_FORCE_INLINE void storeCNRH<1>(const hkVector4f* v, hkFloat32* r) { v[0].store<4,HK_IO_NOT_CACHED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::storeNotCached(hkFloat32* r) const
{
	hkMxVectorf_Implementation::storeCNRH<M>(m_vec.v, r);
}



namespace hkMxVectorf_Implementation
{
template <int I, int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct normalizeH { HK_FORCE_INLINE static void apply(hkVector4f* v) { normalizeH<I-1,N,A,S>::apply(v); v[I-1].normalize<N,A,S>(); } };
template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct normalizeH<1,N,A,S> { HK_FORCE_INLINE static void apply(hkVector4f* v) { v[0].normalize<N,A,S>(); } };
}
template <int M> template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void hkMxVectorf<M>::normalize() { hkMxVectorf_Implementation::normalizeH<M,N,A,S>::apply(m_vec.v); }

template <int M> template <int N> HK_FORCE_INLINE void hkMxVectorf<M>::normalize() { hkMxVectorf_Implementation::normalizeH<M,N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_vec.v); }



namespace hkMxVectorf_Implementation
{
template <int I, int N> struct setNegH { HK_FORCE_INLINE static void apply(hkVector4f* v0, const hkVector4f* v1) { setNegH<I-1,N>::apply(v0,v1); v0[I-1].setNeg<N>(v1[I-1]); } };
template <int N> struct setNegH<1,N> { HK_FORCE_INLINE static void apply(hkVector4f* v0, const hkVector4f* v1) { v0[0].setNeg<N>(v1[0]); } };
}
template <int M> template <int N> HK_FORCE_INLINE void hkMxVectorf<M>::setNeg(hkMxVectorfParameter v0) { hkMxVectorf_Implementation::setNegH<M,N>::apply(m_vec.v, v0.m_vec.v); }

namespace hkMxVectorf_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setDivH { HK_FORCE_INLINE static void apply(hkVector4f* v0, const hkVector4f* v1, const hkVector4f* v2) { setDivH<I-1,A,D>::apply(v0,v1,v2); v0[I-1].setDiv<A,D>(v1[I-1],v2[I-1]); } };
template <hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setDivH<1,A,D> { HK_FORCE_INLINE static void apply(hkVector4f* v0, const hkVector4f* v1, const hkVector4f* v2) { v0[0].setDiv<A,D>(v1[0],v2[0]); } };
}
template <int M> template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void hkMxVectorf<M>::setDiv(hkMxVectorfParameter v0, hkMxVectorfParameter v1) { hkMxVectorf_Implementation::setDivH<M,A,D>::apply(m_vec.v, v0.m_vec.v, v1.m_vec.v); }

template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::setDiv(hkMxVectorfParameter v0, hkMxVectorfParameter v1) { hkMxVectorf_Implementation::setDivH<M,HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_vec.v, v0.m_vec.v, v1.m_vec.v); }

namespace hkMxVectorf_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct setSqrtInverseH { HK_FORCE_INLINE static void apply(hkVector4f* v0, const hkVector4f* v1) { setSqrtInverseH<I-1,A,S>::apply(v0,v1); v0[I-1].setSqrtInverse<A,S>(v1[I-1]); } };
template <hkMathAccuracyMode A, hkMathNegSqrtMode S> struct setSqrtInverseH<1,A,S> { HK_FORCE_INLINE static void apply(hkVector4f* v0, const hkVector4f* v1) { v0[0].setSqrtInverse<A,S>(v1[0]); } };
}
template <int M> template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void hkMxVectorf<M>::setSqrtInverse(hkMxVectorfParameter v0) { hkMxVectorf_Implementation::setSqrtInverseH<M,A,S>::apply(m_vec.v, v0.m_vec.v); }

template <int M> HK_FORCE_INLINE void hkMxVectorf<M>::setSqrtInverse(hkMxVectorfParameter v0) { hkMxVectorf_Implementation::setSqrtInverseH<M,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_vec.v, v0.m_vec.v); }

MXV_NO_OPERANDS( setZero, setZero )

namespace hkMxVectorf_Implementation
{
template <int I, int N> struct zeroCompH { HK_FORCE_INLINE static void apply(hkVector4f* v) { zeroCompH<I-1,N>::apply(v); v[I-1].zeroComponent<N>(); } };
template <int N> struct zeroCompH<1,N> { HK_FORCE_INLINE static void apply(hkVector4f* v) { v[0].zeroComponent<N>(); } };
}
template <int M> 
template <int N> 
HK_FORCE_INLINE void hkMxVectorf<M>::zeroComponent() 
{ 
	hkMxVectorf_Implementation::zeroCompH<M,N>::apply(m_vec.v); 
}

MXV_OPf_MXVECTOR( setAbs, setAbs )
MXV_OPf_MXVECTOR( add, add )
MXV_OPf_MXVECTOR( sub, sub )
MXV_OPf_MXVECTOR( mul, mul )
MXV_OPf_MXREAL( mul, mul )

MXV_OPf_MXVECTOR( setXYZ, setXYZ )
MXV_OPf_MXVECTOR( setW, setW )

MXV_OPf_MXVECTOR_MXVECTOR( setCross, setCross )

MXV_OPf_MXVECTOR_MXVECTOR( setAdd, setAdd )
MXV_OPf_MXVECTOR_MXVECTOR( setSub, setSub )
MXV_OPf_MXVECTOR_MXVECTOR( setMul, setMul )

MXV_OPf_MXVECTOR_MXVECTOR( addMul, addMul )
MXV_OPf_MXVECTOR_MXVECTOR( subMul, subMul )
MXV_OPf_MXVECTOR_MXVECTOR( setMin, setMin )
MXV_OPf_MXVECTOR_MXVECTOR( setMax, setMax )

MXV_OPf_MXREAL_MXVECTOR( addMul, addMul )
MXV_OPf_MXREAL_MXVECTOR( subMul, subMul )
MXV_OPf_MXREAL_MXVECTOR( setMul, setMul )
MXV_OPf_MXREAL_MXSINGLE( setMul, setMul )

MXV_OPf_MXQUATERNION_MXVECTOR( setRotatedDir, _setRotatedDir )
MXV_OPf_MXQUATERNION_MXVECTOR( setRotatedInverseDir, _setRotatedInverseDir )

MXV_OPf_MXVECTOR_MXVECTOR_MXVECTOR( setAddMul, setAddMul )
MXV_OPf_MXVECTOR_MXVECTOR_MXVECTOR( setSubMul, setSubMul )
MXV_OPf_MXVECTOR_MXVECTOR_MXSINGLE( setAddMul, setAddMul )
MXV_OPf_MXVECTOR_MXVECTOR_MXSINGLE( setSubMul, setSubMul )
MXV_OPf_MXVECTOR_MXVECTOR_MXREAL( setSubMul, setSubMul )
MXV_OPf_MXVECTOR_MXSINGLE_MXREAL( setSubMul, setSubMul )

MXV_OPf_MXVECTOR_MXVECTOR_MXREAL( setInterpolate, setInterpolate )

MXV_OPf_MXSINGLE( add, add )
MXV_OPf_MXSINGLE( sub, sub )
MXV_OPf_MXSINGLE( mul, mul )
MXV_OPf_MXSINGLE( setW, setW )
MXV_OPf_MXREAL( setW, setW )
MXV_OPf_MXVECTOR_MXREAL( setXYZ_W, setXYZ_W )


MXV_OPf_MXVECTOR_MXSINGLE( addMul, addMul )
MXV_OPf_MXSINGLE_MXSINGLE( addMul, addMul )
MXV_OPf_MXVECTOR_MXSINGLE( setAdd, setAdd )
MXV_OPf_MXVECTOR_MXSINGLE( setSub, setSub )
MXV_OPf_MXSINGLE_MXVECTOR( setSub, setSub )
MXV_OPf_MXVECTOR_MXSINGLE( setMul, setMul )
MXV_OPf_MXVECTOR_MXSINGLE( setCross, setCross )
MXV_OPf_MXSINGLE_MXVECTOR( setCross, setCross )
MXV_OPf_MXVECTOR_MXSINGLE( setMin, setMin )
MXV_OPf_MXVECTOR_MXSINGLE( setMax, setMax )

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





namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void setAddMulH(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1, hkVector4fParameter v2) { setAddMulH<I-1>(v, v0, v1, v2); v[I-1].setAddMul(v0[I-1], v1[I-1], v2.getComponent<I-1>()); }
template <> HK_FORCE_INLINE void setAddMulH<1>(hkVector4f* v, const hkVector4f* v0, const hkVector4f* v1, hkVector4fParameter v2) { v[0].setAddMul(v0[0], v1[0], v2.getComponent<0>()); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::setAddMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkVector4fParameter v2)
{
	hkMxVectorf_Implementation::setAddMulH<M>(m_vec.v, v0.m_vec.v, v1.m_vec.v, v2); // this is safe because v2.getComponent<> asserts M<=4
}


template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::setXYZ_W(hkMxVectorfParameter v0, hkMxVectorfParameter v1)
{
	setXYZ(v0);
	setW(v1);
}


template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::storeTransposed4(hkMatrix4f& matrix4) const
{
	HK_MXVECTORf_MX_NOT_IMPLEMENTED;
}

template <>
HK_FORCE_INLINE void hkMxVectorf<1>::storeTransposed4(hkMatrix4f& matrix4) const
{
	hkVector4f a; a.setBroadcast<0>(m_vec.v[0]);
	hkVector4f b; b.setBroadcast<1>(m_vec.v[0]);
	hkVector4f c; c.setBroadcast<2>(m_vec.v[0]);
	hkVector4f d; d.setBroadcast<3>(m_vec.v[0]);

	matrix4.setCols(a,b,c,d);
	// todo. for debug: set .yzw to 0x23456789
}

template <>
HK_FORCE_INLINE void hkMxVectorf<2>::storeTransposed4(hkMatrix4f& matrix4) const
{
	matrix4.setRows(m_vec.v[0], m_vec.v[1], m_vec.v[1], m_vec.v[1]);
}

template <>
HK_FORCE_INLINE void hkMxVectorf<3>::storeTransposed4(hkMatrix4f& matrix4) const
{
	matrix4.setRows(m_vec.v[0], m_vec.v[1], m_vec.v[2], m_vec.v[2]);
}

template <>
HK_FORCE_INLINE void hkMxVectorf<4>::storeTransposed4(hkMatrix4f& matrix4) const
{
	matrix4.setRows(m_vec.v[0], m_vec.v[1], m_vec.v[2], m_vec.v[3]);
}


namespace hkMxVectorf_Implementation
{
template <int M, int N> struct hAddH { HK_FORCE_INLINE static void apply(hkMxVectorfParameter v, hkVector4f& addsOut) { HK_MXVECTORf_MX_NOT_IMPLEMENTED; } };
template <int M, int N> struct hAddHS { HK_FORCE_INLINE static void apply(hkMxVectorfParameter v, hkSimdFloat32& addsOut) { HK_MXVECTORf_MX_NOT_IMPLEMENTED; } };
template <> struct hAddH<4,4> { HK_FORCE_INLINE static void apply(const hkMxVectorf<4>& v, hkVector4f& addsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4f t1; t1.setAdd( f.getColumn<2>(), f.getColumn<3>() );
	addsOut.setAdd( t0, t1 );
} };
template <> struct hAddH<4,3> { HK_FORCE_INLINE static void apply(const hkMxVectorf<4>& v, hkVector4f& addsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	addsOut.setAdd( t0, f.getColumn<2>() );
} };
template <> struct hAddH<3,4> { HK_FORCE_INLINE static void apply(const hkMxVectorf<3>& v, hkVector4f& addsOut) 
{ 
	// optimize!
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4f t1; t1.setAdd( f.getColumn<2>(), f.getColumn<3>() );
	addsOut.setAdd( t0, t1 );
} };
template <> struct hAddH<3,3> { HK_FORCE_INLINE static void apply(const hkMxVectorf<3>& v, hkVector4f& addsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	addsOut.setAdd( t0, f.getColumn<2>() );
} };
template <> struct hAddH<2,4> { HK_FORCE_INLINE static void apply(const hkMxVectorf<2>& v, hkVector4f& addsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4f t1; t1.setAdd( f.getColumn<2>(), f.getColumn<3>() );
	addsOut.setAdd( t0, t1 );
} };
template <> struct hAddH<2,3> { HK_FORCE_INLINE static void apply(const hkMxVectorf<2>& v, hkVector4f& addsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setAdd( f.getColumn<0>(), f.getColumn<1>() );
	addsOut.setAdd( t0, f.getColumn<2>() );
} };

template <int N> struct hAddH<1,N> { HK_FORCE_INLINE static void apply(const hkMxVectorf<1>& v, hkVector4f& addsOut) 
{ 
	addsOut.setHorizontalAdd<N>(v.m_vec.v[0]);
} };
template <int N> struct hAddHS<1,N> { HK_FORCE_INLINE static void apply(const hkMxVectorf<1>& v, hkSimdFloat32& addsOut) 
{ 
	addsOut = v.m_vec.v[0].horizontalAdd<N>();
} };
}
template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectorf<M>::horizontalAdd( hkVector4f& addsOut ) const
{
	hkMxVectorf_Implementation::hAddH<M,N>::apply(*this, addsOut);
}

template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectorf<M>::horizontalAdd( hkSimdFloat32& addsOut ) const
{
	hkMxVectorf_Implementation::hAddHS<M,N>::apply(*this, addsOut);
}


namespace hkMxVectorf_Implementation
{
template <int M, int N> struct hMinH { HK_FORCE_INLINE static void apply(hkMxVectorfParameter v, hkVector4f& minsOut) { HK_MXVECTORf_MX_NOT_IMPLEMENTED; } };
template <> struct hMinH<4,4> { HK_FORCE_INLINE static void apply(const hkMxVectorf<4>& v, hkVector4f& minsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4f t1; t1.setMin( f.getColumn<2>(), f.getColumn<3>() );
	minsOut.setMin( t0, t1 );
} };
template <> struct hMinH<4,3> { HK_FORCE_INLINE static void apply(const hkMxVectorf<4>& v, hkVector4f& minsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	minsOut.setMin( t0, f.getColumn<2>() );
} };
template <> struct hMinH<3,4> { HK_FORCE_INLINE static void apply(const hkMxVectorf<3>& v, hkVector4f& minsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4f t1; t1.setMin( f.getColumn<2>(), f.getColumn<3>() );
	minsOut.setMin( t0, t1 );
} };
template <> struct hMinH<3,3> { HK_FORCE_INLINE static void apply(const hkMxVectorf<3>& v, hkVector4f& minsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	minsOut.setMin( t0, f.getColumn<2>() );
} };
template <> struct hMinH<2,4> { HK_FORCE_INLINE static void apply(const hkMxVectorf<2>& v, hkVector4f& minsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4f t1; t1.setMin( f.getColumn<2>(), f.getColumn<3>() );
	minsOut.setMin( t0, t1 );
} };
template <> struct hMinH<2,3> { HK_FORCE_INLINE static void apply(const hkMxVectorf<2>& v, hkVector4f& minsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMin( f.getColumn<0>(), f.getColumn<1>() );
	minsOut.setMin( t0, f.getColumn<2>() );
} };
template <int N> struct hMinH<1,N> { HK_FORCE_INLINE static void apply(const hkMxVectorf<1>& v, hkVector4f& minsOut) 
{ 
	minsOut.setHorizontalMin<N>(v.m_vec.v[0]);
} };
}
template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectorf<M>::horizontalMin( hkVector4f& minsOut ) const
{
	hkMxVectorf_Implementation::hMinH<M,N>::apply(*this, minsOut);
}


namespace hkMxVectorf_Implementation
{
template <int M, int N> struct hMaxH { HK_FORCE_INLINE static void apply(hkMxVectorfParameter v, hkVector4f& maxsOut) { HK_MXVECTORf_MX_NOT_IMPLEMENTED; } };
template <> struct hMaxH<4,4> { HK_FORCE_INLINE static void apply(const hkMxVectorf<4>& v, hkVector4f& maxsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4f t1; t1.setMax( f.getColumn<2>(), f.getColumn<3>() );
	maxsOut.setMax( t0, t1 );
} };
template <> struct hMaxH<4,3> { HK_FORCE_INLINE static void apply(const hkMxVectorf<4>& v, hkVector4f& maxsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	maxsOut.setMax( t0, f.getColumn<2>() );
} };
template <> struct hMaxH<3,4> { HK_FORCE_INLINE static void apply(const hkMxVectorf<3>& v, hkVector4f& maxsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4f t1; t1.setMax( f.getColumn<2>(), f.getColumn<3>() );
	maxsOut.setMax( t0, t1 );
} };
template <> struct hMaxH<3,3> { HK_FORCE_INLINE static void apply(const hkMxVectorf<3>& v, hkVector4f& maxsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	maxsOut.setMax( t0, f.getColumn<2>() );
} };
template <> struct hMaxH<2,4> { HK_FORCE_INLINE static void apply(const hkMxVectorf<2>& v, hkVector4f& maxsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	hkVector4f t1; t1.setMax( f.getColumn<2>(), f.getColumn<3>() );
	maxsOut.setMax( t0, t1 );
} };
template <> struct hMaxH<2,3> { HK_FORCE_INLINE static void apply(const hkMxVectorf<2>& v, hkVector4f& maxsOut) 
{ 
	hkMatrix4f f; v.storeTransposed4(f);
	hkVector4f t0; t0.setMax( f.getColumn<0>(), f.getColumn<1>() );
	maxsOut.setMax( t0, f.getColumn<2>() );
} };
template <int N> struct hMaxH<1,N> { HK_FORCE_INLINE static void apply(const hkMxVectorf<1>& v, hkVector4f& maxsOut) 
{ 
	maxsOut.setHorizontalMax<N>(v.m_vec.v[0]);
} };
}
template <int M>
template <int N>
HK_FORCE_INLINE void hkMxVectorf<M>::horizontalMax( hkVector4f& maxsOut ) const
{
	hkMxVectorf_Implementation::hMaxH<M,N>::apply(*this, maxsOut);
}


namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void reduceAddH(const hkVector4f* v, hkVector4f& addOut) { reduceAddH<I-1>(v, addOut); addOut.add(v[I-1]); }
template <> HK_FORCE_INLINE void reduceAddH<1>(const hkVector4f* v, hkVector4f& addOut) { addOut = v[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::reduceAdd(hkVector4f& addOut) const
{
	hkMxVectorf_Implementation::reduceAddH<M>(m_vec.v, addOut);
}


namespace hkMxVectorf_Implementation
{
template <int I, int N> struct dotH { HK_FORCE_INLINE static void apply(const hkVector4f* v, const hkVector4f* v0, hkSimdFloat32* dotsOut) { dotH<I-1,N>::apply(v, v0, dotsOut); dotsOut[I-1] = v[I-1].dot<N>(v0[I-1]); } };
template <int N> struct dotH<1,N> { HK_FORCE_INLINE static void apply(const hkVector4f* v, const hkVector4f* v0, hkSimdFloat32* dotsOut) { dotsOut[0] = v[0].dot<N>(v0[0]); } };
}
template <int M> 
template <int N> 
HK_FORCE_INLINE void hkMxVectorf<M>::dot(hkMxVectorfParameter v, hkMxRealf<M>& dotsOut) const 
{ 
	hkMxVectorf_Implementation::dotH<M,N>::apply(m_vec.v, v.m_vec.v, dotsOut.m_real.r); 
}


namespace hkMxVectorf_Implementation
{
template <int I, int N> struct dotHSingle { HK_FORCE_INLINE static void apply(const hkVector4f* v, const hkVector4f& v0, hkSimdFloat32* dotsOut) { dotHSingle<I-1,N>::apply(v, v0, dotsOut); dotsOut[I-1] = v[I-1].dot<N>(v0); } };
template <int N> struct dotHSingle<1,N> {   HK_FORCE_INLINE static void apply(const hkVector4f* v, const hkVector4f& v0, hkSimdFloat32* dotsOut) { dotsOut[0] = v[0].dot<N>(v0); } };
}
template <int M> 
template <int N> 
HK_FORCE_INLINE void hkMxVectorf<M>::dot(hkMxSinglefParameter v, hkMxRealf<M>& dotsOut) const 
{ 
	hkMxVectorf_Implementation::dotHSingle<M,N>::apply(m_vec.v, v.m_single.s, dotsOut.m_real.r); 
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherH {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* HK_RESTRICT base)
{
	gatherH<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1] = *hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement );
} };
template <hkUint32 byteAddressIncrement> struct gatherH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* HK_RESTRICT base)
{
	v[0] = *base;
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectorf<M>::gather(const hkVector4f* HK_RESTRICT base)
{
	hkMxVectorf_Implementation::gatherH<M, byteAddressIncrement>::apply(m_vec.v, base);
}

namespace hkMxVectorf_Implementation
{
	template <int N> struct componentCountToSelectMask {};
	template <> struct componentCountToSelectMask<0> { 	enum { Mask = hkVector4ComparisonMask::MASK_NONE }; };
	template <> struct componentCountToSelectMask<1> { 	enum { Mask = hkVector4ComparisonMask::MASK_X }; };
	template <> struct componentCountToSelectMask<2> { 	enum { Mask = hkVector4ComparisonMask::MASK_XY }; };
	template <> struct componentCountToSelectMask<3> { 	enum { Mask = hkVector4ComparisonMask::MASK_XYZ }; };
	template <> struct componentCountToSelectMask<4> { 	enum { Mask = hkVector4ComparisonMask::MASK_XYZW }; };
}

namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement, hkVector4ComparisonMask::Mask MASK> struct gatherHC {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* HK_RESTRICT base)
{
	gatherHC<I-1, byteAddressIncrement, MASK>::apply(v, base);
	v[I-1].setSelect<MASK>(*hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement), v[I-1]);
} };
template <hkUint32 byteAddressIncrement, hkVector4ComparisonMask::Mask MASK> struct gatherHC<1, byteAddressIncrement, MASK> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* HK_RESTRICT base)
{
	v[0].setSelect<MASK>(*base, v[0]);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N>
HK_FORCE_INLINE void hkMxVectorf<M>::gather(const hkVector4f* HK_RESTRICT base)
{
	hkMxVectorf_Implementation::gatherHC<M, byteAddressIncrement, hkVector4ComparisonMask::Mask(hkMxVectorf_Implementation::componentCountToSelectMask<N>::Mask)>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUintH {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* HK_RESTRICT base, const hkUint16* indices)
{
	gatherUintH<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1] = *hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement );
} };
template <hkUint32 byteAddressIncrement> struct gatherUintH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* HK_RESTRICT base, const hkUint16* indices)
{
	v[0] = *hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement );
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectorf<M>::gather(const hkVector4f* HK_RESTRICT base, const hkUint16* indices)
{
	hkMxVectorf_Implementation::gatherUintH<M, byteAddressIncrement>::apply(m_vec.v, base, indices);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherIntH {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* HK_RESTRICT base, const hkInt32* indices)
{
	gatherIntH<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1] = *hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement );
} };
template <hkUint32 byteAddressIncrement> struct gatherIntH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* HK_RESTRICT base, const hkInt32* indices)
{
	v[0] = *hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement );
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectorf<M>::gather(const hkVector4f* HK_RESTRICT base, const hkInt32* indices)
{
	hkMxVectorf_Implementation::gatherIntH<M, byteAddressIncrement>::apply(m_vec.v, base, indices);
}


namespace hkMxVectorf_Implementation
{
	template <int I, hkUint32 byteOffset> struct gatherWithOffsetH {
	HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
	{
		const hkVector4f* HK_RESTRICT ptr0 = (const hkVector4f*)hkAddByteOffsetConst(base[I-1], byteOffset); 
		gatherWithOffsetH<I-1, byteOffset>::apply(v, base);
		v[I-1] = *ptr0;
	} };
	template <hkUint32 byteOffset> struct gatherWithOffsetH<0, byteOffset> {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base){} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxVectorf<M>::gatherWithOffset(const void* base[M])
{
	hkMxVectorf_Implementation::gatherWithOffsetH<M, byteOffset>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
	template <int I, hkUint32 byteOffset, hkVector4ComparisonMask::Mask M> struct gatherWithOffsetHC {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
		{
			const hkVector4f* HK_RESTRICT ptr0 = (const hkVector4f*)hkAddByteOffsetConst(base[I-1], byteOffset); 
			gatherWithOffsetHC<I-1, byteOffset, M>::apply(v, base);
			v[I-1].setSelect<M>(*ptr0, v[I-1]);
		}
	};
	template <hkUint32 byteOffset, hkVector4ComparisonMask::Mask M> struct gatherWithOffsetHC<0, byteOffset, M> {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base){}
	};
}
template <int M>
template <hkUint32 byteOffset, int N> 
HK_FORCE_INLINE void hkMxVectorf<M>::gatherWithOffset(const void* base[M])
{
	hkMxVectorf_Implementation::gatherWithOffsetHC<M, byteOffset, hkVector4ComparisonMask::Mask( hkMxVectorf_Implementation::componentCountToSelectMask<N>::Mask) >::apply(m_vec.v, base);
}



namespace hkMxVectorf_Implementation
{
	template <int I, hkUint32 byteOffset> struct gatherHalfsWithOffsetH {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base)
		{
			const hkHalf* HK_RESTRICT ptr0 = (const hkHalf*)hkAddByteOffsetConst(base[I-1], byteOffset); 
			gatherHalfsWithOffsetH<I-1, byteOffset>::apply(v, base);
			v[I-1].load<4>( ptr0 );
		}
	};
	template <hkUint32 byteOffset> struct gatherHalfsWithOffsetH<0, byteOffset> {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const void** base){}
	};
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxVectorf<M>::gatherHalfsWithOffset(const void* base[M])
{
	hkMxVectorf_Implementation::gatherHalfsWithOffsetH<M, byteOffset>::apply(m_vec.v, base);
}

namespace hkMxVectorf_Implementation
{
	template <int I, hkUint32 byteOffset, int N, hkMathIoMode A> struct loadWithOffsetHC {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const hkFloat32** base)
		{
			const hkFloat32* ptr0 = (const hkFloat32*)hkAddByteOffsetConst(base[I-1], byteOffset); 
			loadWithOffsetHC<I-1, byteOffset, N, A>::apply(v, base);
			v[I-1].load<N, A>(ptr0);
		}
	};
	template <hkUint32 byteOffset, int N, hkMathIoMode A> struct loadWithOffsetHC<0, byteOffset, N, A> {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const hkFloat32** base){}
	 };
}
template <int M>
template <hkUint32 byteOffset, int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkMxVectorf<M>::loadWithOffset(const hkFloat32* base[M])
{
	hkMxVectorf_Implementation::loadWithOffsetHC<M, byteOffset, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteOffset, int N, hkMathIoMode A> struct loadUnpackWithOffsetHC {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkHalf** base)
{
	const hkHalf* ptr0 = (const hkHalf*)hkAddByteOffsetConst(base[I-1], byteOffset); 
	loadUnpackWithOffsetHC<I-1, byteOffset, N, A>::apply(v, base);
	v[I-1].load<N, A>(ptr0);
} };
template <hkUint32 byteOffset, int N, hkMathIoMode A> struct loadUnpackWithOffsetHC<1, byteOffset, N, A> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkHalf** base)
{
	const hkHalf* ptr = (const hkHalf*)hkAddByteOffsetConst(base[0], byteOffset); 
	v[0].load<N, A>(ptr);
} };
}
template <int M>
template <hkUint32 byteOffset, int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkMxVectorf<M>::loadUnpackWithOffset(const hkHalf* base[M])
{
	hkMxVectorf_Implementation::loadUnpackWithOffsetHC<M, byteOffset, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterUintH {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkVector4f* base, const hkUint16* indices)
{
	hkVector4f* HK_RESTRICT ptr = hkAddByteOffset(base, indices[I-1] * byteAddressIncrement);
	scatterUintH<I-1, byteAddressIncrement>::apply(v, base, indices);
	*ptr = v[I-1];
} };
template <hkUint32 byteAddressIncrement> struct scatterUintH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkVector4f* base, const hkUint16* indices)
{
	hkVector4f* HK_RESTRICT ptr = hkAddByteOffset(base, indices[0] * byteAddressIncrement);
	*ptr = v[0];
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectorf<M>::scatter(hkVector4f* base, const hkUint16* indices) const
{
	hkMxVectorf_Implementation::scatterUintH<M, byteAddressIncrement>::apply(m_vec.v, base, indices);
}



namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterIntH {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkVector4f* base, const hkInt32* indices)
{
	hkVector4f* HK_RESTRICT ptr = hkAddByteOffset(base, indices[I-1] * byteAddressIncrement);
	scatterIntH<I-1, byteAddressIncrement>::apply(v, base, indices);
	*ptr = v[I-1];
} };
template <hkUint32 byteAddressIncrement> struct scatterIntH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkVector4f* base, const hkInt32* indices)
{
	hkVector4f* HK_RESTRICT ptr = hkAddByteOffset(base, indices[0] * byteAddressIncrement);
	*ptr = v[0];
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectorf<M>::scatter(hkVector4f* base, const hkInt32* indices) const
{
	hkMxVectorf_Implementation::scatterIntH<M, byteAddressIncrement>::apply(m_vec.v, base, indices);
}



namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterH {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkVector4f* base)
{
	hkVector4f* HK_RESTRICT ptr0 = hkAddByteOffset(base, (I-1) * byteAddressIncrement); 
	scatterH<I-1, byteAddressIncrement>::apply(v, base);
	*ptr0 = v[I-1];
} };
template <hkUint32 byteAddressIncrement> struct scatterH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkVector4f* base)
{
	*base = v[0];
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxVectorf<M>::scatter(hkVector4f* base) const
{
	hkMxVectorf_Implementation::scatterH<M, byteAddressIncrement>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
	template <int I, hkUint32 byteAddressIncrement, hkVector4ComparisonMask::Mask M> struct scatterHC {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkVector4f* base)
{
	hkVector4f* HK_RESTRICT ptr0 = hkAddByteOffset(base, (I-1) * byteAddressIncrement); 
	scatterHC<I-1, byteAddressIncrement, M>::apply(v, base);
	ptr0->setSelect<M>(v[I-1], *ptr0);
} };
template <hkUint32 byteAddressIncrement, hkVector4ComparisonMask::Mask M> struct scatterHC<1, byteAddressIncrement, M> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkVector4f* base)
{
	base->setSelect<M>(v[0], *base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement, int N>
HK_FORCE_INLINE void hkMxVectorf<M>::scatter(hkVector4f* base) const
{
	hkMxVectorf_Implementation::scatterHC<M, byteAddressIncrement, hkVector4ComparisonMask::Mask( hkMxVectorf_Implementation::componentCountToSelectMask<N>::Mask) >::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteOffset> struct scatterWithOffsetH {
HK_FORCE_INLINE static void apply(const hkVector4f* v, void** base)
{
	hkVector4f* HK_RESTRICT ptr0 = (hkVector4f*)hkAddByteOffset(base[I-1], byteOffset); 
	scatterWithOffsetH<I-1, byteOffset>::apply(v, base);
	*ptr0 = v[I-1];
} };
template <hkUint32 byteOffset> struct scatterWithOffsetH<1, byteOffset> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, void** base)
{
	hkVector4f* HK_RESTRICT ptr0 = (hkVector4f*)hkAddByteOffset(base[0], byteOffset); 
	*ptr0 = v[0];
} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxVectorf<M>::scatterWithOffset(void* base[M]) const 
{
	hkMxVectorf_Implementation::scatterWithOffsetH<M, byteOffset>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteOffset, hkVector4ComparisonMask::Mask M> struct scatterWithOffsetHC {
HK_FORCE_INLINE static void apply(const hkVector4f* v, void** base)
{
	hkVector4f* HK_RESTRICT ptr0 = (hkVector4f*)hkAddByteOffset(base[I-1], byteOffset); 
	scatterWithOffsetHC<I-1, byteOffset, M>::apply(v, base);
	ptr0->setSelect<M>(v[I-1], *ptr0);
} };
template <hkUint32 byteOffset, hkVector4ComparisonMask::Mask M> struct scatterWithOffsetHC<1, byteOffset, M> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, void** base)
{
	hkVector4f* HK_RESTRICT ptr0 = (hkVector4f*)hkAddByteOffset(base[0], byteOffset); 
	ptr0->setSelect<M>(v[0], *ptr0);
} };
}
template <int M>
template <hkUint32 byteOffset, int N> 
HK_FORCE_INLINE void hkMxVectorf<M>::scatterWithOffset(void* base[M]) const 
{
	hkMxVectorf_Implementation::scatterWithOffsetHC<M, byteOffset, hkVector4ComparisonMask::Mask(hkMxVectorf_Implementation::componentCountToSelectMask<N>::Mask)>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteOffset, int N, hkMathIoMode A> struct storeWithOffsetHC {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkFloat32** base)
{
	hkFloat32* ptr0 = (hkFloat32*)hkAddByteOffset(base[I-1], byteOffset); 
	storeWithOffsetHC<I-1, byteOffset, N, A>::apply(v, base);
	v[I-1].store<N, A>(ptr0);
} };
template <hkUint32 byteOffset, int N, hkMathIoMode A> struct storeWithOffsetHC<1, byteOffset, N, A> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkFloat32** base)
{
	hkFloat32* ptr0 = (hkFloat32*)hkAddByteOffset(base[0], byteOffset); 
	v[0].store<N, A>(ptr0);
} };
}
template <int M>
template <hkUint32 byteOffset, int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkMxVectorf<M>::storeWithOffset(hkFloat32* base[M]) const 
{
	hkMxVectorf_Implementation::storeWithOffsetHC<M, byteOffset, N, A>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, hkUint32 byteOffset, int N, hkMathIoMode A, hkMathRoundingMode R> struct storePackWithOffsetHC {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf** base)
{
	hkHalf* ptr0 = (hkHalf*)hkAddByteOffset(base[I-1], byteOffset); 
	storePackWithOffsetHC<I-1, byteOffset, N, A, R>::apply(v, base);
	v[I-1].store<N, A, R>(ptr0);
} };
template <hkUint32 byteOffset, int N, hkMathIoMode A, hkMathRoundingMode R> struct storePackWithOffsetHC<1, byteOffset, N, A, R> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkHalf** base)
{
	hkHalf* ptr0 = (hkHalf*)hkAddByteOffset(base[0], byteOffset); 
	v[0].store<N, A, R>(ptr0);
} };
}
template <int M>
template <hkUint32 byteOffset, int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkMxVectorf<M>::storePackWithOffset(hkHalf* base[M]) const 
{
	hkMxVectorf_Implementation::storePackWithOffsetHC<M, byteOffset, N, A, R>::apply(m_vec.v, base);
}


namespace hkMxVectorf_Implementation
{
template <int I, int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct lengthH { HK_FORCE_INLINE static void apply(const hkVector4f* v, hkSimdFloat32* lensOut) { lengthH<I-1,N,A,S>::apply(v, lensOut); lensOut[I-1] = v[I-1].length<N,A,S>(); } };
template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct lengthH<1,N,A,S> { HK_FORCE_INLINE static void apply(const hkVector4f* v, hkSimdFloat32* lensOut) { lensOut[0] = v[0].length<N,A,S>(); } };
}
template <int M> template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void hkMxVectorf<M>::length(hkMxRealf<M>& lensOut) const { hkMxVectorf_Implementation::lengthH<M,N,A,S>::apply(m_vec.v, lensOut.m_real.r); }

template <int M> template <int N> HK_FORCE_INLINE void hkMxVectorf<M>::length(hkMxRealf<M>& lensOut) const { hkMxVectorf_Implementation::lengthH<M,N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_vec.v, lensOut.m_real.r); }

namespace hkMxVectorf_Implementation
{
template <int I, int N> struct lengthSqrH { HK_FORCE_INLINE static void apply(const hkVector4f* v, hkSimdFloat32* lensOut) { lengthSqrH<I-1,N>::apply(v, lensOut); lensOut[I-1] = v[I-1].lengthSquared<N>(); } };
template <int N> struct lengthSqrH<1,N> { HK_FORCE_INLINE static void apply(const hkVector4f* v, hkSimdFloat32* lensOut) { lensOut[0] = v[0].lengthSquared<N>(); } };
}
template <int M> template <int N> HK_FORCE_INLINE void hkMxVectorf<M>::lengthSquared(hkMxRealf<M>& lensOut) const { hkMxVectorf_Implementation::lengthSqrH<M,N>::apply(m_vec.v, lensOut.m_real.r); }

namespace hkMxVectorf_Implementation
{
template <int I, int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct lengthInvH { HK_FORCE_INLINE static void apply(const hkVector4f* v, hkSimdFloat32* lensOut) { lengthInvH<I-1,N,A,S>::apply(v, lensOut); lensOut[I-1] = v[I-1].lengthInverse<N,A,S>(); } };
template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct lengthInvH<1,N,A,S> { HK_FORCE_INLINE static void apply(const hkVector4f* v, hkSimdFloat32* lensOut) { lensOut[0] = v[0].lengthInverse<N,A,S>(); } };
}
template <int M> template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void hkMxVectorf<M>::lengthInverse(hkMxRealf<M>& lensOut) const { hkMxVectorf_Implementation::lengthInvH<M,N,A,S>::apply(m_vec.v, lensOut.m_real.r); }

template <int M> template <int N> HK_FORCE_INLINE void hkMxVectorf<M>::lengthInverse(hkMxRealf<M>& lensOut) const { hkMxVectorf_Implementation::lengthInvH<M,N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_vec.v, lensOut.m_real.r); }



namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void selectH(hkVector4f* v, const hkVector4fComparison* mask, const hkVector4f* tVal, const hkVector4f* fVal) { selectH<I-1>(v, mask, tVal, fVal); v[I-1].setSelect(mask[I-1], tVal[I-1], fVal[I-1]); }
template <> HK_FORCE_INLINE void selectH<1>(hkVector4f* v, const hkVector4fComparison* mask, const hkVector4f* tVal, const hkVector4f* fVal) { v[0].setSelect(mask[0], tVal[0], fVal[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::setSelect(hkMxMaskParameterf mask, hkMxVectorfParameter trueValue, hkMxVectorfParameter falseValue )
{
	hkMxVectorf_Implementation::selectH<M>(m_vec.v, mask.m_comp.c, trueValue.m_vec.v, falseValue.m_vec.v);
}
namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void selectSH(hkVector4f* v, const hkVector4fComparison* mask, hkVector4fParameter tVal, const hkVector4f* fVal) { selectSH<I-1>(v, mask, tVal, fVal); v[I-1].setSelect(mask[I-1], tVal, fVal[I-1]); }
template <> HK_FORCE_INLINE void selectSH<1>(hkVector4f* v, const hkVector4fComparison* mask, hkVector4fParameter tVal, const hkVector4f* fVal) { v[0].setSelect(mask[0], tVal, fVal[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::setSelect(hkMxMaskParameterf mask, hkMxSinglefParameter trueValue, hkMxVectorfParameter falseValue )
{
	hkMxVectorf_Implementation::selectSH<M>(m_vec.v, mask.m_comp.c, trueValue.m_single.s, falseValue.m_vec.v);
}
namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void selectHS(hkVector4f* v, const hkVector4fComparison* mask, const hkVector4f* tVal, hkVector4fParameter fVal) { selectHS<I-1>(v, mask, tVal, fVal); v[I-1].setSelect(mask[I-1], tVal[I-1], fVal); }
template <> HK_FORCE_INLINE void selectHS<1>(hkVector4f* v, const hkVector4fComparison* mask, const hkVector4f* tVal, hkVector4fParameter fVal) { v[0].setSelect(mask[0], tVal[0], fVal); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::setSelect(hkMxMaskParameterf mask, hkMxVectorfParameter trueValue, hkMxSinglefParameter falseValue )
{
	hkMxVectorf_Implementation::selectHS<M>(m_vec.v, mask.m_comp.c, trueValue.m_vec.v, falseValue.m_single.s);
}


namespace hkMxVectorf_Implementation
{
	template <int I, int idx> struct revertH {
	HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* v0)
	{ 
		revertH<I-1,idx+1>::apply(v, v0); 
		v[I-1] = v0[idx]; 
	} };
	template <int idx> struct revertH<1,idx> {
	HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* v0)
	{
		v[0] = v0[idx]; 
	} };
	template <int I> 
	HK_FORCE_INLINE void leftCH(hkVector4f* v, const hkVector4f* v0)
	{ 
		leftCH<I-1>(v, v0); 
		v[I-1] = v0[I]; 
	}
	template <> 
	HK_FORCE_INLINE void leftCH<1>(hkVector4f* v, const hkVector4f* v0)
	{
		v[0] = v0[1]; 
	}
	template <int I> 
	HK_FORCE_INLINE void rightCH(hkVector4f* v, const hkVector4f* v0)
	{ 
		rightCH<I-1>(v, v0); 
		v[I] = v0[I-1]; 
	}
	template <> 
	HK_FORCE_INLINE void rightCH<1>(hkVector4f* v, const hkVector4f* v0)
	{
		v[1] = v0[0]; 
	}
}

template <int M>
template <hkMxVectorPermutation::Permutation P>
HK_FORCE_INLINE void hkMxVectorf<M>::setVectorPermutation(hkMxVectorfParameter m)
{
	HK_COMPILE_TIME_ASSERT2((P==hkMxVectorPermutation::SHIFT_LEFT_CYCLIC)||(P==hkMxVectorPermutation::SHIFT_RIGHT_CYCLIC)||(P==hkMxVectorPermutation::REVERSE),MX_UNKNOWNf_PERMUTATION);

	if (P == hkMxVectorPermutation::SHIFT_LEFT_CYCLIC )
	{
		hkMxVectorf_Implementation::leftCH<M-1>(m_vec.v, m.m_vec.v);
		m_vec.v[M-1] = m.m_vec.v[0];
	}
	else if ( P == hkMxVectorPermutation::SHIFT_RIGHT_CYCLIC )
	{
		m_vec.v[0] = m.m_vec.v[M-1];
		hkMxVectorf_Implementation::rightCH<M-1>(m_vec.v, m.m_vec.v);
	}
	else /*if ( P == hkMxVectorPermutation::REVERSE )*/
	{
		hkMxVectorf_Implementation::revertH<M,0>::apply(m_vec.v, m.m_vec.v);
	}
}


namespace hkMxVectorf_Implementation
{
	template <int I, hkVectorPermutation::Permutation P> struct permuteComponents {
		HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* v0)
		{ 
			permuteComponents<I-1,P>::apply(v, v0); 
			v[I-1].setPermutation<P>( v0[I-1] ); 
		} };
		template <hkVectorPermutation::Permutation P> struct permuteComponents<0,P> {
			HK_FORCE_INLINE static void apply(hkVector4f* v, const hkVector4f* v0){}
			};
}

template <int M>
template <hkVectorPermutation::Permutation P>
HK_FORCE_INLINE void hkMxVectorf<M>::setComponentPermutation(hkMxVectorfParameter m)
{
	hkMxVectorf_Implementation::permuteComponents<M,P>::apply(m_vec.v, m.m_vec.v);
}


namespace hkMxVectorf_Implementation
{
template <int I> HK_FORCE_INLINE void setAllH(hkVector4f* v, hkVector4fParameter v0) { setAllH<I-1>(v, v0); v[I-1].setAll(v0.getComponent<I-1>()); }
template <> HK_FORCE_INLINE void setAllH<1>(hkVector4f* v, hkVector4fParameter v0) { v[0].setAll(v0.getComponent<0>()); }
}
template <int M>
HK_FORCE_INLINE void hkMxVectorf<M>::setAsBroadcast(hkVector4fParameter v)
{
	hkMxVectorf_Implementation::setAllH<M>(m_vec.v, v); // safe, v.getComponent will assert M<=4
}

#undef MXV_NO_OPERANDS
#undef MXV_OPf_MXVECTOR
#undef MXV_OPf_MXVECTOR_MXVECTOR
#undef MXV_OPf_MXQUATERNION_MXVECTOR
#undef MXV_OPf_MXVECTOR_MXVECTOR_MXVECTOR
#undef MXV_OPf_MXVECTOR_MXVECTOR_MXSINGLE
#undef MXV_OPf_MXVECTOR_MXVECTOR_MXREAL
#undef MXV_OPf_MXVECTOR_MXSINGLE_MXREAL
#undef MXV_OPf_MXREAL
#undef MXV_OPf_MXSINGLE
#undef MXV_OPf_MXVECTOR_MXREAL
#undef MXV_OPf_MXREAL_MXVECTOR
#undef MXV_OPf_MXVECTOR_MXSINGLE
#undef MXV_OPf_MXSINGLE_MXSINGLE
#undef MXV_OPf_MXSINGLE_MXVECTOR
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
