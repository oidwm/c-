#pragma once
#include <iostream>
#include "interface.h"
using namespace std;

//商品
class Commodity
{
public:
	Commodity* Next;		//链表所需量
	Commodity()				//无参构造
	{
		No = 0;
		Name = "0";
		Price = 0;
		Discount = 0;
	}
	Commodity(int no, string name, double price, double discount)		//有参构造
	{
		No = no;
		Price = price;
		Discount = discount;
		Name = name;
	}

	int getNo() { return No; }							//获取私有变量函数
	string getName() { return Name; }
	double getPrice() { return Price; }
	double getDiscount() {return Discount;}

	void setNo(int no) { No = no; }						//设置私有变量函数
	void setName(string name) { Name = name; }
	void setPrice(double price) { Price = price; }
	void setDiscount(double discount) { Discount = discount; }

private:
	int No;
	string Name;
	double Price;
	double Discount;
};

//商品库
class CommodityList
{
public:
	int index = 0;			//库帧

	CommodityList()			//无参构造
	{
		HeadCommodity = (Commodity*)malloc(sizeof(Commodity));		//为指针开辟空间避免越界操作
		TailCommodity = (Commodity*)malloc(sizeof(Commodity));
	}

	Commodity* getHeadCommdity() { return HeadCommodity; }			//获取私有变量
	Commodity* getTailCommdity() { return TailCommodity; }

	void SetHeadCommdit(Commodity* commodity) { HeadCommodity = commodity; }		//设置私有变量
	void SetTailCommdit(Commodity* commodity) { TailCommodity = commodity; }

	void CListAdd(Commodity* com) 
	{
		bool exist = false;		//判断录入商品是否存在

		if (index==0)			//判断是否为第一个商品
		{
			HeadCommodity = com;		//将第一个商品作为链表头
			TailCommodity = com;
			index++;
			CListAddSuccess();
			Sleep(2 * 1000);
		}
		else
		{
			Commodity* p;			//防止链表头数据变动，创建p进行历遍
			p = HeadCommodity;

			while (p != NULL)
			{
				if (p->getNo() == com->getNo() || !(p->getName().compare(com->getName())))		//判断商品的编号和名称是否重复
				{
					exist = true;
					break;
				}
				p = p->Next;		//令链表移动
			}

			if (exist)			
			{
				CListAddError();
				Sleep(2 * 1000);
			}
			else
			{
				TailCommodity->Next = com;			//链表尾的移动和变化
				TailCommodity = com;
				index++;		//存入库+1
				CListAddSuccess();
				Sleep(2 * 1000);
			}
		}
	}

	//用于商品文件的读取
	void RListAdd(Commodity* com)
	{
		bool exist = false;		//判断录入商品是否存在

		if (index == 0)			//判断是否为第一个商品
		{
			HeadCommodity = com;		//将第一个商品作为链表头
			TailCommodity = com;
			index++;
		}
		else
		{
			Commodity* p;			//防止链表头数据变动，创建p进行历遍
			p = HeadCommodity;

			while (p != NULL)
			{
				if (p->getNo() == com->getNo() || !(p->getName().compare(com->getName())))		//判断商品的编号和名称是否重复
				{
					exist = true;
					break;
				}
				p = p->Next;		//令链表移动
			}

			if (exist)
			{

			}
			else
			{
				TailCommodity->Next = com;			//链表尾的移动和变化
				TailCommodity = com;
				index++;		//存入库+1
			}
		}
	}

	void CListDel(int num) 
	{
		Commodity* p;		//防止链表头数据变动，创建p进行历遍
		p = HeadCommodity;
		bool DelSuccess = false;

		if (p->getNo() == num)		//判断删除的元素是否为链表头
		{
			HeadCommodity = HeadCommodity->Next;		//将链表头进行移动
			DelSuccess = true;
		}
		else
		{
			while (p != NULL &&p->Next != NULL)		//防止越界
			{
				if (p->Next->getNo() == num)		//判断中间元素是否为要删除节点
				{
					p->Next = p->Next->Next;		//将中间元素越过使第一与第三元素连接
					DelSuccess = true;
					index--;
				}
				p = p->Next;		//链表移动
			}
		}

		if (DelSuccess)		//判断是否删除成功
		{
			CListDelSuccess();
			Sleep(2 * 1000);
		}
		else {
			CListDelError();
			Sleep(2 * 1000);
		}
	}

	//商品编号更改
	void CListChangeO(int num,int no)
	{
		Commodity* p;
		p = HeadCommodity;
		bool ThLegal = true;
		bool ChSucess = false;

		while (p != NULL)
		{
			if (p->getNo() == no)
			{
				CChangeErrorS();
				Sleep(2 * 1000);
				ThLegal = false;
				break;
			}
			p = p->Next;
		}

		if (ThLegal)
		{
			p = HeadCommodity;
			while (p != NULL)
			{
				if (p->getNo() == num)
				{
					p->setNo(no);
					ChSucess = true;
					break;
				}
				p = p->Next;
			}
			if (ChSucess)
			{
				CChangeSuccess();
				Sleep(2 * 1000);
			}
			else
			{
				CChangeErrorN();
				Sleep(2 * 1000);
			}
		}
	}

	//商品名称更改
	void CListChangeN(int num, string name)
	{
		Commodity* p;
		p = HeadCommodity;
		bool ThLegal = true;
		bool ChSucess = false;

		while (p != NULL)
		{
			if (p->getName() == name)
			{
				CChangeErrorS();
				Sleep(2 * 1000);
				ThLegal = false;
				break;
			}
			p = p->Next;
		}

		if (ThLegal)
		{
			p = HeadCommodity;
			while (p != NULL)
			{
				if (p->getNo() == num)
				{
					p->setName(name);
					ChSucess = true;
					break;
				}
				p = p->Next;
			}
			if (ChSucess)
			{
				CChangeSuccess();
				Sleep(2 * 1000);
			}
			else
			{
				CChangeErrorN();
				Sleep(2 * 1000);
			}
		}
	}

	//商品价格更改
	void CListChangeP(int num, double price)
	{
		Commodity* p;
		p = HeadCommodity;
		bool ThLegal = true;
		bool ChSucess = false;

		while (p != NULL)
		{
			if (p->getPrice() == price)
			{
				CChangeErrorS();
				Sleep(2 * 1000);
				ThLegal = false;
				break;
			}
			p = p->Next;
		}

		if (ThLegal)
		{
			p = HeadCommodity;
			while (p != NULL)
			{
				if (p->getNo() == num)
				{
					p->setPrice(price);
					ChSucess = true;
					break;
				}
				p = p->Next;
			}
			if (ChSucess)
			{
				CChangeSuccess();
				Sleep(2 * 1000);
			}
			else
			{
				CChangeErrorN();
				Sleep(2 * 1000);
			}
		}
	}

	//商品折扣更改
	void CListChangeD(int num, double discount)
	{
		Commodity* p;
		p = HeadCommodity;
		bool ThLegal = true;
		bool ChSucess = false;

		while (p != NULL)
		{
			if (p->getDiscount() == discount)
			{
				CChangeErrorS();
				Sleep(2 * 1000);
				ThLegal = false;
				break;
			}
			p = p->Next;
		}

		if (ThLegal)
		{
			p = HeadCommodity;
			while (p != NULL)
			{
				if (p->getNo() == num)
				{
					p->setDiscount(discount);
					ChSucess = true;
					break;
				}
				p = p->Next;
			}
			if (ChSucess)
			{
				CChangeSuccess();
				Sleep(2 * 1000);
			}
			else
			{
				CChangeErrorN();
				Sleep(2 * 1000);
			}
		}
	}

	//根据编号查找
	void CListSeek(int num) 
	{
		Commodity* p;
		p = HeadCommodity;
		bool SeekSuccess = false;

		while (p != NULL)
		{
			if (p->getNo() == num) 
			{
				SeekSuccess = true;
				break;
			}
			p = p->Next;		//链表移动
		}
		if (SeekSuccess)
		{
			CSeekSuccess();
			cout << "编号" << p->getNo() << " 名称" << p->getName() << " 价格" << p->getPrice() << " 折扣" << p->getDiscount() << endl;
			system("pause");
		}
		else
		{
			CSeekError();
			Sleep(2 * 1000);
		}
	}

	//在删除中使用的查找功能
	bool DCListSeek(int num)
	{
		Commodity* p;
		p = HeadCommodity;
		bool SeekSuccess = false;

		while (p != NULL)
		{
			if (p->getNo() == num)
			{
				SeekSuccess = true;
				break;
			}
			p = p->Next;		//链表移动
		}
		if (SeekSuccess)
		{
			cout << "编号" << p->getNo() << " 名称" << p->getName() << " 价格" << p->getPrice() << " 折扣" << p->getDiscount() << endl;
			return true;
		}
		else
		{
			CSeekError();
			Sleep(2 * 1000);
			return false;
		}
	}

	//根据名称查找
	void CListSeek(string name)
	{
		Commodity* p;
		p = HeadCommodity;
		bool SeekSuccess = false;

		while (p != NULL)
		{
			if (p->getName() == name)
			{
				SeekSuccess = true;
				break;
			}
			p = p->Next;		//链表移动
		}

		if (SeekSuccess)
		{
			CSeekSuccess();
			cout << "编号" << p->getNo() << " 名称" << p->getName() << " 价格" << p->getPrice() << " 折扣" << p->getDiscount() << endl;
			system("pause");
		}
		else
		{
			CSeekError();
			Sleep(2 * 1000);
		}
	}

	void CListShow() 
	{
		Commodity* p;			//防止链表头变化，创建p历遍
		p = HeadCommodity;

		while (p != NULL)
		{
			cout << "编号" << p->getNo() << " 名称" << p->getName() << " 价格" << p->getPrice() << " 折扣" << p->getDiscount() << endl;
			p = p->Next;		//链表移动
		}
	}

	//排序后展示
	void SCListShow()
	{
		Commodity* p;			//防止链表头变化，创建p历遍
		p = HeadCommodity;

		while (p != NULL)
		{
			cout << "编号" << p->getNo() << " 名称" << p->getName() << " 价格" << p->getPrice() << " 折扣" << p->getDiscount() << " 折扣后价格" << (p->getPrice()*p->getDiscount()) <<endl;
			p = p->Next;		//链表移动
		}
	}

private:
	Commodity* HeadCommodity  = NULL;	//链表头
	Commodity* TailCommodity = NULL;	//链表尾
};
