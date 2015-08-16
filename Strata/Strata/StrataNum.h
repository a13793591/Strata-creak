#ifndef _CSTRATANUM_H
#define _CSTRATANUM_H
#include <vector>
#include <unordered_set>

//#include <unordered_map>
#define  SAFEDELETE(p) if(p){delete p;p=NULL;}
#define  SAFEDELETEARRAY(p) if(p){delete []p;p=NULL;}
struct GroupNum   //每个数组中的数
{
	WORD wDownNum;   //处于下层
	WORD wUpNum;			//处于上层

};

struct SStep   //记录每次移动的轨迹
{
	WORD wIndex;		//移动的索引， 0 行 1行 2 行
	BYTE		bType;		//类型。表示行或者列
	int		nColor;		//每次移动的颜色
};
class CStrataNum
{
public:
	CStrataNum(void);
	~CStrataNum(void);
	CStrataNum(WORD num,WORD wSNum);//组合个数。以及颜色数量


	bool StartFromFile(const char *filename);
	void InitInputNum();

	bool BFillRow(WORD wRowIndex,BYTE bType);//能否填充行列,计算行或者计算列
	bool FillRowNum(WORD wRowIndex,BYTE bType,WORD wNum);//填充所在行列的值
	void SetWinNumArray();//设置胜利数组
	void SetSelectNum(WORD wSNum);//设置可以选择的数个数
	int GetRowAndColNum(WORD wRowIndex,WORD wColIndex);//获取填充时行列直接交叉的数,就是胜利时所必须要求的数,行数与列数
	int GetRowAndColnmColor(WORD wIndex,BYTE bType);//获取填充时行列直接交叉的数
	bool GetIsWin();//是否胜利停止
	void PrintWinStep();//步骤
protected:
	WORD m_ColNum;	//行数列数
	int  *m_nComboNumsrc;//原数
	GroupNum *m_groupNumArray;  //填充的数组
	WORD  *m_wWinNumArray;  //胜利需要的数组
	WORD  *m_wSelectNum;//可以使用的数。就是彩条的颜色
	WORD m_wSelectCount;//可以选择的彩条的数量
	WORD m_wIndexRow; //当前计算到第几行
	WORD m_wIndexColumn; //当前计算到第几列
	SStep	*m_pStep;	//移动序列
	LONG64 m_lStartTime;
	int	m_nComboCounts;	//总共的组合个数
	DWORD m_dCurentFindIndex;	//当前查找到的数量
	DWORD m_dCurentListIndex;	//用于保存在list中已经查找过的数量

	std::vector<SStep*> m_vStep;//移动序列
	std::vector<LONG64> m_vComboNum;//组合的数
	std::list<LONG64> m_listComboNum; //所有已经查找到的数
	std::list<std::string> m_listComboNumString; //所有已经查找到的数

	typedef::std::unordered_map<std::string ,LONG64>	unstringmap;
	unstringmap m_unmapchar;// 字符串方式储存

	typedef::std::unordered_set<std::string > unstringset;
	unstringset m_unsetchar; //用来存储所有查找到的结果
	unstringset m_unsetcharfound; //用来存储所有已经查找过的结果，因为unordered_set 不是按照顺序存放
	

	std::string m_cstranum;
	std::string m_cstrlastcomnum;  //最后一次计算的数

	std::vector<std::string> m_vChar;// 字符串方式储存

	std::vector<std::string> m_vFindnum;//每次查找到的数字。新数字
	
	//std::unordered_map<std::string ,LONG64> m_unmapchar;	
	
	char	*m_cstratanum;//原数数字

	std::unordered_map<LONG64,LONG64> m_unmap;


	int GetIndexArrayNum(WORD wIndex,BYTE bType);//获取当前索引下的数值 0,Down 1 Up
	int GetIndexArrayNum(WORD wIndex);//获取当前索引下的数值
	int SetIndexArrayNum(WORD wIndex,WORD wNum);//设置前索引下的数值
	void ClearNumArray();//清空数据

	bool NumBerCoverToArray(LONG64 nNumber);//数字转换成数组
	LONG64 ArrayCoverToNumBer();//数组转换成数子
	void CombinationNum();//最多组合
	void CombinationNumString();//最多组合
	bool bCheckRepet(LONG64 lnum);//是否已经重复
	bool bCheckRepetString(std::string strnum);//是否已经重复字符串

	void BeginComNum(); //开始计算组合
	void FindNumString(std::string  strstring); //开始计算组合
	WORD GetNumBerCount(LONG64 nNum);//获取数字位数

	void PrintNumArray();

	int BeginCalculate(WORD wRowIndex,BYTE bRowType,WORD wColumnIndex,BYTE bColType);
	bool CheckRowColum(WORD wCheckIndex,BYTE bType);//检测行列
	void ReleaseStep();

	int BeginCalculate();
	int BeginCalculateString();

	int BeginCalculateNum();
	int BeginCalculateNum(const std::string strnum);
// 	WORD  
// 	WORD *m_IndexColumnManager;//数组索引管理,用于存储当前计算的行列

};
#endif
