#pragma once
class EnemyMgr
{
	DECLARE_SINGLETON(EnemyMgr);
private:
	EnemyMgr();
	virtual ~EnemyMgr();

public:
	void Initialize(const TCHAR* pFilePath, Obj* pPlayer);
	void LoadData(const TCHAR * pFilePath);

public:
	void SetInfo(int type, ATTRIBUTE& attribute);
public:
	void SetEnemyInit(const bool bEnemyInit) { m_bEnemeyInit = bEnemyInit; }
	bool GetEnemyInit() const { return m_bEnemeyInit; }
private:
	void Release();

private:
	Obj* m_pPlayer = nullptr;

private:
	bool m_bEnemeyInit = false;


};

