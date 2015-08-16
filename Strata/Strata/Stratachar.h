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
	void CombinationNum();//计算最多组合

protected:
	//std::unordered_map<std::string,LONG64> m_unmapchar;
	std::vector<std::string> m_vChar;//
	std::string m_strChar;
	char	*m_cstratanum;//原数数字
	WORD	m_ColNum;//行数
	 int ArrayCoverToString(std::string &strnum);
	 int StringCoverToArray(const std::string &strnum);
	 bool bCheckRepet(const std::string &strnum);
	 void AddStringTo(std::string str);
	 	bool GetIsWin();//是否胜利停止
};
#endif
