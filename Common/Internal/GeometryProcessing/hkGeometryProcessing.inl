/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
template <typename VALUE,typename ALLOCATOR>
HKGP_FORCE_INLINE void			hkGeometryProcessing::HashTable<VALUE,ALLOCATOR>::Iterator::next()
{
	++m_item;
	while(m_bucket<m_table->m_buckets.getSize() && (m_bucket==-1 || m_table->m_buckets[m_bucket].getSize()<=m_item))
	{
		++m_bucket;
		m_item=0;
	}
}

//
template <typename VALUE,typename ALLOCATOR>
HKGP_FORCE_INLINE	void			hkGeometryProcessing::HashTable<VALUE,ALLOCATOR>::setBucketsCount(int size)
{
	clear();
	m_buckets.setSize(size);
	for(int i=0;i<size;++i)
	{
		m_buckets[i].clear();
	}
}
//
template <typename VALUE,typename ALLOCATOR>
HKGP_FORCE_INLINE	const VALUE*	hkGeometryProcessing::HashTable<VALUE,ALLOCATOR>::find(int hash,const VALUE& value) const
{
	const hkArray<VALUE,ALLOCATOR>&	values=lookupBucket(hash);
	const int						index=values.indexOf(value);
	if(index==-1)
		return(0);
	else
		return(&values[index]);
}
//
template <typename VALUE,typename ALLOCATOR>
HKGP_FORCE_INLINE	VALUE*			hkGeometryProcessing::HashTable<VALUE,ALLOCATOR>::find(int hash,const VALUE& value)
{
	hkArray<VALUE,ALLOCATOR>&	values=lookupBucket(hash);
	const int					index=values.indexOf(value);
	if(index==-1)
		return(0);
	else
		return(&values[index]);
}
//
template <typename VALUE,typename ALLOCATOR>
HKGP_FORCE_INLINE	VALUE*			hkGeometryProcessing::HashTable<VALUE,ALLOCATOR>::insert(int hash,const VALUE& value)
{
	++m_numItems;
	hkArray<VALUE,ALLOCATOR>&	values=lookupBucket(hash);
	values.expandOne()=value;
	return(&values[values.getSize()-1]);
}
//
template <typename VALUE,typename ALLOCATOR>
HKGP_FORCE_INLINE void			hkGeometryProcessing::HashTable<VALUE,ALLOCATOR>::remove(int hash,const VALUE& value)
{
	--m_numItems;
	hkArray<VALUE,ALLOCATOR>&	values=lookupBucket(hash);
	const int					index=values.indexOf(value);
	if(index>=0) values.removeAt(values.indexOf(value));
}

//
template <typename VALUE,typename ALLOCATOR>
inline void						hkGeometryProcessing::HashTable<VALUE,ALLOCATOR>::append(const HashTable& other)
{
	if(other.m_buckets.getSize()!=m_buckets.getSize())
	{	
		/* Rehash	*/ 
		for(int i=0;i<other.m_buckets.getSize();++i)
		{
			for(int j=0;j<other.m_buckets[i].getSize();++j)
			{
				insert(other.m_buckets[i][j]);
			}
		}
	}	
	else
	{
		/* Append	*/ 
		for(int i=0;i<m_buckets.getSize();++i)
		{
			m_buckets[i].append( other.m_buckets[i].begin(), other.m_buckets[i].getSize() );
		}
	}
}

//
template <typename T,const int N,typename ALLOCATOR>
inline							hkGeometryProcessing::PoolAllocator<T,N,ALLOCATOR>::~PoolAllocator()
{
	clear();
}

//
template <typename T,const int N,typename ALLOCATOR>
inline typename hkGeometryProcessing::PoolAllocator<T,N,ALLOCATOR>::Item*	hkGeometryProcessing::PoolAllocator<T,N,ALLOCATOR>::allocateItem()
{
	Pool*	pool	=	(m_firstPool && m_firstPool->m_free)?m_firstPool:allocateNewPool();
	if (pool)
	{
		Item*	item	=	pool->m_free;
		pool->m_free	=	*(Item**)item;
		item->m_pool	=	pool;
		++pool->m_used;
		return(item);
	}
	else
	{
		return HK_NULL;
	}
}

//
template <typename T,const int N,typename ALLOCATOR>
inline typename hkGeometryProcessing::PoolAllocator<T,N,ALLOCATOR>::Pool*	hkGeometryProcessing::PoolAllocator<T,N,ALLOCATOR>::allocateNewPool()
{
	ALLOCATOR			allocatorType;
	hkMemoryAllocator&	allocator(allocatorType.get(0));
	Item*				prev=HK_NULL;
	Pool*				pool=new(allocator.blockAlloc(sizeof(Pool))) Pool;
	
	if (pool)
	{
		for(int i=N-1;i>=0;--i)
		{
			Item**	current=(Item**)&pool->m_items[i];
			*current	=	prev;
			prev		=	(Item*)current;
		}
		pool->m_used		=	0;
		pool->m_free		=	prev;
		pool->m_links[0]	=	HK_NULL;
		pool->m_links[1]	=	m_firstPool;	
		m_firstPool			=	pool;
		if(pool->m_links[1])
		{
			pool->m_links[1]->m_links[0]=pool;
		}
	}
	return(pool);
}

//
template <typename T,const int N,typename ALLOCATOR>
inline void						hkGeometryProcessing::PoolAllocator<T,N,ALLOCATOR>::releasePool(Pool* pool)
{
	ALLOCATOR			allocatorType;
	hkMemoryAllocator&	allocator(allocatorType.get(0));
	if(pool->m_links[0]) pool->m_links[0]->m_links[1]=pool->m_links[1]; else m_firstPool=pool->m_links[1];
	if(pool->m_links[1]) pool->m_links[1]->m_links[0]=pool->m_links[0];
	pool->~Pool();
	allocator.blockFree(pool,sizeof(Pool));
}

//
template <typename T,const int N,typename ALLOCATOR>
inline void						hkGeometryProcessing::PoolAllocator<T,N,ALLOCATOR>::release(T* object)
{
	if(object)
	{
		/* Call dtor				*/ 
		object->~T();
		/* Locate and update pool	*/ 
		Item*	item((Item*)object);
		Pool*	pool((Pool*)item->m_pool);
		HK_ASSERT2(0x5E8E620D, (item>=pool->m_items) && (item<=&pool->m_items[N-1]), "Invalid pool pointer");
		if(0==--pool->m_used) releasePool(pool);
	}
}

//
template <typename T,const int N,typename ALLOCATOR>
inline void					hkGeometryProcessing::PoolAllocator<T,N,ALLOCATOR>::clear()
{
	while(m_firstPool) releasePool(m_firstPool);
}

//
template <typename T>
HKGP_FORCE_INLINE void		hkGeometryProcessing::Span<T>::setFromVertices(const hkVector4& direction, const hkVector4* vertices,int numVertices)
{
	T bounds = (T)direction.dot<3>(vertices[0]);
	m_bounds[0] = bounds;
	m_bounds[1] = bounds;
	for(int i=1;i<3;++i)
	{
		const T	d = (T)direction.dot<3>(vertices[i]);
		if(d<m_bounds[0])
			m_bounds[0]=d;
		else if(d>m_bounds[1])
			m_bounds[1]=d;
	}
}

//
template <typename T>
HKGP_FORCE_INLINE hkBool32	hkGeometryProcessing::Span<T>::intersect(const Span& a,const Span& b)
{
	if(a.m_bounds[0] > b.m_bounds[1]) return false;
	if(a.m_bounds[1] < b.m_bounds[0]) return false;
	return true;
}

//
HKGP_FORCE_INLINE void HK_CALL hkGeometryProcessing::crossOffset(hkVector4Parameter o, hkVector4Parameter a, hkVector4Parameter b, hkVector4& ret)
{
	hkVector4	oa;
	oa.setSub(a,o);
	hkVector4	ob;
	ob.setSub(b,o);
	ret.setCross(oa,ob);
}

//
HKGP_FORCE_INLINE hkVector4	hkGeometryProcessing::crossEdges(const hkVector4& a0, const hkVector4& a1, const hkVector4& b0, const hkVector4& b1)
{
	hkVector4	a; a.setSub(a1,a0);
	hkVector4	b; b.setSub(b1,b0);
	hkVector4	c; c.setCross(a,b);
	return c;
}

//
HKGP_FORCE_INLINE hkBool32 hkGeometryProcessing::checkTrianglesIntersection(const hkVector4* triangleA,const hkVector4* triangleB)
{
	const hkVector4 (&tA)[3] = *reinterpret_cast<const hkVector4 (*)[3]>(triangleA);
	const hkVector4 (&tB)[3] = *reinterpret_cast<const hkVector4 (*)[3]>(triangleB);
	return hkcdIntersectTriangleTriangle(tA, tB);
}

//
HKGP_FORCE_INLINE bool		hkGeometryProcessing::comparePlanes(const hkVector4& a,const hkVector4& b,hkReal maxDistance,hkReal minCosAngle)
{
	hkSimdReal absDiff; absDiff.setAbs(a.getW()-b.getW());
	if(absDiff.isLessEqual(hkSimdReal::fromFloat(maxDistance)))
	{
		if(a.dot<3>(b).isGreaterEqual(hkSimdReal::fromFloat(minCosAngle)))
		{
			return(true);
		}
	}
	return(false);
}

//
HKGP_FORCE_INLINE hkSimdReal		hkGeometryProcessing::decomposeVector(const hkVector4& vector,const hkVector4& axis,hkVector4& para,hkVector4& perp)
{
	const hkSimdReal	dot=vector.dot<3>(axis);
	para.setMul(dot,axis);
	perp.setAddMul(vector,axis,-dot);
	return dot;
}

//
HKGP_FORCE_INLINE hkVector4	hkGeometryProcessing::projectOnPlane(const hkVector4& vector,const hkVector4& axis)
{
	hkVector4	pa,pe;
	decomposeVector(vector,axis,pa,pe);
	return(pe);
}

//
HKGP_FORCE_INLINE hkVector4	hkGeometryProcessing::projectOnAxis(const hkVector4& vector,const hkVector4& axis)
{
	hkVector4	pa,pe;
	decomposeVector(vector,axis,pa,pe);
	return(pa);
}

//
HKGP_FORCE_INLINE hkSimdReal		hkGeometryProcessing::triangleArea2Squared(hkVector4Parameter a, hkVector4Parameter b)
{
	hkVector4	c;
	c.setCross(a,b);
	return c.lengthSquared<3>();
}

//
HKGP_FORCE_INLINE hkSimdReal		hkGeometryProcessing::triangleArea2(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c)
{
	hkVector4 crossOff;

#if !defined(HK_PLATFORM_CTR) && !defined(HK_ARCH_ARM) // compiler issues
	crossOffset(a,b,c, crossOff);
#else
	hkVector4	ab;
	ab.setSub(b,a);
	hkVector4	ac;
	ac.setSub(c,a);
	crossOff.setCross(ab,ac);
#endif

	return crossOff.length<3>();
}

//
HKGP_FORCE_INLINE hkSimdReal		hkGeometryProcessing::tetrahedronVolume6(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4Parameter d)
{
	hkMatrix3	m;
	m.getColumn<0>().setSub(b,a);
	m.getColumn<1>().setSub(c,a);
	m.getColumn<2>().setSub(d,a);
	return m.getDeterminant();
}

//
HKGP_FORCE_INLINE hkVector4	hkGeometryProcessing::transformPlaneToWorld(const hkTransform& transform,const hkVector4& plane)
{
	hkVector4	worldPlane;
	worldPlane._setRotatedDir(transform.getRotation(),plane);
	worldPlane.setW( plane.getComponent<3>() - worldPlane.dot<3>(transform.getTranslation()) );
	return worldPlane;
}

//
HKGP_FORCE_INLINE hkVector4	hkGeometryProcessing::transformPlaneToLocal(const hkTransform& transform,const hkVector4& plane)
{
	hkVector4	localPlane;
	localPlane._setRotatedInverseDir(transform.getRotation(),plane);
	localPlane.setW( plane.getComponent<3>() + plane.dot<3>(transform.getTranslation()) );
	return localPlane;
}

//
HKGP_FORCE_INLINE hkBool32	hkGeometryProcessing::circumCenter(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4& centerOut)
{
	hkSimdReal	eps; eps.setFromFloat(1.e-5f);
	hkVector4	ba; ba.setSub(b,a);
	hkVector4	ca; ca.setSub(c,a);
	hkVector4	bc; bc.setCross(ba,ca);
	hkSimdReal	det = bc.lengthSquared<3>() * hkSimdReal_2;
	if((det * det) > eps)
	{
		hkVector4	nums;
		nums.setMul(ba.lengthSquared<3>(), ca);
		nums.subMul(ca.lengthSquared<3>(), ba);
		nums.setCross(nums, bc);

		hkSimdReal	invDet; invDet.setReciprocal(det);
		centerOut.setAddMul(a, nums, invDet);

		return 1;
	}
	else
	{
		centerOut = hkVector4::getConstant<HK_QUADREAL_MAX>();
		
		return 0;
	}
}

//
HKGP_FORCE_INLINE hkBool32	hkGeometryProcessing::circumCenter(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4Parameter d, hkVector4& centerOut)
{
	hkSimdReal	eps; eps.setFromFloat(1.e-5f);
	hkVector4	da; da.setSub(d,a);
	hkVector4	ca; ca.setSub(c,a);
	hkVector4	ba; ba.setSub(b,a);

	hkVector4	bc; bc.setCross(ba,ca);
	hkVector4	db; db.setCross(da,ba);
	hkVector4	cd; cd.setCross(ca,da);

	hkSimdReal	det = cd.dot<3>(ba) * hkSimdReal_2;

	if((det * det) > eps)
	{
		hkVector4	nums;
		nums.setMul(da.lengthSquared<3>(), bc);
		nums.addMul(ca.lengthSquared<3>(), db);
		nums.addMul(ba.lengthSquared<3>(), cd);

		hkSimdReal	invDet; invDet.setReciprocal(det);
		centerOut.setAddMul(a, nums, invDet);

		return 1;
	}
	else
	{
		centerOut = hkVector4::getConstant<HK_QUADREAL_MAX>();

		return 0;
	}
}

//
HKGP_FORCE_INLINE void		hkGeometryProcessing::getVertex(const hkAabb& box, int index, hkVector4& vertexOut)
{
	switch(index)
	{
		case	0:	vertexOut = box.m_min;break;
		case	1:	vertexOut.setSelect<hkVector4ComparisonMask::MASK_X> (box.m_max,box.m_min);break;
		case	2:	vertexOut.setSelect<hkVector4ComparisonMask::MASK_XY>(box.m_max,box.m_min);break;
		case	3:	vertexOut.setSelect<hkVector4ComparisonMask::MASK_Y> (box.m_max,box.m_min);break;
		case	4:	vertexOut.setSelect<hkVector4ComparisonMask::MASK_Z> (box.m_max,box.m_min);break;
		case	5:	vertexOut.setSelect<hkVector4ComparisonMask::MASK_XZ>(box.m_max,box.m_min);break;
		case	6:	vertexOut = box.m_max;break;
		case	7:	vertexOut.setSelect<hkVector4ComparisonMask::MASK_YZ>(box.m_max,box.m_min);break;
		default:	box.getCenter(vertexOut);
	}
	vertexOut.zeroComponent<3>();
}

//
template <typename A,typename B>
HKGP_FORCE_INLINE hkUlong		hkGeometryProcessing::makeHash(A ia,B ib)
{
	HK_COMPILE_TIME_ASSERT(sizeof(ia)<=sizeof(hkUlong) && sizeof(ib)<=sizeof(hkUlong));
	hkUlong			va=3424933;(*(A*)&va)=ia;
	hkUlong			vb=1661161;(*(B*)&vb)=ib;
	return( (va*3424933) ^ (vb*1661161) );
}

//
template <typename A,typename B>
HKGP_FORCE_INLINE hkUlong		hkGeometryProcessing::makeSymmetricHash(A a,B b)
{
	if(a<b)
		return(makeHash(a,b));
	else
		return(makeHash(b,a));
}

//
HKGP_FORCE_INLINE int			hkGeometryProcessing::chooseMN_count(int m,int n)
{
	if(!n || n==m) return(1); else return(chooseMN_count(m-1,n-1)+chooseMN_count(m-1,n));
}

//
inline void					hkGeometryProcessing::chooseMN_pick(int m,int n,int i,int* set)
{
	for(int j=0;n && j<m;++j)
	{
		const int c=chooseMN_count(m-j-1,n-1);
		if(i<c)			{ *set++=j;--n; }
		else if(i>=c)	{ i-=c; }
	}
}

//
template <typename T, int CAPACITY>
hkGeometryProcessing::LocalArrayAllocator<T, CAPACITY>::LocalArrayAllocator()

{
	m_data = hkAllocateStack<T>(CAPACITY);
	m_next = m_data;
	m_end = m_data + CAPACITY;

}

//
template <typename T, int CAPACITY>
hkGeometryProcessing::LocalArrayAllocator<T, CAPACITY>::~LocalArrayAllocator()
{
	hkDeallocateStack<T>(m_data);
}

//
template <typename T, int CAPACITY>
T*	hkGeometryProcessing::LocalArrayAllocator<T, CAPACITY>::allocate(const T& value)
{ 
	// Use >= instead of == here 'just in case'
	if( m_next >= m_end )
	{
		return HK_NULL;
	}

	*m_next = value;
	T* retVal = m_next;
	m_next = m_next + 1;
	return retVal;
}

//
template <typename T, int CAPACITY>
T*	hkGeometryProcessing::LocalArrayAllocator<T, CAPACITY>::allocate()
{ 
	// Use >= instead of == here 'just in case'
	if( m_next >= m_end )
	{
		return HK_NULL;
	}

	*m_next = T();
	T* retVal = m_next;
	m_next = m_next + 1;
	return retVal;
}

//
template <typename T, int CAPACITY>
HK_FORCE_INLINE void hkGeometryProcessing::LocalArrayAllocator<T, CAPACITY>::clear()
{
	// call dtor on all objects
	const int size = (int) (m_next - m_data);
	hkArrayUtil::destruct<T>(m_data, size, typename hkIsPodType<T>::type());
	m_next = m_data;
}

//
template <typename FUNCTION>
inline hkVector4	hkGeometryProcessing::minimizeN_R(int steps, int maxDepth, hkReal minConvergence, const FUNCTION& function)
{
	// Build fractions.
	hkInplaceArray<hkSimdReal,32>	fractions; fractions.setSize(steps+2);
	hkSimdReal invSize; invSize.setReciprocal<HK_ACC_FULL,HK_DIV_IGNORE>(hkSimdReal::fromInt32(fractions.getSize()-1));
	for(int i=0; i<fractions.getSize(); ++i)
	{
		fractions[i] = hkSimdReal::fromInt32(i) * invSize;
	}

	// Build half fractions.
	hkInplaceArray<hkSimdReal,32>	hfractions; hfractions.setSize(fractions.getSize()-1);
	for(int i=0; i<fractions.getSize()-1; ++i)
	{
		hfractions[i] = (fractions[i] + fractions[i+1]) * hkSimdReal_Half;
	}

	// Scan and subdivide domain.
	hkSimdReal	xSpan[2] = { hkSimdReal::getConstant<HK_QUADREAL_0>(), hkSimdReal::getConstant<HK_QUADREAL_1>() };
	hkSimdReal	ySpan[2] = { hkSimdReal::getConstant<HK_QUADREAL_0>(), hkSimdReal::getConstant<HK_QUADREAL_1>() };
	hkVector4	solution; solution.setZero(); solution.setW(hkSimdReal_Max);
	for(int depth = 0; depth < maxDepth; ++depth)
	{
		const hkSimdReal	xDelta = xSpan[1] - xSpan[0];
		const hkSimdReal	yDelta = ySpan[1] - ySpan[0];
		const hkSimdReal	prevValue = solution.getW();
		int					bestX=-1,bestY=-1;
		hkVector4			uv; uv.setZero();
		for(int y = 0; y < hfractions.getSize(); ++y)
		{
			uv.setComponent<1>(ySpan[0] + yDelta * hfractions[y]);
			for(int x = 0; x < hfractions.getSize(); ++x)
			{
				uv.setComponent<0>(xSpan[0] + xDelta * hfractions[x]);

				hkVector4	normal; hkGeometryProcessing::octahedronToNormal(uv, normal);
				hkSimdReal	value; value.setFromFloat(function(normal));
				if(bestX == -1 || value < solution.getW())
				{
					if(value.isEqualZero())
					{
						value.setFromFloat(function(normal)); 
					}
					bestX = x; bestY = y;
					solution.setXYZ_W(normal, value);
				}
			}			
		}

		const hkSimdReal convergence = prevValue - solution.getW();

		if(convergence > hkSimdReal::fromFloat(minConvergence) && bestX != -1)
		{
			xSpan[1] = xSpan[0] + xDelta * fractions[bestX+1];
			xSpan[0] = xSpan[0] + xDelta * fractions[bestX];
			ySpan[1] = ySpan[0] + yDelta * fractions[bestY+1];
			ySpan[0] = ySpan[0] + yDelta * fractions[bestY];
		}
		else
		{
			break;
		}
	}

	return solution;
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
