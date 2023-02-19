#include <iostream>
#include <windows.h>
#include "commodityData.h"
#include "userData.h"
#include "interface.h"
#include "tool.h"

int main()
{
    int Time=0;                         //记录密码输错次数
    int Choice= 0;                       //用户选项

    int Account=0;                      //用户信息输入
    string PassWord;
    string UserName;
    int UserNo;

    string SuperWord = "admin";         //管理员口令和输入
    string EnterSuperWord;

    int CommodityNo;                    //商品信息输入
    string CommodityName;
    double CommodityPrice;
    double CommodityDiscount;

    bool OrderSuc = true;               //判断是否循环
    bool Continue = true;

    int no;                             //更改信息输入
    int changeNo;
    string changeName;
    double changePrice;
    double changeDiscount;
    int changeAccount;
    string changePassWord;

    int seekNo;                         //查询信息输入
    string seekName;

    CommodityList commoditylist;        //用户及商品库
    UserList userlist;

    UFileRead(&userlist);               //读取用户库
    CFileRead(&commoditylist);          //读取商品库

    //登录界面
    while (OrderSuc)
    {
        if (Time >=3)
        {
            CheckTimeUp();
            exit(1);
        }
        Basic();
        cin >> Choice;
        switch (Choice)
        {
        case 1:                     //用户登录
                if (userlist.index == 0)
                {
                    UListNotingError();
                    Sleep(2 * 1000);
                }
                else
                {
                    Login();
                    cin >> Account >> PassWord;
                    OrderSuc = userlist.CheckAccount(Account, PassWord);
                    Time++;
                }
                break;
            
        case 2:                     //用户注册
            {
                Sign();
                cin >> UserName >> Account >> PassWord;
                User* user = new User(CreatNo(), UserName, Account, PassWord, false);            //由于使用链表需要每次创建对象使用不同的地址
                userlist.UListAdd(user);
                UFileWrite(userlist);
                break;
            }
        case 3:                     //退出系统
            ExitSystem();
            exit(0);
        default:                    //防止用户乱输入
            ChoiceError();
            Sleep(2 * 1000);
            break;
        }
    }
   
    User* LoginUser = FindUser(userlist,Account);       //在用户数据库中找到登录用户

    //商品或用户界面
    while (!OrderSuc)
    {
        OrderSuc = true;
        //界面选择
        while (OrderSuc)
        {
            FuctionChoice();
            cin >> Choice;

            switch (Choice)
            {
            case 1:                     //选择商品界面
                OrderSuc = false;
                break;
            case 2:                     //选择用户界面
                if (LoginUser->getVip())    //验证是否有权限
                {
                    OrderSuc = false;
                }
                else
                {
                    UserAdminError();
                    Sleep(2 * 1000);
                }
                break;
            case 3:                     //权限提升界面
                AdminUp();
                cin >> EnterSuperWord;
                if (EnterSuperWord == SuperWord)
                {
                    LoginUser->setVip(true);
                    AdminUpSuccess();
                    Sleep(2 * 1000);
                }
                else
                {
                    AdminUpError();
                    Sleep(2 * 1000);
                }
                break;
            default:                    //防止用户乱选
                ChoiceError();
                Sleep(2 * 1000);
                break;
            }

        }

        OrderSuc = true;        //重新循环
        //功能选择
        switch (Choice)
        {
        case 1:             //商品管理界面
            while (OrderSuc)
            {
                LoginSuccess();
                cin >> Choice;
                switch (Choice)
                {
                case 1:         //商品添加
                {
                    if (!LoginUser->getVip())   //判斷是否有权限
                    {
                        UserAdminError();
                        Sleep(2 * 1000);
                        break;
                    }
                    else
                    {
                        Continue = true;
                        while (Continue)
                        {
                            CAdd();
                            cin >> CommodityName >> CommodityPrice >> CommodityDiscount;
                            Commodity* commodity = new Commodity(CreatNo(), CommodityName, CommodityPrice, CommodityDiscount);          //使用链表应创建不同的对象防止地址相同
                            commoditylist.CListAdd(commodity);

                            Repeat();
                            cin >> Choice;
                            switch (Choice)     //判断是否继续
                            {
                            case 2:
                                Continue = false;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                }
                case  2:        //商品删除
                    if (!LoginUser->getVip())
                    {
                        UserAdminError();
                        Sleep(2 * 1000);
                        break;
                    }
                    if (commoditylist.index == 0)   //判断库中是否有数据
                    {
                        ShowError();
                        Sleep(2 * 1000);
                    }
                    else
                    {
                        Continue = true;
                        while (Continue)
                        {
                            CDel();
                            commoditylist.CListShow();
                            cin >> CommodityNo;
                            if (commoditylist.DCListSeek(CommodityNo))      //判断是否存在
                            {
                                DelCheck();
                                cin >> Choice;
                                switch (Choice)
                                {
                                case 1:
                                    commoditylist.CListDel(CommodityNo);
                                    break;
                                case 2:
                                    break;
                                default:
                                    ChoiceError();
                                    Sleep(2 * 1000);
                                    break;
                                }
                            }

                            Repeat();
                            cin >> Choice;
                            switch (Choice)     //判断是否继续
                            {
                            case 1:
                                break;
                            case 2:
                                Continue = false;
                                break;
                            default:
                                ChoiceError();
                                Sleep(2 * 1000);
                                break;
                            }
                        }
                    }
                    break;

                case 3:         //商品修改

                    if (!LoginUser->getVip())       //判断是否有权限
                    {
                        UserAdminError();
                        Sleep(2 * 1000);
                        break;
                    }

                    if (commoditylist.index == 0)   //判断库中是否有数据
                    {
                        ShowError();
                        Sleep(2 * 1000);
                    }
                    else
                    {
                        Continue = true;
                        while (Continue)
                        {
                            CChange();
                            int ChangeChoice;
                            cin >> ChangeChoice;
                            switch (ChangeChoice)
                            {
                            case 1:     //修改编号
                                CChangeEnter();
                                commoditylist.CListShow();
                                cin >> no >> changeNo;
                                commoditylist.CListChangeO(no, changeNo);
                                break;
                            case 2:     //修改名称
                                CChangeEnter();
                                commoditylist.CListShow();
                                cin >> no >> changeName;
                                commoditylist.CListChangeN(no, changeName);
                                break;
                            case 3:     //修改价格
                                CChangeEnter();
                                commoditylist.CListShow();
                                cin >> no >> changePrice;
                                commoditylist.CListChangeP(no, changePrice);
                                break;
                            case 4:     //修改折扣
                                CChangeEnter();
                                commoditylist.CListShow();
                                cin >> no >> changeDiscount;
                                commoditylist.CListChangeD(no, changeDiscount);
                                break;
                            default:    //防止用户乱输入
                                ChoiceError();
                                Sleep(2 * 1000);
                                break;
                            }

                            Repeat();
                            cin >> Choice;
                            switch (Choice)     //判断是否继续
                            {
                            case 1:
                                break;
                            case 2:
                                Continue = false;
                                break;
                            default:
                                ChoiceError();
                                Sleep(2 * 1000);
                                break;
                            }
                        }
                    }
                    break;
                case 4:         //商品列表显示
                    if (!(commoditylist.index == 0))        //判断是否有数据
                    {
                        SortCommodity(&commoditylist);
                        system("pause");
                    }
                    else
                    {
                        ShowError();
                        Sleep(2 * 1000);
                    }
                    break;
                case 5:         //商品编号查询
                    if (commoditylist.index == 0)   //判断库中是否有数据
                    {
                        ShowError();
                        Sleep(2 * 1000);
                        break;
                    }
                    Continue = true;
                    while (Continue)
                    {
                        CSeekO();
                        cin >> seekNo;
                        commoditylist.CListSeek(seekNo);

                        Repeat();
                        cin >> Choice;
                        switch (Choice)     //判断是否继续
                        {
                        case 2:
                            Continue = false;
                            break;
                        }
                    }
                    break;
                case 6:         //商品名称查询
                    if (commoditylist.index == 0)   //判断库中是否有数据
                    {
                        ShowError();
                        Sleep(2 * 1000);
                        break;
                    }

                    Continue = true;
                    while (Continue)
                    {
                        CSeekN();
                        cin >> seekName;
                        commoditylist.CListSeek(seekName);

                        Repeat();
                        cin >> Choice;
                        switch (Choice)     //判断是否继续
                        {
                        case 2:
                            Continue = false;
                            break;
                        }
                    }
                    break;
                case 7:       //返回上一级
                    OrderSuc = false;
                    break;
                case 8:       //退出程序
                    ExitSystem();
                    exit(0);
                default:      //防止用户乱输入
                    ChoiceError();
                    Sleep(2 * 1000);
                    break;
                }
                CFileWrite(commoditylist);          //将商品导出到文件
            }
            break;
        case 2:             //用户管理界面
            while (OrderSuc)
            {
                UserAdmin();
                cin >> Choice;
                switch (Choice)
                {
                case 1:         //用户添加
                {
                    Continue = true;
                    while (Continue)
                    {
                        UAdd();
                        cin >> UserName >> Account >> PassWord;
                        User* user = new User(CreatNo(), UserName, Account, PassWord, false);           //使用链表应创建不同的对象防止地址相同
                        userlist.UListAdd(user);

                        Repeat();
                        cin >> Choice;
                        switch (Choice)     //判断是否继续
                        {
                        case 2:
                            Continue = false;
                            break;
                        }
                    }
                    break;
                }
                case  2:        //用户删除
                    Continue = true;
                    while (Continue)
                    {
                        UDel();
                        userlist.UListShow();
                        cin >> UserNo;
                        if (userlist.DUListSeek(UserNo))
                        {
                            DelCheck();
                            cin >> Choice;
                            switch (Choice)
                            {
                            case 1:
                                userlist.UListDel(UserNo);
                                break;
                            case 2:
                                break;
                            default:
                                ChoiceError();
                                Sleep(2 * 1000);
                                break;
                            }
                        }

                        Repeat();
                        cin >> Choice;
                        switch (Choice)     //判断是否继续
                        {
                        case 1:
                            break;
                        case 2:
                            Continue = false;
                            break;
                        default:
                            ChoiceError();
                            Sleep(2 * 1000);
                            break;
                        }
                    }
                    break;
                case 3:         //用户修改
                    Continue = true;
                    while (Continue)
                    {
                        UChange();
                        int ChangeChoice;
                        cin >> ChangeChoice;
                        switch (ChangeChoice)
                        {
                        case 1:     //修改编号
                            UChangeEnter();
                            userlist.UListShow();
                            cin >> no >> changeNo;
                            userlist.UListChangeO(no, changeNo);
                            break;
                        case 2:     //修改姓名
                            UChangeEnter();
                            userlist.UListShow();
                            cin >> no >> changeName;
                            userlist.UListChangeN(no, changeName);
                            break;
                        case 3:     //修改账户
                            UChangeEnter();
                            userlist.UListShow();
                            cin >> no >> changeAccount;
                            userlist.UListChangeA(no, changeAccount);
                            break;
                        case 4:     //修改密码
                            UChangeEnter();
                            userlist.UListShow();
                            cin >> no >> changePassWord;
                            userlist.UListChangeP(no, changePassWord);
                            break;
                        default:    //防止用户乱输入
                            ChoiceError();
                            Sleep(2 * 1000);
                            break;
                        }

                        Repeat();
                        cin >> Choice;
                        switch (Choice)     //判断是否继续
                        {
                        case 2:
                            Continue = false;
                            break;
                        }
                    }
                    break;
                case 4:         //用户列表显示
                    if (!(userlist.index == 0))
                    {
                        userlist.UListShow();
                        system("pause");
                    }
                    else
                    {
                        ShowError();
                        Sleep(2 * 1000);
                    }
                    break;
                case 5:         //用户编号查询
                    Continue = true;
                    while (Continue)
                    {
                        USeekO();
                        cin >> seekNo;
                        userlist.UListSeek(seekNo);

                        Repeat();
                        cin >> Choice;
                        switch (Choice)     //判断是否继续
                        {
                        case 2:
                            Continue = false;
                            break;
                        }
                    }
                    break;
                case 6:         //用户姓名查询
                    Continue = true;
                    while (Continue)
                    {
                        USeekN();
                        cin >> seekName;
                        userlist.UListSeek(seekName);

                        Repeat();
                        cin >> Choice;
                        switch (Choice)     //判断是否继续
                        {
                        case 2:
                            Continue = false;
                            break;
                        }
                    }
                    break;
                case 7:       //返回上一级
                    OrderSuc = false;
                    break;
                case 8:       //退出程序
                    ExitSystem();
                    exit(0);
                default:      //防止用户乱输入
                    ChoiceError();
                    Sleep(2 * 1000);
                    break;
                }
                UFileWrite(userlist);       //将用户信息导出文件
            }
            break;
        default:            //防止用户乱输入
            ChoiceError();
            Sleep(2 * 1000);
            break;
        }
    }


    return 0;
}
