#pragma once

#define MESSAGE_BOX(ErrorName, Function)			\
MessageBox(g_hWnd, ErrorName, Function, MB_OK);		\
DestroyWindow(g_hWnd);								\
exit(0);

#define MESSAGE_BOX_NOEXIT(ErrorName, Function)	    \
MessageBox(g_hWnd, ErrorName, Function, MB_OK);		\

#define DECLARE_SINGLETON(ClassName)			\
public:											\
	static ClassName* GetInstance()				\
	{											\
		if (m_pInstance == nullptr)				\
			m_pInstance = new ClassName;		\
												\
		return m_pInstance;						\
	}											\
												\
	void DestroyInstance()						\
	{											\
		if (m_pInstance)						\
		{										\
			delete m_pInstance;					\
			m_pInstance = nullptr;				\
		}										\
	}											\
												\
private:										\
	static ClassName* m_pInstance;				\

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;
