#pragma once
#include "userData.h"
#include <fstream>
#include <time.h>
#include "userData.h"
#include "interface.h"
#include "commodityData.h"

//查找数据库中是否有该用户
User* FindUser(UserList userlist,int account)
{
	User* p;
	p = userlist.getHeadUser();

	while (p != NULL)
	{
		if (p->getAccount() == account)
		{
			return p;
		}
		p = p->Next;		//链表移动
	}
}

//以时间码作为编号
int CreatNo()
{
	return time(NULL);
}

//用户的读取写入
void UFileWrite(UserList userlist)
{
	ofstream ofile;
	ofile.open("UserData.txt",ios::trunc);

	User* p;
	p = userlist.getHeadUser();
	if (!(userlist.index == 0))
	{
		while (p != NULL)
		{
			ofile << p->getNo() << " " << p->getName() << " " << p->getAccount() << " " << p->getPassWord() << " " << p->getVip() << endl;
			p = p->Next;
		}
	}
	ofile.close();
}
void UFileRead(UserList* userlist)
{
	ifstream ifile;
	ifile.open("UserData.txt");

	int userNo;
	int userAccount;
	string userName;
	string userPassWord;
	bool userVip;

	if (!(ifile.peek() == EOF))
	{
		ifile.seekg(0,ios::beg);
		while (!ifile.eof())
		{
			ifile >> userNo >> userName >> userAccount >> userPassWord >> userVip;
			User* user = new User(userNo, userName, userAccount, userPassWord, userVip);
			userlist->RListAdd(user);
		}
	}

	ifile.close();
}

//商品的读取写入
void CFileWrite(CommodityList commoditylist)
{
	ofstream ofile;
	ofile.open("CommodityListData.txt", ios::trunc);

	Commodity* p;
	p = commoditylist.getHeadCommdity();
	if (!(commoditylist.index == 0))
	{
		while (p != NULL)
		{
			ofile << p->getNo() << " " << p->getName() << " " << p->getPrice() << " " << p->getDiscount() << endl;
			p = p->Next;
		}
	}
	ofile.close();
}
void CFileRead(CommodityList* commoditylist)
{
	ifstream ifile;
	ifile.open("CommodityListData.txt");

	int commodityNo;
	string commodityName;
	double commodityPrice;
	double commodityDiscount;

	if (!(ifile.peek() == EOF))
	{
		while (!ifile.eof())
		{
			ifile >> commodityNo >> commodityName >> commodityPrice >> commodityDiscount;
			Commodity* commodity = new Commodity(commodityNo, commodityName, commodityPrice, commodityDiscount);
			commoditylist->RListAdd(commodity);
		}
	}
	ifile.close();
}

//商品折扣后排序
void SortCommodity(CommodityList* commoditylist)
{
	Commodity* p;
	p = commoditylist->getHeadCommdity();

	Commodity* c1;
	Commodity* c2;

	int No;			
	string Name;
	double Price;
	double Discount;

	//冒泡算法排序
	for (int i = 0; i <commoditylist->index - 1; i++)					
	{
		p = commoditylist->getHeadCommdity();				//指针回归
		for (int j = 0; j <commoditylist->index - i - 1; j++)
		{
			c1 = p;
			c2 = p->Next;

			if ((c1->getPrice()*c1->getDiscount()) > (c2->getPrice()*c2->getDiscount()))
			{
				//数据交换
				No = c1->getNo();
				Name = c1->getName();
				Price = c1->getPrice();
				Discount = c1->getDiscount();

				c1->setNo(c2->getNo());
				c1->setName(c2->getName());
				c1->setPrice(c2->getPrice());
				c1->setDiscount(c2->getDiscount());

				c2->setNo(No);
				c2->setName(Name);
				c2->setPrice(Price);
				c2->setDiscount(Discount);
			}
			p = p->Next;				//指针偏移
		}
	}
	commoditylist->SCListShow();
}