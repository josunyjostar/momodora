#ifndef SceneMgr_h__
#define SceneMgr_h__

#include "Title.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Ending.h"
#include "Loading.h"

class CSceneMgr :public TSingleton<CSceneMgr>
{
	friend TSingleton;
public:
	enum SCENE_TYPE
	{SCENE_TITLE,SCENE_STAGE_1, SCENE_STAGE_2, SCENE_STAGE_3, SCENE_STAGE_4,SCENE_ENDING,SCENE_END};
public:
	explicit  CSceneMgr(void);
	virtual  ~CSceneMgr(void) {}
private:
	SCENE_TYPE m_eCurScene;
	SCENE_TYPE m_ePrevScene;

	CLoading	m_Loading;
	CTitle		m_Title;
	CStage1		m_Stage1;
	CStage2		m_Stage2;
	CStage3		m_Stage3;
	CStage4		m_Stage4;
	CEnding		m_Ending;

	CScene*		m_pCurScene[SCENE_END];

	float		m_fGround_Hight;
public:
	float		GetGroundHeight(void) const {return m_fGround_Hight;}
	void		SetGroundHeight(float _fhight) {m_fGround_Hight = _fhight;}
public:
	CScene*		GetScene(SCENE_TYPE _eType) {return m_pCurScene[_eType];}
	SCENE_TYPE	GetCurScene(void) const {return m_eCurScene;}
	CLoading*	GetLoading(void) {return &m_Loading;}
public:
	void PrevScene(void);
	void SetScene(SCENE_TYPE _eScene);
	void Update(void);
	void Release(void);
};

#endif // SceneMgr_h__
