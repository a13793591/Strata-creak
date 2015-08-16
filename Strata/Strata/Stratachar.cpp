#include "StdAfx.h"
#include "Stratachar.h"


CStratachar::CStratachar(void)
{
}

CStratachar::CStratachar( WORD num )
{
	m_ColNum = num;
	m_cstratanum = new char[num * 2];
	memset(m_cstratanum,0,sizeof(char)*num*2);
	char 	bstart = 'a';
	for(int i = 0;i<m_ColNum * 2 ;i++)
	{
		m_cstratanum[i] = bstart;
		bstart++;
	}
	CombinationNum();
}


CStratachar::~CStratachar(void)
{
}

int CStratachar::BeginCalculate()
{
	for(int i = 0 ;i< m_ColNum * 2 -1 ;i++)
	{
		for(int j = i+1 ;j< m_ColNum * 2;j++)
		{
			char nCoverNum = m_cstratanum[i];
			m_cstratanum[i] = m_cstratanum[j];
			m_cstratanum[j] = nCoverNum;
			std::string strnum;
			if (ArrayCoverToString(strnum) == 1)
			{
				if (!bCheckRepet(strnum))
				{
					m_vChar.push_back(strnum);
				}
			}
		}
	}
	return 0;
}

void CStratachar::CombinationNum()
{
	BeginCalculate();

	std::vector<std::string> vTempNum;
	bool bIsWin = false;
//	m_lStartTime = GetTickCount64();
	while(1)
	{
		SIZE_T nsize = vTempNum.size();
		SIZE_T sitersize = nsize;
		vTempNum.clear();
		for (std::vector<std::string>::iterator itert = m_vChar.begin();itert != m_vChar.end();itert ++)
		{
			if (sitersize > 0)
			{
				sitersize --;
			}
			else if (sitersize == 0)
			{
				vTempNum.push_back(*itert);
			}
		}

		for (std::vector<std::string>::iterator itert = vTempNum.begin();itert != vTempNum.end();itert ++)
		{
			std::string strsnum = *itert;
			if (StringCoverToArray(*itert))
			{
				BeginCalculate();
			}
		}

		if (bIsWin)
		{
			break;;
		}

		if (nsize + vTempNum.size() == m_vChar.size())
		{
			break;
		}
	}
}

int CStratachar::ArrayCoverToString( std::string &strnum )
{
	for(int i = 0 ;i< m_ColNum * 2  ;i++)
	{
		strnum.push_back(m_cstratanum[i]);
	}
	return 1;
}

int CStratachar::StringCoverToArray( const std::string &strnum )
{
	if (strnum.size() < m_ColNum * 2)
	{
		return 0;
	}
	for(int i = 0 ;i< m_ColNum * 2  ;i++)
	{
		m_cstratanum[i] = strnum[i];
	}
	return 1;
}

bool CStratachar::bCheckRepet( const std::string &strnum )
{
	for(std::vector<std::string>::iterator itertmap = m_vChar.begin();itertmap != m_vChar.end();itertmap ++)
	{
		if (strnum.compare(*itertmap)== 0)
		{
			return true;
		}
	}
	return false;
}

void CStratachar::AddStringTo( std::string str )
{
	m_vChar.push_back(str);
}

bool CStratachar::GetIsWin()
{
	return true;
}
