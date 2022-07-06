// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.

#pragma once
#pragma comment(lib, "msimg32.lib") // TransparentBlit()
#pragma comment(lib, "winmm.lib")	// 사운드 출력
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN         // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C의 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <map>
#include <queue>
#include <stack>
#include <typeinfo>
#include <ctime>
#include <cmath>
#include <atlimage.h>	//[MFC : CCImage]

//#include "vld.h"

//XXX: Header 순서 변경 금지
using namespace std;

#include "Define.h"
#include "enum.h"
#include "Struct.h"
#include "MathLib.h"

#include "FastRTTI.h"
#include "TemplateSingleton.h"
#include "KeyState.h"

#include "Obj.h"
#include "GameObject.h"
#include "Component.h"

#include "Camera.h"
#include "ObjectMgr.h"

#include "CollisionMgr.h"
#include "Collider.h"
#include "Trigger.h"
#include "Unit.h"

#include "AnimationMgr.h"
#include "SpriteMgr.h"
#include "TextureMgr.h"
#include "RenderMgr.h"
#include "CallBackMgr.h"

#include "Renderer.h"
#include "Animator.h"
#include "Sprite.h"
#include "Font.h"
#include "FontMgr.h"
#include "Timer.h"
#include "AniEffect.h"
#include "UI.h"
#include "InfoMgr.h"
#include "PlayerUI.h"

#include "NextStageTrigger.h"