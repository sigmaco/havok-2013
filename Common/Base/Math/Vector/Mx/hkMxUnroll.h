/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE
#ifndef HK_MXUNROLL_H
#define HK_MXUNROLL_H

namespace hkCompileError
{

	template <bool b> struct MX_UNROLL_NOT_IMPLEMENTED_FOR_THIS_VECTOR_LENGTH;
	template <> struct MX_UNROLL_NOT_IMPLEMENTED_FOR_THIS_VECTOR_LENGTH<true>{ };
}
#define MX_UNROLL_NOT_IMPLEMENTED               HK_COMPILE_TIME_ASSERT2(M==0, MX_UNROLL_NOT_IMPLEMENTED_FOR_THIS_VECTOR_LENGTH)

// helper struct to force code iteration
// use this to create variable repeating code pieces according to
// compiletime constants
// the action to execute in each step needs to expose a member
// 	void step(const int i) {}

template<int START, int END, int STEP = 1>
struct hkMxIterator
{
	template<typename ACTION>
	HK_FORCE_INLINE static void step(ACTION& action) 
	{
		for (int i=START; i!=END; i+=STEP) action.template step(i);
	}

	template<typename ACTION>
	HK_FORCE_INLINE static void predicatedStep(ACTION& action, const int LIMIT) 
	{
		for (int i=START; (i!=END) && (i<LIMIT); i+=STEP) action.template step(i);
	}
};

template<int STEP>
struct hkMxIterator<0, 1, STEP>
{
	template<typename ACTION>
	HK_FORCE_INLINE static void step(ACTION& action) 
	{
		action.template step(0);
	}
};


// helper struct to force code unroll
// use this to create variable repeating code pieces according to
// compiletime constants
// the action to execute in each step needs to expose a template member


template<int START, int END, int STEP = 1>
struct hkMxUnroller 
{
	template<typename ACTION>
	HK_FORCE_INLINE static void step(ACTION& action) 
	{
		action.step<START>();
		hkMxUnroller<START+STEP, END, STEP>::step(action);
	}

	template<typename ACTION, int LIMIT>
	HK_FORCE_INLINE static void predicatedStep(ACTION& action) 
	{
		if (START < LIMIT)
		{
			action.step<START>();
			hkMxUnroller<START+STEP, END, STEP>::template predicatedStep<ACTION, LIMIT>(action);
		}
	}
};

template<int END, int STEP>
struct hkMxUnroller<END, END, STEP> 
{
	template<typename ACTION>
	HK_FORCE_INLINE static void step(ACTION& action) { }

	template<typename ACTION, int LIMIT>
	HK_FORCE_INLINE static void predicatedStep(ACTION& action) { }
};



// helper macro to unroll code
// use this to create repeating code with literal available repetition number
// note: you should always prefer the mx classes member functions as they are optimized
//       use this macro only in rare cases as this can generate a lot of code
#	define hkMxUNROLL(x,c) HK_PREPROCESSOR_JOIN_TOKEN(hkMxUNROLL_,x)(c)

#define hkMxUNROLL_0(c)
#define hkMxUNROLL_1(c) hkMxUNROLL_0(c) { const int hkMxI = 0; c; }
#define hkMxUNROLL_2(c) hkMxUNROLL_1(c) { const int hkMxI = 1; c; }
#define hkMxUNROLL_3(c) hkMxUNROLL_2(c) { const int hkMxI = 2; c; }
#define hkMxUNROLL_4(c) hkMxUNROLL_3(c) { const int hkMxI = 3; c; }
#define hkMxUNROLL_5(c) hkMxUNROLL_4(c) { const int hkMxI = 4; c; }
#define hkMxUNROLL_6(c) hkMxUNROLL_5(c) { const int hkMxI = 5; c; }
#define hkMxUNROLL_7(c) hkMxUNROLL_6(c) { const int hkMxI = 6; c; }
#define hkMxUNROLL_8(c) hkMxUNROLL_7(c) { const int hkMxI = 7; c; }
#define hkMxUNROLL_9(c) hkMxUNROLL_8(c) { const int hkMxI = 8; c; }
#define hkMxUNROLL_10(c) hkMxUNROLL_9(c) { const int hkMxI = 9; c; }
#define hkMxUNROLL_11(c) hkMxUNROLL_10(c) { const int hkMxI = 10; c; }
#define hkMxUNROLL_12(c) hkMxUNROLL_11(c) { const int hkMxI = 11; c; }
#define hkMxUNROLL_13(c) hkMxUNROLL_12(c) { const int hkMxI = 12; c; }
#define hkMxUNROLL_14(c) hkMxUNROLL_13(c) { const int hkMxI = 13; c; }
#define hkMxUNROLL_15(c) hkMxUNROLL_14(c) { const int hkMxI = 14; c; }
#define hkMxUNROLL_16(c) hkMxUNROLL_15(c) { const int hkMxI = 15; c; }
#define hkMxUNROLL_17(c) hkMxUNROLL_16(c) { const int hkMxI = 16; c; }
#define hkMxUNROLL_18(c) hkMxUNROLL_17(c) { const int hkMxI = 17; c; }
#define hkMxUNROLL_19(c) hkMxUNROLL_18(c) { const int hkMxI = 18; c; }
#define hkMxUNROLL_20(c) hkMxUNROLL_19(c) { const int hkMxI = 19; c; }
#define hkMxUNROLL_21(c) hkMxUNROLL_20(c) { const int hkMxI = 20; c; }
#define hkMxUNROLL_22(c) hkMxUNROLL_21(c) { const int hkMxI = 21; c; }
#define hkMxUNROLL_23(c) hkMxUNROLL_22(c) { const int hkMxI = 22; c; }
#define hkMxUNROLL_24(c) hkMxUNROLL_23(c) { const int hkMxI = 23; c; }
#define hkMxUNROLL_25(c) hkMxUNROLL_24(c) { const int hkMxI = 24; c; }
#define hkMxUNROLL_26(c) hkMxUNROLL_25(c) { const int hkMxI = 25; c; }
#define hkMxUNROLL_27(c) hkMxUNROLL_26(c) { const int hkMxI = 26; c; }
#define hkMxUNROLL_28(c) hkMxUNROLL_27(c) { const int hkMxI = 27; c; }
#define hkMxUNROLL_29(c) hkMxUNROLL_28(c) { const int hkMxI = 28; c; }
#define hkMxUNROLL_30(c) hkMxUNROLL_29(c) { const int hkMxI = 29; c; }
#define hkMxUNROLL_31(c) hkMxUNROLL_30(c) { const int hkMxI = 30; c; }
#define hkMxUNROLL_32(c) hkMxUNROLL_31(c) { const int hkMxI = 31; c; }
#define hkMxUNROLL_33(c) { MX_UNROLL_NOT_IMPLEMENTED; }

#endif // HK_MXUNROLL_H

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
