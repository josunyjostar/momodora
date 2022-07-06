#ifndef InfoMgr_h__
#define InfoMgr_h__

class CPlayer;
class CInfoMgr : public TSingleton<CInfoMgr>
{
	friend TSingleton;
private:
	explicit CInfoMgr(void);
	virtual ~CInfoMgr(void){}
public:
	float	m_fPlayerHP;
	float	m_fPlayerMAXHP;
	float	m_fPlayerSP;
	float	m_fPlayerMAXSP;
	int		m_iCoin;
	int		m_iTime;
	bool	m_bDove;
public:
	void SaveInfo(CPlayer* pPlayer);
	void LoadInfo(CPlayer* pPlayer);
};

#endif // InfoMgr_h__
