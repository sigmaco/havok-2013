/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_VISUALIZE_COLOR
#define HK_VISUALIZE_COLOR


extern const class hkClass hkColorClass;

	/// Colors are represented as unsigned ints [0xAARRGGBB] and there are helper
	/// functions to create them from floats or chars
class hkColor
{
		HK_DECLARE_REFLECTION();
		
	public:

		typedef hkUint32 Argb;
	
			/// Creates a color using the specified char Argbs.
		static Argb HK_CALL rgbFromChars( unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 0xff );
		
			/// Creates a color using the specified floating-point Argbs interpreted as RGB colors in [0,1].
		static Argb HK_CALL rgbFromFloats( const hkReal red, const hkReal green, const hkReal blue, const hkReal alpha = 1.0f );
	
			/// Creates a color using the specified floating-point Argbs interpreted as HSV colors in [0,1]
		static Argb HK_CALL rgbFromHSV( const hkReal h, const hkReal s, const hkReal v, const hkReal alpha = 1.0f );

			/// Creates a random color
		static Argb HK_CALL getRandomColor();

			/// Creates a random color using the given hkPseudoRandomGenerator
		static Argb HK_CALL getRandomColor( class hkPseudoRandomGenerator& rand );

			/// Create a color from the visible spectrum.
		static Argb HK_CALL getSpectrumColor( hkReal Argb );

			/// Get the i'th color from s_colorTable with optional alpha.
		static Argb HK_CALL getPaletteColor( int i, unsigned char alpha=0xff );

			/// Gets the Alpha component of a color.
		inline static char HK_CALL getAlphaAsChar(Argb color) { return char((color >> 24) & 0xFF);	}
		inline static hkReal HK_CALL getAlphaAsFloat(Argb color) { return hkReal((color>>24)&0xff) / hkReal(255.0f); }

			/// Gets the Red component of a color.
		inline static char HK_CALL getRedAsChar(Argb color) { return char((color >> 16) & 0xFF); }
		inline static hkReal HK_CALL getRedAsFloat(Argb color) { return hkReal((color>>16)&0xff) / hkReal(255.0f); }

			/// Gets the Green component of a color.
		inline static char HK_CALL getGreenAsChar(Argb color) { return char((color >> 8) & 0xFF); }
		inline static hkReal HK_CALL getGreenAsFloat(Argb color) { return hkReal((color>>8)&0xff) / hkReal(255.0f); }

			/// Gets the Blue component of a color.
		inline static char HK_CALL getBlueAsChar(Argb color) { return char(color & 0xFF); }
		inline static hkReal HK_CALL getBlueAsFloat(Argb color) { return hkReal(color&0xff) / hkReal(255.0f); }

			/// Combine two colors. Uses the identity (a+b)/2 == (a^b)>>1 + (a&b).
		inline static Argb HK_CALL average(Argb a, Argb b) {return ( ((a^b)&0xfefefefe) >> 1 ) + (a&b); }

			/// Halve the alpha.
		inline static Argb HK_CALL semiTransparent(Argb color, int n=1)
		{
			return ((color>>n) & 0xFF000000) | (color&0x00ffffff);
		}

			/// Make the color darker.
		inline static Argb HK_CALL darken(Argb col, int n=1)
		{
			Argb masklo = (((1<<n) - 1) * 0x00010101); // Build a mask for the lower n bits of each of the bytes
			Argb maskLoAndAlpha = masklo | 0xff000000;
			Argb colShifted = ( col & ~maskLoAndAlpha ) >> n; // Clear alpha, Mask out the lower bits of each component and shift
 			return (col & 0xff000000) | colShifted; // Restore alpha
		}

			/// Make the color lighter.
		inline static int HK_CALL lighten(Argb col, int n=1)
		{
			Argb lobits = (( (1<<   n ) - 1) * 0x00010101); // populate new low bits with 1s
			Argb maskhi = (( (1<<(8-n)) - 1) * 0x00010101); // mask of bits shifted out
			return (col & ~maskhi) // preserve alpha and high bits of each component. consider lighten(col=0xff808080,n=1)
				| ((col&maskhi) << n) // shift bits in each component upward, mask ensures components don't interfere
				| lobits; // fill new low bits with 1s
		}

		HK_FORCE_INLINE static Argb fromArgb( unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue )
		{
			return ((static_cast<Argb>(alpha)<<24) | (static_cast<Argb>(red)<<16) | (static_cast<Argb>(green)<<8) | static_cast<Argb>(blue));
		}
		
		HK_FORCE_INLINE static Argb replaceAlpha( unsigned char alpha, Argb rgb )
		{
			return ((static_cast<Argb>(alpha)<<24) | (rgb & 0x00ffffff));
		}

	public:

		// Standard Colors
		

		static const Argb MAROON;
		static const Argb DARKRED;
		static const Argb RED;
		static const Argb LIGHTPINK;
		static const Argb CRIMSON;
		static const Argb PALEVIOLETRED;
		static const Argb HOTPINK;
		static const Argb DEEPPINK;
		static const Argb MEDIUMVIOLETRED;
		static const Argb PURPLE;
		static const Argb DARKMAGENTA;
		static const Argb ORCHID;
		static const Argb THISTLE;
		static const Argb PLUM;
		static const Argb VIOLET;
		static const Argb FUCHSIA;
		static const Argb MAGENTA;
		static const Argb MEDIUMORCHID;
		static const Argb DARKVIOLET;
		static const Argb DARKORCHID;
		static const Argb BLUEVIOLET;
		static const Argb INDIGO;
		static const Argb MEDIUMPURPLE;
		static const Argb SLATEBLUE;
		static const Argb MEDIUMSLATEBLUE;
		static const Argb DARKBLUE;
		static const Argb MEDIUMBLUE;
		static const Argb BLUE;
		static const Argb NAVY;
		static const Argb MIDNIGHTBLUE;
		static const Argb DARKSLATEBLUE;
		static const Argb ROYALBLUE;
		static const Argb CORNFLOWERBLUE;
		static const Argb LIGHTSTEELBLUE;
		static const Argb ALICEBLUE;
		static const Argb GHOSTWHITE;
		static const Argb LAVENDER;
		static const Argb DODGERBLUE;
		static const Argb STEELBLUE;
		static const Argb DEEPSKYBLUE;
		static const Argb SLATEGRAY;
		static const Argb LIGHTSLATEGRAY;
		static const Argb LIGHTSKYBLUE;
		static const Argb SKYBLUE;
		static const Argb LIGHTBLUE;
		static const Argb TEAL;
		static const Argb DARKCYAN;
		static const Argb DARKTURQUOISE;
		static const Argb CYAN;
		static const Argb MEDIUMTURQUOISE;
		static const Argb CADETBLUE;
		static const Argb PALETURQUOISE;
		static const Argb LIGHTCYAN;
		static const Argb AZURE;
		static const Argb LIGHTSEAGREEN;
		static const Argb TURQUOISE;
		static const Argb POWDERBLUE;
		static const Argb DARKSLATEGRAY;
		static const Argb AQUAMARINE;
		static const Argb MEDIUMSPRINGGREEN;
		static const Argb MEDIUMAQUAMARINE;
		static const Argb SPRINGGREEN;
		static const Argb MEDIUMSEAGREEN;
		static const Argb SEAGREEN;
		static const Argb LIMEGREEN;
		static const Argb DARKGREEN;
		static const Argb GREEN;
		static const Argb LIME;
		static const Argb FORESTGREEN;
		static const Argb DARKSEAGREEN;
		static const Argb LIGHTGREEN;
		static const Argb PALEGREEN;
		static const Argb MINTCREAM;
		static const Argb HONEYDEW;
		static const Argb CHARTREUSE;
		static const Argb LAWNGREEN;
		static const Argb OLIVEDRAB;
		static const Argb DARKOLIVEGREEN;
		static const Argb YELLOWGREEN;
		static const Argb GREENYELLOW;
		static const Argb BEIGE;
		static const Argb LINEN;
		static const Argb LIGHTGOLDENRODYELLOW;
		static const Argb OLIVE;
		static const Argb YELLOW;
		static const Argb LIGHTYELLOW;
		static const Argb IVORY;
		static const Argb DARKKHAKI;
		static const Argb KHAKI;
		static const Argb PALEGOLDENROD;
		static const Argb WHEAT;
		static const Argb GOLD;
		static const Argb LEMONCHIFFON;
		static const Argb PAPAYAWHIP;
		static const Argb DARKGOLDENROD;
		static const Argb GOLDENROD;
		static const Argb ANTIQUEWHITE;
		static const Argb CORNSILK;
		static const Argb OLDLACE;
		static const Argb MOCCASIN;
		static const Argb NAVAJOWHITE;
		static const Argb ORANGE;
		static const Argb BISQUE;
		static const Argb TAN;
		static const Argb DARKORANGE;
		static const Argb BURLYWOOD;
		static const Argb SADDLEBROWN;
		static const Argb SANDYBROWN;
		static const Argb BLANCHEDALMOND;
		static const Argb LAVENDERBLUSH;
		static const Argb SEASHELL;
		static const Argb FLORALWHITE;
		static const Argb SNOW;
		static const Argb PERU;
		static const Argb PEACHPUFF;
		static const Argb CHOCOLATE;
		static const Argb SIENNA;
		static const Argb LIGHTSALMON;
		static const Argb CORAL;
		static const Argb DARKSALMON;
		static const Argb MISTYROSE;
		static const Argb ORANGERED;
		static const Argb SALMON;
		static const Argb TOMATO;
		static const Argb ROSYBROWN;
		static const Argb PINK;
		static const Argb INDIANRED;
		static const Argb LIGHTCORAL;
		static const Argb BROWN;
		static const Argb FIREBRICK;
		static const Argb BLACK;
		static const Argb DIMGRAY;
		static const Argb GRAY;
		static const Argb DARKGRAY;
		static const Argb SILVER;
		static const Argb LIGHTGREY;
		static const Argb GAINSBORO;
		static const Argb WHITESMOKE;
		static const Argb WHITE;
		static const Argb GREY;
		static const Argb GREY25;
		static const Argb GREY50;
		static const Argb GREY75;
		
		// Havok product colors
		static const Argb PHYSICS;
		static const Argb DESTRUCTION;
		static const Argb ANIMATION;
		static const Argb BEHAVIOR;
		static const Argb CLOTH;
		static const Argb AI;
		static const Argb SCRIPT;
		
			// A simple color table - arrange in batches of 8 colors light to dark
		static Argb s_colorTable[32];
};

#endif // HK_VISUALIZE_COLOR

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
