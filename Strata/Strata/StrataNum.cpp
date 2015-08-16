#include "StdAfx.h"
#include "StrataNum.h"
#include <math.h>
#include <string>
#include < fstream>
#include <sstream>
#include <strstream>
#define MAX_FIND_NUM	100		//每次最大查找数量
//WORD g_WinNumArray[] = {3,3,1,2,3,0,3,1,2,3,3,2,1,2,2,3,1,0,2,1,3,2,1,0,2};
//WORD g_WinNumArray[] = {1,2,2,1,2,0,2,1,1,2,1,1,2,0,2,0};
//WORD g_WinNumArray[] = {2,2,0,2,1,0,1,3,2,2,0,3,3,3,3,0};
//WORD g_WinNumArray[] = {2,1,1,2,3,1,3,0,3};
WORD *g_WinNumArray = NULL;
CStrataNum::CStrataNum(void)
{
	StartFromFile("num.txt");
	return;
	int nNum = 0;
	printf("InPutNum:");
	scanf("%d",&nNum);
	if (nNum <= 0)
	{
		return;
	}
	g_WinNumArray = new WORD[nNum * nNum];
	if (g_WinNumArray)
	{
		for(int i = 0;i<nNum;i++)
		{
			int nIndex = 0;
			nIndex = i * nNum;
			if (nNum == 3)
			{
				printf("InPutWinArray:");
				scanf("%d%d%d",&g_WinNumArray[nIndex],&g_WinNumArray[nIndex + 1],&g_WinNumArray[nIndex + 2]);
			}
			else if (nNum ==4)
			{
				printf("InPutWinArray:");
				scanf("%d%d%d%d",&g_WinNumArray[nIndex],&g_WinNumArray[nIndex + 1],&g_WinNumArray[nIndex + 2],&g_WinNumArray[nIndex + 3]);
			}
			if (nNum == 5)
			{
				printf("InPutWinArray:");
				scanf("%d%d%d%d%d",&g_WinNumArray[nIndex],&g_WinNumArray[nIndex + 1],&g_WinNumArray[nIndex + 2],&g_WinNumArray[nIndex + 3],&g_WinNumArray[nIndex + 4]);
			}
		}
	}

	WORD wColornum = 0;		//查找颜色数量
	for(int i = 0;i<nNum * nNum;i++)
	{
		if (g_WinNumArray[i] > wColornum)
		{
			wColornum = g_WinNumArray[i];
		}
	}



	CStrataNum(nNum,wColornum);

// 	for(int i = 0;i<nNum;i++)
// 	{
// 		int nIndex = 0;
// 		nIndex = i * nNum;
// 		printf("%d %d %d \r\n",wWinArray[nIndex],wWinArray[nIndex + 1],wWinArray[nIndex + 2]);
// 	}
}

CStrataNum::CStrataNum( WORD num,WORD wSNum )
{
	m_ColNum = num;
	m_groupNumArray = new GroupNum[m_ColNum*m_ColNum];
	memset(m_groupNumArray,0,sizeof(GroupNum)*m_ColNum*m_ColNum);

	m_wSelectCount = wSNum;
	m_wSelectNum = new WORD[wSNum];
	for (int i = 0;i<wSNum;i++)
	{
		m_wSelectNum[i] = i+1;
	}

	m_wIndexRow = m_wIndexColumn = 0;
	m_dCurentFindIndex = m_dCurentListIndex = 0;

	m_nComboNumsrc = new int[num * 2];
	for(int i = 0;i<m_ColNum * 2 ;i++)
	{
		m_nComboNumsrc[i] = i;
	}
	m_nComboCounts = 1;
	for(int i = m_ColNum * 2;i > 0 ;i--)
	{
		m_nComboCounts *= i;
	}

	char 	bstart = 'a';
	for(int i = 0;i<m_ColNum * 2 ;i++)
	{
		m_cstranum.append(sizeof(char),bstart);
		bstart++;
	}

	//CombinationNum();
	CombinationNumString();

}


CStrataNum::~CStrataNum(void)
{
	if (m_groupNumArray)
	{
		delete []m_groupNumArray;
		m_groupNumArray = NULL;
	}

	SAFEDELETEARRAY(m_nComboNumsrc);

// 	if (m_pStep)
// 	{
// 		delete []m_pStep;
// 		m_pStep = NULL;
// 	}
}

int CStrataNum::BeginCalculate()
{
	DWORD dtempnum = 0;
	m_listComboNum.clear();
	for (std::unordered_map<LONG64,LONG64>::iterator itert = m_unmap.begin();itert != m_unmap.end();itert ++)
	{
		if (dtempnum >= m_dCurentFindIndex)
		{
			LONG64 nCnum = itert->second;
			m_listComboNum.push_back(nCnum);
		}
		dtempnum++;
	}
	m_dCurentFindIndex += m_listComboNum.size();
	for(std::list<LONG64>::iterator itrt = m_listComboNum.begin();itrt != m_listComboNum.end();itrt++)
	{
		LONG64 nCnum = *itrt;
		if (NumBerCoverToArray(nCnum))
		{
			if (BeginCalculateNum() == 1)
			{
				return 1;
			}
		}
	}


// 	printf(" \r\n");
// 	printf("CombinationNum Ok  NUM:%d ,TIME :%d ",m_unmap.size(),m_lStartTime);
// 	system("pause");
// 	if (BeginCalculate(m_wIndexRow,0,m_wIndexColumn,1) == 0 )
// 	{
// 		m_wIndexRow = m_wIndexRow = 0;
// 		ClearNumArray();//清空重新计算
// 		BeginCalculate(m_wIndexColumn,1,m_wIndexRow,0);
// 	}
	

// 	BYTE bColorIndex = 0;
// 	while (1)
// 	{
// 			for(int j = 0;j<m_ColNum;j++)
// 			{
// 				int wcolor = GetRowAndColNum(m_wIndexRow,m_wIndexColumn);
// 				if (wcolor < 0 )
// 				{
// 					printf("GetColor Faile  In : %d   : %d ",m_wIndexRow,m_wIndexColumn );
// 					break;
// 				}
// 
// 				if (FillRowNum(m_wIndexRow,0,wcolor))
// 				{
// 					FillRowNum(m_wIndexColumn,1,wcolor);
// 					m_wIndexRow ++;
// 					m_wIndexColumn++;
// 
// 					m_wIndexRow %= m_ColNum ;
// 					m_wIndexColumn %= m_ColNum ;
// 				}
// 				//PrintNumArray();
// 			}
// 
// 			if (GetIsWin())
// 			{
// 				printf("Win Stop");
// 				break;
// 			}
// 			PrintNumArray();
// 			ClearNumArray();//清空重新计算
// 
// 			bColorIndex++;
// 			if (bColorIndex %m_ColNum == 0)
// 			{
// 				m_wIndexRow ++;
// 			}
// 			m_wIndexColumn  = bColorIndex %m_ColNum;
// 
// 			if (bColorIndex >= m_ColNum * m_ColNum)
// 			{
// 				break;
// 			}
// 	}
	return 0;
}

int CStrataNum::BeginCalculate( WORD wRowIndex,BYTE bRowType,WORD wColumnIndex,BYTE bColType )
{
	BYTE bColorIndex = 0;
	while (1)
	{
		for(int j = 0;j<m_ColNum;j++)
		{
			int  wcolor =GetRowAndColnmColor(wRowIndex,bRowType);

			if ( wcolor < 0 )
			{
				printf("GetColor Faile  In : %d   : %d ",wRowIndex,wColumnIndex );
				break;
			}

			if (FillRowNum(wRowIndex,bRowType,wcolor))
			{
				if (!CheckRowColum(wRowIndex,bRowType))
				{
					break;
				}

				SStep	*pRowStep  = new SStep;
				pRowStep->bType = bRowType;
				pRowStep->nColor = wcolor;
				pRowStep->wIndex = wRowIndex;
				m_vStep.push_back(pRowStep);

				wcolor =GetRowAndColnmColor(wColumnIndex,bColType);
				FillRowNum(wColumnIndex,bColType,wcolor);

				if (!CheckRowColum(wColumnIndex,bColType))
				{
					break;
				}

				SStep	*pColumnStep  = new SStep;
				pColumnStep->bType = bColType;
				pColumnStep->nColor = wcolor;
				pColumnStep->wIndex = wColumnIndex;
				m_vStep.push_back(pColumnStep);

				wRowIndex ++;
				wColumnIndex++;

				wRowIndex %= m_ColNum ;
				wColumnIndex %= m_ColNum ;

	
			}
			system("cls");
			PrintNumArray();
			//PrintNumArray();
		}

		if (GetIsWin())
		{
			system("cls");
			printf("Win Stop \r\n");
			PrintWinStep();
			return 1;
		}
		system("cls");
		PrintNumArray();
		ClearNumArray();//清空重新计算
		ReleaseStep();

		bColorIndex++;

		wRowIndex = bColorIndex / m_ColNum;

// 		if (bColorIndex %m_ColNum == 0)
// 		{
// 			wRowIndex ++;
// 		}
		wColumnIndex  = bColorIndex %m_ColNum;

		if (bColorIndex >= m_ColNum * m_ColNum)
		{
			break;
		}
	}
	return 0;
}

int CStrataNum::GetIndexArrayNum( WORD wIndex,BYTE bType )
{
	if (wIndex < m_ColNum*m_ColNum)
	{
		if (bType == 0)
		{
			return m_groupNumArray[wIndex].wDownNum;
		}
		else
		{
			return m_groupNumArray[wIndex].wUpNum;
		}
	}
	return -1;
}

int CStrataNum::GetIndexArrayNum( WORD wIndex )
{
	if (wIndex < m_ColNum*m_ColNum)
	{
		if (m_groupNumArray[wIndex].wUpNum == 0 )
		{
			return m_groupNumArray[wIndex].wDownNum;
		}
		else
		{
			return m_groupNumArray[wIndex].wUpNum;
		}
	}
	return -1;
}

bool CStrataNum::BFillRow( WORD wRowIndex,BYTE bType )
{
	WORD *nTemp = new WORD[m_ColNum];
	memset(nTemp,0,sizeof(WORD)*m_ColNum);
	bool bfill = true;
	if (bType == 0) //行，顺序相加
	{
		for(int i = 0;i<m_ColNum;i++)
		{
			nTemp[i] = GetIndexArrayNum(wRowIndex);
			wRowIndex ++;
		}
	}
	else if (bType == 1 ) //列，叠加
	{
		for(int i = 0;i<m_ColNum;i++)
		{
			nTemp[i] = GetIndexArrayNum(wRowIndex);
			wRowIndex += m_ColNum;
		}
	}

	for(int i = 0;i<m_ColNum;i++)
	{
		for(int j = 0;j<m_ColNum;j++)
		{
			if (nTemp[i] > 0 && nTemp[j] > 0)
			{
				if (nTemp[i] != nTemp[j])
				{
					bfill = false;
					break;
				}
			}
		}
	}

	delete nTemp;
	nTemp = NULL;
	return bfill;
}

bool CStrataNum::FillRowNum( WORD wRowIndex,BYTE bType,WORD wNum )
{
	if (bType == 0) //行
	{
		wRowIndex *= m_ColNum;
	}

	for(int i = 0;i<m_ColNum;i++)
	{
		
		if (SetIndexArrayNum(wRowIndex,wNum) < 0)
		{
			return false;
		}
		
		if (bType == 0) //行，顺序相加
		{
			wRowIndex ++;
		}
		else if (bType == 1)	//列，叠加
		{
			wRowIndex += m_ColNum;
		}
		else
		{
			return false;
		}
	}
	return true;
}

int CStrataNum::SetIndexArrayNum( WORD wIndex,WORD wNum )
{
	if (wIndex < m_ColNum*m_ColNum)
	{
		if (m_groupNumArray[wIndex].wDownNum == 0)
		{
			m_groupNumArray[wIndex].wDownNum = wNum;
			return 1;
		}
		else if (m_groupNumArray[wIndex].wUpNum == 0)
		{
			m_groupNumArray[wIndex].wUpNum = wNum;
			return 1;
		}
	}
	return -1;
}

void CStrataNum::SetWinNumArray()
{
	
}

void CStrataNum::SetSelectNum( WORD wSNum )
{
	m_wSelectCount = wSNum;
	m_wSelectNum = new WORD[wSNum];
	for (int i = 0;i<wSNum;i++)
	{
		m_wSelectNum[i] = i+1;
	}
}

int CStrataNum::GetRowAndColNum( WORD wRowIndex,WORD wColIndex ) //行数与列数
{
	int iNum = -1;
	wRowIndex *= m_ColNum;

	WORD *wRowArray = new WORD[m_ColNum];
	WORD *wColArray = new WORD[m_ColNum];
	if (wRowIndex < m_ColNum*m_ColNum && wColIndex < m_ColNum * m_ColNum)
	{
		for(int i = 0;i < m_ColNum;i++)
		{
			wRowArray[i] = wRowIndex;
			wRowIndex++;
			wColArray[i] = wColIndex;
			wColIndex += m_ColNum;
		}
		for(int i = 0;i < m_ColNum;i++)
		{
			for(int j = 0;j < m_ColNum;j++)
			{
				if (wRowArray[i] == wColArray[j])
				{
					iNum = g_WinNumArray[wRowArray[i]];
					break; 
				}
			}
		}
	}
	delete []wRowArray;
	wRowArray = NULL;
	delete []wColArray;
	wColArray = NULL;
	return iNum;
}

bool CStrataNum::GetIsWin()
{
	for (int i= 0;i<m_ColNum*m_ColNum;i++)
	{
		int iarraynum = GetIndexArrayNum(i,1);
		if (iarraynum >= 0 )
		{
			if (g_WinNumArray[i] >0 && g_WinNumArray[i] !=iarraynum)
			{
				return false;
			}
		}
	}
	return true;
}

void CStrataNum::ClearNumArray()
{
	for (int i= 0;i<m_ColNum*m_ColNum;i++)
	{
		m_groupNumArray[i].wDownNum = m_groupNumArray[i].wUpNum = 0;
	}
}

void CStrataNum::PrintNumArray()
{
	char pnumstr[200]={};
	for (int i= 0;i<m_ColNum*m_ColNum;i+=m_ColNum)
	{
		char pstr[50] = {};
		sprintf(pstr,"%d   %d   %d  ",GetIndexArrayNum(i),GetIndexArrayNum(i+1),GetIndexArrayNum(i+2));
		strcat(pnumstr,pstr);
		strcat(pnumstr,"\r\n");
	}
	printf(pnumstr);

}

bool CStrataNum::CheckRowColum( WORD wCheckIndex,BYTE bType )
{
	if (bType == 0) //行
	{
		wCheckIndex *= m_ColNum;
	}
	if (bType == 0 )
	{
		 for (int i = wCheckIndex;i<wCheckIndex + m_ColNum;i++)
		 {
			 if (g_WinNumArray[i] >0 && GetIndexArrayNum(i,1) > 0 )//上层已经有值
			 {
				 if (g_WinNumArray[i] !=  GetIndexArrayNum(i,1))
				 {
					 return false;
				 }
			 }
		 }
	}
	else if (bType == 1)
	{
		for (int i = wCheckIndex;i<m_ColNum * m_ColNum;i+= m_ColNum)
		{
			if (g_WinNumArray[i] >0 && GetIndexArrayNum(i,1) > 0 )//上层已经有值
			{
				if (g_WinNumArray[i] !=  GetIndexArrayNum(i,1))
				{
					return false;
				}
			}
		}
	}
	return true;
}

int CStrataNum::GetRowAndColnmColor( WORD wIndex,BYTE bType )//获取填充时行列直接交叉的数
{
	if (wIndex >= m_ColNum)
	{
		return -1;
	}

	if (bType == 0 ) //行
	{
		wIndex *= m_ColNum;
	}

	if (bType == 0 )
	{
		for (int i =wIndex;i<wIndex +m_ColNum;i++ )
		{
			if (g_WinNumArray[i]>0&&GetIndexArrayNum(i,0))
			{
				return g_WinNumArray[i];
			}
		}
	}
	else if (bType == 1)
	{
		for (int i = wIndex;i<m_ColNum * m_ColNum;i+= m_ColNum)
		{
			if (g_WinNumArray[i]>0&&GetIndexArrayNum(i,0))
			{
				return  g_WinNumArray[i];
			}
		}
	}
	return 1;
}

void CStrataNum::ReleaseStep()
{
	for(std::vector<SStep*>::iterator itr = m_vStep.begin();itr != m_vStep.end();itr++)
	{
		SStep* pstep = *itr;
		SAFEDELETE(pstep);
	}
	m_vStep.clear();
}

void CStrataNum::PrintWinStep()
{
	printf("InPutNumArray:  \r\n");
	for(int i = 0;i<m_ColNum*m_ColNum ;i++)
	{
		printf("%d \t",g_WinNumArray[i]);
		if (i > 0 && (i + 1) % m_ColNum == 0)
		{
			printf(" \r\n");
		}
	}
	printf(" \r\n");
	char pnumstr[800]={};
	for(std::vector<SStep*>::iterator itr = m_vStep.begin();itr != m_vStep.end();itr++)
	{
		SStep* pstep = *itr;
		if (pstep)
		{
			char pstr[50] = {};
			if (pstep->bType == 0)
			{
				sprintf(pstr,"TYPE: ---- Index: %d  Color: %d    \r\n",pstep->wIndex,pstep->nColor);
			}
			else
			{
				sprintf(pstr,"TYPE:   |  Index: %d  Color: %d     \r\n",pstep->wIndex,pstep->nColor);
			}
			//sprintf(pstr,"TYPE: %d   Color: %d  Index: %d   \r\n",pstep->bType,pstep->nColor,pstep->wIndex);
			strcat(pnumstr,pstr);
		}
	}
	printf(pnumstr);
}


bool CStrataNum::NumBerCoverToArray( LONG64 nNumber )
{
	LONG64 ltemp = nNumber;
	WORD wArrayIndex = 0;// 数组索引

	while(1)
	{
		if (nNumber / 10 > 0)
		{
			WORD wonenum = nNumber % 10;
			if (wArrayIndex < m_ColNum * 2)
			{
				m_nComboNumsrc[wArrayIndex] = wonenum;
			}
			nNumber /= 10;
			wArrayIndex++;
		}
		else
		{
			m_nComboNumsrc[wArrayIndex] = nNumber;
			wArrayIndex++;
			break;
		}
	}
	if (wArrayIndex != m_ColNum * 2)
	{
		WORD ncount = GetNumBerCount(ltemp);
		if (ncount == m_ColNum * 2 - 1 && wArrayIndex == ncount)
		{
			m_nComboNumsrc[wArrayIndex] = 0;
			return true;
		}
		else
		{
			printf("NumBerCoverToArray Error At %d ",wArrayIndex);
			return false;
		}
	}

	return true;
}

LONG64 CStrataNum::ArrayCoverToNumBer()
{
	LONG64 cNum = 0;
	long double n = 10;
	for(int i = 0;i<m_ColNum*2;i++)
	{
		LONG64 nPow= pow(n,i);
		cNum += m_nComboNumsrc[i] * nPow ;
	}
	return cNum;
}

bool CStrataNum::bCheckRepet( LONG64 lnum )
{
// 	for (std::vector<LONG64>::iterator itert = m_vComboNum.begin();itert != m_vComboNum.end();itert ++)
// 	{
// 		if (lnum == *itert)
// 		{
// 			return true;
// 		}
// 	}

	std::unordered_map<LONG64,LONG64>::iterator itertmap = m_unmap.find(lnum);
	if (itertmap == m_unmap.end())
	{
		return false;
	}
	return true;
}

void CStrataNum::BeginComNum()
{
	
	for(int i = 0 ;i< m_ColNum * 2 -1 ;i++)
	{
		for(int j = i+1 ;j< m_ColNum * 2;j++)
		{
			WORD nCoverNum = m_nComboNumsrc[i];
			m_nComboNumsrc[i] = m_nComboNumsrc[j];
			m_nComboNumsrc[j] = nCoverNum;
			LONG64 nNum = ArrayCoverToNumBer();  
			if (nNum > 0)
			{
				if (!bCheckRepet(nNum))
				{
					m_unmap[nNum] = nNum;
					//m_dCurentFindIndex++;
				}
			}
			else
			{
				printf("ArrayCoverToNumBer Error");
			}
		}
	}
}

int CStrataNum::BeginCalculateNum()
{
	for(int i = 0;i<m_ColNum * 2 ;i++)
	{
		WORD nstepnum = m_nComboNumsrc[i];

		BYTE bRowType = nstepnum % 2;
		nstepnum /= 2;

		int  wcolor =GetRowAndColnmColor(nstepnum,bRowType);

		if ( wcolor < 0 )
		{
			printf("GetColor Faile  In : %d   : %d ",nstepnum );
			break;
		}

		if (FillRowNum(nstepnum,bRowType,wcolor))
		{
			if (!CheckRowColum(nstepnum,bRowType))
			{
				break;
			}

			SStep	*pRowStep  = new SStep;
			pRowStep->bType = bRowType;
			pRowStep->nColor = wcolor;
			pRowStep->wIndex = nstepnum;
			m_vStep.push_back(pRowStep);
		}
// 		system("cls");
// 		PrintNumArray();
	}

	if (GetIsWin())
	{
		system("cls");
		printf("Win Stop \r\n");
		PrintWinStep();
		return 1;
	}

// 	system("cls");
// 	PrintNumArray();
	ClearNumArray();//清空重新计算
	ReleaseStep();
	return 0;
}

int CStrataNum::BeginCalculateNum( const std::string strnum )
{
	for(int i = 0;i<m_ColNum * 2 ;i++)
	{
		char ncstrnum = strnum[i];
		WORD nstepnum = ncstrnum - 'a';
		//WORD nstepnum = m_nComboNumsrc[i];

		BYTE bRowType = nstepnum % 2;
		nstepnum /= 2;

		int  wcolor =GetRowAndColnmColor(nstepnum,bRowType);

		if ( wcolor < 0 )
		{
			printf("GetColor Faile  In : %d   : %d ",nstepnum );
			break;
		}

		if (FillRowNum(nstepnum,bRowType,wcolor))
		{
			if (!CheckRowColum(nstepnum,bRowType))
			{
				break;
			}

			SStep	*pRowStep  = new SStep;
			pRowStep->bType = bRowType;
			pRowStep->nColor = wcolor;
			pRowStep->wIndex = nstepnum;
			m_vStep.push_back(pRowStep);
		}
		// 		system("cls");
		// 		PrintNumArray();
	}

	if (GetIsWin())
	{
		system("cls");
		printf("Win Stop \r\n");
		PrintWinStep();
		return 1;
	}

	// 	system("cls");
	// 	PrintNumArray();
	ClearNumArray();//清空重新计算
	ReleaseStep();
	return 0;
}

WORD CStrataNum::GetNumBerCount( LONG64 nNum )
{
	WORD wCount = 1;
	while(1)
	{
		if (nNum / 10 > 0)
		{
			nNum /= 10;
			wCount ++;
		}
		else
		{
			break;
		}
	}
	return wCount;
}

void CStrataNum::FindNumString(std::string  strstring)
{
	for(int i = 0 ;i< m_ColNum * 2 -1 ;i++)
	{
		for(int j = i+1 ;j< m_ColNum * 2;j++)
		{
			char nCoverNum =strstring[i];
			strstring[i] = strstring[j];
			strstring[j] = nCoverNum;
			if (!bCheckRepetString(strstring))
			{
				m_unsetchar.insert(strstring);
				m_vFindnum.push_back(strstring);
			}
// 			std::pair<std::unordered_set<std::string>::iterator,bool>mapinsert = m_unsetchar.insert(m_cstranum);
// 			if (mapinsert.second)
// 			{
// 				m_vFindnum.push_back(m_cstranum);
// 			}
		}
	}
	return;
}

bool CStrataNum::bCheckRepetString( std::string strnum )
{
	unstringset::iterator iterset = m_unsetchar.find(strnum);
	if (iterset == m_unsetchar.end())
	{
		return false;
	}

// 	unstringmap::iterator itertmap = m_unmapchar.find(strnum);
// 	if (itertmap == m_unmapchar.end())
// 	{
// 		return false;
// 	}
	return true;
}

void CStrataNum::CombinationNumString()
{
	//m_unmapchar.insert(unstringmap::value_type(m_cstranum,GetTickCount64()));
	bool bIsWin = false;
	m_lStartTime = GetTickCount64();

	FindNumString(m_cstranum);
	if (BeginCalculateString() == 0)
	{
		std::vector<std::string> vTempNum;
		while(1)
		{
			vTempNum = m_vFindnum;
			m_vFindnum.clear();
			for (std::vector<std::string>::iterator itert = vTempNum.begin();itert != vTempNum.end();itert ++) //每次查找仅需要查找新查找的数字
			{
				//m_cstranum = *itert;
				FindNumString(*itert);
			}

			if (BeginCalculateString() == 1)
			{
				bIsWin = true;
				break;
			}

			if (m_vFindnum.size() == 0)
			{
				printf("not found new num \n");
				break;
			}

		}
	}
	m_lStartTime = (GetTickCount64()-m_lStartTime)/1000;
	if (bIsWin)
	{
		printf("CombinationNum Ok  NUM:%d ,TIME :%d  \r\n",m_unsetchar.size(),m_lStartTime);
	}
	
	//CStrataNum::CStrataNum();
}

int CStrataNum::BeginCalculateString()
{
	SIZE_T n =0;
	DWORD dtempnum = 0;
	for (std::vector<std::string>::iterator itert = m_vFindnum.begin();itert != m_vFindnum.end();itert ++)
	{
		unstringset::iterator iterset = m_unsetcharfound.find(*itert);
		if (iterset == m_unsetcharfound.end())
		{
			m_unsetcharfound.insert(*itert);
			if (BeginCalculateNum(*itert) == 1)
			{
				return 1;
			}
		}
	}
	m_dCurentFindIndex = m_unsetcharfound.size();
	//m_listComboNumString.clear(); //没有找到。清楚队列，重新开始插入
	printf(" Found  %d number \r\n",m_dCurentFindIndex);


// 	if (m_listComboNumString.size() >= MAX_FIND_NUM)
// 	{
// 		for(std::list<std::string>::iterator itrt = m_listComboNumString.begin();itrt != m_listComboNumString.end();itrt++)
// 		{
// 			std::string strnum =*itrt;
// 			if (BeginCalculateNum(strnum) == 1)
// 			{
// 				return 1;
// 			}
// 		}
// 		m_dCurentFindIndex = m_unsetcharfound.size();
// 		m_listComboNumString.clear(); //没有找到。清楚队列，重新开始插入
// 		printf(" Found  %d number \r\n",m_dCurentFindIndex);
// 	}

	return 0;
}

bool CStrataNum::StartFromFile( const char *filename )
{
	std::ifstream infile(filename);
	BYTE  bline = 0;
	while(!infile.eof())
	{
		char str[100]={};
		infile.getline(str,100);
		if (str[0] == 0)
		{
			break;
		}
	//	printf("%s \n",str);
		std::strstream  sstream(str,100);
		DWORD temp = 0;
		if (bline == 0)
		{
			m_ColNum = 0;
			m_ColNum	= ((sstream >> temp), temp);temp = 0;
			g_WinNumArray = new WORD[m_ColNum * m_ColNum];
		}
		else
		{
			int start = (bline - 1)* m_ColNum;
			int send =start + m_ColNum;
			for(int i = start;i < send;i++)
			{
				g_WinNumArray[i] = ((sstream >> temp), temp);temp = 0;
			}
		}
		bline++;
	}
	infile.close();
	WORD wColornum = 0;		//查找颜色数量
	for(int i = 0;i<m_ColNum * m_ColNum;i++)
	{
		if (g_WinNumArray[i] > wColornum)
		{
			wColornum = g_WinNumArray[i];
		}
	}
	CStrataNum(m_ColNum,wColornum);
	return true;
}
