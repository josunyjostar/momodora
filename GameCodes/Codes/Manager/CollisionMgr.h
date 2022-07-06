#ifndef CollisionMgr_h__
#define CollisionMgr_h__

const int MAX_COLLIDER	= 4096;

enum COL_STATE
{CS_ENTER, CS_COL, CS_EXIT};

enum COL_DIR
{CD_LEFT, CD_RIGHT, CD_TOP, CD_BOTTOM};

class CCollider;
typedef struct CollisionManagementData 
{
	CCollider* I_Collider;
	CCollider* J_Collider;
	bool bPrevCol;
	bool bTrigger;

}COL_MGR_DATA;

typedef struct IndexList 
{
	int i;
	int j;

}INDEX_LIST;

typedef struct WallCollisionInfo 
{
	int Index;
	fRect ColRect;

}WALL_COL;

class CCollisionMgr : public TSingleton<CCollisionMgr>
{
	friend TSingleton;
private:
	explicit  CCollisionMgr(void);
	virtual  ~CCollisionMgr(void);
private:
	CCollider*		m_Collider[MAX_COLLIDER];
	COL_MGR_DATA	m_ColData[MAX_COLLIDER][MAX_COLLIDER];
	int m_iSize;

	INDEX_LIST		m_DataIndexList[MAX_COLLIDER*MAX_COLLIDER];
	int m_iListSize;	

	CCollider*	m_Wall[MAX_COLLIDER];
	int			m_iWallSize;
	WALL_COL	m_ColList[MAX_COLLIDER];
	int			m_iColCount;

public:
	void Update(void);
	void Release(void);
	bool WallColCheck(CCollider* _pCol, tVector& _MoveVector);
	void AddCollider(CCollider* _pCol);
	void DeleteCollider(CCollider* _pCol);
	int  GetCollisionCount(void) {return m_iSize + m_iWallSize;}
private:
	void SaveColData(int _i, int _j);
	void DeleteColData(int _i);
	void DeleteColData(int _i, int _j);

	bool CollisionCheck(CCollider* _pCol, CCollider* _pCol2);
	void CallCollision(CCollider* _pCol, CCollider* _pCol2, int _ColState);
	void CallTrigger(CCollider* _pCol, CCollider* _pCol2, int _ColState);

	void CircleInCircleCol(COL_INFO& _ColInfo, COL_INFO& _ColInfo2);
};
#endif // CollisionMgr_h__