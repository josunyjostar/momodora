#include "stdafx.h"
#include "TextureMgr.h"

ATL::CImage* CTextureMgr::AddTexture(char* _pName, WCHAR* _pFilePath)
{
	CImage** dpImage = &m_mapTexture[_pName];

	if (*dpImage)
		return *dpImage;

	*dpImage = new CImage;
	if (FAILED((*dpImage)->Load(_pFilePath)))
		SAFE_DELETE(*dpImage);

	return *dpImage;
}

void CTextureMgr::Init(void)
{
	CImage *pImage, *pImageL, *pImageR;
	float*	pFrameDelay;

	//Filter
	pImage = this->AddTexture("White",L"../../Resources/Filter/White.png");
	m_pSpriteMgr->AddSprite(pImage,"White",0,0,16,16,0,0,RENDER_NORMAL);
	pImage = this->AddTexture("Red",L"../../Resources/Filter/Red.png");
	m_pSpriteMgr->AddSprite(pImage,"Red",0,0,16,16,0,0,RENDER_NORMAL);

	//HP bar
	pImage = this->AddTexture("ItemUI",L"../../Resources/UI/ItemUI.png");
	m_pSpriteMgr->AddSprite(pImage,"ItemUI",0,0,72,72,0,0,RENDER_NORMAL);

	pImage = this->AddTexture("BarFrame",L"../../Resources/UI/BarFrame.png");

	m_pSpriteMgr->AddSprite(pImage,"BarFrame_Root",0,0,14,18,0,0,RENDER_NORMAL);
	m_pSpriteMgr->AddSprite(pImage,"BarFrame_Body",14,0,1,18,0,0,RENDER_ALPHA);
	m_pSpriteMgr->AddSprite(pImage,"BarFrame_Head",124,0,12,18,0,0,RENDER_ALPHA);


	pImage = this->AddTexture("HPSP",L"../../Resources/UI/HPSP.png");
	m_pSpriteMgr->AddSprite(pImage,"HPbar_Back",126,3,21,5,0,0,RENDER_ALPHA);
	m_pSpriteMgr->AddSprite(pImage,"HPbar_Front",126,12,21,5,0,0,RENDER_ALPHA);
	m_pSpriteMgr->AddSprite(pImage,"SPbar_Back",153,3,21,5,0,0,RENDER_ALPHA);
	m_pSpriteMgr->AddSprite(pImage,"SPbar_Front",153,12,21,5,0,0,RENDER_ALPHA);

	//Tile
	pImage = this->AddTexture("Tile", L"../../Resources/Stage/Tile/Tile1.png");

	m_pSpriteMgr->AddSprite(pImage, "Tile1_Small" , 0, 0, 48, 16, 0, 0, RENDER_NORMAL);
	m_pSpriteMgr->AddSprite(pImage, "Tile1_Middle", 0,18, 127,16, 0, 0, RENDER_NORMAL);
	m_pSpriteMgr->AddSprite(pImage, "Tile1_Large" , 0,36, 256,16, 0, 0, RENDER_NORMAL);
	m_pSpriteMgr->AddSprite(pImage, "Tile2_Small" , 0,54, 67,16, 0, 0, RENDER_NORMAL);

	//Stage_1 Background
	pImage = this->AddTexture("Waterfall", L"../../Resources/Stage/Stage1/waterfall.png");
	m_pAniMgr->AddAni(pImage,pImage,"Waterfall",15,0 ,0,86,254,0,0,19,0,RENDER_ALPHA,true);

	pImage = this->AddTexture("WaterSurface", L"../../Resources/Stage/Stage1/watersurface.png");
	m_pAniMgr->AddAni(pImage,pImage,"WaterSurface",3,0,0,126,6,0,0,0,2,RENDER_ALPHA,true);

	pImage = this->AddTexture("WaterSurface2", L"../../Resources/Stage/Stage1/watersurface2.png");
	m_pAniMgr->AddAni(pImage,pImage,"WaterSurface2",4,0,0,64,10,0,0,0,0,RENDER_ALPHA,true);
	
	pImage = this->AddTexture("Stage1", L"../../Resources/Stage/Stage1/Stage1.png");
	m_pSpriteMgr->AddSprite(pImage, "Stage1", 0, 0, 1023, 320, 0, 0, RENDER_ALPHA);

	pImage = this->AddTexture("Stage1_Back1", L"../../Resources/Stage/Stage1/Stage1_Back1.png");
	m_pSpriteMgr->AddSprite(pImage, "Stage1_Back1", 0, 0, 768, 256, 0, 0, RENDER_ALPHA);

	pImage = this->AddTexture("Stage1_Back3", L"../../Resources/Stage/Stage1/Stage1_Back3.png");
	m_pSpriteMgr->AddSprite(pImage, "Stage1_Back3", 0, 0, 600, 256, 0, 0, RENDER_NORMAL);

	pImage = this->AddTexture("Stage1_Back3_", L"../../Resources/Stage/Stage1/Stage1_Back3_.png");
	m_pSpriteMgr->AddSprite(pImage, "Stage1_Back3_", 0, 0, 600, 256, 0, 0, RENDER_NORMAL);


	//Stage_2 Background
	pImage = this->AddTexture("Stage2", L"../../Resources/Stage/Stage2/Stage2.png");
	m_pSpriteMgr->AddSprite(pImage, "Stage2", 0, 0, 506, 706, 0, 0, RENDER_ALPHA);

	pImage = this->AddTexture("Stage2_Back1", L"../../Resources/Stage/Stage2/Stage2_Back1.png");
	m_pSpriteMgr->AddSprite(pImage, "Stage2_Back1", 0, 0, 286, 100, 0, 0, RENDER_ALPHA);

	//Stage_3 Background
	pImage = this->AddTexture("Stage3", L"../../Resources/Stage/Stage3/Stage3.png");
	m_pSpriteMgr->AddSprite(pImage, "Stage3", 0, 0, 1792, 207, 0, 0, RENDER_ALPHA);

	//Stage_4 Background
	pImage = this->AddTexture("Stage4", L"../../Resources/Stage/Stage4/Stage4.png");
	m_pSpriteMgr->AddSprite(pImage, "Stage4", 0, 0, 1024, 463, 0, 0, RENDER_NORMAL);

	//Stage_Ending Background
	pImage = this->AddTexture("StageEnding", L"../../Resources/Stage/StageEnding/StageEnding.png");
	m_pSpriteMgr->AddSprite(pImage, "StageEnding", 0, 0, 415, 463, 0, 0, RENDER_NORMAL);

	//Player
	pImageL = this->AddTexture("MomoL", L"../../Resources/Player/MomoL.png");
	pImageR = this->AddTexture("MomoR", L"../../Resources/Player/MomoR.png");	

	pFrameDelay = new float[6];
	for(int i = 0; i < 6; ++i)
		pFrameDelay[i] = 0.053f;

	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Idle",6,1 ,2198,48,48,0,0,1,0,RENDER_ALPHA,true,NULL,pFrameDelay);

	pFrameDelay = new float[5];
	for(int i = 0; i < 5; ++i)
		pFrameDelay[i] = 0.048f;

	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Run"       ,5,99,843 ,48,48,0,0,1,0,RENDER_ALPHA,true,NULL,pFrameDelay);
	pFrameDelay = new float[2];
	for(int i = 0; i < 2; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Run_Start" ,2,1, 843 ,48,48,0,0,1,0,RENDER_ALPHA,false,"Momo_Run",pFrameDelay);
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Jump"      ,3,1 ,1694,48,48,0,0,1,0,RENDER_ALPHA,false);
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Fall"      ,3,99,1757,48,48,0,0,1,0,RENDER_ALPHA,true);
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Fall_Start",2,1 ,1757,48,48,0,0,1,0,RENDER_ALPHA,false,"Momo_Fall");

	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Dash"      ,1,1 ,3284,48,48,0,0,1,0,RENDER_ALPHA,true);
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Dash_Start"		,3,1,3221,48,48,0,0,1,0,RENDER_ALPHA,false,"Momo_Dash");

	pFrameDelay = new float[1];
	for(int i = 0; i < 1; ++i)
		pFrameDelay[i] = 0.3f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Hit"       ,1,1 ,2135,48,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[3];
	for(int i = 0; i < 3; ++i)
		pFrameDelay[i] = 0.037f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Dash_End"		,3,1,3347,48,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[5];
	for(int i = 0; i < 5; ++i)
		pFrameDelay[i] = 0.025f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Dash_End_InAir" ,5,1,3410,48,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);


	pFrameDelay = new float[8];
	for(int i = 0; i < 5; ++i)
		pFrameDelay[i] = 0.06f;
	for(int i = 5; i < 3; ++i)
		pFrameDelay[i] = 0.045f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Roll"      ,8,1 ,3536,48,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Attack_01" ,7,1  ,75 ,48,48,0,0,1,0,RENDER_ALPHA,false);

	pFrameDelay = new float[4];
	for(int i = 0; i < 4; ++i)
		pFrameDelay[i] = 0.059f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Leaf_Attack_01" ,4,292,390,96,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[7];
	for(int i = 0; i < 7; ++i)
		pFrameDelay[i] = 0.055f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Attack_02" ,7,1 ,138,48,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[4];
	for(int i = 0; i < 4; ++i)
		pFrameDelay[i] = 0.055f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Leaf_Attack_02" ,4,292,453,96,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[11];
	for(int i = 0; i < 11; ++i)
		pFrameDelay[i] = 0.05f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Attack_03" ,11,1 ,201,48,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[11];
	for(int i = 0; i < 11; ++i)
		pFrameDelay[i] = 0.065f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Leaf_Attack_03" ,9,1 ,516,96,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[7];
	for(int i = 0; i < 7; ++i)
		pFrameDelay[i] = 0.03f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Brake"     ,7,1 ,906 ,48,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Attack_InAir",7,1,264,48,48,0,0,1,0,RENDER_ALPHA,false);
	m_pAniMgr->AddAni(pImageL,pImageR,"Leaf_Attack_InAir",6,1,579,96,56,0,0,1,0,RENDER_ALPHA,false);

	//Momo Ending
	pFrameDelay = new float[28];
	for(int i = 0; i < 28; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_EndPaying" ,28,1,1582,48,48,0,0,1,1,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[4];
	for(int i = 0; i < 4; ++i)
		pFrameDelay[i] = 0.06f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_Paying" ,4,1,1883,48,48,0,0,1,0,RENDER_ALPHA,true,NULL,pFrameDelay);

	pFrameDelay = new float[6];
	for(int i = 0; i < 6; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Momo_ToPaying" ,6,1,1820,48,48,0,0,1,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	//Effect
	pImageL = this->AddTexture("Explosion", L"../../Resources/Effect/Explosion3.png");
	pFrameDelay = new float[10];
	for(int i = 0; i < 10; ++i)
		pFrameDelay[i] = 0.05f;

	m_pAniMgr->AddAni(pImageL,pImageL,"Explosion",10,1,1,89,89,0,0,3,3,RENDER_TRANSPARENT,false,NULL,pFrameDelay);

	pImageL = this->AddTexture("Sparkle", L"../../Resources/Effect/Sparkle.png");
	pFrameDelay = new float[48];
	for(int i = 0; i < 48; ++i)
		pFrameDelay[i] = 0.013f;
	m_pAniMgr->AddAni(pImageL,pImageL,"Sparkle",48,1 ,1 ,48,48,0,0,1,1,RENDER_ALPHA,false,NULL,pFrameDelay);

	pImageL = this->AddTexture("HitEffectL", L"../../Resources/Effect/HitEffectR.png");
	pImageR = this->AddTexture("HitEffectR", L"../../Resources/Effect/HitEffectL.png");

	pFrameDelay = new float[8];
	for(int i = 0; i < 8; ++i)
		pFrameDelay[i] = 0.03f;
	m_pAniMgr->AddAni(pImageL,pImageR,"HitEffect",8,0,0,180,180,0,0,0,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pImageL = this->AddTexture("IceBerg", L"../../Resources/Effect/IceBerg.png");
	pFrameDelay = new float[5];
	pFrameDelay[0] = 0.04f;
	pFrameDelay[1] = 0.06f;
	pFrameDelay[2] = 0.05f;
	pFrameDelay[3] = 0.2f;
	pFrameDelay[4] = 0.01f;
	m_pAniMgr->AddAni(pImageL,pImageL,"IceBerg",5,0,0,98,136,0,0,0,0,RENDER_TRANSPARENT,false,NULL,pFrameDelay);

	pImageL = this->AddTexture("Thunder", L"../../Resources/Effect/Thunder.png");

	pFrameDelay = new float[7];
	for(int i = 0; i < 7; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageL,"Thunder",7,0,0,111,215,0,0,0,0,RENDER_TRANSPARENT,false,NULL,pFrameDelay);

	pImageL = this->AddTexture("Thunder2", L"../../Resources/Effect/Thunder2.png");
	pFrameDelay = new float[8];
	for(int i = 0; i < 8; ++i)
		pFrameDelay[i] = 0.055f;
	m_pAniMgr->AddAni(pImageL,pImageL,"Thunder2",8,0,0,39,157,0,0,0,0,RENDER_TRANSPARENT,false,NULL,pFrameDelay);

	pImageL = this->AddTexture("Bomb", L"../../Resources/Effect/Bomb.png");
	pFrameDelay = new float[11];
	for(int i = 0; i < 11; ++i)
		pFrameDelay[i] = 0.025f;
	m_pAniMgr->AddAni(pImageL,pImageL,"Bomb",11,0,0,218,200,0,0,0,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pImageL = this->AddTexture("StingL", L"../../Resources/Effect/StingL.png");
	pImageR = this->AddTexture("StingR", L"../../Resources/Effect/StingR.png");
	pFrameDelay = new float[6];
	for(int i = 0; i < 6; ++i)
		pFrameDelay[i] = 0.045f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Sting",6,0,0,120,120,0,0,0,0,RENDER_TRANSPARENT,false,NULL,pFrameDelay);

	pImageL = this->AddTexture("MasicCircle2", L"../../Resources/Effect/MasicCircle2.png");
	pFrameDelay = new float[16];
	for(int i = 0; i < 16; ++i)
		pFrameDelay[i] = 0.065f;
	m_pAniMgr->AddAni(pImageL,pImageL,"MasicCircle2",16,0,0,256,256,0,0,0,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pImageL = this->AddTexture("Ring", L"../../Resources/Effect/Ring.png");
	pFrameDelay = new float[8];
	for(int i = 0; i < 8; ++i)
		pFrameDelay[i] = 0.065f;
	m_pAniMgr->AddAni(pImageL,pImageL,"Ring",8,4,4,200,200,0,0,4,4,RENDER_ALPHA,false,NULL,pFrameDelay);

	//Item
	pImage = this->AddTexture("Item", L"../../Resources/Item/Item.png");
	m_pAniMgr->AddAni(pImage,pImage,"ItemDove",2,0,0,10,11,0,0,0,0,RENDER_ALPHA,true);
	m_pSpriteMgr->AddSprite(pImage, "Nest", 0, 11, 27, 13, 0, 0, RENDER_ALPHA);
	m_pSpriteMgr->AddSprite(pImage, "MaxHP", 0, 24, 30, 31, 0, 0, RENDER_ALPHA);
	m_pSpriteMgr->AddSprite(pImage, "MaxSP", 31,24, 30, 31, 0, 0, RENDER_ALPHA);

	//Door
	pImage = this->AddTexture("Door", L"../../Resources/Stage/Stage4/Door.png");
	m_pSpriteMgr->AddSprite(pImage, "Door",0,0,16,112,0,0,RENDER_ALPHA);

	//Crystal
	pImageL = this->AddTexture("Crystal2", L"../../Resources/Item/Crystal2.png");
	m_pAniMgr->AddAni(pImageL,pImageL,"Crystal2",8,0 ,0 ,16,24,0,0,0,0,RENDER_TRANSPARENT,true);

	//Dove
	pImageL = this->AddTexture("DoveL", L"../../Resources/Pet/DoveL.png");
	pImageR = this->AddTexture("DoveR", L"../../Resources/Pet/DoveR.png");

	pFrameDelay = new float[2];
	for(int i = 0; i < 2; ++i)
		pFrameDelay[i] = 0.1f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Dove_Stright"   ,2,0,0  ,23,29,0,0,0,0,RENDER_ALPHA,true,NULL,pFrameDelay);

	//Player
	pImageL = this->AddTexture("ImpL", L"../../Resources/Monster/ImpL.png");
	pImageR = this->AddTexture("ImpR", L"../../Resources/Monster/ImpR.png");	

	m_pAniMgr->AddAni(pImageL,pImageR,"Imp_Idle",1,2,21,32,32,0,0,0,0,RENDER_ALPHA,true);
	pFrameDelay = new float[1];
	for(int i = 0; i < 1; ++i)
		pFrameDelay[i] = 0.3f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Imp_Hit",1,2,74,32,32,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);
	m_pAniMgr->AddAni(pImageL,pImageR,"Imp_Jump",1,2,233,32,32,0,0,0,0,RENDER_ALPHA,true);
	m_pAniMgr->AddAni(pImageL,pImageR,"Imp_Fall",6,2,286,32,32,0,0,2,0,RENDER_ALPHA,true);
	m_pAniMgr->AddAni(pImageL,pImageR,"Imp_ThrowKnife",10,2,339,32,32,0,0,2,0,RENDER_ALPHA,false);

	pFrameDelay = new float[5];
	for(int i = 0; i < 5; ++i)
		pFrameDelay[i] = 0.1f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Imp_ShieldWalk",5,2,551,32,32,0,0,2,0,RENDER_ALPHA,true,NULL,pFrameDelay);

	m_pAniMgr->AddAni(pImageL,pImageR,"Imp_MeleeAtk",8,2,604,32,32,0,0,2,0,RENDER_ALPHA,false);

	m_pAniMgr->AddAni(pImageL,pImageR,"Knife",1,30,657,16,16,0,0,0,0,RENDER_ALPHA,false);

	//Sato
	pImageL = this->AddTexture("SatoL", L"../../Resources/Monster/SatoL.png");
	pImageR = this->AddTexture("SatoR", L"../../Resources/Monster/SatoR.png");	

	pFrameDelay = new float[8];
	for(int i = 0; i < 8; ++i)
		pFrameDelay[i] = 0.05f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Sato_Idle",8,2,21,48,48,0,0,2,0,RENDER_ALPHA,true,NULL,pFrameDelay);

	pFrameDelay = new float[7];
	for(int i = 0; i < 7; ++i)
		pFrameDelay[i] = 0.06f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Sato_Roll",7,2,90,48,48,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[1];
	for(int i = 0; i < 1; ++i)
		pFrameDelay[i] = 0.2f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Sato_Hit",1,2,159,48,48,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[9];
	for(int i = 0; i < 9; ++i)
		pFrameDelay[i] = 0.05f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Sato_Atk_1",9,2,228,128,96,0,0,2,4,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[9];
	for(int i = 0; i < 9; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Sato_Atk_2",9,2,445,92,96,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[10];
	for(int i = 0; i < 4; ++i)
		pFrameDelay[i] = 0.1f;
	for(int i = 4; i < 8; ++i)
		pFrameDelay[i] = 0.065f;
	for(int i = 8; i < 10; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Sato_Atk_3",10,2,562,80,48,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[18];
	for(int i = 0; i < 18; ++i)
		pFrameDelay[i] = 0.062f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Sato_Atk_4",18,2,631,80,48,0,0,2,4,RENDER_ALPHA,false,NULL,pFrameDelay);

	//Magnolia
	pImageL = this->AddTexture("MagnoliaL", L"../../Resources/Monster/MagnoliaL.png");
	pImageR = this->AddTexture("MagnoliaR", L"../../Resources/Monster/MagnoliaR.png");	

	pFrameDelay = new float[6];
	for(int i = 0; i < 6; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Magnolia_Idle",6,2,21,48,48,0,0,2,0,RENDER_ALPHA,true,NULL,pFrameDelay);

	pFrameDelay = new float[4];
	for(int i = 0; i < 4; ++i)
		pFrameDelay[i] = 0.12f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Magnolia_Ready_Atk",4,2,90,48,48,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[6];
	for(int i = 0; i < 6; ++i)
		pFrameDelay[i] = 0.04f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Magnolia_Jump",6,2,159,48,48,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[5];
	for(int i = 0; i < 5; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Magnolia_Fall",5,2,228,48,48,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[1];
	for(int i = 0; i < 1; ++i)
		pFrameDelay[i] = 0.2f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Magnolia_Hit",1,2,366,48,48,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[7];
	for(int i = 0; i < 7; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Magnolia_Atk",7,2,297,92,48,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	//Fennel
	pImageL = this->AddTexture("FennelL", L"../../Resources/Monster/FennelL.png");
	pImageR = this->AddTexture("FennelR", L"../../Resources/Monster/FennelR.png");	

	pFrameDelay = new float[19];
	for(int i = 0; i < 2; ++i)
		pFrameDelay[i] = 0.25f;
	for(int i = 2; i < 19; ++i)
		pFrameDelay[i] = 0.075f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Intro1",19,2,1208,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);
	pFrameDelay = new float[8];
	for(int i = 0; i < 8; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Intro2",8,2,1307,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);
	pFrameDelay = new float[14];
	for(int i = 0; i < 14; ++i)
		pFrameDelay[i] = 0.075f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Intro3",14,2,1406,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);
	pFrameDelay = new float[3];
	for(int i = 0; i < 3; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Intro4",3,2,1505,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[5];
	for(int i = 0; i < 5; ++i)
		pFrameDelay[i] = 0.075f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Idle",5,2,22,118,78,0,0,2,0,RENDER_ALPHA,true,NULL,pFrameDelay);

	pFrameDelay = new float[22];
	for(int i = 0; i < 22; ++i)
		pFrameDelay[i] = 0.075f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Impact",22,2,418,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[9];
	for(int i = 0; i < 9; ++i)
		pFrameDelay[i] = 0.075f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Impact",9,2,1701,256,158,0,0,2,0,RENDER_TRANSPARENT,false,NULL,pFrameDelay);

	pFrameDelay = new float[13];
	for(int i = 0; i < 13; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_BackFlip",13,2,715,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Dash",1,2,814,118,78,0,0,0,0,RENDER_ALPHA,true);

	pFrameDelay = new float[3];
	for(int i = 0; i < 3; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Ready_Dash2",3,2,1505,118,78,0,0,2,0,RENDER_ALPHA,false,"Fennel_Dash",pFrameDelay);

	pFrameDelay = new float[14];
	for(int i = 0; i < 14; ++i)
		pFrameDelay[i] = 0.06f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Ready_Dash",14,2,1406,118,78,0,0,2,0,RENDER_ALPHA,false,"Fennel_Ready_Dash2",pFrameDelay);

	pFrameDelay = new float[10];
	for(int i = 0; i < 10; ++i)
		pFrameDelay[i] = 0.06f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Brake",10,1442,418,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[15];
	for(int i = 0; i < 15; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Buff",15,2,913,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[2];
	for(int i = 0; i < 2; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Hit",2,2,121,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[7];
	for(int i = 0; i < 7; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Jump",7,2,616,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[12];
	for(int i = 0; i < 12; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Atk_InAir",12,2,319,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[23];
	for(int i = 0; i < 23; ++i)
		pFrameDelay[i] = 0.05f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Atk_1",23,2,220,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[13];
	for(int i = 0; i < 13; ++i)
		pFrameDelay[i] = 0.07f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Fennel_Atk_Down",13,2,517,118,78,0,0,2,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	//Fennel
	pImageL = this->AddTexture("DemonL", L"../../Resources/Effect/DemonL.png");
	pImageR = this->AddTexture("DemonR", L"../../Resources/Effect/DemonR.png");	

	pFrameDelay = new float[3];
	for(int i = 0; i < 3; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Demon_jump",3,0,0,123,158,0,0,0,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[3];
	for(int i = 0; i < 3; ++i)
		pFrameDelay[i] = 0.1f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Demon_Fall",3,0,158,123,111,0,0,0,0,RENDER_ALPHA,false,NULL,pFrameDelay);

	pFrameDelay = new float[1];
	for(int i = 0; i < 1; ++i)
		pFrameDelay[i] = 0.08f;
	m_pAniMgr->AddAni(pImageL,pImageR,"Demon_Atk",1,0,270,123,128,0,0,0,0,RENDER_ALPHA,false,NULL,pFrameDelay);
}

void CTextureMgr::Release(void)
{
	map<char*, CImage*>::iterator Iter = m_mapTexture.begin();
	map<char*, CImage*>::iterator Iter_end = m_mapTexture.end();

	while(Iter_end != Iter)
	{
		SAFE_DELETE(Iter->second);
		++Iter;
	}
	m_mapTexture.clear();
}

