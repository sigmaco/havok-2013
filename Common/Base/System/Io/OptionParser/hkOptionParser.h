/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HKOPTIONPARSER_H
#define HKBASE_HKOPTIONPARSER_H

class hkOptionParser
{
public:

	HK_DECLARE_PLACEMENT_ALLOCATOR();

	hkOptionParser(const char* title, const char* desc);

	enum OptionType
	{
		OPTION_BOOL,
		OPTION_COUNTER,
		OPTION_INT,
		OPTION_STRING
	};

	enum ArgumentsType
	{
		ARGUMENTS_ONE,
		ARGUMENTS_ONE_OR_MORE,
		ARGUMENTS_ZERO_OR_MORE
	};

	enum ParseResult
	{
		PARSE_SUCCESS,
		PARSE_FAILURE,
		PARSE_HELP		/// help was sought (using the help option)
	};

	union OptionValue
	{
		int i;
		unsigned int u;
		const char* s;
		bool b;
	};

	struct Option
	{
		
		Option() {}

		/// Create a string type option
		Option(const char* shortFlag, const char* longFlag, const char* help, const char** value, const char* defaultValue = HK_NULL);

		/// Create a boolean type option
		Option(const char* shortFlag, const char* longFlag, const char* help, bool* value, bool defaultValue = false);

		/// Create a integer type option
		Option(const char* shortFlag, const char* longFlag, const char* help, int* value, int defaultValue = 0);

		/// Create a counter (unsigned integer) type option
		Option(const char* shortFlag, const char* longFlag, const char* help, unsigned int* value, unsigned int defaultValue = 0u);

		const char* m_shortFlag;
		const char* m_longFlag;
		const char* m_help;
		OptionType m_type;
		OptionValue* m_value;
		OptionValue m_default;
	};

	/// Adds an option to the parser
	bool setOptions(Option* options, int count);
	
	/// Sets the positional arguments
	void setArguments(const char* name, const char* help, ArgumentsType argumentsType, const char** arguments, int count);

	/// Parse the argument vector and store the result in the variables specified in addOption and setArguments
	ParseResult parse(int argc, const char** argv);

	/// Print out the usage/help information for this parser
	void usage(const char* extra = HK_NULL);

private:

	/// Unsorted storage for options
	Option* m_options;
	int m_optionCount;
	const char** m_arguments;
	int m_argumentCount;

	/// Program details
	const char* m_title;
	const char* m_desc;

	/// Arguments details
	const char* m_argumentsName;
	const char* m_argumentsHelp;
	ArgumentsType m_argumentsType;
};

#endif // HKBASE_HKOPTIONPARSER_H

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
