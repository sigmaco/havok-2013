/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Sets the material strength

inline void hkpBreakableMaterial::setMaterialStrength(hkReal newStrength)
{ 
	m_strength = newStrength;
}

//
//	Returns the encoded material strength. For internal use only!

inline void hkpBreakableMaterial::getEncodedMaterialStrength(hkUFloat8& strengthOut) const
{
	strengthOut = hkFloat32(m_strength);
}

//
//	Sets the material extra data

inline void hkpBreakableMaterial::setExtraData(hkUint8 extraData)
{
	m_typeAndFlags	&= ~MATERIAL_EXTRA_DATA_MASK;
	m_typeAndFlags	|= (extraData << MATERIAL_EXTRA_DATA_SHIFT) & MATERIAL_EXTRA_DATA_MASK;
}

//
//	Returns the material extra data

inline hkUint8 hkpBreakableMaterial::getExtraData() const
{
	return (hkUint8)((m_typeAndFlags & MATERIAL_EXTRA_DATA_MASK) >> MATERIAL_EXTRA_DATA_SHIFT);
}


//
//	Ensures the material is capable of storing custom properties

inline void hkpBreakableMaterial::ensurePropertiesExist()
{
	if ( !m_properties )
	{
		m_properties = new Properties();
	}
}

//
//	Removes the custom properties

inline void hkpBreakableMaterial::removeProperties()
{
	if ( m_properties )
	{
		delete m_properties;
		m_properties = HK_NULL;
	}
}

//
//	Gets the material properties. Read / write.

inline hkpBreakableMaterial::Properties* hkpBreakableMaterial::getProperties()
{
	return m_properties;
}

//
//	Gets the material properties. Read-only.

inline const hkpBreakableMaterial::Properties* hkpBreakableMaterial::getProperties() const
{
	return m_properties;
}

//
//	Shortcut for retrieving a given material property

inline hkReferencedObject* hkpBreakableMaterial::getProperty(PropertyKey propertyKey)
{
	Properties* props = getProperties();
	HK_ASSERT(0x6978cec8, props);
	return props->accessProperty(propertyKey);
}

//
//	Shortcut for retrieving a given material property

inline const hkReferencedObject* hkpBreakableMaterial::getProperty(PropertyKey propertyKey) const
{
	const Properties* props = getProperties();
	HK_ASSERT(0x6978cec8, props);
	return props->accessProperty(propertyKey);
}

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
