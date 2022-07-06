#ifndef Unit_h__
#define Unit_h__

#include "HitBox.h"


class CUnit abstract : public CGameObject
{
	DeclRTTI(CUnit, CGameObject);
public:
	explicit CUnit(void):m_pCollider(NULL),m_fVelocity(0.f), m_fHP(0), m_fMaxHP(0),m_fSP(0),m_fMaxSP(0),m_PrevPos(){}
	virtual ~CUnit(void) {}
protected:		
	CCollider*	m_pCollider;

	float		m_fHP;
	float		m_fMaxHP;
	float		m_fSP;
	float		m_fMaxSP;
	float		m_fVelocity;
	tPos		m_PrevPos;
public:
	virtual void Hit(const float& _fDamage){}
public:
	void	SetHP(float _iHP) {m_fHP = _iHP;}
	void	SetSP(float _iSP)	  {m_fSP = _iSP;}
	void	SetMAXHP(float _iMaxHP) {m_fMaxHP = _iMaxHP;}
	void	SetMAXSP(float _iMaxSP) {m_fMaxSP = _iMaxSP;}
	void	AddMAXHP(float _iMaxHP) {m_fMaxHP += _iMaxHP;}
	void	AddMAXSP(float _iMaxSP) {m_fMaxSP += _iMaxSP;}

	const	float&	GetHP(void)		const	{return m_fHP;}
	const	float&	GetMaxHP(void)	const	{return m_fMaxHP;}
	const	float&	GetSP(void)		const	{return m_fSP;}
	const	float&	GetMaxSP(void)	const	{return m_fMaxSP;}
};
#endif // Unit_h__