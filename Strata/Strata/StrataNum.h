#ifndef _CSTRATANUM_H
#define _CSTRATANUM_H
#include <vector>
#include <unordered_set>

//#include <unordered_map>
#define  SAFEDELETE(p) if(p){delete p;p=NULL;}
#define  SAFEDELETEARRAY(p) if(p){delete []p;p=NULL;}
struct GroupNum   //ÿ�������е���
{
	WORD wDownNum;   //�����²�
	WORD wUpNum;			//�����ϲ�

};

struct SStep   //��¼ÿ���ƶ��Ĺ켣
{
	WORD wIndex;		//�ƶ��������� 0 �� 1�� 2 ��
	BYTE		bType;		//���͡���ʾ�л�����
	int		nColor;		//ÿ���ƶ�����ɫ
};
class CStrataNum
{
public:
	CStrataNum(void);
	~CStrataNum(void);
	CStrataNum(WORD num,WORD wSNum);//��ϸ������Լ���ɫ����


	bool StartFromFile(const char *filename);
	void InitInputNum();

	bool BFillRow(WORD wRowIndex,BYTE bType);//�ܷ��������,�����л��߼�����
	bool FillRowNum(WORD wRowIndex,BYTE bType,WORD wNum);//����������е�ֵ
	void SetWinNumArray();//����ʤ������
	void SetSelectNum(WORD wSNum);//���ÿ���ѡ���������
	int GetRowAndColNum(WORD wRowIndex,WORD wColIndex);//��ȡ���ʱ����ֱ�ӽ������,����ʤ��ʱ������Ҫ�����,����������
	int GetRowAndColnmColor(WORD wIndex,BYTE bType);//��ȡ���ʱ����ֱ�ӽ������
	bool GetIsWin();//�Ƿ�ʤ��ֹͣ
	void PrintWinStep();//����
protected:
	WORD m_ColNum;	//��������
	int  *m_nComboNumsrc;//ԭ��
	GroupNum *m_groupNumArray;  //��������
	WORD  *m_wWinNumArray;  //ʤ����Ҫ������
	WORD  *m_wSelectNum;//����ʹ�õ��������ǲ�������ɫ
	WORD m_wSelectCount;//����ѡ��Ĳ���������
	WORD m_wIndexRow; //��ǰ���㵽�ڼ���
	WORD m_wIndexColumn; //��ǰ���㵽�ڼ���
	SStep	*m_pStep;	//�ƶ�����
	LONG64 m_lStartTime;
	int	m_nComboCounts;	//�ܹ�����ϸ���
	DWORD m_dCurentFindIndex;	//��ǰ���ҵ�������
	DWORD m_dCurentListIndex;	//���ڱ�����list���Ѿ����ҹ�������

	std::vector<SStep*> m_vStep;//�ƶ�����
	std::vector<LONG64> m_vComboNum;//��ϵ���
	std::list<LONG64> m_listComboNum; //�����Ѿ����ҵ�����
	std::list<std::string> m_listComboNumString; //�����Ѿ����ҵ�����

	typedef::std::unordered_map<std::string ,LONG64>	unstringmap;
	unstringmap m_unmapchar;// �ַ�����ʽ����

	typedef::std::unordered_set<std::string > unstringset;
	unstringset m_unsetchar; //�����洢���в��ҵ��Ľ��
	unstringset m_unsetcharfound; //�����洢�����Ѿ����ҹ��Ľ������Ϊunordered_set ���ǰ���˳����
	

	std::string m_cstranum;
	std::string m_cstrlastcomnum;  //���һ�μ������

	std::vector<std::string> m_vChar;// �ַ�����ʽ����

	std::vector<std::string> m_vFindnum;//ÿ�β��ҵ������֡�������
	
	//std::unordered_map<std::string ,LONG64> m_unmapchar;	
	
	char	*m_cstratanum;//ԭ������

	std::unordered_map<LONG64,LONG64> m_unmap;


	int GetIndexArrayNum(WORD wIndex,BYTE bType);//��ȡ��ǰ�����µ���ֵ 0,Down 1 Up
	int GetIndexArrayNum(WORD wIndex);//��ȡ��ǰ�����µ���ֵ
	int SetIndexArrayNum(WORD wIndex,WORD wNum);//����ǰ�����µ���ֵ
	void ClearNumArray();//�������

	bool NumBerCoverToArray(LONG64 nNumber);//����ת��������
	LONG64 ArrayCoverToNumBer();//����ת��������
	void CombinationNum();//������
	void CombinationNumString();//������
	bool bCheckRepet(LONG64 lnum);//�Ƿ��Ѿ��ظ�
	bool bCheckRepetString(std::string strnum);//�Ƿ��Ѿ��ظ��ַ���

	void BeginComNum(); //��ʼ�������
	void FindNumString(std::string  strstring); //��ʼ�������
	WORD GetNumBerCount(LONG64 nNum);//��ȡ����λ��

	void PrintNumArray();

	int BeginCalculate(WORD wRowIndex,BYTE bRowType,WORD wColumnIndex,BYTE bColType);
	bool CheckRowColum(WORD wCheckIndex,BYTE bType);//�������
	void ReleaseStep();

	int BeginCalculate();
	int BeginCalculateString();

	int BeginCalculateNum();
	int BeginCalculateNum(const std::string strnum);
// 	WORD  
// 	WORD *m_IndexColumnManager;//������������,���ڴ洢��ǰ���������

};
#endif
