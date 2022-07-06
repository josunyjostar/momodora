#ifndef MathLib_h__
#define MathLib_h__

inline int CALL_CONV Sqr(const int& _param)
{
	return _param << 2;
}

inline float CALL_CONV D2R(const float& _Degree)
{
	return _Degree / 180.f * PI;
}

inline float CALL_CONV R2D(const float& _Radian)
{
	return _Radian / PI * 180.f;
}

inline float CALL_CONV V2R(const tVector& _Vec)
{
	return atan2(_Vec.y,_Vec.x);
}

inline float CALL_CONV V2D(const tVector& _Vec)
{
	return R2D(V2R(_Vec));
}

// UV == Unit Vector
inline tVector R2UV(const float& _Rad) 
{
	return tVector(cosf(_Rad),sinf(_Rad));
}

inline tVector CALL_CONV D2UV(const float& _Degree)
{
	return R2UV(D2R(_Degree));
}

inline tVector CALL_CONV GetVector(const tPos& _from, const tPos& _to)
{
	return _to-_from;
}

inline float CALL_CONV Dot(const tVector& _Vec1,const tVector& _Vec2)
{
	return _Vec1.x*_Vec2.x+_Vec1.y*_Vec2.y; 
}

inline float Cross(const tVector& _Vec1, const tVector& _Vec2)
{
	return _Vec1.x*_Vec2.y - _Vec1.y*_Vec2.x;
}


//cos theta가 결과값
inline float CALL_CONV DotToCosTheta(const tVector& _Vec1,const tVector& _Vec2)
{
	tVector v1 = R2UV(V2R(_Vec1));
	tVector v2 = R2UV(V2R(_Vec2));

	return v1.x*v2.x+v1.y*v2.y; 
}

inline float CALL_CONV sqrDistance(const tPos& _Pos1,const tPos& _Pos2)
{
	return SQR(_Pos1.x-_Pos2.x)+SQR(_Pos1.y-_Pos2.y);
}

inline float CALL_CONV Distance(const tPos& _Pos1,const tPos& _Pos2)
{
	return sqrt(sqrDistance(_Pos1,_Pos2));
}

inline float CALL_CONV sqrMagnitude(const tVector& _Vec)
{
	return SQR(_Vec.x)+SQR(_Vec.y);
}

inline float CALL_CONV Magnitude(const tVector& _Vec)
{
	return sqrt(sqrMagnitude(_Vec));
}

inline tVector CALL_CONV VectorSub(const tPos& _from,const tPos& _to)
{
	return _to-_from;
}

inline tVector CALL_CONV Vector2Line(const tPos& _from,const tPos& _to)
{
	tVector TempVec = VectorSub(_from,_to);
	if (TempVec.x < 0.f)
		TempVec.x = -TempVec.x;
	if (TempVec.y < 0.f)
		TempVec.y = -TempVec.y;

	return TempVec;
}

//XXX: 0 vector  return - 단위 방향벡터
inline tVector CALL_CONV LookAt(const tPos& _from, const tPos& _to) 
{
	tVector vec = _to-_from;

	return vec/Magnitude(vec);
}

inline tVector CALL_CONV LookAt2(const tPos& _from, const tPos& _to)
{
	tVector vec = _to-_from;

	return R2UV(V2R(vec));
}

inline tVector CALL_CONV Normalize(const tVector& _Vec)
{
	return R2UV(V2R(_Vec));
}

inline tVector CALL_CONV Normalize2(const tVector& _Vec)
{
	float mag = Magnitude(_Vec);
#ifdef _DEBUG
	if (mag == 0.f)
		MSG_BOX("Error mag == 0");
#endif
	return tVector(_Vec.x/mag,_Vec.y/mag);
}

inline bool CALL_CONV PosInRect(const tRect& _Rect,const tPos& _Pos)
{
	if (_Rect.L() > _Pos.x ||
		_Rect.R() < _Pos.x ||
		_Rect.T() > _Pos.y ||
		_Rect.B() < _Pos.y)
		return false;
	return true;
}

inline bool CALL_CONV PosInCircle(const tPos& _Center, float _Radius, const tPos& _Pos)
{
	return sqrDistance(_Center, _Pos) < (_Radius * _Radius);
}

inline bool CALL_CONV PosInCircleEx(const tPos& _Center, float _Radius, const tPos& _Pos, fRect& _ColRect)
{
	if(sqrDistance(_Center, _Pos) < (_Radius * _Radius)) 
	{
		tPos cp = LookAt(_Center, _Pos)*_Radius+_Center;

		if(cp.x >_Pos.x) 
		{
			_ColRect.l = _Pos.x;
			_ColRect.r = cp.x;
		}
		else 
		{
			_ColRect.l = cp.x;
			_ColRect.r = _Pos.x;
		}
		if(cp.y >_Pos.y) 
		{
			_ColRect.t = _Pos.y;
			_ColRect.b = cp.y;
		}
		else 
		{
			_ColRect.t = cp.y;
			_ColRect.b = _Pos.y;
		}
		return true;
	}
	return false;
}

inline bool CALL_CONV RectInRect(const tRect& _Rect1,const tRect& _Rect2)//R1이 R2안에 있는 경우
{
	if (_Rect1.L() < _Rect2.R() &&
		_Rect1.R() > _Rect2.L() &&
		_Rect1.T() < _Rect2.B() &&
		_Rect1.B() > _Rect2.T())
		return true;

	return false;
}

inline bool CALL_CONV RectInRectEx(const tRect& _Rect1, const tRect& _Rect2, fRect& _ColRect)
{
	if( _Rect1.l() < _Rect2.r() && 
		_Rect1.r() > _Rect2.l()	&&
		_Rect1.t() < _Rect2.b() && 
		_Rect1.b() > _Rect2.t()	)
	{
		_ColRect.l = MAX(_Rect1.l(),_Rect2.l());
		_ColRect.r = MIN(_Rect1.r(),_Rect2.r());
		_ColRect.t = MAX(_Rect1.t(),_Rect2.t());
		_ColRect.b = MIN(_Rect1.b(),_Rect2.b());
		return true;
	}
	return false;
}

inline bool CALL_CONV CircleInCircle(const tPos& _Center1,const float& _Radius1,const tPos& _Center2,const float& _Radius2)
{
	return sqrDistance(_Center1,_Center2) < SQR(_Radius1+_Radius2);
}

inline bool CALL_CONV CircleInCircle(const tRect& _Rect1,const tRect& _Rect2)
{
	return CircleInCircle(_Rect1.Pos(),MIN(_Rect1.cx,_Rect1.cy)*0.5f,
						  _Rect2.Pos(),MIN(_Rect2.cx,_Rect2.cy)*0.5f);
}

enum LINE_DIR {LINE_DIR_NONE, LINE_DIR_CW, LINE_DIR_CCW};

//Cross Product - 법선 방향으로 CW CCW구별 식은 determinant
inline LINE_DIR CALL_CONV GetLineDir(const tPos& _Pos1, const tPos& _Pos2, const tPos& _Pos3)
{
	float fDir = (((_Pos2.x - _Pos1.x) * (_Pos3.y - _Pos1.y)) - ((_Pos3.x - _Pos1.x) * (_Pos2.y - _Pos1.y)));

	if		(fDir > 0)	return LINE_DIR_CCW;
	else if (fDir < 0)	return LINE_DIR_CW;
	else				return LINE_DIR_NONE;
}

inline bool CALL_CONV LineInLine(const tLine& _Line1, const tLine& _Line2)
{
	if ((GetLineDir(_Line1.SP(), _Line1.EP(), _Line2.SP()) != GetLineDir(_Line1.SP(), _Line1.EP(), _Line2.EP())) &&
		(GetLineDir(_Line2.SP(), _Line2.EP(), _Line1.SP()) != GetLineDir(_Line2.SP(), _Line2.EP(), _Line1.EP())) )
		return true;
	return false;
}

inline bool CALL_CONV LineInLine(const tPos& _SP1, const tPos& _EP1, const tPos& _SP2, const tPos& _EP2)
{
	if ((GetLineDir(_SP1, _EP1, _SP2) != GetLineDir(_SP1, _EP1, _EP2)) &&
		(GetLineDir(_SP2, _EP2, _SP1) != GetLineDir(_SP2, _EP2, _EP1)) )
		return true;
	return false;
}

inline bool CALL_CONV LineInLineEx(const tLine& _Line1, const tLine& _Line2, tPos& _ColPos)
{
	float t;
	float s;

	float under = (_Line2.EP().y-_Line2.SP().y)*(_Line1.EP().x-_Line1.SP().x)-(_Line2.EP().x-_Line2.SP().x)*(_Line1.EP().y-_Line1.SP().y);

	if(under==0)
		return false;

	float _t = (_Line2.EP().x-_Line2.SP().x)*(_Line1.SP().y-_Line2.SP().y) - (_Line2.EP().y-_Line2.SP().y)*(_Line1.SP().x-_Line2.SP().x);
	float _s = (_Line1.EP().x-_Line1.SP().x)*(_Line1.SP().y-_Line2.SP().y) - (_Line1.EP().y-_Line1.SP().y)*(_Line1.SP().x-_Line2.SP().x);

	t = _t/under;
	s = _s/under;



	if(t<0.0 || t>1.0 || s<0.0 || s>1.0)
		return false;

	if(_t==0 && _s==0)
		return false;

	_ColPos.x = _Line1.SP().x + t * (_Line1.EP().x-_Line1.SP().x);
	_ColPos.y = _Line1.SP().y + t * (_Line1.EP().y-_Line1.SP().y);

	return true;
}

inline bool CALL_CONV LineInLineEx(const tPos& _SP1, const tPos& _EP1, const tPos& _SP2, const tPos& _EP2, tPos& _ColPos)
{
	//매개변수 t s는 0~1사이값 초과시 선분이 아닌 직선
	float t;
	float s;
	//under 매개변수가 되는 t s의 분모
	float common_denominator = (_EP2.y-_SP2.y)*(_EP1.x-_SP1.x)-(_EP2.x-_SP2.x)*(_EP1.y-_SP1.y);

	if(common_denominator==0) //평행선
		return false;

	//_t_s 매개변수 t의 분자
	float t_numerator = (_EP2.x-_SP2.x)*(_SP1.y-_SP2.y) - (_EP2.y-_SP2.y)*(_SP1.x-_SP2.x);
	float s_numerator = (_EP1.x-_SP1.x)*(_SP1.y-_SP2.y) - (_EP1.y-_SP1.y)*(_SP1.x-_SP2.x);

	//t s 각각 매개변수
	t = t_numerator/common_denominator; 
	s = s_numerator/common_denominator;

	//t[0~1] 0 or 1일 경우 양 끝점이 나옴
	if(t<=0.0 || t>1.0 || s<=0.0 || s>1.0)
		return false;

	//직선의 방정식 매개변수로 표현하여 교차점 구하기
	_ColPos.x = _SP2.x + s * (_EP2.x-_SP2.x);
	_ColPos.y = _SP2.y + s * (_EP2.y-_SP2.y);

	return true;
}

inline bool CALL_CONV LineInRect(const tPos& _SP, const tPos& _EP, const tRect& _Rect)
{
	if (LineInLine(_SP, _EP, _Rect.LB(), _Rect.LT()) || 
		LineInLine(_SP, _EP, _Rect.LT(), _Rect.RT()) ||
		LineInLine(_SP, _EP, _Rect.RT(), _Rect.RB()) || 
		LineInLine(_SP, _EP, _Rect.RB(), _Rect.LB()))
		return true;
	return false;
}

inline bool CALL_CONV LineInRect(const tLine& _Line, const tRect& _Rect)
{
	if (LineInLine(_Line, _Rect.LLine()) || 
		LineInLine(_Line, _Rect.TLine()) ||
		LineInLine(_Line, _Rect.RLine()) || 
		LineInLine(_Line, _Rect.BLine()))
		return true;
	return false;
}

inline bool CALL_CONV LineInRectEx(const tLine& _Line, const tRect& _Rect, fRect& _ColRect)
{
	int TrueCount = 0;
	tPos p[2];

	if(LineInLineEx(_Line, _Rect.LLine(), p[TrueCount])) 
		TrueCount++;
	if(LineInLineEx(_Line, _Rect.RLine(), p[TrueCount])) 
		TrueCount++;
	if(TrueCount==2) 
		goto TRUE_RETURN;
	if(LineInLineEx(_Line, _Rect.TLine(), p[TrueCount])) 
		TrueCount++;
	if(TrueCount==2) 
		goto TRUE_RETURN;
	if(LineInLineEx(_Line, _Rect.BLine(), p[TrueCount])) 
		TrueCount++;
	if(TrueCount==2) 
		goto TRUE_RETURN;

	if(TrueCount == 1)
	{
		if(p[0].x == _Rect.l())
		{
			_ColRect.l = p[0].x;

			if(p[0].y == _Rect.b() || p[0].y == _Rect.t())
			{
				_ColRect.r = p[0].x;
				_ColRect.t = _ColRect.b = p[0].y;
			}
			else if(_Line.cy < 0.f) // ↗
			{
				_ColRect.r = _Line.EP().x;
				_ColRect.t = _Line.EP().y;
				_ColRect.b = p[0].y;
			}
			else
			{
				_ColRect.r = _Line.EP().x;
				_ColRect.t = p[0].y;
				_ColRect.b = _Line.EP().y;
			}
		}
		else if(p[0].x == _Rect.r())
		{
			_ColRect.r = p[0].x;
			if(p[0].y == _Rect.b() || p[0].y == _Rect.t())
			{
				_ColRect.l = p[0].x;
				_ColRect.t = _ColRect.b = p[0].y;
			}
			else if(_Line.cy < 0.f)
			{
				_ColRect.l = _Line.SP().x;
				_ColRect.b = _Line.SP().y;
				_ColRect.t = p[0].y;
			}
			else
			{
				_ColRect.l = _Line.SP().x;
				_ColRect.t = _Line.SP().y;
				_ColRect.b = p[0].y;
			}
		}
		else
		{
			if(p[0].y == _Rect.t())
			{
				_ColRect.t = p[0].y;
				if(_Line.cy < 0.f)
				{
					_ColRect.b = _Line.SP().y;
					_ColRect.l = _Line.SP().x;
					_ColRect.r = p[0].x;
				}
				else
				{
					_ColRect.b = _Line.EP().y;
					_ColRect.l = p[0].x;
					_ColRect.r = _Line.EP().x;
				}
			}
			else
			{
				_ColRect.b = p[0].y;
				if(_Line.cy < 0.f)
				{
					_ColRect.t = _Line.EP().y;
					_ColRect.l = p[0].x;
					_ColRect.r = _Line.EP().x;
				}
				else
				{
					_ColRect.t = _Line.SP().y;
					_ColRect.l = _Line.SP().x;
					_ColRect.r = p[0].x;
				}
			}
		}
		return true;
	}

	return false;
TRUE_RETURN:

	if(p[0].x > p[1].x)
	{
		_ColRect.r = p[0].x;
		_ColRect.l = p[1].x;
	}
	else
	{
		_ColRect.l = p[0].x;
		_ColRect.r = p[1].x;
	}
	if(p[0].y > p[1].y)
	{
		_ColRect.b = p[0].y;
		_ColRect.t = p[1].y;
	}
	else
	{
		_ColRect.t = p[0].y;
		_ColRect.b = p[1].y;
	}

	return true;
}

inline bool CALL_CONV RectInCircle(const tRect& _Rect, const tPos& _Pos, float _Radius)
{
	float L = _Rect.l(), R = _Rect.r(), T = _Rect.t(), B = _Rect.b();
	if( L - _Radius < _Pos.x &&
		R + _Radius > _Pos.x &&
		T - _Radius < _Pos.y &&
		B + _Radius > _Pos.y )
	{
		if(L > _Pos.x && T > _Pos.y) return PosInCircle(tPos(L, T), _Radius, _Pos);
		if(R < _Pos.x && T > _Pos.y) return PosInCircle(tPos(R, T), _Radius, _Pos);
		if(L > _Pos.x && B < _Pos.y) return PosInCircle(tPos(L, B), _Radius, _Pos);
		if(R < _Pos.x && B < _Pos.y) return PosInCircle(tPos(R, B), _Radius, _Pos);
		return true;
	}
	return false;
}

inline bool CALL_CONV RectInCircle(const tRect& _Rect, const tRect& _Circle)
{
	return RectInCircle(_Rect, _Circle.Pos(), MIN(_Circle.cx, _Circle.cy)*0.5f);
}

inline bool CALL_CONV RectInCircleEx(const tRect& _Rect, const tPos& _Pos, float _Radius, fRect& _ColRect, float& _fAngle)
{
	float L = _Rect.l(), R = _Rect.r(), T = _Rect.t(), B = _Rect.b();
	if( L - _Radius < _Pos.x &&
		R + _Radius > _Pos.x &&
		T - _Radius < _Pos.y &&
		B + _Radius > _Pos.y )
	{
		if(L > _Pos.x && T > _Pos.y) {_fAngle = 225.f; return PosInCircleEx(tPos(L, T), _Radius, _Pos, _ColRect);}
		if(R < _Pos.x && T > _Pos.y) {_fAngle = 315.f; return PosInCircleEx(tPos(R, T), _Radius, _Pos, _ColRect);}
		if(L > _Pos.x && B < _Pos.y) {_fAngle = 135.f; return PosInCircleEx(tPos(L, B), _Radius, _Pos, _ColRect);}
		if(R < _Pos.x && B < _Pos.y) {_fAngle = 45.f; return PosInCircleEx(tPos(R, B), _Radius, _Pos, _ColRect);}

		_fAngle = 0.f;
		_ColRect.l = MAX(L,_Pos.x-_Radius);
		_ColRect.r = MIN(R,_Pos.x+_Radius);
		_ColRect.t = MAX(T,_Pos.y-_Radius);
		_ColRect.b = MIN(B,_Pos.y+_Radius);
		return true;
	}
	return false;
}

extern inline bool RectInCircleEx(const tRect& _Rect, const tRect& _Circle, fRect& _ColRect, float& _fAngle)
{
	return RectInCircleEx(_Rect, _Circle.Pos(), MIN(_Circle.cx, _Circle.cy)*0.5f, _ColRect, _fAngle);
}



#endif // MathLib_h__