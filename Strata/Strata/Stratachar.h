#pragma once
#ifndef		_STRATACHAR_H_
#define		_STRATACHAR_H_

#define MAX_STRATANUM	100
class CStratachar
{
public:
	CStratachar(void);
	~CStratachar(void);
	CStratachar(WORD num);
	int BeginCalculate();
	void CombinationNum();//����������

protected:
	//std::unordered_map<std::string,LONG64> m_unmapchar;
	std::vector<std::string> m_vChar;//
	std::string m_strChar;
	char	*m_cstratanum;//ԭ������
	WORD	m_ColNum;//����
	 int ArrayCoverToString(std::string &strnum);
	 int StringCoverToArray(const std::string &strnum);
	 bool bCheckRepet(const std::string &strnum);
	 void AddStringTo(std::string str);
	 	bool GetIsWin();//�Ƿ�ʤ��ֹͣ
};
#endif
