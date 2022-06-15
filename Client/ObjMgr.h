#pragma once

class Obj;
class LifeObj;

class ObjMgr
{
	DECLARE_SINGLETON(ObjMgr);

private:
	ObjMgr();
	~ObjMgr();

public:
	Obj* GetObj(const OBJ_ID objID) const { return mObjSpace[objID].front(); }
	Obj* GetEffectObj(const int type);
	Obj* GetUIObj( const int type);
	const list<Obj*>& GetObjSpace(const OBJ_ID objID) const { return mObjSpace[objID]; }
public:
	void AddObject(const OBJ_ID objID, Obj* pObj);
	void Update();
	void Render();
	void Collision();
	void Release();

public:
	void DeleteObj(int objID);
	void DeleteSelectObj(Obj* pObj, int objID);

public:
	list<Obj*> mObjSpace[OBJ_END];
	list<Obj*> mObjSortSpace;
};

