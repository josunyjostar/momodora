// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.

#pragma once
#pragma comment(lib, "msimg32.lib") // TransparentBlit()
#pragma comment(lib, "winmm.lib")	// ���� ���
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN         // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C�� ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <map>
#include <queue>
#include <stack>
#include <typeinfo>
#include <ctime>
#include <cmath>
#include <atlimage.h>	//[MFC : CCImage]

//#include "vld.h"

//XXX: Header ���� ���� ����
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