#include "stdafx.h"
#include "CollisionMgr.h"

CCollisionMgr::CCollisionMgr(void)
:m_iSize(0), m_iListSize(0), m_iWallSize(0),m_iColCount(0)
{
	memset(m_Collider, NULL, sizeof(m_Collider));
	memset(m_ColData, NULL, sizeof(m_ColData));
	memset(m_Wall, NULL, sizeof(m_Wall));
	memset(m_ColList,NULL,sizeof(m_ColList));
	//XXX: 의도적으로 1로 초기화하여 멤버의 값을 16843009으로 만들려는 목적
	memset(m_DataIndexList, 1, sizeof(m_DataIndexList));
	//http://blog.naver.com/smrl7460/220979949217
}

CCollisionMgr::~CCollisionMgr(void)
{
	this->Release();
}

bool CCollisionMgr::CollisionCheck(CCollider* _pCol, CCollider* _pCol2)
{
	bool ColCheck = false;

	switch(_pCol->GetTag())
	{
	case TAG_PLAYER:
		switch(_pCol2->GetTag()) 
		{
		case TAG_PLAYER:	ColCheck = false;	break;
		case TAG_ENEMY:		ColCheck = true;	break;
		case TAG_EFFECT:	ColCheck = true;	break;
		case TAG_PLATFORM:	ColCheck = true;	break;
		case TAG_ITEM:		ColCheck = true;	break;
		case TAG_PET:		ColCheck = false;	break;
		} break;

	case TAG_ENEMY:
		switch(_pCol2->GetTag()) 
		{
		case TAG_PLAYER:	ColCheck = true;	break;
		case TAG_ENEMY:		ColCheck = false;	break;
		case TAG_EFFECT:	ColCheck = true;	break;
		case TAG_PLATFORM:	ColCheck = true;	break;
		case TAG_ITEM:		ColCheck = false;	break;
		case TAG_PET:		ColCheck = false;	break;
		} break;

	case TAG_EFFECT:
		switch(_pCol2->GetTag()) 
		{
		case TAG_PLAYER:	ColCheck = true;	break;
		case TAG_ENEMY:		ColCheck = true;	break;
		case TAG_EFFECT:	ColCheck = false;	break;
		case TAG_PLATFORM:	ColCheck = false;	break;
		case TAG_ITEM:		ColCheck = false;	break;
		case TAG_PET:		ColCheck = false;	break;
		} break;

	case TAG_PLATFORM:
		switch(_pCol2->GetTag()) 
		{
		case TAG_PLAYER:	ColCheck = true;	break;
		case TAG_ENEMY:		ColCheck = true;	break;
		case TAG_EFFECT:	ColCheck = false;	break;
		case TAG_PLATFORM:	ColCheck = false;	break;
		case TAG_ITEM:		ColCheck = false;	break;
		case TAG_PET:		ColCheck = false;	break;
		} break;
	case TAG_ITEM:
		switch(_pCol2->GetTag()) 
		{
		case TAG_PLAYER:	ColCheck = true;	break;
		case TAG_ENEMY:		ColCheck = false;	break;
		case TAG_EFFECT:	ColCheck = false;	break;
		case TAG_PLATFORM:	ColCheck = false;	break;
		case TAG_ITEM:		ColCheck = false;	break;
		case TAG_PET:		ColCheck = true;	break;
		} break;
	case TAG_PET:
		switch(_pCol2->GetTag()) 
		{
		case TAG_PLAYER:	ColCheck = false;	break;
		case TAG_ENEMY:		ColCheck = false;	break;
		case TAG_EFFECT:	ColCheck = false;	break;
		case TAG_PLATFORM:	ColCheck = false;	break;
		case TAG_ITEM:		ColCheck = true;	break;
		case TAG_PET:		ColCheck = false;	break;
		} break;
	}

	if(!ColCheck) 
		return false;

	switch(_pCol->GetColType())
	{
	case COL_RECT:
		switch(_pCol2->GetColType()) 
		{
		case COL_RECT:		
			return RectInRect(_pCol->GetColRect(), _pCol2->GetColRect());
		case COL_CIRCLE:	
			return RectInCircle(_pCol->GetColRect(), _pCol2->GetColRect());
		} break;

	case COL_CIRCLE:
		switch(_pCol2->GetColType()) 
		{
		case COL_RECT:		
			return RectInCircle(_pCol2->GetColRect(), _pCol->GetColRect());
		case COL_CIRCLE:	
			return CircleInCircle(_pCol->GetColRect(), _pCol2->GetColRect());
		} break;
	}

	return false;
}

void CCollisionMgr::CallCollision(CCollider* _pCol, CCollider* _pCol2, int _ColState)
{
	COL_INFO Col1(_pCol->GetGameObject()), Col2(_pCol2->GetGameObject());

	switch(_ColState)
	{
	case CS_ENTER:
		Col1.pObj->CollisionEnter(Col2);
		Col2.pObj->CollisionEnter(Col1);
		break;
	case CS_COL:
		Col1.pObj->Collision(Col2);
		Col2.pObj->Collision(Col1);
		break;
	case CS_EXIT:
		Col1.pObj->CollisionExit(Col2);
		Col2.pObj->CollisionExit(Col1);
		break;
	}
}

void CCollisionMgr::CallTrigger(CCollider* _pCol, CCollider* _pCol2, int _ColState)
{
	switch(_ColState)
	{
	case CS_ENTER:
		_pCol->GetGameObject()->TriggerEnter(_pCol2->GetGameObject());
		_pCol2->GetGameObject()->TriggerEnter(_pCol->GetGameObject());
		break;
	case CS_COL:
		_pCol->GetGameObject()->Trigger(_pCol2->GetGameObject());
		_pCol2->GetGameObject()->Trigger(_pCol->GetGameObject());
		break;
	case CS_EXIT:
		_pCol->GetGameObject()->TriggerExit(_pCol2->GetGameObject());
		_pCol2->GetGameObject()->TriggerExit(_pCol->GetGameObject());
		break;
	}
}

void CCollisionMgr::CircleInCircleCol(COL_INFO& _ColInfo, COL_INFO& _ColInfo2)
{
	tRect R1, R2;
	tPos P1, P2;

	R1 = _ColInfo.pObj->GetRect();
	R2 = _ColInfo2.pObj->GetRect();

	P1 = LookAt(R1.Pos(), R2.Pos()) * (((R1.cx < R1.cy)?R1.cx:R1.cy)/2.f) + R1.Pos();
	P2 = LookAt(R2.Pos(), R1.Pos()) * (((R2.cx < R2.cy)?R2.cx:R2.cy)/2.f) + R2.Pos();

	if(P1.x == P2.x && P1.y == P2.y)
	{
		_ColInfo.Vec = tVector(0.1f, 0.0f);
		_ColInfo2.Vec = tVector(-0.1f, 0.0f);
	}
	else
	{
		_ColInfo.Vec = (P1 - P2)/2.f;
		_ColInfo2.Vec = (P2 - P1)/2.f;
	}

	if(sqrMagnitude(P1) < sqrDistance(R1.Pos(), R2.Pos())) {
		_ColInfo2.Pos = _ColInfo.Pos = (P1 + P2) / 2.f;
	}
	else {
		if(sqrMagnitude(P1) > sqrMagnitude(P2))
			_ColInfo2.Pos = _ColInfo.Pos = P2;
		else
			_ColInfo2.Pos = _ColInfo.Pos = P1;
	}
}

void CCollisionMgr::Update()
{
	for(int i = 0; i < m_iSize-1; ++i)
	{
		if(!m_Collider[i]) 
			continue;

		for(int j = i+1; j < m_iSize; ++j)
		{
			if(!m_Collider[j]) 
				continue;

			if(!this->CollisionCheck(m_Collider[i], m_Collider[j])) 
			{
				if((m_ColData[i][j].I_Collider == m_Collider[i]) &&
					(m_ColData[i][j].J_Collider == m_Collider[j])&&
					m_ColData[i][j].bPrevCol)
				{
					this->DeleteColData(i, j);

					if(m_ColData[i][j].bTrigger)
						this->CallTrigger(m_Collider[i], m_Collider[j], CS_EXIT);
					else
						this->CallCollision(m_Collider[i], m_Collider[j], CS_EXIT);

					if(!m_Collider[i])
						break;
				}
				continue;
			}

			if(m_Collider[i]->IsTrigger() && m_Collider[j]->IsTrigger()) 
				continue;

			if(m_Collider[i]->IsTrigger() || m_Collider[j]->IsTrigger())
			{
				if((m_ColData[i][j].I_Collider != m_Collider[i]) ||
					(m_ColData[i][j].J_Collider != m_Collider[j])||
					!m_ColData[i][j].bTrigger ||
					!m_ColData[i][j].bPrevCol)
				{
					m_ColData[i][j].I_Collider = m_Collider[i];
					m_ColData[i][j].J_Collider = m_Collider[j];
					m_ColData[i][j].bTrigger = true;
					m_ColData[i][j].bPrevCol = true;
					this->SaveColData(i, j);
					this->CallTrigger(m_Collider[i], m_Collider[j], CS_ENTER);
				}
				else
					this->CallTrigger(m_Collider[i], m_Collider[j], CS_COL);
			}
			else
			{
				if((m_ColData[i][j].I_Collider != m_Collider[i]) ||
					(m_ColData[i][j].J_Collider != m_Collider[j])||
					m_ColData[i][j].bTrigger)
				{
					m_ColData[i][j].I_Collider = m_Collider[i];
					m_ColData[i][j].J_Collider = m_Collider[j];
					m_ColData[i][j].bTrigger = false;
					m_ColData[i][j].bPrevCol = true;
					this->SaveColData(i, j);
					this->CallCollision(m_Collider[i], m_Collider[j], CS_ENTER);
				}
				else
					this->CallCollision(m_Collider[i], m_Collider[j], CS_COL);
			}

			if(!m_Collider[i]) break;
		}
	}
}

void CCollisionMgr::Release()
{
	memset(m_Collider, NULL, sizeof(m_Collider));
	memset(m_ColData, NULL, sizeof(m_ColData));
	memset(m_DataIndexList, 1, sizeof(m_DataIndexList));
	memset(m_Wall, NULL, sizeof(m_Wall));
	memset(m_ColList,NULL,sizeof(m_ColList));

	m_iSize = 0;
	m_iListSize = 0;
	m_iWallSize = 0;
	m_iColCount = 0;
}

bool CCollisionMgr::WallColCheck(CCollider* _pCollider, tVector& _MoveVector)
{
	if(!_pCollider) 
		return false;

	float ColAngle  = 0.f;
	m_iColCount		= 0;

	for(int i = 0; i < m_iWallSize; ++i)
	{
		if(!m_Wall[i]) 
			continue;

		switch(_pCollider->GetColType()) 
		{
		case COL_RECT:
			if(!RectInRectEx(m_Wall[i]->GetColRect(), _pCollider->GetColRect(), m_ColList[m_iColCount].ColRect)) 
				goto CONTINUE;
			break;
		case COL_CIRCLE:
			if(!RectInCircleEx(m_Wall[i]->GetColRect(), _pCollider->GetColRect(), m_ColList[m_iColCount].ColRect, ColAngle)) 
				goto CONTINUE;
			break;
		}

		m_ColList[m_iColCount].Index = i;
		++m_iColCount;
CONTINUE:;
	}

	if (m_iColCount == 0) 
		return false;

	fRect IntegralColRect = m_ColList[0].ColRect;
	tRect ObjColRect = _pCollider->GetColRect();

	for(int i = 1; i < m_iColCount; ++i)
	{
		IntegralColRect.l = MIN(IntegralColRect.l,m_ColList[i].ColRect.l);
		IntegralColRect.r = MAX(IntegralColRect.r,m_ColList[i].ColRect.r);
		IntegralColRect.t = MIN(IntegralColRect.t,m_ColList[i].ColRect.t);
		IntegralColRect.b = MAX(IntegralColRect.b,m_ColList[i].ColRect.b);
	}

	if(_MoveVector.y > 0.f && IntegralColRect.t > ObjColRect.b()-10.f)
	{
		_pCollider->GetGameObject()->SetY(IntegralColRect.t - (ObjColRect.b()-ObjColRect.y));
		return true;
	}
	else if(_MoveVector.y < 0.f && IntegralColRect.b < ObjColRect.t()+10.f)
	{
		_pCollider->GetGameObject()->SetY(IntegralColRect.b + (ObjColRect.y-ObjColRect.t()));
		return true;
	}

	if(_MoveVector.x == 0.f)
	{
		if(_MoveVector.y > 0.f)
		{
			if(m_iColCount == 1)
			{
				if(IntegralColRect.b > ObjColRect.b()-50.f)
				{
					_pCollider->GetGameObject()->SetY(IntegralColRect.t - (ObjColRect.b()-ObjColRect.y));
				}
				else
				{
					if(IntegralColRect.l == ObjColRect.l())
						_pCollider->GetGameObject()->SetX(IntegralColRect.r + (ObjColRect.x-ObjColRect.l()));
					else
						_pCollider->GetGameObject()->SetX(IntegralColRect.l - (ObjColRect.r()-ObjColRect.x));
				}
			}
			else
			{
				for (int i = 0; i < m_iColCount; ++i)
				{	
					if(m_ColList[i].ColRect.b > ObjColRect.b()-50.f)
					{
						float MinY = MIN(_pCollider->GetGameObject()->GetY(), m_ColList[i].ColRect.t - (ObjColRect.b()-ObjColRect.y));
						_pCollider->GetGameObject()->SetY(MinY);
						ObjColRect = _pCollider->GetColRect();
					}
					else
					{
						if(m_ColList[i].ColRect.l == ObjColRect.l())
							_pCollider->GetGameObject()->SetX(m_ColList[i].ColRect.r + (ObjColRect.x-ObjColRect.l()));
						else
							_pCollider->GetGameObject()->SetX(m_ColList[i].ColRect.l - (ObjColRect.r()-ObjColRect.x));
					}
				}
			}
		}
		else
		{
			if(m_iColCount == 1)
			{
				if(IntegralColRect.t < ObjColRect.t()+50.f)
					_pCollider->GetGameObject()->SetY(IntegralColRect.b + (ObjColRect.y-ObjColRect.t()));
				else
				{
					if(IntegralColRect.l == ObjColRect.l())
						_pCollider->GetGameObject()->SetX(IntegralColRect.r + (ObjColRect.x-ObjColRect.l()));
					else
						_pCollider->GetGameObject()->SetX(IntegralColRect.l - (ObjColRect.r()-ObjColRect.x));
				}
			}
			else
			{
				for (int i = 0; i < m_iColCount; ++i)
				{
					if(m_ColList[i].ColRect.t < ObjColRect.t()+50.f)
					{
						float MaxY = MAX(_pCollider->GetGameObject()->GetY(), IntegralColRect.b + (ObjColRect.y-ObjColRect.t()));
						_pCollider->GetGameObject()->SetY(m_ColList[i].ColRect.b + (ObjColRect.y-ObjColRect.t()));
						ObjColRect = _pCollider->GetColRect();
					}
					else
					{
						if(m_ColList[i].ColRect.l == ObjColRect.l())
							_pCollider->GetGameObject()->SetX(m_ColList[i].ColRect.r + (ObjColRect.x-ObjColRect.l()));
						else
							_pCollider->GetGameObject()->SetX(m_ColList[i].ColRect.l - (ObjColRect.r()-ObjColRect.x));
					}
				}
			}
		}
	}
	else if(_MoveVector.y == 0.f)
	{
		if(_MoveVector.x > 0.f)
		{
			if(IntegralColRect.t > ObjColRect.b()-10.f)
				_pCollider->GetGameObject()->SetY(IntegralColRect.t - (ObjColRect.b()-ObjColRect.y));
			else if(IntegralColRect.b < ObjColRect.t()+10.f)
				_pCollider->GetGameObject()->SetY(IntegralColRect.b + (ObjColRect.y-ObjColRect.t()));
			else 
				_pCollider->GetGameObject()->SetX(IntegralColRect.l - (ObjColRect.r()-ObjColRect.x));
		}
		else
		{
			if(IntegralColRect.t > ObjColRect.b()-10.f)
				_pCollider->GetGameObject()->SetY(IntegralColRect.t - (ObjColRect.b()-ObjColRect.y));
			else if(IntegralColRect.b < ObjColRect.t()+10.f)
				_pCollider->GetGameObject()->SetY(IntegralColRect.b + (ObjColRect.y-ObjColRect.t()));
			else 
				_pCollider->GetGameObject()->SetX(IntegralColRect.r + (ObjColRect.x-ObjColRect.l()));
		}
	}
	else //Dir x != 0 && y != 0
	{
		tVector InverseVec = -_MoveVector;
		float rx = 0, lx = 0;
		float ry = 0, ly = 0;
		float w=0, h=0;

		//Dir Right 
		if(_MoveVector.x > 0.f)
		{
			//RightDown
			if(_MoveVector.y > 0.f) 
			{
				if(m_iColCount == 1)
				{
					w = ObjColRect.r() - IntegralColRect.l;
					h = ObjColRect.b() - IntegralColRect.t;

					if(w  > ObjColRect.cx-1.f)
						_pCollider->GetGameObject()->SetY(IntegralColRect.b - h - (ObjColRect.b()-ObjColRect.y));
					else if(h > ObjColRect.cy-1.f)
						_pCollider->GetGameObject()->SetX(IntegralColRect.r - w - (ObjColRect.r()-ObjColRect.x));
					else if(InverseVec.y * w < InverseVec.x * h)//?
						_pCollider->GetGameObject()->SetY(IntegralColRect.b - h - (ObjColRect.b()-ObjColRect.y));
					else 
						_pCollider->GetGameObject()->SetX(IntegralColRect.r - w - (ObjColRect.r()-ObjColRect.x));
				}
				else
				{
					for(int i = 0; i < m_iColCount; ++i)
					{
						w = IntegralColRect.r - m_ColList[i].ColRect.l;
						h = IntegralColRect.b - m_ColList[i].ColRect.t;
				
						if(InverseVec.y * w < InverseVec.x * h)
						{
							if(lx <= w) 
							{
								lx = w;
								ly = MAX(ly, h);
							}
						}
						else
						{
							if(ry <= h)
							{
								rx = MAX(rx,w);
								ry = h;
							}
						}
					}

					if(rx < lx) 
						_pCollider->GetGameObject()->SetY(IntegralColRect.b - ly - (ObjColRect.b()-ObjColRect.y));
					if(ly < ry) 
						_pCollider->GetGameObject()->SetX(IntegralColRect.r - rx - (ObjColRect.r()-ObjColRect.x));
				}
			}
			//RU 우,우상
			else
			{
				if(m_iColCount == 1)
				{
					w = ObjColRect.r() - IntegralColRect.l;
					h = IntegralColRect.b - ObjColRect.t();

					if(InverseVec.y * w < -InverseVec.x * h)
						_pCollider->GetGameObject()->SetX(IntegralColRect.r - w - (ObjColRect.r()-ObjColRect.x));
					else
						_pCollider->GetGameObject()->SetY(IntegralColRect.t + h + (ObjColRect.y-ObjColRect.t()));
				}
				else
				{
					for(int i = 0; i < m_iColCount; ++i) 
					{
						w = IntegralColRect.r - m_ColList[i].ColRect.l;
						h = m_ColList[i].ColRect.b - IntegralColRect.t;

						if(InverseVec.y * w < -InverseVec.x * h)
						{
							if(rx <= w) 
							{
								rx = w;
								ry = MAX(ry, h);
							}
						}
						else
						{
							if(ly <= h) 
							{
								lx = MAX(lx,w);
								ly = h;
							}
						}
					}

					if(rx < lx)
						_pCollider->GetGameObject()->SetY(IntegralColRect.t + ly + (ObjColRect.y-ObjColRect.t()));
					if(ly < ry)
						_pCollider->GetGameObject()->SetX(IntegralColRect.r - rx - (ObjColRect.r()-ObjColRect.x));
				}
			}
		}
		else //Left All
		{
			//LD LeftDown
			if(_MoveVector.y > 0.f)
			{
				if(m_iColCount == 1)
				{
					w = IntegralColRect.r - ObjColRect.l();
					h = ObjColRect.b() - IntegralColRect.t;

					if(w == ObjColRect.cx)
						_pCollider->GetGameObject()->SetY(IntegralColRect.b - h - (ObjColRect.b()-ObjColRect.y));
					else if(h == ObjColRect.cy)
						_pCollider->GetGameObject()->SetX(IntegralColRect.l + w + (ObjColRect.x-ObjColRect.l()));
					else if(-InverseVec.y * w < InverseVec.x * h)
						_pCollider->GetGameObject()->SetX(IntegralColRect.l + w + (ObjColRect.x-ObjColRect.l()));
					else
						_pCollider->GetGameObject()->SetY(IntegralColRect.b - h - (ObjColRect.b()-ObjColRect.y));
				}
				else
				{
					for(int i = 0; i < m_iColCount; ++i) 
					{
						w = m_ColList[i].ColRect.r - IntegralColRect.l;
						h = IntegralColRect.b - m_ColList[i].ColRect.t;

						if(-InverseVec.y * w < InverseVec.x * h)
						{
							if(lx <= w) 
							{
								lx = w;
								ly = MAX(ly, h);
							}
						}
						else
						{
							if(ry <= h) 
							{
								rx = MAX(rx,w);
								ry = h;
							}
						}
					}

					if(rx > lx) 
						_pCollider->GetGameObject()->SetY(IntegralColRect.b - ry - (ObjColRect.b()-ObjColRect.y));
					if(ly > ry) 
						_pCollider->GetGameObject()->SetX(IntegralColRect.l + lx + (ObjColRect.x-ObjColRect.l()));
				}
			}
			//LU
			else
			{
				if(m_iColCount == 1)
				{
					w = IntegralColRect.r - ObjColRect.l();
					h = IntegralColRect.b - ObjColRect.t();

					if(InverseVec.y * w < InverseVec.x * h)
						_pCollider->GetGameObject()->SetX(IntegralColRect.l + w + (ObjColRect.x-ObjColRect.l()));
					else
						_pCollider->GetGameObject()->SetY(IntegralColRect.t + h + (ObjColRect.y-ObjColRect.t()));
				}
				else
				{
					for(int i = 0; i < m_iColCount; ++i) 
					{
						w = m_ColList[i].ColRect.r - IntegralColRect.l;
						h = m_ColList[i].ColRect.b - IntegralColRect.t;

						if(InverseVec.y * w < InverseVec.x * h)
						{
							if(rx <= w) 
							{
								rx = w;
								ry = MAX(ry, h);
							}
						}
						else
						{
							if(ly <= h) 
							{
								lx = MAX(lx,w);
								ly = h;
							}
						}
					}

					if(rx < lx)
						_pCollider->GetGameObject()->SetY(IntegralColRect.t + ly + (ObjColRect.y-ObjColRect.t()));
					if(ly < ry) 
						_pCollider->GetGameObject()->SetX(IntegralColRect.l + rx + (ObjColRect.x-ObjColRect.l()));
				}
			}
		}		
	}
	
	return true;
}

void CCollisionMgr::AddCollider(CCollider* _pCollider)
{
	if(_pCollider->GetTag() == TAG_PLATFORM && !_pCollider->IsTrigger())
	{
		for(int i = 0; i < m_iWallSize; ++i) 
		{
			if(m_Wall[i]) 
				continue;

			m_Wall[i] = _pCollider;
			return;
		}

		m_Wall[m_iWallSize++] = _pCollider;
	}
	else 
	{
		for(int i = 0; i < m_iSize; ++i) 
		{
			if(m_Collider[i]) 
				continue;

			m_Collider[i] = _pCollider;
			return;
		}
		m_Collider[m_iSize++] = _pCollider;
	}
}

void CCollisionMgr::DeleteCollider(CCollider* _pCollider)
{
	if(_pCollider->GetTag() == TAG_PLATFORM && !_pCollider->IsTrigger()) 
	{
		for(int i = 0; i < m_iWallSize; ++i) 
		{
			if(m_Wall[i] == _pCollider) 
			{
				m_Wall[i] = NULL;
				return;
			}
		}
	}
	else 
	{
		for(int i = 0; i < m_iSize; ++i) 
		{
			if(m_Collider[i] == _pCollider)
			{
				this->DeleteColData(i);
				m_Collider[i] = NULL;
				return;
			}
		}
	}
}

void CCollisionMgr::SaveColData(int _i, int _j)
{
	for(int i = 0; i < m_iListSize; ++i) 
	{
		if(m_DataIndexList[i].i == INIT_VAL) 
		{
			m_DataIndexList[i].i = _i;
			m_DataIndexList[i].j = _j;
			return;
		}
	}
	m_DataIndexList[m_iListSize].i = _i;
	m_DataIndexList[m_iListSize++].j = _j;
}

void CCollisionMgr::DeleteColData(int _i)
{
	for(int i = 0; i < m_iListSize; ++i) 
	{
		if(m_DataIndexList[i].i == _i || m_DataIndexList[i].j == _i) 
		{
			m_ColData[m_DataIndexList[i].i][m_DataIndexList[i].j].I_Collider = NULL;
			m_ColData[m_DataIndexList[i].i][m_DataIndexList[i].j].J_Collider = NULL;
			m_ColData[m_DataIndexList[i].i][m_DataIndexList[i].j].bPrevCol = false;
			m_DataIndexList[i].i = INIT_VAL;
			m_DataIndexList[i].j = INIT_VAL;
		}
	}
}

void CCollisionMgr::DeleteColData(int _i, int _j)
{
	for(int i = 0; i < m_iListSize; ++i) 
	{
		if(m_DataIndexList[i].i == _i && m_DataIndexList[i].j == _j)
		{
			m_ColData[m_DataIndexList[i].i][m_DataIndexList[i].j].I_Collider = NULL;
			m_ColData[m_DataIndexList[i].i][m_DataIndexList[i].j].J_Collider = NULL;
			m_ColData[m_DataIndexList[i].i][m_DataIndexList[i].j].bPrevCol = false;
			m_DataIndexList[i].i = INIT_VAL;
			m_DataIndexList[i].j = INIT_VAL;
			return;
		}
	}
}