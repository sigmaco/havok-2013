/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HAVOK_FILTER_UTILS__H
#define HAVOK_FILTER_UTILS__H

#include <ContentTools/Common/Filters/Common/Filter/hctFilterDescriptor.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Base/Container/String/Deprecated/hkStringOld.h>

class hkPackfileData;

	/// A collection of useful utility methods for the filters and exporters
class hctFilterUtils
{
	public:
			
			/// Get the position of the cinfo data (i.e., not the local fixups) in the options data block.
		static void* interpretOptions( void* data );

			/// Write the options data to memory. A pointer to the data is returned.
		static void* writeOptionsXml( const hkClass& klass, const void* data, hkArray<char>& buffer, const char* filterName );
		
			/// Read the options data from memory.
		static hkResult readOptionsXml ( const void* optionData, const int optionDataSize, hkArray<char>& buffer, const hkClass klass );

			/// Create a complete copy of an entire filter set,
			/// so that processing does not affect the original data.
		static void* deepCopyObject ( const void* obj, const hkClass* klass, hkPackfileData*& sceneCopyData );
		
			/// Create an array using the items listed in the delimited string.
		static void createArrayFromDelimitedString( hkArray<hkStringOld>& buf, const char* delimitedString, const char delimiter );

			/// Create an array using the items listed in the delimited string - using a full hkStringOld delimiter
		static void createArrayFromDelimitedString( hkArray<hkStringOld>& buf, const char* delimitedString, const hkStringOld& delimiter );

			/// Create a single string from the given array of strings, using "delimiter" to split the strings.
		static void createDelimitedStringFromArray( const hkArray<hkStringOld>& array, const char* delimiter, hkStringOld& delimitedStringOut);

			/// Create an array of array of strings from a delimited string using an inner and outer delimiter
		static void createArrayOfArrayOfStringsFromDelimitedString( hkArray< hkArray< hkStringOld > >& out, const char* delimitedString, char inner, char outer );

			/// Create a single string from a given array of array of strings using an inner and outer delimiter
		static void createDelimitedStringFromArrayOfArrayOfStrings( const hkArray< hkArray< hkStringOld > >& in, hkStringOld& out, char inner, char outer );

			/// Returns the path to the specified asset file. It does so by looking for an hkxEnvironment in the asset and otherwise
			/// by looking at the asset name in the hkxScene object.
		static void getAssetFolder( const hkRootLevelContainer& rootLevelContainer, hkStringOld& assetFolderOut );

			/// Given a filename, it detects whether it is relative or not to the asset path, and in that case
			/// it prepends it.
		static void getFullPath ( const hkRootLevelContainer& rootLevelContainer, const char* userPath, hkStringOld& fullPathOut);

			/// Get the path to the specified file relative to the specified asset path.
		static void getReducedFilename( const char* fname, const hkStringOld& assetPath, hkStringOld& reducedName );

			/// Looks for an hkxEnvironment inside the given contents, and queries for the given variable. If not present,
			/// it will try to use data in hkxScene. Returns HK_NULL if no environment was found or the variable is undefined.
		static const char* getEnvironmentVariable (const hkRootLevelContainer& contents, const char* variable);

		/// Looks for a Windows environment variable with the given name
		static const char* getOSEnvironmentVariable (const char* variable);

			/// Given an hkxEnvironment and an input string, it returns (through outputString) the string with all substrings
			/// of the form \$(name) replaced by its corresponding value in the environment. Returns true if all substitutions
			/// succeeded, false otherwise.
		static bool replaceVariables (const class hkxEnvironment& environment, const char* inputString, hkStringOld& outputString, hkBool useOSEnvironment = false);

			/// Converts a category code to its string representation
		static const char* filterCategoryToString( hctFilterDescriptor::FilterCategory c );


			/// Move non-eportable classes to the end of the root-level container, and return their count
		static int moveNonExportablesToEnd( class hkRootLevelContainer& data );

			/// True if this class is expected to be exported, false if it is not (typically internal data for the filter stack only)
		static bool isExportable( const hkRootLevelContainer::NamedVariant& a );

			/// Utility function to sort named variants based on their exportability
		static bool compareExportableLess( const hkRootLevelContainer::NamedVariant& a, const hkRootLevelContainer::NamedVariant& b );

			///	Attempts to resolve the absolute path to the given script, based on the path of the current asset
		static hkResult HK_CALL resolvePath(const char* fileName, const char* assetPath, hkStringBuf& filePathOut);

			// Packfile/Tagfile extensions list for open/save file dialogs
		static const char s_DialogFileExtensions[];
};

#endif // HAVOK_FILTER_UTILS__H

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
